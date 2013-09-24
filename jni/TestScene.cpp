#include "TestScene.h"
#include "AssetManaging/Texture2D.h"
#include "libs/OpenGL/GLEW/include/GL/glew.h"

namespace star
{
	TestScene::TestScene(const tstring & Name):
		BaseScene(Name),
		m_TotalFrames(0),
		m_FPS(0),
		m_PassedMiliseconds(0),
		m_pTestObject(nullptr),
		m_pRectComp(nullptr)
	{
		
	}

	status TestScene::Initialize( const Context& contex )
	{
		m_Initialized=true;

		star::TextureManager::GetInstance()->LoadTexture(_T("assets/TestDaPng.png"),_T("TestPNG"));
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

			Logger::GetSingleton()->Log(LogLevel::Info, str.str());
		}
		star::TextureManager::GetInstance()->GetTextureID(_T("TestPNG"));

		return STATUS_OK;
	}

	status TestScene::Draw()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red
		glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
		glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

		glFrustum(-1,1,-1,1,0.1f,500.0f);

		glTranslatef(0,0,-1.0f);
		glBegin(GL_QUADS);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner
		glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner
		glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner
		glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner

		glEnd();
		glFlush();

		return STATUS_OK;
	}



}
