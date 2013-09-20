#include "EventLoop.h"
#include "Logger.h"
#include "SceneManaging/SceneManager.h"

namespace star
{
#define LOGGER (Logger::GetSingleton())

	EventLoop::EventLoop(android_app* pApplication):
				mApplicationPtr(pApplication)
	{
		mApplicationPtr->onAppCmd = activityCallback;
		mApplicationPtr->userData = this;
		mSceneManager = SceneManager::GetInstance();
	}

	void EventLoop::run()
	{
		int32 lResult;
		int32 lEvents;
		android_poll_source* lSource;

		app_dummy();

		LOGGER->Log(LogLevel::Info,"Starting event loop");
		while(true)
		{
			while((lResult = ALooper_pollAll(-1, NULL, &lEvents, (void**) &lSource)) >= 0)
			{
				if(lSource != NULL)
				{
					LOGGER->Log(LogLevel::Info,"processing an event");
				}
				lSource->process(mApplicationPtr, lSource);
			}
			if(mApplicationPtr->destroyRequested)
			{
				LOGGER->Log(LogLevel::Info,"Exiting event loop");
				return;
			}
			if((mEnabled)&& (!mQuit))
			{
				if(mSceneManager->Update(0.1f)!= STATUS_OK)
				{
					mQuit =true;
					ANativeActivity_finish(mApplicationPtr->activity);
				}
				if(mSceneManager->Draw()!= STATUS_OK)
				{
					mQuit =true;
					ANativeActivity_finish(mApplicationPtr->activity);
				}
			}
		}
	}

	void EventLoop::activityCallback(android_app* pApplication, int32_t pCommand)
	{
		EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
		SceneManager::GetInstance()->processActivityEvent(pCommand);
	}

	// ---------------------------------------
	// Don't touch - Symon
	// ---------------------------------------

/*
	void EventLoop::activate()
		{
			if((!mEnabled) && (mApplicationPtr->window != NULL))
			{
				mQuit = false;
				mEnabled=true;
				if(mActivityHandler->onActivate() != STATUS_OK)
				{
					mQuit = true;
					ANativeActivity_finish(mApplicationPtr->activity);
				}
			}
		}

	void EventLoop::deactivate()
	{
			if(mEnabled)
		{
			mActivityHandler->onDeactivate();
			mEnabled=false;
		}
	}

	void EventLoop::processActivityEvent(int32_t pCommand)
	{
		switch(pCommand)
		{
		case APP_CMD_CONFIG_CHANGED:
			mActivityHandler->onConfigurationChanged();
			break;
		case APP_CMD_INIT_WINDOW:
			mActivityHandler->onCreateWindow();
			break;
		case APP_CMD_DESTROY:
			mActivityHandler->onDestroy();
			break;
		case APP_CMD_GAINED_FOCUS:
			activate();
			mActivityHandler->onGainFocus();
			break;
		case APP_CMD_LOST_FOCUS:
			mActivityHandler->onLostFocus();
			deactivate();
			break;
		case APP_CMD_LOW_MEMORY:
			mActivityHandler->onLowMemory();
			break;
		case APP_CMD_PAUSE:
			mActivityHandler->onPause();
			deactivate();
			break;
		case APP_CMD_RESUME:
			mActivityHandler->onResume();
			break;
		case APP_CMD_SAVE_STATE:
			mActivityHandler->onSaveState(&mApplicationPtr->savedState,&mApplicationPtr->savedStateSize);
			break;
		case APP_CMD_START:
			mActivityHandler->onStart();
			break;
		case APP_CMD_STOP:
			mActivityHandler->onStop();
			break;
		case APP_CMD_TERM_WINDOW:
			mActivityHandler->onDestroyWindow();
			deactivate();
			break;
		default:
			break;
		}
	}
*/




}

