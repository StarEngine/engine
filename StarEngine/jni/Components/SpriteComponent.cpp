#include "SpriteComponent.h"
#include "../Logger.h"
#include "../Helpers/Filepath.h"
#include "../AssetManaging/TextureManager.h"
#include "../GraphicsManager.h"
#include "../Components/TransformComponent.h"

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
		uint32 height = GraphicsManager::GetInstance()->GetWindowHeigth();

		mat4x4 projection = mat4x4(
				 (1.0f/width)/0.5f	, 0				, 0, -1
				,0			, (1.0f/height)/0.5f	, 0, -1
				,0			, 0				, 1, 0
				,0			, 0				, 0, 1
				);

		glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"Projection"),1,GL_FALSE,glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"Translation"),1,GL_FALSE,glm::value_ptr(GetTransform()->GetWorldMatrix()));

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		m_Shader.Unbind();
	}
}
