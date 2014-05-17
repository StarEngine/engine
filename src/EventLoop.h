#ifdef ANDROID

#pragma once

#include "defines.h"
#include <android_native_app_glue.h>
#include "BaseGame.h"
#include "Context.h"
#include "TimeManager.h"

namespace star
{
	class SceneManager;

	class EventLoop final
	{
	public:
		~EventLoop();

		static EventLoop * GetInstance();

		void Run();
		void End();

		void Initialize(android_app* pApplication, BaseGame * pBaseGame);
		const android_app * GetAndroidApp() const;

	protected:

	private:
		static EventLoop *mEventLoop;

		bool mMainGameInitialized;
		bool mEnabled;
		bool mQuit;
		BaseGame* mMainGame;
		Context mContext;
		android_app* mApplicationPtr;

		EventLoop();

		static void activityCallback(android_app* pApplication, int32_t pCommand);
		static int32 inputCallback(android_app* pApplication, AInputEvent* pEvent);
	};
}
#endif
