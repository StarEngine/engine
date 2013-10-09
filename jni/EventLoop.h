#pragma once

#include "../StarEngine/jni/Defines.h"
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
	static android_app* mApplicationPtr;

	EventLoop(android_app* pApplication);

	void run();
	void end();

	//[COMMENT] Scanning through the sample files, these methodes are private. can they be moved?
protected:
	static void activityCallback(android_app* pApplication, int32_t pCommand);
	static int32 inputCallback(android_app* pApplication, AInputEvent* pEvent);

private:

	bool mMainGameInitialized;
	bool mEnabled;
	bool mQuit;
	Game* mMainGame;
	star::TimeManager* mTimeManager;
	star::Context mContext;
};
