#include "GraphicsManager.h"
#include "Logger.h"

namespace star
{
	GraphicsManager* GraphicsManager::mGraphicsManager = nullptr;

	GraphicsManager::GraphicsManager() :
			mScreenHeight(0),
			mScreenWidth(0)
	{
	}

	GraphicsManager* GraphicsManager::GetInstance()
	{
		if(mGraphicsManager == nullptr)
		{
			mGraphicsManager = new GraphicsManager();
		}			
		return mGraphicsManager;	
	}

#ifdef _WIN32
	void GraphicsManager::Initialize(int32 screenWidth, int32 screenHeight)
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager: Initialized"));
		
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;

#ifdef _WIN32
		glewInit();
#endif
		//Initializes base GL state.
		// In a simple 2D game, we have control over the third
		// dimension. So we do not really need a Z-buffer.
		// [COMMENT] Depends. It's one of many techniques
		// for ordering your 2D elements in different/the same layer(s).
		glDisable(GL_DEPTH_TEST);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
#else
	void GraphicsManager::Initialize(const android_app* pApplication)
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Initialized"));
		EGLint lFormat, lNumConfigs, lErrorResult;
		EGLConfig lConfig;
		// Defines display requirements. 16bits mode here.
		const EGLint lAttributes[] = {
		            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		            EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6, EGL_RED_SIZE, 5,
		            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		            EGL_NONE
		};
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Getting attached display"));
		mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (mDisplay == EGL_NO_DISPLAY)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : No display found"));
			return;
		}
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Initialize Display"));
		if (!eglInitialize(mDisplay, NULL, NULL))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Could not initialize display"));
			return;
		}
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Choosing display config"));
		if(!eglChooseConfig(mDisplay, lAttributes, &lConfig, 1,&lNumConfigs) || (lNumConfigs <= 0))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : No display config"));
			return;
		}
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Getting config attributes"));
		if (!eglGetConfigAttrib(mDisplay, lConfig,EGL_NATIVE_VISUAL_ID, &lFormat))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : No config attributes"));
			return;
		}
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Setting window geometry"));
		ANativeWindow_setBuffersGeometry(pApplication->window, 0, 0,lFormat);

		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Creating window surface"));
		mSurface = eglCreateWindowSurface(mDisplay, lConfig, pApplication->window, NULL );
		if (mSurface == EGL_NO_SURFACE)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Could not create surface"));
			return;
		}

		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : creating context"));
		EGLint contextAttrs[] = {
		     EGL_CONTEXT_CLIENT_VERSION, 2,
		     EGL_NONE
		};
		mContext = eglCreateContext(mDisplay, lConfig, EGL_NO_CONTEXT, contextAttrs);
		if (mContext == EGL_NO_CONTEXT)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Could not create context"));
			return;
		}

		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Making display, surface & conext Current"));
		if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)
		 || !eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mScreenWidth)
		 || !eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mScreenHeight)
		 || (mScreenWidth <= 0) || (mScreenHeight <= 0))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Could not activate display"));
			return;
		}

		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Setting viewport"));
		glViewport(0,0,mScreenWidth,mScreenHeight);

	}

	void GraphicsManager::Destroy()
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Destroying Context and Display"));
        // Destroys OpenGL context.
        if (mDisplay != EGL_NO_DISPLAY)
        {
            eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,EGL_NO_CONTEXT);
            if (mContext != EGL_NO_CONTEXT)
            {
                eglDestroyContext(mDisplay, mContext);
                mContext = EGL_NO_CONTEXT;
            }
            if (mSurface != EGL_NO_SURFACE)
            {
                eglDestroySurface(mDisplay, mSurface);
                mSurface = EGL_NO_SURFACE;
            }
            eglTerminate(mDisplay);
            mDisplay = EGL_NO_DISPLAY;
        }
	}
#endif


	void GraphicsManager::StartDraw()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)

#ifdef _WIN32
		glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
		float ratio = (float)mScreenWidth/(float)mScreenHeight;
		glFrustum(-1*ratio,1*ratio,-1,1,0.1f,500.0f);
		glTranslatef(0,0,-1.0f);

#endif
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GraphicsManager::StopDraw()
	{

		 glDisable(GL_BLEND);

#ifndef _WIN32
		 if (eglSwapBuffers(mDisplay, mSurface) != EGL_TRUE)
		 {
			 return;
		 }
#endif
		 glFlush();
	}
}
