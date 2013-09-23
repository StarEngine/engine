#include "TimeManager.h"

namespace star
{
	TimeManager::TimeManager()
#ifdef _WIN32
		:mFrequency()
		,mF1()
		,mF2()
#else
		:mF1(0)
		,mF2(0)
		,mElapsed(0)
#endif
		,mDeltaMs(0)
		,mDeltaS(0)
		,mDeltauS(0)
	{

	}

	void TimeManager::StartMonitoring()
	{
#ifdef _WIN32
		QueryPerformanceCounter(&mF1);
#else
		timespec lTimeVal;
		clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
		mF1 = lTimeVal.tv_sec + (lTimeVal.tv_nsec*1.0e-9);
#endif
	}

	void TimeManager::StopMonitoring()
	{
#ifdef _WIN32
		QueryPerformanceCounter(&mF2);
		QueryPerformanceFrequency(&mFrequency);
		mDeltauS = (mF2.QuadPart - mF1.QuadPart) * 1000000.0 / mFrequency.QuadPart;
		mDeltaMs = (mF2.QuadPart - mF1.QuadPart) * 1000.0 / mFrequency.QuadPart;
		mDeltaS	 = (mF2.QuadPart - mF1.QuadPart) * 1.0 / mFrequency.QuadPart;
#else
		timespec lTimeVal;
		clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
		mF2 = lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
		mDeltauS = (mF2 - mF1) * 1000000.0;
		mDeltaMs = (mF2 - mF1) * 1000.0;
		mDeltaS  = (mF2 - mF1);
#endif
	}

	double TimeManager::GetSeconds() const
	{
		return mDeltaS;
	}

	double TimeManager::GetMiliSeconds() const
	{
		return mDeltaMs;
	}

	double TimeManager::GetMicroSeconds() const
	{
		return mDeltauS;
	}
}
