#pragma once

#include "../defines.h"

#include <map>
#include <functional>

namespace star
{
	struct Context;
	class Timer;
	
	class Stopwatch final
	{
	public:
		Stopwatch();
		~Stopwatch();

		void Update(const Context& context);

		bool CreateTimer(	const tstring & name, float32 targetTime, bool countingDown, 
							bool loop, std::function<void ()> func, bool paused = false);
		bool RemoveTimer(const tstring & name);
		void PauseTimer(const tstring & name, bool paused);
		void SetCountingDownTimer(const tstring & name, bool countingDown);
		void SetLoopTimer(const tstring & name, bool looping);
		void ResetTimer(const tstring & name, bool paused = false);
		void SetTargetTimeTimer(const tstring & name, float32 targetTime, bool reset = true, bool paused = false);
		void SetFunctionTimer(const tstring & name, std::function<void ()> func);
		float64 ForceEndTimer(const tstring & name);
		void ForwardTimer(const tstring & name, float64 time);
		void ForwardAllTimers(float64 time);

		int32 GetTimerMinutes(const tstring & name) const;
		int32 GetTimerSeconds(const tstring & name) const;
		int32 GetTimerTotalSeconds(const tstring & name) const;
		float64 GetTimerTargetTime(const tstring & name) const;
		float64 GetTimerAccurateTime(const tstring & name) const;

	private:
		std::map<const tstring, Timer> m_TimerContainer;
		std::map<const tstring, Timer> m_GarbageContainer;
		std::map<const tstring, Timer> m_TempContainer;

		Stopwatch(const Stopwatch& yRef);
		Stopwatch(Stopwatch&& yRef);
		Stopwatch& operator=(const Stopwatch& yRef);
		Stopwatch& operator=(Stopwatch&& yRef);
	};
}
