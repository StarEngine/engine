#pragma once

#include "../StarEngine/jni/defines.h"
#include <android_native_app_glue.h>
#include "Game.h"
#include "../StarEngine/jni/Context.h"
#include "../StarEngine/jni/TimeManager.h"

namespace star
{
	class SceneManager;
}

class EventLoop
{
public:
	~EventLoop();

	static EventLoop * GetInstance();

	void Run();
	void End();

	void Initialize(android_app* pApplication);
	const android_app * GetAndroidApp() const;

protected:

private:
	static EventLoop *mEventLoop;

	bool mMainGameInitialized;
	bool mEnabled;
	bool mQuit;
	Game* mMainGame;
	star::TimeManager* mTimeManager;
	star::Context mContext;
	android_app* mApplicationPtr;

	EventLoop();

	static void activityCallback(android_app* pApplication, int32_t pCommand);
	static int32 inputCallback(android_app* pApplication, AInputEvent* pEvent);
};
