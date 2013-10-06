#pragma once

#ifdef _WIN32
#include <jni/defines.h>
#else
#include <defines.h>
#include <time.h>
#endif

namespace star
{
	class TimeManager
	{
	public:
		TimeManager();
		virtual ~TimeManager(){};

		void StartMonitoring();
		void StopMonitoring();

		double GetSeconds() const;
		double GetMilliSeconds() const;
		double GetMicroSeconds() const;

		double GetSecondsSinceStart() const;
		double GetMilliSecondsSinceStart() const;

	private:
		//[COMMENT] For windows this is needed otherwise there are quite big rounding errors !
		//			I tested it with one variable but it really messed things up.
		//			Since the difference scale is 1000 or 1000 000
		//			Also calculating the time in the get functions gives very wrong results since there is no way to be sure
		//			that the 2 times are from 1 cycle. (Get can be called in a cycle which gives wrong results)
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
	};
}
