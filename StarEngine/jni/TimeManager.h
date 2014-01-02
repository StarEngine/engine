#pragma once

#include "defines.h"
#include <memory>
#include "Helpers\Time.h"

#include <chrono>

namespace star
{
	class TimeManager final
	{
	public:
		static std::shared_ptr<TimeManager> GetInstance();
		~TimeManager();

		void StartMonitoring();
		void StopMonitoring();

		const Time & DeltaTime();
		const Time & TimeSinceStart();
		const Time & CurrentTime();

		tstring GetTimeStamp();

	private:
		static std::shared_ptr<TimeManager> m_TimeManager;
		TimeManager();

		std::chrono::system_clock::time_point m_StartTime;
		Time m_DeltaTime;
		Time m_ElapsedTime;
		Time m_CurrentTime;

		TimeManager(const TimeManager& t);
		TimeManager(TimeManager&& t);
		TimeManager& operator=(const TimeManager& t);
		TimeManager& operator=(TimeManager&& t);
	};
}
