#include "Stopwatch.h"
#include "../TimeManager.h"
#include "../Logger.h"

namespace star
{
	Stopwatch::Stopwatch()
		: m_bPaused(false)
		, m_bStarted(false)
		, m_TimePairVec()
		, m_Laps()
	{
	}

	Stopwatch::Stopwatch(const Stopwatch & yRef)
		: m_bPaused(yRef.m_bPaused)
		, m_bStarted(yRef.m_bStarted)
		, m_TimePairVec(yRef.m_TimePairVec)
		, m_Laps(yRef.m_Laps)
	{
	}

	Stopwatch::Stopwatch(Stopwatch && yRef)
		: m_bPaused(std::move(yRef.m_bPaused))
		, m_bStarted(std::move(yRef.m_bStarted))
		, m_TimePairVec(std::move(yRef.m_TimePairVec))
		, m_Laps(std::move(yRef.m_Laps))
	{
	}

	Stopwatch::~Stopwatch()
	{
	}

	Stopwatch & Stopwatch::operator=(const Stopwatch & yRef)
	{
		m_bPaused = yRef.m_bPaused;
		m_bStarted = yRef.m_bStarted;
		m_TimePairVec = yRef.m_TimePairVec;
		m_Laps = yRef.m_Laps;
		return * this;
	}

	Stopwatch & Stopwatch::operator=(Stopwatch && yRef)
	{
		m_bPaused = std::move(yRef.m_bPaused);
		m_bStarted = std::move(yRef.m_bStarted);
		m_TimePairVec = std::move(yRef.m_TimePairVec);
		m_Laps = std::move(yRef.m_Laps);
		return * this;
	}

	void Stopwatch::Start()
	{
		if(m_bStarted)
		{
			LOG(LogLevel::Warning, _T("Stopwatch::Start(): \
Stopwatch already running! Overwriting start time..."), STARENGINE_LOG_TAG);
		}
		m_TimePairVec.push_back(
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
		m_TimePairVec.back().second = TimeManager::GetInstance()->CurrentTime();
		m_bPaused = true;
		m_bStarted = false;
	}

	void Stopwatch::Reset()
	{
		m_TimePairVec.clear();
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
		Time totalTime;
		if(m_bPaused)
		{
			m_TimePairVec.back().second = TimeManager::GetInstance()->CurrentTime();
		}
		for(const auto & time : m_TimePairVec)
		{
			totalTime += time.second - time.first;
		}
		return totalTime;
	}
}
