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
		//[COMMENT] Why use 3 variables for the same purpose?
		//			Right now you have 3 different members that all save the current delta time.
		//			This is waste of memory and should be avoided. Choose one and just do the 
		//			convert in the get functions, if the user asks for them.
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
