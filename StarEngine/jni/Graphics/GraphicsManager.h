#pragma once

#include "../defines.h"
#include <memory>

#ifdef _WIN32
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

		static std::shared_ptr<GraphicsManager> GetInstance();

#ifdef _WIN32
		void Initialize(int32 screenWidth, int32 screenHeight);
#else
		void Initialize(const android_app* pApplication);
		void Destroy();
#endif

		void StartDraw();
		void StopDraw();

		int32 GetWindowWidth() const;
		int32 GetWindowHeight() const;
		float GetWindowAspectRatio() const;

		void SetWindowDimensions(int32 width, int32 height);

	private:
		GraphicsManager();

#ifdef _WIN32
		bool WGLExtensionSupported(const char* extension_name);
		bool InitializeOpenGLFunctors();
#endif

		static std::shared_ptr<GraphicsManager> mGraphicsManager;

		int32 mScreenWidth;
		int32 mScreenHeight;

#ifndef _WIN32
        EGLDisplay mDisplay;
        EGLSurface mSurface;
        EGLContext mContext;
#endif

		GraphicsManager(const GraphicsManager& yRef);
		GraphicsManager(GraphicsManager&& yRef);
		GraphicsManager& operator=(const GraphicsManager& yRef);
	};


}
