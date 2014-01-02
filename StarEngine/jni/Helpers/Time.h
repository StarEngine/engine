#pragma once
#include "../defines.h"

#include <chrono>
namespace star
{
	class Time final
	{
	public:
		Time();
		~Time();
		float64 GetSeconds() const;
		float64 GetMilliSeconds() const;
		float64 GetMicroSeconds() const;
		int64 GetNanoSeconds() const;

	private:
		friend class TimeManager;
		std::chrono::system_clock::duration m_TimeDuration;

		static const float64 NANO_TO_SECONDS;
		static const float64 NANO_TO_MILLISECONDS;
		static const float64 NANO_TO_MICROSECONDS;

		Time(const Time& t);
		Time(Time&& t);
		Time& operator=(const Time& t);
		Time& operator=(Time&& t);
	};
}
