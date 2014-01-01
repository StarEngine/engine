#include "Stopwatch.h"

namespace star
{
	Stopwatch::Stopwatch()
		: m_StartTime(0)
		, m_PausedTime(0)
		, m_Laps()
	{
	}


	Stopwatch::~Stopwatch()
	{
	}

	void Stopwatch::Start()
	{
		m_StartTime = time(NULL);
	}

	void Stopwatch::Stop()
	{
		m_PausedTime = time(NULL);
	}

	void Stopwatch::Reset()
	{
		m_PausedTime = 0;
	}

	void Stopwatch::Lap()
	{
		m_Laps.push_back(GetTime());
	}

	const std::vector<float64> & Stopwatch::GetLapTimes()
	{
		return m_Laps;
	}

	float64 Stopwatch::GetTime()
	{
		return m_PausedTime == 0 ? 
			difftime(time(NULL), m_StartTime) : 
			difftime(m_PausedTime, m_StartTime);
	}
}
