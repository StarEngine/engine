#include "EventLoop.h"
#include "../StarEngine/jni/Logger.h"
#include "../StarEngine/jni/SceneManaging/SceneManager.h"
#include "../StarEngine/jni/GraphicsManager.h"
#include <unistd.h>
#include "../StarEngine/jni/Input/InputManager.h"
#include "../StarEngine/jni/StarEngine.h"

EventLoop * EventLoop::mEventLoop = nullptr;

EventLoop::~EventLoop()
{
	delete mMainGame;
	delete mTimeManager;
}

EventLoop::EventLoop():
			mMainGameInitialized(false),
			mQuit(false),
			mEnabled(false),
			mMainGame(new Game()),
			mTimeManager(new star::TimeManager()),
			mApplicationPtr(nullptr)
{

}

void EventLoop::Initialize(android_app * pApplication)
{
	mApplicationPtr = pApplication;
	mApplicationPtr->onAppCmd = activityCallback;
	mApplicationPtr->userData = this;
	mContext.mTimeManager = mTimeManager;
	//mApplicationPtr->onAppCmd = activityCallback;
	mApplicationPtr->onInputEvent = inputCallback;
	star::StarEngine::GetInstance()->SetAndroidApp(mApplicationPtr);
}


EventLoop * EventLoop::GetInstance()
{
	if(mEventLoop == nullptr)
	{
		mEventLoop = new EventLoop();
	}
	return mEventLoop;
}

void EventLoop::Run()
	{
		int32 lResult;
		int32 lEvents;
		android_poll_source* lSource;

		app_dummy();

	star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Starting EventLoop"));

	while(true)
	{
		mTimeManager->StartMonitoring();
		while((lResult = ALooper_pollAll(mEnabled ? 0 : -1, NULL, &lEvents, (void**) &lSource)) >= 0)
		{
			if(lSource != NULL)
			{
				lSource->process(mApplicationPtr, lSource);
			}

			if(mApplicationPtr->destroyRequested)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Exiting Event"));
				mQuit = true;
				mEnabled=false;
				return;
			}
		}

		if((mEnabled)&& (!mQuit))
		{

			if(mMainGame->Update(mContext) != STATUS_OK)
			{
				mQuit = true;
				End();
			}
			else if(mMainGame->Draw() != STATUS_OK)
			{
				mQuit = true;
				End();
			}
		}
		usleep(100);
		mTimeManager->StopMonitoring();
	}
}

void EventLoop::End()
{
	star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Ending App"));
	mMainGame->End();
	ANativeActivity_finish(mApplicationPtr->activity);
}

void EventLoop::activityCallback(android_app* pApplication, int32_t pCommand)
{
	// [COMMENT] Use C++ Casts please!
	EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;

	switch(pCommand)
	{
	case APP_CMD_INIT_WINDOW:
		if(pApplication->window != nullptr)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Eventloop Callback : INIT Window"));
			star::GraphicsManager::GetInstance()->Initialize(pApplication);
			lEventLoop.mQuit=false;
		}
	break;

	case APP_CMD_GAINED_FOCUS:
		if(lEventLoop.mMainGame->Initialize(0,0) != STATUS_OK)
		{
			lEventLoop.mEnabled = false;
			lEventLoop.End();
		}
		else
		{
			lEventLoop.mEnabled = true;
			star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Eventloop Callback : GAINED FOXUS, Initited MainGame"));
		}
		break;

	default:
		//star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Callback to scenemanager"));
		star::SceneManager::GetInstance()->processActivityEvent(pCommand,pApplication);
		break;
	}


}

int32 EventLoop::inputCallback(android_app* pApplication, AInputEvent* pEvent)
{
	return star::SceneManager::GetInstance()->processInputEvent(pEvent);
}
