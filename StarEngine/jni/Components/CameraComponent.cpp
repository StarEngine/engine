#include "CameraComponent.h"
#include "..\GraphicsManager.h"
#include "..\SceneGraph\Object.h"
#include "..\Context.h"
#include "..\Logger.h"

namespace star
{
	CameraComponent::CameraComponent():
		m_FOV(3.14159265358979323846264338327950288f /4),
		m_NearPlane(0.1f),
		m_FarPlane(5000.0f),
		m_Size(25.0f),
		m_bPerspectiveProjection(true),
		m_bIsActive(false),
		BaseComponent()
	{
	}

	CameraComponent::~CameraComponent(void)
	{
	}

	void CameraComponent::Update(const Context& context)
	{
		float aspectRatio = GraphicsManager::GetInstance()->GetScreenAspectRatio();
	
		if(m_bPerspectiveProjection)
		{
			m_Projection = MatrixPerspectiveFOV(m_FOV, aspectRatio, m_NearPlane, m_FarPlane);
		}
		else
		{
			//calc ortho matrix
			if(m_Size < 0)
			{
				m_Size = static_cast<float>(GraphicsManager::GetInstance()->GetScreenWidth());
			}

			m_Projection = MatrixOrtho(m_Size * aspectRatio, m_Size, m_NearPlane, m_FarPlane);
		}

		vec3 vEyePt = m_pParentObject->GetComponent<TransformComponent>()->GetWorldPosition();
		vec3 vLookat, vUpVec;
		mat4x4 rotTransform;
	
		quat rotation = m_pParentObject->GetComponent<TransformComponent>()->GetWorldRotation();
		rotTransform = glm::toMat4(rotation);

		//Only vec4 * mat4x4  possible
		vec4 vLookTemp = vec4(0,0,1,0) * rotTransform;
		vec4 vUpVecTemp = vec4(0,1,0,0) * rotTransform;

		//put them into a vec3
		vLookat = vec3(vLookTemp.x, vLookTemp.y, vLookTemp.z);
		vUpVec = vec3(vUpVecTemp.x, vUpVecTemp.y, vUpVecTemp.z);

		//Calculate the viewmatrix and inverse
		m_View = MatrixLookAt(vEyePt, (vEyePt + vLookat), vUpVec);
		m_ViewInverse = glm::inverse(m_View);
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
}
