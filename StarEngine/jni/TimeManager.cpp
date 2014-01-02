#include "TimeManager.h"
#include "Logger.h"
#include "Helpers\Helpers.h"

namespace star
{
	std::shared_ptr<TimeManager> TimeManager::m_TimeManager = nullptr;
	std::shared_ptr<TimeManager> TimeManager::GetInstance()
	{
		if(m_TimeManager == nullptr)
		{
			m_TimeManager = std::shared_ptr<TimeManager>(new TimeManager());
		}
		return m_TimeManager;
	}

	TimeManager::TimeManager()
		: m_StartTime()
		, m_DeltaTime()
		, m_ElapsedTime()
		, m_CurrentTime()
	{

	}

	TimeManager::~TimeManager()
	{

	}

	const Time & TimeManager::DeltaTime()
	{
		return m_DeltaTime;
	}

	const Time & TimeManager::TimeSinceStart()
	{
		return m_ElapsedTime;
	}

	const Time & TimeManager::CurrentTime()
	{
		m_CurrentTime.m_TimeDuration = 
			std::chrono::high_resolution_clock::now().time_since_epoch();
		return m_CurrentTime;
	}

	void TimeManager::StartMonitoring()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}

	void TimeManager::StopMonitoring()
	{
		auto endTime = std::chrono::high_resolution_clock::now();
		m_DeltaTime.m_TimeDuration = endTime - m_StartTime;
		m_ElapsedTime += m_DeltaTime;
	}

	tstring TimeManager::GetTimeStamp()
	{
		int32 totalSeconds = int32(m_ElapsedTime.GetSeconds());
		int32 seconds = totalSeconds % 60;
		int32 minutes = totalSeconds / 60;
		int32 hours = totalSeconds / 3600;

		tstringstream strstr;
		if(hours < 10)
		{
			strstr << _T("0");
		}
		strstr << hours << _T(":");
		if(minutes < 10)
		{
			strstr << _T("0");
		}
		strstr << minutes << _T(":");
		if(seconds < 10)
		{
			strstr << _T("0");
		}
		strstr << seconds;

		return strstr.str();
	}


}
