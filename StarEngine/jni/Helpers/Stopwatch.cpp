#include "Stopwatch.h"
#include "../TimeManager.h"

namespace star
{
	Stopwatch::Stopwatch()
		: m_StartTime()
		, m_PausedTime()
		, m_Laps()
	{
	}


	Stopwatch::~Stopwatch()
	{
	}

	void Stopwatch::Start()
	{
		m_StartTime = TimeManager::GetInstance()->CurrentTime();
	}

	void Stopwatch::Stop()
	{
		m_PausedTime = TimeManager::GetInstance()->CurrentTime();
	}

	void Stopwatch::Reset()
	{

	}

	void Stopwatch::Lap()
	{
		m_Laps.push_back(GetTime());
	}

	const std::vector<Time> & Stopwatch::GetLapTimes() const
	{
		return m_Laps;
	}

	Time Stopwatch::GetTime() const
	{
		return m_PausedTime - m_StartTime;
	}
}
