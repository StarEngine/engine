#pragma once

#include "..\defines.h"

#include <map>
#include <functional>

namespace star
{
	struct Context;
	class Timer;
	
	class Stopwatch final
	{
	public:
		virtual ~Stopwatch() {}

		static Stopwatch * GetInstance();

		void Update(const Context& context);

		bool CreateTimer(	const tstring & name, float targetTime, bool countingDown, 
							bool loop, std::function<void ()> func, bool paused = false);
		bool RemoveTimer(const tstring & name);
		void PauseTimer(const tstring & name, bool paused);
		void SetCountingDownTimer(const tstring & name, bool countingDown);
		void SetLoopTimer(const tstring & name, bool looping);
		void ResetTimer(const tstring & name, bool paused = false);
		void SetTargetTimeTimer(const tstring & name, float targetTime, bool reset = true, bool paused = false);
		void SetFunctionTimer(const tstring & name, std::function<void ()> func);

		int GetTimerMinutes(const tstring & name) const;
		int GetTimerSeconds(const tstring & name) const;
		int GetTimerTotalSeconds(const tstring & name) const;
		double GetTimerAccurateTime(const tstring & name) const;

	private:
		static Stopwatch *m_pStopwatch; //Singleton
		std::map<const tstring, Timer> m_TimerContainer;
		std::map<const tstring, Timer> m_GarbageContainer;
		std::map<const tstring, Timer> m_TempContainer;

		Stopwatch() {}

		Stopwatch(const Stopwatch& yRef);
		Stopwatch& operator=(const Stopwatch& yRef);
	};
}
