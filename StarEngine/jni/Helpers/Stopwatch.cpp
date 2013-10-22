#include "Stopwatch.h"
#include "Timer.h"
#include "../Context.h"
#include <algorithm>

#ifdef _DEBUG
#include "../Logger.h"
#endif

namespace star
{
	Stopwatch::Stopwatch()
	{

	}

	Stopwatch::~Stopwatch()
	{

	}

	void Stopwatch::Update(const Context& context)
	{
		//clean up the trash
		for(auto it : m_GarbageContainer)
		{
			m_TimerContainer.erase(it.first);
		}
		m_GarbageContainer.clear();

		//add new timers
		for(auto it : m_TempContainer)
		{
			m_TimerContainer[it.first] = it.second;
		}
		m_TempContainer.clear();

		for(auto it = m_TimerContainer.begin() ; it != m_TimerContainer.end() ; ) 
		{
			if (it->second.Update(context)) 
			{
				m_TimerContainer.erase(it++);
			} 
			else 
			{
				++it;
			}
		}
	}

	bool Stopwatch::CreateTimer(	const tstring & name, float targetTime,
									bool countingDown, bool loop,
									std::function<void ()> func, bool paused)
	{
		for(auto it : m_TempContainer)
		{
			if(it.first == name)
			{
				return false;
			}
		}

		for (auto it = m_TimerContainer.begin(); it != m_TimerContainer.end() ; ++it)
		{
			if(it->first == name)
			{
				m_GarbageContainer[it->first] = it->second;
				break;
			}
		}

		Timer newTimer(targetTime, countingDown, loop, func, paused);
		m_TempContainer[name] = newTimer;
		return true;
	}

	bool Stopwatch::RemoveTimer(const tstring & name)
	{
		for (auto it = m_TimerContainer.begin(); it != m_TimerContainer.end() ; ++it)
		{
			if (it->first == name)
			{
				m_GarbageContainer[it->first] = it->second;
				return true;
			}
		}
		return false;
	}

	void Stopwatch::PauseTimer(const tstring & name, bool paused)
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetPaused(paused);
				return;
			}
		}
	}

	void Stopwatch::SetCountingDownTimer(const tstring & name, bool countingDown)
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetCountingDown(countingDown);
				return;
			}
		}
	}

	void Stopwatch::SetLoopTimer(const tstring & name, bool looping)
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetLoop(looping);
				return;
			}
		}
	}

	void Stopwatch::ResetTimer(const tstring & name, bool paused)
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.Reset(paused);
				return;
			}
		}
	}

	void Stopwatch::SetTargetTimeTimer(const tstring & name, float targetTime, bool reset, bool paused)
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetTargetTime(paused);
				return;
			}
		}
	}

	void Stopwatch::SetFunctionTimer(const tstring & name, std::function<void ()> func)
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetFunction(func);
				return;
			}
		}
	}

	int Stopwatch::GetTimerMinutes(const tstring & name) const
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentMinutes();
			}
		}
#ifdef _DEBUG
		Logger::GetInstance()->Log(LogLevel::Warning, 
			_T("GetTimerMinutes: Couldn't find the timer '") + name + _T("'."));
#endif
		return 0;
	}

	int Stopwatch::GetTimerSeconds(const tstring & name) const
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentSeconds();
			}
		}
#ifdef _DEBUG
		Logger::GetInstance()->Log(LogLevel::Warning, 
			_T("GetTimerSeconds: Couldn't find the timer '") + name + _T("'."));
#endif
		return 0;
	}

	int Stopwatch::GetTimerTotalSeconds(const tstring & name) const
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentTotalSeconds();
			}
		}
#ifdef _DEBUG
		Logger::GetInstance()->Log(LogLevel::Warning, 
			_T("GetTimerTotalSeconds: Couldn't find the timer '") + name + _T("'."));
#endif
		return 0;
	}

	double Stopwatch::GetTimerAccurateTime(const tstring & name) const
	{
		for(auto it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentAccurateTime();
			}
		}
#ifdef _DEBUG
		Logger::GetInstance()->Log(LogLevel::Warning, 
			_T("GetTimerAccurateTime: Couldn't find the timer '") + name + _T("'."));
#endif
		return 0;
	}
}
