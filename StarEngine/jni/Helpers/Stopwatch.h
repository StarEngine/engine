#pragma once
#include "../defines.h"
#include <vector>

namespace star
{
	class Stopwatch final
	{
	public:
		Stopwatch();
		~Stopwatch();

		void Start();
		void Stop();
		void Reset();
		void Lap();
		const std::vector<float64> & GetLapTimes();
		float64 GetTime();

	private:
		time_t m_StartTime;
		time_t m_PausedTime;
		std::vector<float64> m_Laps;
	};
}
