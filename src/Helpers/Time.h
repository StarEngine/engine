#pragma once
#include "../defines.h"

#include <chrono>
namespace star
{
	class Time final
	{
	public:
		Time();
		Time(const Time & t);
		Time(Time && t);

		~Time();
	
		Time & operator=(const Time & t);
		Time & operator=(Time && t);

		Time & operator+=(const Time & t);
		Time & operator-=(const Time & t);
		Time & operator*=(const std::chrono::system_clock::duration::rep & t);
		Time & operator/=(const std::chrono::system_clock::duration::rep & t);
		Time & operator%=(const std::chrono::system_clock::duration::rep & t);
		Time & operator%=(const Time & t);

		Time operator+(const Time & t) const;
		Time operator-(const Time & t) const;

		Time & operator++();
		Time operator++(int32 t);
		Time & operator--();
		Time operator--(int32 t);

		float64 GetHours() const;
		float64 GetMinutes() const;
		float64 GetSeconds() const;
		float64 GetMilliSeconds() const;
		float64 GetMicroSeconds() const;
		float64 GetNanoSeconds() const;

	private:
		friend class TimeManager;
		friend class Stopwatch;

		std::chrono::system_clock::duration m_TimeDuration;

		static const float64 NANO_TO_SECONDS;
		static const float64 NANO_TO_MILLISECONDS;
		static const float64 NANO_TO_MICROSECONDS;
	};
}
