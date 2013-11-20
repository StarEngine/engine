#include "TimeManager.h"
#include "Logger.h"
#include "Helpers\Helpers.h"

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

	TimeManager::~TimeManager()
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

	float64 TimeManager::GetSeconds() const
	{
		return mDeltaS;
	}

	float64 TimeManager::GetMilliSeconds() const
	{
		return mDeltaMs;
	}

	float64 TimeManager::GetMicroSeconds() const
	{
		return mDeltauS;
	}

	float64 TimeManager::GetMilliSecondsSinceStart() const
	{
		return mTotalMS;
	}

	tstring TimeManager::GetTimeStamp()
	{
		int32 totalSeconds = int32(mTotalMS / 1000);
		int32 seconds = totalSeconds % 60;
		int32 minutes = totalSeconds / 60;
		int32 hours = totalSeconds / 3600;

		tstringstream strstr;
		if(hours < 10)
		{
			strstr << _T("0");
		}
		strstr << hours << _T(":");
		if(minutes < 10)
		{
			strstr << _T("0");
		}
		strstr << minutes << _T(":");
		if(seconds < 10)
		{
			strstr << _T("0");
		}
		strstr << seconds;

		return strstr.str();
	}

	float64 TimeManager::GetSecondsSinceStart() const
	{
		return mTotalMS / MILLIMULTIPLIER;
	}
}
