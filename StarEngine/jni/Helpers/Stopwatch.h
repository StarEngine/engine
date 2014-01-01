#pragma once
#include "../Entity.h"
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

		void Update(const Context & context);

	private:
		float64 m_ElapsedTime;
		std::vector<float64> m_Laps;
		bool m_Active;
	};
}
