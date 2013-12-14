#pragma once

#include "TimedAction.h"

namespace star
{
	class ScaleAction : public TimedAction
	{
	public:
		ScaleAction(
				float32 seconds,
				float32 begin,
				float32 end,
				const std::function<void()> & callback = nullptr
				);
	
		ScaleAction(
				const tstring & name,
				float32 seconds,
				float32 begin,
				float32 end,
				const std::function<void()> & callback = nullptr
				);
	
		virtual ~ScaleAction(void);
	
		virtual void Restart();
	
	protected:
		virtual void Update(const Context& context);
	
		float32 m_CurrentSeconds,
				m_BeginValue,
				m_EndValue;
	
	private:
		ScaleAction & operator=(const ScaleAction&);
		ScaleAction & operator=(ScaleAction&&);
		ScaleAction(const ScaleAction&);
		ScaleAction(ScaleAction&&);
	};
}
