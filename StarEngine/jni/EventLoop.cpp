#ifdef ANDROID

#include "EventLoop.h"
#include "Logger.h"
#include "Scenes/SceneManager.h"
#include "Graphics/GraphicsManager.h"
#include <unistd.h>
#include "Input/InputManager.h"
#include "StarEngine.h"
#include "Sound/AudioManager.h"

namespace star {
	EventLoop * EventLoop::mEventLoop = nullptr;

	EventLoop::~EventLoop() 
	{
		delete mTimeManager;
	}

	EventLoop::EventLoop() :
			mMainGameInitialized(false), 
			mQuit(false), 
			mEnabled(false), 
			mMainGame(nullptr), 
			mTimeManager(new TimeManager()),
			mApplicationPtr(nullptr) 
	{

	}

	void EventLoop::Initialize(android_app * pApplication, BaseGame * pBaseGame) 
	{
		mMainGame = pBaseGame;
		mApplicationPtr = pApplication;
		mApplicationPtr->onAppCmd = activityCallback;
		mApplicationPtr->userData = this;
		mContext.mTimeManager = mTimeManager;
		//mApplicationPtr->onAppCmd = activityCallback;
		mApplicationPtr->onInputEvent = inputCallback;
		StarEngine::GetInstance()->SetAndroidApp(mApplicationPtr);
	}

	EventLoop * EventLoop::GetInstance() 
	{
		if (mEventLoop == nullptr) 
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

		Logger::GetInstance()->Log(LogLevel::Info, _T("Starting EventLoop"));

		while (true)
		{
			mTimeManager->StartMonitoring();
			while ((lResult = ALooper_pollAll(mEnabled ? 0 : -1, NULL, &lEvents,
					(void**) &lSource)) >= 0)
			{
				if (lSource != NULL)
				{
					lSource->process(mApplicationPtr, lSource);
				}

				if (mApplicationPtr->destroyRequested)
				{
					Logger::GetInstance()->Log(LogLevel::Info, _T("Exiting Event"));
					mQuit = true;
					mEnabled = false;
					mTimeManager->StopMonitoring();
					return;
				}
			}

			if (mEnabled && !mQuit)
			{
				GraphicsManager::GetInstance()->SetHasWindowChanged(false);
				mMainGame->Update(mContext);
				mMainGame->Draw();
			}
			usleep(100);
			mTimeManager->StopMonitoring();
		}
	}

	void EventLoop::End()
	{
		//[COMMENT] This "delete this" looks very unsafe... 
		Logger::GetInstance()->Log(LogLevel::Info, _T("Ending App"));
		mMainGame->End();
		delete InputManager::GetInstance();
		delete this;
		ANativeActivity_finish(mApplicationPtr->activity);
	}

	void EventLoop::activityCallback(android_app* pApplication, int32_t pCommand)
	{
		EventLoop& lEventLoop =
				*reinterpret_cast<EventLoop*>(pApplication->userData);

		switch (pCommand)
		{
		//Gets called first on fresh app launch
		case APP_CMD_INIT_WINDOW:
			if (pApplication->window != nullptr)
			{
				Logger::GetInstance()->Log(LogLevel::Info,
						_T("Eventloop : APP CMD INIT WINDOW"));
				GraphicsManager::GetInstance()->Initialize(pApplication);
				lEventLoop.mQuit = false;
			}
			else
			{
				lEventLoop.mQuit = true;
				ANativeActivity_finish(pApplication->activity);
			}
			GraphicsManager::GetInstance()->SetHasWindowChanged(true);
			break;

			//Gets called second after the window init
		case APP_CMD_GAINED_FOCUS: 
		{
			if (!lEventLoop.mMainGameInitialized) 
			{
				lEventLoop.mMainGame->Initialize(0, 0);
			}
			lEventLoop.mMainGameInitialized = true;
			lEventLoop.mEnabled = true;
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP CMD GAINED FOXUS, Initited MainGame"));
			TextureManager::GetInstance()->ReloadAllTextures();
			SceneManager::GetInstance()->processActivityEvent(pCommand,
					pApplication);
		}
			break;

		case APP_CMD_LOST_FOCUS:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP_CMD_LOST_FOCUS"));
			AudioManager::GetInstance()->PauseAllSounds();
			break;

			//Gets called first when rotating the screen
			//After this the Save State gets called in the scene manager
		case APP_CMD_PAUSE:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP CMD PAUSE"));
			lEventLoop.mEnabled = false;
			AudioManager::GetInstance()->PauseAllSounds();
			break;

		case APP_CMD_RESUME:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP_CMD_RESUME"));
			break;

			//Gets called after the pause command
		case APP_CMD_STOP:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP_CMD_STOP"));
			SceneManager::GetInstance()->processActivityEvent(pCommand,
					pApplication);
			break;

		case APP_CMD_START:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP_CMD_START"));
			break;

		case APP_CMD_TERM_WINDOW:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP_CMD_TERM_WINDOW"));
			TextureManager::GetInstance()->EraseAllTextures();
			break;

		case APP_CMD_DESTROY:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP_CMD_DESTROY"));
			GraphicsManager::GetInstance()->Destroy();

			break;

		case APP_CMD_LOW_MEMORY:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP_CMD_LOW_MEMORY"));
			break;

		case APP_CMD_CONFIG_CHANGED:
			Logger::GetInstance()->Log(LogLevel::Info,
					_T("Eventloop : APP_CMD_CONFIG_CHANGED"));
			break;

		default:
			SceneManager::GetInstance()->processActivityEvent(pCommand,
					pApplication);
			break;
		}

	}

	int32 EventLoop::inputCallback(android_app* pApplication, AInputEvent* pEvent)
	{
		return SceneManager::GetInstance()->processInputEvent(pEvent);
	}
}
#endif
