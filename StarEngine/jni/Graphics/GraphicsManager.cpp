#include "GraphicsManager.h"
#include "../Logger.h"
#include "ScaleSystem.h"
#include "SpriteBatch.h"

#ifdef _WIN32
#include <Windows.h>
#include <glew.h>
#endif

#ifdef MOBILE
#include <GLES/gl.h>
#endif

#ifdef DESKTOP
#include <wglext.h>
#endif

namespace star
{
	GraphicsManager * GraphicsManager::mGraphicsManager = nullptr;
	
	GraphicsManager::~GraphicsManager()
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Destructor"));
	}

	GraphicsManager::GraphicsManager() :
			mScreenResolution(0,0),
			mViewportResolution(0,0),
			m_bHasWindowChanged(false),
			mIsInitialized(false)
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Constructor"));
	}

	void GraphicsManager::CalculateViewPort()
	{
		//Calculate the correct viewport
		vec2 screenRes = GetWindowResolution();
		vec2 workingRes = ScaleSystem::GetInstance()->GetWorkingResolution();
		
		float width = screenRes.x / workingRes.x;
		float height = screenRes.y / workingRes.y;

		int xOffset(0), yOffset(0);
		float aspectRatio(0);

		if(width > height)
		{
			height = screenRes.y;
			aspectRatio = (workingRes.x / workingRes.y);
			width = height * aspectRatio;
			xOffset = static_cast<int>((screenRes.x - width)/2);
		}
		else
		{
			width = screenRes.x;
			aspectRatio = (workingRes.y / workingRes.x);
			height = width * aspectRatio;
			yOffset = static_cast<int>((screenRes.y - height)/2);
		}

		glViewport(xOffset, yOffset, static_cast<int>(width), static_cast<int>(height));

		mViewportResolution.x = width;
		mViewportResolution.y = height;

		ScaleSystem::GetInstance()->CalculateScale();
	}

	GraphicsManager * GraphicsManager::GetInstance()
	{
		if(mGraphicsManager == nullptr)
		{
			mGraphicsManager = new GraphicsManager();
		}			
		return mGraphicsManager;	
	}

#ifdef DESKTOP
	void GraphicsManager::Initialize(int32 screenWidth, int32 screenHeight)
	{
		if(!mIsInitialized)
		{
			mScreenResolution.x = float(screenWidth);
			mScreenResolution.y = float(screenHeight);
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
			mIsInitialized = true;

			CalculateViewPort();
		}
	}
#else
	void GraphicsManager::Initialize(const android_app* pApplication)
	{
		if(!mIsInitialized)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Initialize"));
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
			EGLint sX(0), sY(0);
			if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)
			 || !eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &sX)
			 || !eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &sY)
			 || (sX <= 0) || (sY <= 0))
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Graphics Manager : Could not activate display"));
				return;
			}
			mViewportResolution.x = sX;
			mViewportResolution.y = sY;
			mScreenResolution = mViewportResolution;
			glViewport(0, 0, mViewportResolution.x, mViewportResolution.y);


			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Initialized"));

			mIsInitialized = true;
		}
	}

	void GraphicsManager::Destroy()
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : Destroy"));
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

            SpriteBatch::GetInstance()->CleanUp();

            mIsInitialized = false;
        }
	}
#endif

	void GraphicsManager::StartDraw()
	{
		//star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : StartDraw"));
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		/*
		GLint temp[4];
		glGetIntegerv(GL_VIEWPORT, temp);

		tstringstream buffer;
		buffer << _T("Viewport Width: ") << temp[2] << _T(" Viewport Height: ") << temp[3];
		Logger::GetInstance()->Log(LogLevel::Info, buffer.str());*/
	}

	void GraphicsManager::StopDraw()
	{
		//star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Graphics Manager : StopDraw"));
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
		return int32(mScreenResolution.x);
	}

	int32 GraphicsManager::GetWindowHeight() const
	{
		return int32(mScreenResolution.y);
	}

	int32 GraphicsManager::GetTargetWindowWidth() const
	{
		return int32(ScaleSystem::GetInstance()->GetWorkingResolution().x);
	}

	int32 GraphicsManager::GetTargetWindowHeight() const
	{
		return int32(ScaleSystem::GetInstance()->GetWorkingResolution().y);
	}

	float GraphicsManager::GetWindowAspectRatio() const
	{
		return mScreenResolution.x / mScreenResolution.y;
	}

	float GraphicsManager::GetTargetWindowAspectRatio() const
	{
		return ScaleSystem::GetInstance()->GetAspectRatio();
	}

	const vec2 & GraphicsManager::GetWindowResolution() const
	{
		return mScreenResolution;
	}

	const vec2 & GraphicsManager::GetViewportResolution() const
	{
		return mViewportResolution;
	}

	const vec2& GraphicsManager::GetTargetWindowResolution() const
	{
		return ScaleSystem::GetInstance()->GetActualResolution();
	}

	void GraphicsManager::SetWindowDimensions(int32 width, int32 height)
	{
		mScreenResolution.x = float(width);
		mScreenResolution.y = float(height);
		CalculateViewPort();
	}

	void GraphicsManager::SetHasWindowChanged(bool isTrue)
	{
		m_bHasWindowChanged = isTrue;
		if(isTrue)
		{
			CalculateViewPort();
		}
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
