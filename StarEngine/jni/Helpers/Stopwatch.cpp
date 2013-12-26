#include "Stopwatch.h"
#include "Timer.h"
#include "../Context.h"
#include <algorithm>

#include "../Logger.h"

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
		for(auto& it : m_GarbageContainer)
		{
			m_TimerContainer.erase(it.first);
		}
		m_GarbageContainer.clear();

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

	bool Stopwatch::CreateTimer(	const tstring & name, float32 targetTime,
									bool countingDown, bool loop,
									std::function<void ()> func, bool paused)
	{
		for(auto& it : m_TimerContainer)
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
		m_TimerContainer[name] = newTimer;
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
		LOG(LogLevel::Warning,
			_T("Stopwatch::RemoveTimer: trying to remove unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
		return false;
	}

	void Stopwatch::PauseTimer(const tstring & name, bool paused)
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetPaused(paused);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::PauseTimer: trying to pause unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void Stopwatch::SetCountingDownTimer(const tstring & name, bool countingDown)
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetCountingDown(countingDown);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::SetCountingDownTimer: trying to adjust unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void Stopwatch::SetLoopTimer(const tstring & name, bool looping)
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetLoop(looping);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::SetLoopTimer: trying to adjust unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void Stopwatch::ResetTimer(const tstring & name, bool paused)
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.Reset(paused);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::ResetTimer: trying to reset unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void Stopwatch::SetTargetTimeTimer(const tstring & name, float32 targetTime, bool reset, bool paused)
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetTargetTime(targetTime, reset, paused);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::SetTargetTimeTimer: trying to adjust unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void Stopwatch::SetFunctionTimer(const tstring & name, const std::function<void ()> & func)
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetFunction(func);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::SetFunctionTimer: trying to adjust unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	float64 Stopwatch::ForceEndTimer(const tstring & name)
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.ForceEnd();
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::ForceEndTimer: trying to end unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
		return 0;
	}
	
	void Stopwatch::ForwardTimer(const tstring & name, float64 time)
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.Forward(time);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::ForwardTimer: trying to forward unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void Stopwatch::ForwardAllTimers(float64 time)
	{
		for(auto& it : m_TimerContainer)
		{
			it.second.Forward(time);
		}
	}

	int32 Stopwatch::GetTimerMinutes(const tstring & name) const
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentMinutes();
			}
		}
		LOG(LogLevel::Warning, 
			_T("GetTimerMinutes: Couldn't find the timer '") + name + _T("'."),
			STARENGINE_LOG_TAG);
		return 0;
	}

	int32 Stopwatch::GetTimerSeconds(const tstring & name) const
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentSeconds();
			}
		}
		LOG(LogLevel::Warning, 
			_T("GetTimerSeconds: Couldn't find the timer '") + name + _T("'."),
			STARENGINE_LOG_TAG);
		return 0;
	}

	int32 Stopwatch::GetTimerTotalSeconds(const tstring & name) const
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentTotalSeconds();
			}
		}
		LOG(LogLevel::Warning, 
			_T("GetTimerTotalSeconds: Couldn't find the timer '") + name + _T("'."),
			STARENGINE_LOG_TAG);
		return 0;
	}
	
	float64 Stopwatch::GetTimerTargetTime(const tstring & name) const
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetTargetTime();
			}
		}
		LOG(LogLevel::Warning,
			_T("Stopwatch::GetTimerTargetTime: trying to access unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
		return 0;
	}

	float64 Stopwatch::GetTimerAccurateTime(const tstring & name) const
	{
		for(auto& it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentAccurateTime();
			}
		}
		LOG(LogLevel::Warning, 
			_T("GetTimerAccurateTime: Couldn't find the timer '") + name + _T("'."),
			STARENGINE_LOG_TAG);
		return 0;
	}
}
