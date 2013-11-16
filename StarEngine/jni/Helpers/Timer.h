#pragma once

#include "../defines.h"
#include <functional>

namespace star
{
	struct Context;

	class Timer final
	{
	public:
		Timer();
		Timer(	double targetTime, bool countingDown, bool loop,
				std::function<void ()> func, bool paused = false);
		~Timer();
		Timer(const Timer& yRef);
		Timer(Timer&& yRef);

		Timer& operator=(const Timer& yRef);
		Timer& operator=(Timer&& yRef);

		bool Update(const Context& context);
		void SetPaused(bool paused);
		void SetCountingDown(bool countingDown);
		void SetLoop(bool looping);
		void Reset(bool paused = false);
		void SetTargetTime(double targetTime, bool reset = true, bool paused = false);
		void SetFunction(std::function<void ()> func);

		int GetCurrentMinutes() const;
		int GetCurrentSeconds() const;
		int GetCurrentTotalSeconds() const;
		double GetTargetTime() const;
		double GetCurrentAccurateTime() const;

	private:
		double	m_TargetTime,
				m_CurrentTime;
		bool	m_CountingDown,
				m_Looping,
				m_Paused,
				m_Infinite;
		std::function<void ()> m_ExcecutingFunction;
	};
}
