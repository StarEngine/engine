#include "EventLoop.h"
#include "../StarEngine/jni/Logger.h"
#include "../StarEngine/jni/SceneManaging/SceneManager.h"
#include "../StarEngine/jni/GraphicsManager.h"
#include <unistd.h>
#include "../StarEngine/jni/Input/InputManager.h"
#include "../StarEngine/jni/StarEngine.h"
#include "../StarEngine/jni/Sound/SoundService.h"

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
		//Gets called first on fresh app launch
	case APP_CMD_INIT_WINDOW:
		if(pApplication->window != nullptr)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Eventloop : APP CMD INIT WINDOW"));
			star::GraphicsManager::GetInstance()->Initialize(pApplication);
			lEventLoop.mQuit=false;
		}
		else
		{
			lEventLoop.mQuit = true;
			ANativeActivity_finish(pApplication->activity);
		}
	break;

		//Gets called second after the window init
	case APP_CMD_GAINED_FOCUS:
		if(lEventLoop.mMainGame->Initialize(0,0) != STATUS_OK)
		{
			lEventLoop.mEnabled = false;
			lEventLoop.End();
		}
		else
		{
			lEventLoop.mEnabled = true;
			star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Eventloop : APP CMD GAINED FOXUS, Initited MainGame"));
			star::SceneManager::GetInstance()->processActivityEvent(pCommand,pApplication);
		}
		break;

	case APP_CMD_LOST_FOCUS:
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Eventloop : APP_CMD_LOST_FOCUS"));
		star::SoundService::GetInstance()->PauseAllSound();
		break;

		//Gets called first when rotating the screen
		//After this the Save State gets called in the scene manager
	case APP_CMD_PAUSE:
		star::Logger::GetInstance()->Log(star::LogLevel::Info,_T("Eventloop : APP CMD PAUSE"));
		lEventLoop.mEnabled = false;
		star::SoundService::GetInstance()->PauseAllSound();
		break;

	case APP_CMD_RESUME:
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Eventloop : APP_CMD_RESUME"));
		break;

		//Gets called after the pause command
	case APP_CMD_STOP:
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Eventloop : APP_CMD_STOP"));
		star::SceneManager::GetInstance()->processActivityEvent(pCommand,pApplication);
		break;

	case APP_CMD_START:
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Eventloop : APP_CMD_START"));
		break;

	case APP_CMD_TERM_WINDOW:
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Eventloop : APP_CMD_TERM_WINDOW"));
		star::TextureManager::GetInstance()->EraseTextures();
		break;

	case APP_CMD_DESTROY:
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Eventloop : APP_CMD_DESTROY"));
		star::GraphicsManager::GetInstance()->Destroy();

		break;


	case APP_CMD_LOW_MEMORY:
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Eventloop : APP_CMD_LOW_MEMORY"));
		break;

	case APP_CMD_CONFIG_CHANGED:
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Eventloop : APP_CMD_CONFIG_CHANGED"));
		break;

	default:
		star::SceneManager::GetInstance()->processActivityEvent(pCommand,pApplication);
		break;
	}


}

int32 EventLoop::inputCallback(android_app* pApplication, AInputEvent* pEvent)
{
	return star::SceneManager::GetInstance()->processInputEvent(pEvent);
}
