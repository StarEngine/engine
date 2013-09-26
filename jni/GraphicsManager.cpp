#include "GraphicsManager.h"
#include "Logger.h"


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

#ifdef _WIN32
	void GraphicsManager::Initialize()
	{
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Graphics Manager Initialized"));
		//Initializes base GL state.
		glEnable(GL_TEXTURE_2D);
		// In a simple 2D game, we have control over the third
		// dimension. So we do not really need a Z-buffer.
		glDisable(GL_DEPTH_TEST);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	}
#else
	void GraphicsManager::Initialize(const android_app* pApplication)
	{
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Graphics Manager Initialized"));
		EGLint lFormat, lNumConfigs, lErrorResult;
		EGLConfig lConfig;
		// Defines display requirements. 16bits mode here.
		const EGLint lAttributes[] = {
		            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		            EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6, EGL_RED_SIZE, 5,
		            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		            EGL_NONE
		};
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Get display"));
		mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (mDisplay == EGL_NO_DISPLAY)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("No display found"));
						return;
		}
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Initialize Display"));
		if (!eglInitialize(mDisplay, NULL, NULL))
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Could not initialize display"));
			return;
		}
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Choosing config"));
		if(!eglChooseConfig(mDisplay, lAttributes, &lConfig, 1,&lNumConfigs) || (lNumConfigs <= 0))
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("No display config"));
			return;
		}
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("getting config attributes"));
		if (!eglGetConfigAttrib(mDisplay, lConfig,EGL_NATIVE_VISUAL_ID, &lFormat))
		{

		}
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Setting window geometry"));
		ANativeWindow_setBuffersGeometry(pApplication->window, 0, 0,lFormat);

		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("creating window surface"));
		mSurface = eglCreateWindowSurface(mDisplay, lConfig, pApplication->window, NULL );
		if (mSurface == EGL_NO_SURFACE)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Could not create surface"));
			return;
		}

		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("creating context"));
		EGLint contextAttrs[] = {
		     EGL_CONTEXT_CLIENT_VERSION, 2,
		     EGL_NONE
		};
		mContext = eglCreateContext(mDisplay, lConfig, EGL_NO_CONTEXT, contextAttrs);
		if (mContext == EGL_NO_CONTEXT)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Could not create context"));
			return;
		}

		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Making current"));
		if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)
		 || !eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mWidth)
		 || !eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mHeight)
		 || (mWidth <= 0) || (mHeight <= 0))
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Could not activate display"));
			return;
		}

		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Setting viewport"));
		glViewport(0,0,mWidth,mHeight);

		Setup();
	}

	void GraphicsManager::Destroy()
	{
        // Destroys OpenGL context.
        if (mDisplay != EGL_NO_DISPLAY) {
            eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,EGL_NO_CONTEXT);
            if (mContext != EGL_NO_CONTEXT) {
                eglDestroyContext(mDisplay, mContext);
                mContext = EGL_NO_CONTEXT;
            }
            if (mSurface != EGL_NO_SURFACE) {
                eglDestroySurface(mDisplay, mSurface);
                mSurface = EGL_NO_SURFACE;
            }
            eglTerminate(mDisplay);
            mDisplay = EGL_NO_DISPLAY;
        }
	}
#endif

	void GraphicsManager::Setup()
	{
        // Initializes base GL state.
        glEnable(GL_TEXTURE_2D);
        // In a simple 2D game, we have control over the third
        // dimension. So we do not really need a Z-buffer.
        glDisable(GL_DEPTH_TEST);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        // Set-up view and projection matrixes.
        /*glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrthof(0.0f, mWidth, 0.0f, mHeight, 0.0f, 1.0f);

        glMatrixMode( GL_MODELVIEW);
        glLoadIdentity();*/
	}



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


#ifdef _WIN32
		glDisable(GL_BLEND);
		glFlush();
#else
		 glDisable(GL_BLEND);
		 // Shows rendering surface.
		 if (eglSwapBuffers(mDisplay, mSurface) != EGL_TRUE)
		 {
			 return;
		 }
		 glFlush();
#endif
	}


}
