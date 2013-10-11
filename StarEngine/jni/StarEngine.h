#pragma once

#include "defines.h"

#ifndef _WIN32
#include "android_native_app_glue.h"
#include  <SLES/OpenSLES.h>
#include  <SLES/OpenSLES_Android.h>
#include  <SLES/OpenSLES_AndroidConfiguration.h>
#endif

namespace star
{
	struct Context;

	class StarEngine final
	{
	public:
		~StarEngine();

		static StarEngine * GetInstance();

		status Initialize(int32 window_width, int32 window_height);

		status Update(const Context & context);
		status Draw();

		status End();

		void SetActive();
		void SetInactive();

#ifndef _WIN32
		void SetAndroidApp(android_app * app) { m_pAndroidApp = app; }
		android_app * GetAndroidApp() const { return m_pAndroidApp; }
#endif

	private:
		static StarEngine * m_pEngine;

#ifndef _WIN32
		android_app *m_pAndroidApp;
#endif

		StarEngine();

		StarEngine(const StarEngine &);
		StarEngine(StarEngine &&);
		StarEngine & operator=(const StarEngine &);
	};
}
