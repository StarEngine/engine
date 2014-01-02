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

	Time::~Time()
	{

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

	int64 Time::GetNanoSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>
			(m_TimeDuration).count();
	}
}
