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
		Timer(	float64 targetTime, bool countingDown, bool loop,
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
		void SetTargetTime(float64 targetTime, bool reset = true, bool paused = false);
		void SetFunction(std::function<void ()> func);
		float64 ForceEnd();
		void Forward(float64 time);

		int32 GetCurrentMinutes() const;
		int32 GetCurrentSeconds() const;
		int32 GetCurrentTotalSeconds() const;
		float64 GetTargetTime() const;
		float64 GetCurrentAccurateTime() const;

	private:
		float64	m_TargetTime,
				m_CurrentTime;
		bool	m_CountingDown,
				m_Looping,
				m_Paused,
				m_Infinite;
		std::function<void ()> m_ExcecutingFunction;
	};
}
