#include "Stopwatch.h"
#include "../Context.h"

namespace star
{
	Stopwatch::Stopwatch()
		: m_ElapsedTime(0)
		, m_Laps()
		, m_Active(false)
	{
	}


	Stopwatch::~Stopwatch()
	{
	}

	void Stopwatch::Start()
	{
		m_Active = true;
	}

	void Stopwatch::Stop()
	{
		m_Active = false;
	}

	void Stopwatch::Reset()
	{
		m_ElapsedTime = 0;
		m_Active = false;
	}

	void Stopwatch::Lap()
	{
		m_Laps.push_back(m_ElapsedTime);
	}

	const std::vector<float64> & Stopwatch::GetLapTimes()
	{
		return m_Laps;
	}

	float64 Stopwatch::GetTime()
	{
		return m_ElapsedTime;
	}

	void Stopwatch::Update(const Context & context)
	{
		if(m_Active)
		{
			m_ElapsedTime += context.mTimeManager->GetMicroSeconds();
		}
	}
}
