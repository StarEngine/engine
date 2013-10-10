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
		,mTotalMS(0)
	{

	}

	void TimeManager::StartMonitoring()
	{
#ifdef _WIN32
		QueryPerformanceCounter(&mF1);
#else
		timespec lTimeVal;
		clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
		mF1 = lTimeVal.tv_sec + (lTimeVal.tv_nsec*NSMULTIPLIER);
#endif
	}

	void TimeManager::StopMonitoring()
	{
#ifdef _WIN32
		QueryPerformanceCounter(&mF2);
		QueryPerformanceFrequency(&mFrequency);
		mDeltauS = (mF2.QuadPart - mF1.QuadPart) * MICROMULTIPLIER / mFrequency.QuadPart;
		mDeltaMs = (mF2.QuadPart - mF1.QuadPart) * MILLIMULTIPLIER / mFrequency.QuadPart;
		mDeltaS	 = (mF2.QuadPart - mF1.QuadPart) * SECONDMULTIPLIER / mFrequency.QuadPart;
#else
		timespec lTimeVal;
		clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
		mF2 = lTimeVal.tv_sec + (lTimeVal.tv_nsec * NSMULTIPLIER);
		mDeltauS = (mF2 - mF1) * MICROMULTIPLIER;
		mDeltaMs = (mF2 - mF1) * MILLIMULTIPLIER;
		mDeltaS  = (mF2 - mF1);
#endif
		mTotalMS += mDeltaMs;
	}

	double TimeManager::GetSeconds() const
	{
		return mDeltaS;
	}

	double TimeManager::GetMilliSeconds() const
	{
		return mDeltaMs;
	}

	double TimeManager::GetMicroSeconds() const
	{
		return mDeltauS;
	}

	double TimeManager::GetMilliSecondsSinceStart() const
	{
		return mTotalMS;
	}

	double TimeManager::GetSecondsSinceStart() const
	{
		return mTotalMS/MILLIMULTIPLIER;
	}
}
