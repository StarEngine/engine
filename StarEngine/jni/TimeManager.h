#pragma once

#include "defines.h"

#ifndef _WIN32
#include <time.h>
#endif

namespace star
{
	const double NSMULTIPLIER = 1.0e-9;
	const double MICROMULTIPLIER = 1000000.0;
	const double MILLIMULTIPLIER = 1000.0;
	const double SECONDMULTIPLIER = 1.0;

	class TimeManager final
	{
	public:
		TimeManager();
		~TimeManager();

		void StartMonitoring();
		void StopMonitoring();

		double GetSeconds() const;
		double GetMilliSeconds() const;
		double GetMicroSeconds() const;

		double GetSecondsSinceStart() const;
		double GetMilliSecondsSinceStart() const;

		tstring GetTimeStamp();

	private:
#ifdef _WIN32

		LARGE_INTEGER	mFrequency;
		LARGE_INTEGER	mF1,
						mF2;
#else
		double 	mF1,
				mF2;
		float mElapsed;
#endif

		double	mDeltaMs,
				mDeltaS,
				mDeltauS;

		double	mTotalMS;

		TimeManager(const TimeManager& t);
		TimeManager(TimeManager&& t);
		TimeManager& operator=(const TimeManager& t);
		TimeManager& operator=(TimeManager&& t);
	};
}
