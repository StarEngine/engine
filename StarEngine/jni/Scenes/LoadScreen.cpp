#include "LoadScreen.h"
#include "../Logger.h"
#include "../Helpers/Filepath.h"
#include "../Graphics/TextureManager.h"
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
		,m_TextureId()
	{
	}

	void LoadScreen::Initialize()
	{
		tstring vShader(_T("Shaders/VertexPosColTexShader.vert")),
				fShader(_T("Shaders/VertexPosColTexShader.frag"));

		if(!m_Shader.Init(vShader, fShader))
		{
			Logger::GetInstance()->Log(star::LogLevel::Info,
				_T("Initialization of the Loadscreen Shader has failed!"), STARENGINE_LOG_TAG);
		}

		TextureManager::GetInstance()->LoadTexture(m_FilePath.GetAssetsPath(),m_SpriteName);
		m_Width = TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).x;
		m_Height =  TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).y;
		m_TextureId = glGetUniformLocation(m_Shader.GetID(), "textureSampler");
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
		/*
		m_Shader.Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(m_SpriteName));
		
		glUniform1i(m_TextureId, 0);

		//Set attributes and buffers
		glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT,0,0, m_Vertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, m_UvCoords);
		glEnableVertexAttribArray(ATTRIB_UV);

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_UV);

		m_Shader.Unbind();*/
	}
}
