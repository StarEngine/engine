#include "TimerManager.h"
#include "Timer.h"
#include "../Context.h"
#include <algorithm>

#include "../Logger.h"

namespace star
{
	TimerManager::TimerManager()
	{

	}

	TimerManager::~TimerManager()
	{

	}

	void TimerManager::Update(const Context& context)
	{
		//clean up the trash
		for(auto & it : m_GarbageContainer)
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

	bool TimerManager::CreateTimer(	const tstring & name, float32 targetTime,
									bool countingDown, bool loop,
									std::function<void ()> func, bool paused)
	{
		for(auto & it : m_TimerContainer)
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

	bool TimerManager::RemoveTimer(const tstring & name)
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
			_T("TimerManager::RemoveTimer: trying to remove unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
		return false;
	}

	void TimerManager::PauseTimer(const tstring & name, bool paused)
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetPaused(paused);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::PauseTimer: trying to pause unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void TimerManager::SetCountingDownTimer(const tstring & name, bool countingDown)
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetCountingDown(countingDown);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::SetCountingDownTimer: trying to adjust unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void TimerManager::SetLoopTimer(const tstring & name, bool looping)
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetLoop(looping);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::SetLoopTimer: trying to adjust unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void TimerManager::ResetTimer(const tstring & name, bool paused)
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.Reset(paused);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::ResetTimer: trying to reset unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void TimerManager::SetTargetTimeTimer(const tstring & name, float32 targetTime, bool reset, bool paused)
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetTargetTime(targetTime, reset, paused);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::SetTargetTimeTimer: trying to adjust unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void TimerManager::SetFunctionTimer(const tstring & name, const std::function<void ()> & func)
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.SetFunction(func);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::SetFunctionTimer: trying to adjust unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	float64 TimerManager::ForceEndTimer(const tstring & name)
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.ForceEnd();
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::ForceEndTimer: trying to end unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
		return 0;
	}
	
	void TimerManager::ForwardTimer(const tstring & name, float64 time)
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				it.second.Forward(time);
				return;
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::ForwardTimer: trying to forward unknown timer '")
			+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void TimerManager::ForwardAllTimers(float64 time)
	{
		for(auto & it : m_TimerContainer)
		{
			it.second.Forward(time);
		}
	}

	int32 TimerManager::GetTimerMinutes(const tstring & name) const
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentMinutes();
			}
		}
		LOG(LogLevel::Warning, 
			_T("TimerManager::GetTimerMinutes: Couldn't find the timer '")
				+ name + _T("'."),
			STARENGINE_LOG_TAG);
		return 0;
	}

	int32 TimerManager::GetTimerSeconds(const tstring & name) const
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentSeconds();
			}
		}
		LOG(LogLevel::Warning, 
			_T("TimerManager::GetTimerSeconds: Couldn't find the timer '")
				+ name + _T("'."),
			STARENGINE_LOG_TAG);
		return 0;
	}

	int32 TimerManager::GetTimerTotalSeconds(const tstring & name) const
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentTotalSeconds();
			}
		}
		LOG(LogLevel::Warning, 
			_T("TimerManager::GetTimerTotalSeconds: Couldn't find the timer '")
				+ name + _T("'."),
			STARENGINE_LOG_TAG);
		return 0;
	}
	
	float64 TimerManager::GetTimerTargetTime(const tstring & name) const
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetTargetTime();
			}
		}
		LOG(LogLevel::Warning,
			_T("TimerManager::GetTimerTargetTime: trying to access unknown timer '")
				+ name + _T("'."), STARENGINE_LOG_TAG);
		return 0;
	}

	float64 TimerManager::GetTimerAccurateTime(const tstring & name) const
	{
		for(auto & it : m_TimerContainer)
		{
			if(it.first == name)
			{
				return it.second.GetCurrentAccurateTime();
			}
		}
		LOG(LogLevel::Warning, 
			_T("TimerManager::GetTimerAccurateTime: Couldn't find the timer '")
				+ name + _T("'."),
			STARENGINE_LOG_TAG);
		return 0;
	}
}
