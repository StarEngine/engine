#pragma once

#include "defines.h"

#ifndef _WIN32
#include <time.h>
#endif

namespace star
{
	const float64 NSMULTIPLIER = 1.0e-9;
	const float64 MICROMULTIPLIER = 1000000.0;
	const float64 MILLIMULTIPLIER = 1000.0;
	const float64 SECONDMULTIPLIER = 1.0;

	class TimeManager final
	{
	public:
		TimeManager();
		~TimeManager();

		void StartMonitoring();
		void StopMonitoring();

		float64 GetSeconds() const;
		float64 GetMilliSeconds() const;
		float64 GetMicroSeconds() const;

		float64 GetSecondsSinceStart() const;
		float64 GetMilliSecondsSinceStart() const;

		tstring GetTimeStamp();

	private:
#ifdef _WIN32

		LARGE_INTEGER	mFrequency;
		LARGE_INTEGER	mF1,
						mF2;
#else
		float64 	mF1,
				mF2;
		float32 mElapsed;
#endif

		float64	mDeltaMs,
				mDeltaS,
				mDeltauS;

		float64	mTotalMS;

		TimeManager(const TimeManager& t);
		TimeManager(TimeManager&& t);
		TimeManager& operator=(const TimeManager& t);
		TimeManager& operator=(TimeManager&& t);
	};
}
