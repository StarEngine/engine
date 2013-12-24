#pragma once

#include "defines.h"
#include "Helpers/FPS.h"
#include <memory>

#include <random>

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
		void Initialize(int32 window_width, int32 window_height);

		void Update(const Context & context);
		void Draw();
		void End();

		void SetActive();
		void SetInactive();

		int32 GetCurrentFPS() const;
		int32 GetPreviousFPS() const;

		void SetGameTitle(const tstring & title);
		void SetGameSubTitle(const tstring & title);

		const tstring & GetGameTitle();

		bool HasTitleUpdated() const;
		void ResetTitleUpdateMark();

		std::mt19937& GetMt19937Engine();

		void Quit();

#ifdef ANDROID
		void SetAndroidApp(android_app * app);
		android_app * GetAndroidApp() const;
#endif

	private:
		static std::shared_ptr<StarEngine> m_pEngine;
		FPS m_FPS;
		tstring m_Title, m_SubTitle;
		bool m_TitleHasUpdated;
		std::mt19937 m_RandomEngine;

#ifdef ANDROID
		android_app *m_pAndroidApp;
#endif
		bool m_bInitialized;
		StarEngine();

#ifdef _WIN32
		friend class Window;
#endif

		StarEngine(const StarEngine &);
		StarEngine(StarEngine &&);
		StarEngine & operator=(const StarEngine &);
		StarEngine & operator=(StarEngine &&);
	};
}
