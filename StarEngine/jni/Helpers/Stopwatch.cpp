#include "Stopwatch.h"
#include "../TimeManager.h"
#include "../Logger.h"

namespace star
{
	Stopwatch::Stopwatch()
		: m_bPaused(false)
		, m_bStarted(false)
		, m_TimePair()
		, m_Laps()
	{
	}


	Stopwatch::~Stopwatch()
	{
	}

	void Stopwatch::Start()
	{
		if(m_bStarted)
		{
			LOG(LogLevel::Warning, _T("Stopwatch::Start(): \
Stopwatch already running! Overwriting start time..."));
		}
		m_TimePair.push_back(
			std::make_pair(
				TimeManager::GetInstance()->CurrentTime(),
				Time()
				)
			);
		m_bStarted = true;
		m_bPaused = false;
	}

	void Stopwatch::Stop()
	{
		m_TimePair.back().second = TimeManager::GetInstance()->CurrentTime();
		m_bPaused = true;
		m_bStarted = false;
	}

	void Stopwatch::Reset()
	{
		m_TimePair.clear();
		m_bStarted = false;
		m_bPaused = false;
	}

	void Stopwatch::Lap()
	{
		m_Laps.push_back(GetTime());
	}

	const std::vector<Time> & Stopwatch::GetLapTimes() const
	{
		return m_Laps;
	}

	Time Stopwatch::GetTime()
	{
		Time totalTime = Time();
		if(m_bPaused)
		{
			m_TimePair.back().second = TimeManager::GetInstance()->CurrentTime();
		}
		for(auto time : m_TimePair)
		{
			totalTime += (time.second - time.first);
		}
		return totalTime;
	}
}
