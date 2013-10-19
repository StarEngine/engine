#include "GraphicsManager.h"
#include "../Logger.h"
#include "ScaleSystem.h"

#ifdef DESKTOP
#include <Windows.h>
#include <wglext.h>
#endif

namespace star
{
	std::shared_ptr<GraphicsManager> GraphicsManager::mGraphicsManager = nullptr;
	
	GraphicsManager::~GraphicsManager()
	{
	}

	GraphicsManager::GraphicsManager() :
			mScreenHeight(0),
			mScreenWidth(0),
			m_bHasWindowChanged(false)
	{
	}

	std::shared_ptr<GraphicsManager> GraphicsManager::GetInstance()
	{
		if(mGraphicsManager == nullptr)
		{
			mGraphicsManager = std::shared_ptr<GraphicsManager>(new GraphicsManager());
		}			
		return mGraphicsManager;	
	}

#ifdef DESKTOP
	void GraphicsManager::Initialize(int32 screenWidth, int32 screenHeight)
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;
		glewInit();

		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Initializing OpenGL Functors"));
		if(!InitializeOpenGLFunctors())
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : Graphics card doesn't support VSync option!!"));
		}

		//Initializes base GL state.
		// In a simple 2D game, we have control over the third
		// dimension. So we do not really need a Z-buffer.
		glDisable(GL_DEPTH_TEST);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
#else
	void GraphicsManager::Initialize(const android_app* pApplication)
	{
		EGLint lFormat, lNumConfigs, lErrorResult;
		EGLConfig lConfig;
		// Defines display requirements. 16bits mode here.
		const EGLint lAttributes[] = {
		            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		            EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6, EGL_RED_SIZE, 5,
		            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		            EGL_NONE
		};
		mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (mDisplay == EGL_NO_DISPLAY)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : No display found"));
			return;
		}
		if (!eglInitialize(mDisplay, NULL, NULL))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : Could not initialize display"));
			return;
		}
		if(!eglChooseConfig(mDisplay, lAttributes, &lConfig, 1,&lNumConfigs) || (lNumConfigs <= 0))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : No display config"));
			return;
		}
		if (!eglGetConfigAttrib(mDisplay, lConfig,EGL_NATIVE_VISUAL_ID, &lFormat))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : No config attributes"));
			return;
		}
		ANativeWindow_setBuffersGeometry(pApplication->window, 0, 0,lFormat);

		mSurface = eglCreateWindowSurface(mDisplay, lConfig, pApplication->window, NULL );
		if (mSurface == EGL_NO_SURFACE)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : Could not create surface"));
			return;
		}
		EGLint contextAttrs[] = {
		     EGL_CONTEXT_CLIENT_VERSION, 2,
		     EGL_NONE
		};
		mContext = eglCreateContext(mDisplay, lConfig, EGL_NO_CONTEXT, contextAttrs);
		if (mContext == EGL_NO_CONTEXT)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : Could not create context"));
			return;
		}
		if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)
		 || !eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mScreenWidth)
		 || !eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mScreenHeight)
		 || (mScreenWidth <= 0) || (mScreenHeight <= 0))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : Could not activate display"));
			return;
		}
		glViewport(0,0,mScreenWidth,mScreenHeight);


		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Initialized"));
	}

	void GraphicsManager::Destroy()
	{
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
            star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Destroyed"));
        }
	}
#endif

	void GraphicsManager::StartDraw()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GraphicsManager::StopDraw()
	{
		 glDisable(GL_BLEND);
#ifdef ANDROID
		 if (eglSwapBuffers(mDisplay, mSurface) != EGL_TRUE)
		 {
			 return;
		 }
#endif
	}

	int32 GraphicsManager::GetWindowWidth() const
	{
		return mScreenWidth;
	}

	int32 GraphicsManager::GetWindowHeight() const
	{
		return mScreenHeight;
	}

	float GraphicsManager::GetWindowAspectRatio() const
	{
		return float(mScreenWidth) / float(mScreenHeight);
	}

	void GraphicsManager::SetWindowDimensions(int32 width, int32 height)
	{
		mScreenWidth = width;
		mScreenHeight = height;
		glViewport(0,0,width, height);
		ScaleSystem::GetInstance()->UpdateWorkingResolution();
	}

	void GraphicsManager::SetHasWindowChanged(bool isTrue)
	{
		m_bHasWindowChanged = isTrue;
	}

	bool GraphicsManager::GetHasWindowChanged() const
	{
		return m_bHasWindowChanged;
	}

#ifdef DESKTOP

	bool GraphicsManager::WGLExtensionSupported(const char* extension_name)
	{
		// this is the pointer to the function which returns the pointer to string with the list of all wgl extensions
		PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

		// determine pointer to wglGetExtensionsStringEXT function
		_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) wglGetProcAddress("wglGetExtensionsStringEXT");

		if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL)
		{
			// string was not found
			return false;
		}

		// extension is supported
		return true;
	}

	bool GraphicsManager::InitializeOpenGLFunctors()
	{
		PFNWGLSWAPINTERVALEXTPROC       wglSwapIntervalEXT = NULL;
		PFNWGLGETSWAPINTERVALEXTPROC    wglGetSwapIntervalEXT = NULL;

		if (WGLExtensionSupported("WGL_EXT_swap_control"))
		{
			// Extension is supported, init pointers.
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");

			// this is another function from WGL_EXT_swap_control extension
			wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC) wglGetProcAddress("wglGetSwapIntervalEXT");

			wglSwapIntervalEXT(1);
			return true;
		}
		return false;
	}

#endif

}
