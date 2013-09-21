#include "EventLoop.h"
#include "Logger.h"
#include "SceneManaging/SceneManager.h"
#include <unistd.h>

namespace star
{

	EventLoop::EventLoop(android_app* pApplication):
				mApplicationPtr(pApplication),
				mEnabled(true),
				mQuit(false)
	{

		//mApplicationPtr->onAppCmd = activityCallback;
		//mApplicationPtr->userData = this;
		mMainGame = new MainGame();
		mTimeManager = new TimeManager();
		mContext.mTimeManager = mTimeManager;
	}

	void EventLoop::run()
	{
		int32 lResult;
		int32 lEvents;
		android_poll_source* lSource;

		app_dummy();

		star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Starting Event Loop"));

		if(mMainGame->Initialize()!=STATUS_OK)
		{
			//mQuit=true;
			//end();
		}
		star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Initialize Done"));
		while(true)
		{
			mTimeManager->StartMonitoring();
			while((lResult = ALooper_pollAll(mEnabled ? 0 : -1, NULL, &lEvents, (void**) &lSource)) >= 0)
			{
				if(lSource != NULL)
				{
					star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Processing Event"));
					lSource->process(mApplicationPtr, lSource);
				}

				if(mApplicationPtr->destroyRequested)
				{
					star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Exiting Event"));
					mQuit=true;
					return;
				}
			}

			if((mEnabled)&& (!mQuit))
			{
				if(mMainGame->Run(mContext)!=STATUS_OK)
				{
					mQuit=true;
					end();
				}
			}
			usleep(100);
			mTimeManager->StopMonitoring();
		}
	}

	void EventLoop::end()
	{
		star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Ending App"));
		mMainGame->End();
		ANativeActivity_finish(mApplicationPtr->activity);
	}

	void EventLoop::activityCallback(android_app* pApplication, int32_t pCommand)
	{
		EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
		SceneManager::GetInstance()->processActivityEvent(pCommand,pApplication);
	}

}

