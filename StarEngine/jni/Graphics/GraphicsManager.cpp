#include "GraphicsManager.h"
#include "../Logger.h"
#include "SpriteBatch.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/BaseScene.h"
#include "../Objects/BaseCamera.h"
#include "../Components/CameraComponent.h"
#include "ScaleSystem.h"
#include "../defines.h"

#ifdef DESKTOP
#include <wglext.h>
#endif

#ifdef MOBILE
#include <GLES/gl.h>
#endif

namespace star
{
	GraphicsManager * GraphicsManager::mGraphicsManager = nullptr;
	
	GraphicsManager::~GraphicsManager()
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Graphics Manager : Destructor"), STARENGINE_LOG_TAG);
	}

	GraphicsManager::GraphicsManager()
		: mHorizontalViewportOffset(0)
		, mVerticalViewportOffset(0)
		, mViewProjectionMatrix()
		, mViewInverseMatrix()
		, mProjectionMatrix()
		, mScreenResolution(0,0)
		, mViewportResolution(0,0)
		, mbHasWindowChanged(false)
		, mIsInitialized(false)
#ifdef DESKTOP
		, mWglSwapIntervalEXT(NULL)
		, mWglGetSwapIntervalEXT(NULL)
#endif
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Graphics Manager : Constructor"), STARENGINE_LOG_TAG);
	}

	void GraphicsManager::CalculateViewPort()
	{
		vec2 screenRes = GetWindowResolution();
		vec2 workingRes = ScaleSystem::GetInstance()->GetWorkingResolution();
				
		float32 width = screenRes.x / workingRes.x;
		float32 height = screenRes.y / workingRes.y;

		mHorizontalViewportOffset = 0;
		mVerticalViewportOffset = 0;
		float32 aspectRatio(0);

		if(width > height)
		{
				height = screenRes.y;
				aspectRatio = (workingRes.x / workingRes.y);
				width = height * aspectRatio;

				mHorizontalViewportOffset = static_cast<int32>((screenRes.x - width)/2);
		}
		else
		{
				width = screenRes.x;
				aspectRatio = (workingRes.y / workingRes.x);
				height = width * aspectRatio;

				mVerticalViewportOffset = static_cast<int32>((screenRes.y - height)/2);
		}

		glViewport(mHorizontalViewportOffset, mVerticalViewportOffset, static_cast<int32>(width), static_cast<int32>(height));

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

	void GraphicsManager::SetVSync(bool vSync)
	{
#ifdef DESKTOP
		//Enables or disables VSync.
		//0 = No Sync , 1+ = VSync
		//Default value is 1.
		if(!vSync)
		{
			mWglSwapIntervalEXT(0);
		}
		else
		{
			mWglSwapIntervalEXT(1);
		}
	#else
		Logger::GetInstance()->Log(LogLevel::Warning, 
			_T("Setting VSync on mobile is not supported. Default VSync is enabled"),
			STARENGINE_LOG_TAG);
#endif
	}

	bool GraphicsManager::GetVSync() const
	{
#ifdef DESKTOP
		return !(mWglGetSwapIntervalEXT() == 0);
#else
		Logger::GetInstance()->Log(LogLevel::Warning, 
			_T("Toggeling VSync on mobile is not supported. Default VSync is enabled"),
			STARENGINE_LOG_TAG);
		return true;
#endif
	}

#ifdef DESKTOP
	void GraphicsManager::Initialize(int32 screenWidth, int32 screenHeight)
	{
		if(!mIsInitialized)
		{
			mScreenResolution.x = float32(screenWidth);
			mScreenResolution.y = float32(screenHeight);
			glewInit();

			star::Logger::GetInstance()->Log(star::LogLevel::Info,
				_T("Graphics Manager : Initializing OpenGL Functors"),
				STARENGINE_LOG_TAG);
			if(!InitializeOpenGLFunctors())
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Graphics Manager : Graphics card doesn't support VSync option!!"),
					STARENGINE_LOG_TAG);
			}

			SetVSync(true);

			//Initializes base GL state.
			//DEPTH_TEST is default disabled
			InitializeOpenGLStates();
			mIsInitialized = true;
		}
	}
#else
	void GraphicsManager::Initialize(const android_app* pApplication)
	{
		if(!mIsInitialized)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info,
				_T("Graphics Manager : Initialize"), STARENGINE_LOG_TAG);
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
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Graphics Manager : No display found"), STARENGINE_LOG_TAG);
				return;
			}
			if (!eglInitialize(mDisplay, NULL, NULL))
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Graphics Manager : Could not initialize display"), STARENGINE_LOG_TAG);
				return;
			}
			if(!eglChooseConfig(mDisplay, lAttributes, &lConfig, 1,&lNumConfigs) || (lNumConfigs <= 0))
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Graphics Manager : No display config"), STARENGINE_LOG_TAG);
				return;
			}
			if (!eglGetConfigAttrib(mDisplay, lConfig,EGL_NATIVE_VISUAL_ID, &lFormat))
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Graphics Manager : No config attributes"), STARENGINE_LOG_TAG);
				return;
			}
			ANativeWindow_setBuffersGeometry(pApplication->window, 0, 0,lFormat);

			mSurface = eglCreateWindowSurface(mDisplay, lConfig, pApplication->window, NULL );
			if (mSurface == EGL_NO_SURFACE)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Graphics Manager : Could not create surface"), STARENGINE_LOG_TAG);
				return;
			}
			EGLint contextAttrs[] = {
				 EGL_CONTEXT_CLIENT_VERSION, 2,
				 EGL_NONE
			};
			mContext = eglCreateContext(mDisplay, lConfig, EGL_NO_CONTEXT, contextAttrs);
			if (mContext == EGL_NO_CONTEXT)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Graphics Manager : Could not create context"), STARENGINE_LOG_TAG);
				return;
			}
			EGLint sX(0), sY(0);
			if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)
			 || !eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &sX)
			 || !eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &sY)
			 || (sX <= 0) || (sY <= 0))
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Graphics Manager : Could not activate display"),
					STARENGINE_LOG_TAG);
				return;
			}
			//[COMMENT] This might be redundant!
			mViewportResolution.x = sX;
			mViewportResolution.y = sY;
			mScreenResolution = mViewportResolution;
			glViewport(0, 0, mViewportResolution.x, mViewportResolution.y);
			InitializeOpenGLStates();
			star::Logger::GetInstance()->Log(star::LogLevel::Info,
				_T("Graphics Manager : Initialized"), STARENGINE_LOG_TAG);

			mIsInitialized = true;
		}
	}

	void GraphicsManager::Destroy()
	{
		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Graphics Manager : Destroy"), STARENGINE_LOG_TAG);
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
			star::Logger::GetInstance()->Log(star::LogLevel::Info,
				_T("Graphics Manager : Destroyed"), STARENGINE_LOG_TAG);

			mIsInitialized = false;
		}
	}
#endif

	void GraphicsManager::InitializeOpenGLStates()
	{
		//glDisable(GL_DEPTH_TEST);
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	void GraphicsManager::StartDraw()
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
	}

	void GraphicsManager::StopDraw()
	{
#ifdef ANDROID
		 if (eglSwapBuffers(mDisplay, mSurface) != EGL_TRUE)
		 {
			 return;
		 }
#endif
	}

	void GraphicsManager::Update()
	{
		if(SceneManager::GetInstance()->GetActiveScene())
		{
			auto projectionObject(SceneManager::GetInstance()->GetActiveScene()->GetActiveCamera());
			if(projectionObject)
			{
				const mat4& projection = projectionObject->GetComponent<CameraComponent>()
					->GetProjection();
				const mat4& viewInverse = projectionObject->GetComponent<CameraComponent>()
					->GetViewInverse();
				mProjectionMatrix = projection;
				mViewInverseMatrix = viewInverse;
				mViewProjectionMatrix = projection * viewInverse;
			}		
		}
	}

	int32 GraphicsManager::GetWindowWidth() const
	{
		return int32(mScreenResolution.x);
	}

	int32 GraphicsManager::GetWindowHeight() const
	{
		return int32(mScreenResolution.y);
	}

	int32 GraphicsManager::GetViewportWidth() const
	{
		return int32(mViewportResolution.x);
	}

	int32 GraphicsManager::GetViewportHeight() const
	{
		return int32(mViewportResolution.y);
	}

	int32 GraphicsManager::GetScreenWidth() const
	{
		return int32(ScaleSystem::GetInstance()->GetWorkingResolution().x);
	}

	int32 GraphicsManager::GetScreenHeight() const
	{
		return int32(ScaleSystem::GetInstance()->GetWorkingResolution().y);
	}

	const mat4& GraphicsManager::GetViewProjectionMatrix() const
	{
		return mViewProjectionMatrix;
	}

	const mat4& GraphicsManager::GetProjectionMatrix() const
	{
		return mProjectionMatrix;
	}

	const mat4& GraphicsManager::GetViewInverseMatrix() const
	{
		return mViewInverseMatrix;
	}

	float32 GraphicsManager::GetWindowAspectRatio() const
	{
		return mScreenResolution.x / mScreenResolution.y;
	}

	const vec2 & GraphicsManager::GetWindowResolution() const
	{
		return mScreenResolution;
	}

	const vec2 & GraphicsManager::GetViewportResolution() const
	{
		return mViewportResolution;
	}

	const vec2 & GraphicsManager::GetScreenResolution() const
	{
		return ScaleSystem::GetInstance()->GetWorkingResolution();
	}

	float32 GraphicsManager::GetViewportAspectRatio() const
	{
		return mViewportResolution.x / mViewportResolution.y;
	}

	int32 GraphicsManager::GetHorizontalViewportOffset() const
	{
		return mHorizontalViewportOffset;
	}

	int32 GraphicsManager::GetVerticalViewportOffset() const
	{
		return mVerticalViewportOffset;
	}

	void GraphicsManager::SetWindowDimensions(int32 width, int32 height)
	{
		mScreenResolution.x = float32(width);
		mScreenResolution.y = float32(height);
		CalculateViewPort();
	}

	void GraphicsManager::SetHasWindowChanged(bool isTrue)
	{
		mbHasWindowChanged = isTrue;
		if(isTrue)
		{
			CalculateViewPort();
		}
	}

	bool GraphicsManager::GetHasWindowChanged() const
	{
		return mbHasWindowChanged;
	}

#ifdef DESKTOP

	bool GraphicsManager::WGLExtensionSupported(const schar* extension_name)
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
		if (WGLExtensionSupported("WGL_EXT_swap_control"))
		{
			// Extension is supported, init pointers.
			mWglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");

			// this is another function from WGL_EXT_swap_control extension
			mWglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC) wglGetProcAddress("wglGetSwapIntervalEXT");
			return true;
		}
		return false;
	}
#endif
}
