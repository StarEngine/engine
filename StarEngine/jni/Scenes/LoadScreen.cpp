#include "LoadScreen.h"
#include "../Logger.h"
#include "../Helpers/Filepath.h"
#include "../Assets/TextureManager.h"
#include "../Graphics/GraphicsManager.h"
#include "../Components/TransformComponent.h"
#include "../Objects/FreeCamera.h"
#include "../Components/CameraComponent.h"

namespace star
{
	LoadScreen::LoadScreen(const tstring& filePath,const tstring& spriteName)
		:m_Shader()
		, m_FilePath(filePath)
		, m_SpriteName(spriteName)
	{
	}

	void LoadScreen::Initialize()
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

		TextureManager::GetInstance()->LoadTexture(m_FilePath.GetFullPath(),m_SpriteName);
		m_Width = TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).x;
		m_Heigth =  TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).y;

		CreateSquare();
	}

	LoadScreen::~LoadScreen()
	{
		TextureManager::GetInstance()->DeleteTexture(m_SpriteName);
	}

	void LoadScreen::CreateSquare()
	{
		m_Vertices[0] = 0.5;
		m_Vertices[1] = 0.5;
		m_Vertices[2] = 0.5;
		m_Vertices[3] = -0.5f;
		m_Vertices[4] = -0.5f;
		m_Vertices[5] = 0.5f;
		m_Vertices[6] = -0.5f;
		m_Vertices[7] = -0.5f;

		 
		m_UvCoords[0] = 1.0f;
		m_UvCoords[1] = 1.0f;
		m_UvCoords[2] = 1.0f;
		m_UvCoords[3] = 0.0f;
		m_UvCoords[4] = 0.0f;
		m_UvCoords[5] = 1.0f;
		m_UvCoords[6] = 0.0f;
		m_UvCoords[7] = 0.0f;
	}

	void LoadScreen::Draw()
	{
		m_Shader.Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(m_SpriteName));
		GLint s_textureId = glGetUniformLocation(m_Shader.GetId(), "textureSampler");
		glUniform1i(s_textureId, 0);

		//Set attributes and buffers
		glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT,0,0, m_Vertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, m_UvCoords);
		glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		m_Shader.Unbind();
	}
}
