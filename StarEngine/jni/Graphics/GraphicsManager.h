#pragma once

#include "../defines.h"

#ifdef DESKTOP
#include <glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <android_native_app_glue.h>
#endif

namespace star
{
	class GraphicsManager
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

		int32 GetWindowWidth() const;
		int32 GetWindowHeight() const;
		int32 GetTargetWindowWidth() const;
		int32 GetTargetWindowHeight() const;

		float GetWindowAspectRatio() const;
		float GetTargetWindowAspectRatio() const;

		vec2 GetWindowResolution() const;
		const vec2& GetTargetWindowResolution() const;

		void SetWindowDimensions(int32 width, int32 height);
		void SetHasWindowChanged(bool isTrue);
		bool GetHasWindowChanged() const;

	private:
		GraphicsManager();

#ifdef DESKTOP
		bool WGLExtensionSupported(const char* extension_name);
		bool InitializeOpenGLFunctors();
#endif

		static GraphicsManager * mGraphicsManager;

		int32 mScreenWidth;
		int32 mScreenHeight;
		bool m_bHasWindowChanged;
		bool mIsInitialized;

#ifdef ANDROID
        EGLDisplay mDisplay;
        EGLSurface mSurface;
        EGLContext mContext;
#endif

		GraphicsManager(const GraphicsManager& yRef);
		GraphicsManager(GraphicsManager&& yRef);
		GraphicsManager& operator=(const GraphicsManager& yRef);
	};


}
