#include "EventLoop.h"
#include "Logger.h"

namespace star
{
#define LOGGER (Logger::GetSingleton())

	EventLoop::EventLoop(android_app* pApplication):
				mApplicationPtr(pApplication)
	{
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
				if(lSource != nullptr)
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
		}
	}
}

