#include "CameraComponent.h"
#include "../GraphicsManager.h"
#include "../SceneGraph/Object.h"
#include "../Input/InputManager.h"
#include "../Context.h"
#include "../Logger.h"

//General info
//
//Using custom matrix4x4 calculation functions
//since OpenGl uses matrices in a different way

namespace star
{
	CameraComponent::CameraComponent():
		BaseComponent(),
		m_Projection(),
		m_View(),
		m_ViewInverse(),
		m_FarPlane(100.0f),
		m_NearPlane(0.1f),
		m_FOV(static_cast<float>(PI/4.0f)),
		m_Size(0.0f),
		m_bIsActive(false),
		m_bPerspectiveProjection(false),
		m_Zoom(1.0f),
		m_AspectRatio(1.0f)
	{
	}

	CameraComponent::~CameraComponent(void)
	{
	}

	void CameraComponent::InitializeComponent()
	{
		m_AspectRatio = GraphicsManager::GetInstance()->GetWindowAspectRatio();
	
		if(m_bPerspectiveProjection)
		{
			m_Projection = MatrixPerspectiveFOV(m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
		}
		else
		{
			//calc ortho matrix
			if(m_Size <= 0)
			{
				m_Size = static_cast<float>(GraphicsManager::GetInstance()->GetWindowHeight());
			}

			m_Projection = MatrixOrtho(m_Size * m_AspectRatio * m_Zoom, m_Size * m_Zoom, m_NearPlane, m_FarPlane);
		}
	}

	void CameraComponent::Update(const Context& context)
	{
#ifdef _WIN32
		if(m_Size != GraphicsManager::GetInstance()->GetWindowHeight() || m_Size * m_AspectRatio != GraphicsManager::GetInstance()->GetWindowWidth())
		{
			m_AspectRatio = GraphicsManager::GetInstance()->GetWindowAspectRatio();
			if(m_bPerspectiveProjection)
			{
				m_Projection = MatrixPerspectiveFOV(m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
			}
			else
			{
				m_Size = static_cast<float>(GraphicsManager::GetInstance()->GetWindowHeight());
				m_Projection = MatrixOrtho(m_Size * m_AspectRatio * m_Zoom, m_Size * m_Zoom, m_NearPlane, m_FarPlane);
			}
		}

		if(InputManager::GetInstance()->IsKeyboardKeyDown('O'))
		{
			m_Zoom += 0.1f * static_cast<float>(context.mTimeManager->GetSeconds());			
			m_Projection = MatrixOrtho(m_Size * m_AspectRatio * m_Zoom, m_Size * m_Zoom, m_NearPlane, m_FarPlane);
		}
		else if(InputManager::GetInstance()->IsKeyboardKeyDown('P'))
		{
			m_Zoom -= 0.1f * static_cast<float>(context.mTimeManager->GetSeconds());
			m_Projection = MatrixOrtho(m_Size * m_AspectRatio * m_Zoom, m_Size * m_Zoom, m_NearPlane, m_FarPlane);
		}
#endif
		vec3 vEyePt = m_pParentObject->GetComponent<TransformComponent>()->GetWorldPosition();
		vec3 vLookat, vUpVec;
		mat4x4 rotTransform;
	
		quat rotation = m_pParentObject->GetComponent<TransformComponent>()->GetWorldRotation();
		rotTransform = glm::toMat4(rotation);

		//Only vec4 * mat4x4  possible
		vec4 vLookTemp = vec4(0,0,1,0) * InverseMatrix(rotTransform);
		vec4 vUpVecTemp = vec4(0,1,0,0) * InverseMatrix(rotTransform);

		//put them into a vec3
		vLookat = vec3(vLookTemp.x, vLookTemp.y, vLookTemp.z);
		vUpVec = vec3(vUpVecTemp.x, vUpVecTemp.y, vUpVecTemp.z);

		//Calculate the viewmatrix and inverse
		m_View = MatrixLookAt(vEyePt, (vEyePt + vLookat), vUpVec);
		m_ViewInverse = InverseMatrix(m_View);
	}
	
	void CameraComponent::SetActive()
	{
		auto scene = GetGameScene();
	
		if(scene==nullptr)
		{
			Logger::GetInstance()->Log( LogLevel::Error,_T("Can't set camera active, add this camera to a scene first!"));
		}
		else
		{
			scene->SetActiveCamera(this);
		}
	}

	mat4x4 CameraComponent::MatrixPerspectiveFOV(float FovY, float ratio, float nearPlane, float farPlane)
	{
		float viewSpaceWidth, viewSpaceHeight;
		
		viewSpaceHeight = glm::cot(FovY/2);
		viewSpaceWidth = viewSpaceHeight * ratio;

		mat4x4 matPerspective 
		(
		viewSpaceWidth, 0, 0, 0,
		0, viewSpaceHeight, 0, 0,
		0, 0, farPlane / (farPlane - nearPlane), 1,
		0, 0, -nearPlane * farPlane / (farPlane - nearPlane), 0
		);

		return matPerspective;
	}

	mat4x4 CameraComponent::MatrixOrtho(float width, float height, float nearPlane, float farPlane)
	{
		//opengl standard is -1 to 1 --> 2 width
		mat4x4 matOrtho
		(
		2/width, 0, 0, 0,
		0, 2/height, 0, 0,
		0, 0, 1/(farPlane - nearPlane), 0,
		0, 0, nearPlane/(nearPlane - farPlane), 1
		);

		return matOrtho;
	}

	mat4x4 CameraComponent::MatrixLookAt(const vec3& eye, const vec3& at, const vec3& up)
	{
		vec3 xAxis, yAxis, zAxis;

		zAxis = glm::normalize(at - eye);
		xAxis = glm::normalize(glm::cross(up, zAxis));
		yAxis = glm::cross(zAxis, xAxis);
		
		mat4x4 matLookAt 
		(
		 xAxis.x, yAxis.x, zAxis.x, 0,
		 xAxis.y, yAxis.y, zAxis.y, 0,
		 xAxis.z, yAxis.z, zAxis.z, 0,
		-glm::dot(xAxis, eye),  -glm::dot(yAxis, eye),  -glm::dot(zAxis, eye),  1
		);

		return matLookAt;
	}

	mat4x4 CameraComponent::InverseMatrix(const mat4x4& matrix)
	{
		float x1, y1, z1, w1,
			  x2, y2, z2, w2,
			  x3, y3, z3, w3,
			  x4, y4, z4, w4;

		x1 = matrix[0][0];
		x2 = matrix[1][0];
		x3 = matrix[2][0];
		x4 = matrix[3][0];

		y1 = matrix[0][1];
		y2 = matrix[1][1];
		y3 = matrix[2][1];
		y4 = matrix[3][1];

		z1 = matrix[0][2];
		z2 = matrix[1][2];
		z3 = matrix[2][2];
		z4 = matrix[3][2];

		w1 = matrix[0][3];
		w2 = matrix[1][3];
		w3 = matrix[2][3];
		w4 = matrix[3][3];

		mat4x4 inverseMatrix
		(
		x1, y1, z1, x4,
		x2, y2, z2, y4,
		x3, y3, z3, z4,
		w1, w2, w3, w4
		);

		return inverseMatrix;
	}

	mat4x4 CameraComponent::GetProjection() const
	{
		return m_Projection * m_ViewInverse;
	}
}
