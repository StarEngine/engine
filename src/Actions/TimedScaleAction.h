#pragma once

#include "TimedAction.h"

namespace star
{
	class TimedScaleAction : public TimedAction
	{
	public:
		TimedScaleAction(
				float32 seconds,
				float32 begin,
				float32 end,
				const std::function<void()> & callback = nullptr
				);
	
		TimedScaleAction(
				const tstring & name,
				float32 seconds,
				float32 begin,
				float32 end,
				const std::function<void()> & callback = nullptr
				);
	
		virtual ~TimedScaleAction(void);
	
		virtual void Restart();
	
	protected:
		virtual void Update(const Context& context);
	
		float32 m_CurrentSeconds,
				m_BeginValue,
				m_EndValue;
	
	private:
		TimedScaleAction & operator=(const TimedScaleAction&);
		TimedScaleAction & operator=(TimedScaleAction&&);
		TimedScaleAction(const TimedScaleAction&);
		TimedScaleAction(TimedScaleAction&&);
	};
}
