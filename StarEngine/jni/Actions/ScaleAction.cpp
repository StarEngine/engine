#include "ScaleAction.h"
#include "../Objects/Object.h"
#include "../Helpers/Math.h"

namespace star
{
	ScaleAction::ScaleAction(
		float32 seconds,
		float32 begin,
		float32 end,
		const std::function<void()> & callback
		)
		: TimedAction(seconds, callback)
		, m_BeginValue(begin)
		, m_EndValue(end)
		, m_CurrentSeconds(0)
	{
	}
	
	ScaleAction::ScaleAction(
		const tstring & name,
		float32 seconds,
		float32 begin,
		float32 end,
		const std::function<void()> & callback
		)
		: TimedAction(name, seconds, callback)
		, m_BeginValue(begin)
		, m_EndValue(end)
		, m_CurrentSeconds(0)
	{
	}
	
	ScaleAction::~ScaleAction()
	{	
	}
	
	void ScaleAction::Update(const Context & context)
	{
		float32 dt = float32(context.time->DeltaTime().GetSeconds());
		m_CurrentSeconds += dt;
		
		m_pParent->GetTransform()->Scale
			(
			star::Lerp(m_BeginValue, m_EndValue, m_CurrentSeconds / m_Seconds)
			);
	}
	
	void ScaleAction::Restart()
	{
		m_CurrentSeconds = 0;
	}
}
