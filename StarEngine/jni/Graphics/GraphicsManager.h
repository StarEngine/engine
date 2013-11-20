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

		int32 GetScreenWidth() const;
		int32 GetScreenHeight() const;

		const mat4& GetViewProjectionMatrix() const;
		const mat4& GetViewInverseMatrix() const;
		const mat4& GetProjectionMatrix() const;

		float32 GetWindowAspectRatio() const;

		const vec2 & GetWindowResolution() const;
		const vec2 & GetViewportResolution() const;
		const vec2 & GetScreenResolution() const;

		float32 GetViewportAspectRatio() const;

		int32 GetHorizontalViewportOffset() const;
		int32 GetVerticalViewportOffset() const;

		void SetWindowDimensions(int32 width, int32 height);
		void SetHasWindowChanged(bool isTrue);
		bool GetHasWindowChanged() const;
		void CalculateViewPort();

		void SetVSync(bool VSync);
		bool GetVSync() const;

	private:
		GraphicsManager();

#ifdef DESKTOP
		bool WGLExtensionSupported(const schar* extension_name);
		bool InitializeOpenGLFunctors();

		PFNWGLSWAPINTERVALEXTPROC       mWglSwapIntervalEXT;
		PFNWGLGETSWAPINTERVALEXTPROC    mWglGetSwapIntervalEXT;
#endif

		static GraphicsManager * mGraphicsManager;

		int32 mHorizontalViewportOffset,
			mVerticalViewportOffset;

		mat4 mViewProjectionMatrix;
		mat4 mViewInverseMatrix;
		mat4 mProjectionMatrix;
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
