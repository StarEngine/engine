#pragma once

#include "../defines.h"

#ifdef DESKTOP
#include <Windows.h>
#include <glew.h>
#include <wglext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <android_native_app_glue.h>
#endif

namespace star
{
	class GraphicsManager final
	{
	public:
		~GraphicsManager();

		static GraphicsManager * GetInstance();

#ifdef DESKTOP
		void Initialize(int32 screenWidth, int32 screenHeight);
#else
		void Initialize(const android_app* pApplication);
		void Destroy();
#endif

		void StartDraw();
		void StopDraw();
		void Update();

		int32 GetWindowWidth() const;
		int32 GetWindowHeight() const;

		int32 GetViewportWidth() const;
		int32 GetViewportHeight() const;

		const mat4x4& GetViewProjectionMatrix() const;
		const mat4x4& GetViewInverseMatrix() const;
		const mat4x4& GetProjectionMatrix() const;

		float GetWindowAspectRatio() const;

		const vec2 & GetWindowResolution() const;
		const vec2 & GetViewportResolution() const;

		float GetViewportAspectRatio() const;

		void SetWindowDimensions(int32 width, int32 height);
		void SetHasWindowChanged(bool isTrue);
		bool GetHasWindowChanged() const;
		void CalculateViewPort();

		void SetVSync(bool VSync);
		bool GetVSync() const;

	private:
		GraphicsManager();

#ifdef DESKTOP
		bool WGLExtensionSupported(const char* extension_name);
		bool InitializeOpenGLFunctors();

		PFNWGLSWAPINTERVALEXTPROC       mWglSwapIntervalEXT;
		PFNWGLGETSWAPINTERVALEXTPROC    mWglGetSwapIntervalEXT;
#endif

		static GraphicsManager * mGraphicsManager;

		mat4x4 mViewProjectionMatrix;
		mat4x4 mViewInverseMatrix;
		mat4x4 mProjectionMatrix;
		vec2 mScreenResolution, mViewportResolution;
		bool mbHasWindowChanged;
		bool mIsInitialized;

#ifdef ANDROID
        EGLDisplay mDisplay;
        EGLSurface mSurface;
        EGLContext mContext;
#endif

		GraphicsManager(const GraphicsManager& yRef);
		GraphicsManager(GraphicsManager&& yRef);
		GraphicsManager& operator=(const GraphicsManager& yRef);
		GraphicsManager& operator=(GraphicsManager&& yRef);
	};


}
