#pragma once

#include "defines.h"
#include "Helpers/FPS.h"
#include <memory>

#ifdef ANDROID
#include "android_native_app_glue.h"
#include  <SLES/OpenSLES.h>
#include  <SLES/OpenSLES_Android.h>
#include  <SLES/OpenSLES_AndroidConfiguration.h>
#elif defined(_WIN32)
class Window;
#endif

namespace star
{
	struct Context;

	class StarEngine final
	{
	public:
		~StarEngine();

		static std::shared_ptr<StarEngine> GetInstance();

		status Initialize(int32 window_width, int32 window_height);

		status Update(const Context & context);
		status Draw();

		status End();

		void SetActive();
		void SetInactive();

		int GetCurrentFPS() const;
		int GetPreviousFPS() const;

		void SetGameTitle(const tstring & title);
		void SetGameSubTitle(const tstring & title);

		bool HasTitleUpdated() const;
		void ResetTitleUpdateMark();

#ifdef ANDROID
		void SetAndroidApp(android_app * app);
		android_app * GetAndroidApp() const;
#endif

	private:
		static std::shared_ptr<StarEngine> m_pEngine;
		FPS m_FPS;
		tstring m_Title, m_SubTitle;
		bool m_TitleHasUpdated;

#ifdef ANDROID
		android_app *m_pAndroidApp;
#endif

		StarEngine();

#ifdef _WIN32
		friend class Window;
#endif

		StarEngine(const StarEngine &);
		StarEngine(StarEngine &&);
		StarEngine & operator=(const StarEngine &);
	};
}
