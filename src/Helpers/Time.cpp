#include "Time.h"

namespace star
{
	const float64 Time::NANO_TO_SECONDS = 1.0e-9;
	const float64 Time::NANO_TO_MILLISECONDS = 1.0e-6;
	const float64 Time::NANO_TO_MICROSECONDS = 1.0e-3;

	Time::Time()
		: m_TimeDuration()
	{

	}

	Time::Time(const Time & t)
		: m_TimeDuration(t.m_TimeDuration)
	{

	}

	Time::Time(Time && t)
		: m_TimeDuration(t.m_TimeDuration)
	{

	}

	Time::~Time()
	{

	}

	Time & Time::operator=(const Time & t)
	{
		m_TimeDuration = t.m_TimeDuration;
		return * this;
	}

	Time & Time::operator=(Time && t)
	{
		m_TimeDuration = t.m_TimeDuration;
		return * this;
	}

	Time & Time::operator+=(const Time & t)
	{
		m_TimeDuration += t.m_TimeDuration;
		return * this;
	}

	Time & Time::operator-=(const Time & t)
	{
		m_TimeDuration -= t.m_TimeDuration;
		return * this;
	}

	Time & Time::operator*=(const std::chrono::system_clock::duration::rep & t)
	{
		m_TimeDuration *= t;
		return * this;
	}

	Time & Time::operator/=(const std::chrono::system_clock::duration::rep & t)
	{
		m_TimeDuration /= t;
		return * this;
	}

	Time & Time::operator%=(const std::chrono::system_clock::duration::rep & t)
	{
		m_TimeDuration %= t;
		return * this;
	}

	Time & Time::operator%=(const Time & t)
	{
		m_TimeDuration %= t.m_TimeDuration;
		return * this;
	}

	Time Time::operator+(const Time & t) const
	{
		Time time(*this);
		time += t;
		return time;
	}

	Time Time::operator-(const Time & t) const
	{
		Time time(*this);
		time -= t;
		return time;
	}

	Time & Time::operator++()
	{
		++m_TimeDuration;
		return * this;
	}

	Time Time::operator++(int32)
	{
		Time time(*this);
		time.m_TimeDuration++;
		return time;
	}

	Time & Time::operator--()
	{
		--m_TimeDuration;
		return * this;
	}

	Time Time::operator--(int32)
	{
		Time time(*this);
		time.m_TimeDuration--;
		return time;
	}

	float64 Time::GetHours() const
	{
		return GetSeconds() / 3600.0;
	}

	float64 Time::GetMinutes() const
	{
		return GetSeconds() / 60.0;
	}

	float64 Time::GetSeconds() const
	{
		return GetNanoSeconds() * NANO_TO_SECONDS;
	}

	float64 Time::GetMilliSeconds() const
	{
		return GetNanoSeconds() * NANO_TO_MILLISECONDS;
	}

	float64 Time::GetMicroSeconds() const
	{
		return GetNanoSeconds() * NANO_TO_MICROSECONDS;
	}

	float64 Time::GetNanoSeconds() const
	{
		return float64(std::chrono::duration_cast<std::chrono::nanoseconds>
			(m_TimeDuration).count());
	}
}
