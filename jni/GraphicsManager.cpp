#include "GraphicsManager.h"

namespace star
{
	GraphicsManager* GraphicsManager::mGraphicsManager =nullptr;

	GraphicsManager::GraphicsManager():mScreenHeight(752),mScreenWidth(1280)
	{
		
	}

	GraphicsManager* GraphicsManager::GetInstance()
	{
		if(mGraphicsManager ==nullptr)
		{
			mGraphicsManager = new GraphicsManager();
		}			
		return mGraphicsManager;	
	}

	void GraphicsManager::Initialize()
	{
		
		// Initializes base GL state.
		glEnable(GL_TEXTURE_2D);
		// In a simple 2D game, we have control over the third
		// dimension. So we do not really need a Z-buffer.
		glDisable(GL_DEPTH_TEST);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void GraphicsManager::StartDraw()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red
		glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
		glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

		float ratio = (float)mScreenWidth/(float)mScreenHeight;

		glFrustum(-1*ratio,1*ratio,-1,1,0.1f,500.0f);

		glTranslatef(0,0,-1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GraphicsManager::StopDraw()
	{
		glDisable(GL_BLEND);
		glFlush();
	}


}
