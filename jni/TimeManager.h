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
		double GetMiliSeconds() const;
		double GetMicroSeconds() const;

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

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		TimeManager(const TimeManager& t);
		TimeManager& operator=(const TimeManager& t);
	};
}
