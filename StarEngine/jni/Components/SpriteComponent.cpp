#include "SpriteComponent.h"
#include "../Logger.h"
#include "../Helpers/Filepath.h"
#include "../AssetManaging/TextureManager.h"
#include "../GraphicsManager.h"
#include "../Components/TransformComponent.h"
#include "../Objects/FreeCamera.h"
#include "../Components/CameraComponent.h"
#include "../SceneGraph/Object.h"

namespace star
{
	SpriteComponent::SpriteComponent(const tstring& filePath,const tstring& spriteName)
		: BaseComponent()
		, m_Shader()
		, m_FilePath(filePath)
		, m_SpriteName(spriteName)
	{
	}

	void SpriteComponent::InitializeComponent()
	{
#ifdef _WIN32
		Filepath texshaderVertex(_T("WinShaders/"), _T("Texture_Shader.vert"));
		Filepath texshaderFrag(_T("WinShaders/"), _T("Texture_Shader.frag"));
#else
		Filepath texshaderVertex(_T("AndroidShaders/"), _T("BaseTexShader.vert"));
		Filepath texshaderFrag(_T("AndroidShaders/"), _T("BaseTexShader.frag"));

#endif
		if(!m_Shader.Init(texshaderVertex.GetFullPath(),texshaderFrag.GetFullPath()))
		{
			Logger::GetInstance()->Log(star::LogLevel::Info, _T("Making Shader Failed"));
		}

		TextureManager::GetInstance()->LoadTexture(m_FilePath,m_SpriteName);
		m_Width = TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).x;
		m_Heigth =  TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).y;

		CreateSquare();
	}

	SpriteComponent::~SpriteComponent()
	{
		TextureManager::GetInstance()->DeleteTexture(m_SpriteName);
	}

	void SpriteComponent::CreateSquare()
	{
		m_Vertices[0] = (GLfloat)m_Width;
		m_Vertices[1] = (GLfloat)m_Heigth;
		m_Vertices[2] = 0;
		m_Vertices[3] = (GLfloat)m_Width;
		m_Vertices[4] = 0;
		m_Vertices[5] = 0;
		m_Vertices[6] = 0;
		m_Vertices[7] = (GLfloat)m_Heigth;
		m_Vertices[8] = 0;
		m_Vertices[9] = 0;
		m_Vertices[10] = 0;
		m_Vertices[11] = 0;
		 
		m_UvCoords[0] = 1.0f;
		m_UvCoords[1] = 1.0f;
		m_UvCoords[2] = 1.0f;
		m_UvCoords[3] = 0.0f;
		m_UvCoords[4] = 0.0f;
		m_UvCoords[5] = 1.0f;
		m_UvCoords[6] = 0.0f;
		m_UvCoords[7] = 0.0f;
	}

	void SpriteComponent::Draw()
	{
		m_Shader.Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(m_SpriteName));
		GLint s_textureId = glGetUniformLocation(m_Shader.GetId(), "textureSampler");
		glUniform1i(s_textureId, 0);

		//Set attributes and buffers
		glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT,0,0, m_Vertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, m_UvCoords);
		glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		uint32 width = GraphicsManager::GetInstance()->GetWindowWidth();
		uint32 height = GraphicsManager::GetInstance()->GetWindowHeight();
		auto projectionObject = m_pParentObject->GetScene()->GetActiveCamera();
		mat4x4 projection = projectionObject->GetComponent<CameraComponent>()->GetProjection();

		glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"Projection"),1,GL_FALSE,glm::value_ptr(projection));
		mat4x4 world = GetTransform()->GetWorldMatrix();
		mat4x4 worldInverse = InverseMatrix(world);
		glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"Translation"),1,GL_FALSE,glm::value_ptr(worldInverse));

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		m_Shader.Unbind();
	}

	mat4x4 SpriteComponent::InverseMatrix(const mat4x4& matrix)
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
}
