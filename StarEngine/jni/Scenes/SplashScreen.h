#pragma once

#include "SlideScene.h"

namespace star
{
	class SplashScreen : public SlideScene
	{
	public:
		SplashScreen(const tstring& name, const tstring & nextScene);
		virtual ~SplashScreen();

		virtual void AfterInitializedObjects();

	private:
		SplashScreen(const SplashScreen& t);
		SplashScreen(SplashScreen&& t);
		SplashScreen& operator=(const SplashScreen& t);
		SplashScreen& operator=(SplashScreen&& t);
	};
}
