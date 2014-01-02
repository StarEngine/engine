#pragma once
#include "../defines.h"
#include "Time.h"
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
		const std::vector<Time> & GetLapTimes() const;
		Time GetTime() const;

	private:
		Time m_StartTime;
		Time m_PausedTime;
		std::vector<Time> m_Laps;

		Stopwatch(const Stopwatch& yRef);
		Stopwatch(Stopwatch&& yRef);
		Stopwatch& operator=(const Stopwatch& yRef);
		Stopwatch& operator=(Stopwatch&& yRef);
	};
}
