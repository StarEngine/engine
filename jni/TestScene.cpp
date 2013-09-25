#include "TestScene.h"
#include "AssetManaging/Texture2D.h"

#ifdef _WIN32
#include "libs/OpenGL/GLEW/include/GL/glew.h"
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#define INPUT_MANAGER (InputManager::GetSingleton())
#define LOGGER (Logger::GetSingleton())

namespace star
{
	TestScene::TestScene(const tstring & Name):
		BaseScene(Name),
		m_TotalFrames(0),
		m_FPS(0),
		m_PassedMiliseconds(0)
	{
		
	}

	status TestScene::Initialize( const Context& contex )
	{
		m_Initialized=true;

		star::TextureManager::GetInstance()->LoadTexture(_T("assets/TestDaPng.png"),_T("TestPNG"));
		star::TextureManager::GetInstance()->LoadTexture(_T("assets/Awesome.png"),_T("Awesome"));
		return STATUS_OK;
	}

	status TestScene::Update(const Context& context)
	{
		++m_TotalFrames;
		m_PassedMiliseconds += float(context.mTimeManager->GetMicroSeconds());
		if(m_PassedMiliseconds >= 1000000)
		{
			m_FPS = m_TotalFrames;
			m_TotalFrames = 0;
			m_PassedMiliseconds -= 1000000;

			tstringstream str;
			str << "FPS: " << m_FPS;

			LOGGER->Log(LogLevel::Info, str.str());
		}

		return STATUS_OK;
	}

	status TestScene::Draw()
	{
		glEnable(GL_TEXTURE_2D);
#ifndef _WIN32
		glActiveTexture(GL_TEXTURE0);
#endif
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(_T("TestPNG")));

#ifdef _WIN32
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(-8.0f, -8.0f);
		glTexCoord2f(1.0, 0.0); glVertex2f(0.0f, -8.0f);
		glTexCoord2f(1.0, 1.0); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(-8.0f, 0.0f);
		glEnd();
#endif
#ifndef _WIN32
		glActiveTexture(GL_TEXTURE0);
#endif
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(_T("Awesome")));

#ifdef _WIN32
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0, 0.0); glVertex2f(8.0f, 0.0f);
		glTexCoord2f(1.0, 1.0); glVertex2f(8.0f, 8.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0f, 8.0f);
		glEnd();
#endif

		glDisable(GL_TEXTURE_2D);
		


		return STATUS_OK;
	}



}
