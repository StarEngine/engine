#include "DelayedAction.h"
#include "../Helpers/Helpers.h"
#include "../Objects/Object.h"
#include "../Scenes/BaseScene.h"

namespace star
{
	uint64 DelayedAction::ID_COUNTER = 0;

	DelayedAction::DelayedAction(float32 seconds)
		: Action()
		, m_UniqueID(_T("DA_"))
		, m_Seconds(seconds)
		, m_Callback(nullptr)
		, m_HasStarted(false)
	{
		m_UniqueID += string_cast<tstring>(ID_COUNTER++);
	}

	DelayedAction::DelayedAction(
		const tstring & name,
		float32 seconds
		)
		: Action(name)
		, m_UniqueID(_T("DA_"))
		, m_Seconds(seconds)
		, m_Callback(nullptr)
		, m_HasStarted(false)
	{
		m_UniqueID += string_cast<tstring>(ID_COUNTER++);
	}

	DelayedAction::~DelayedAction()
	{

	}

	void DelayedAction::Initialize()
	{
		CreateTimer();
	}

	void DelayedAction::Restart()
	{
		if(!m_HasStarted)
		{
			m_pParent->GetScene()->GetStopwatch()->ResetTimer(
				m_UniqueID,
				false
				);
		}
		else
		{
			m_HasStarted = false;
			CreateTimer();
		}
	}

	void DelayedAction::Pause()
	{
		if(!m_HasStarted)
		{
			m_pParent->GetScene()->GetStopwatch()->PauseTimer(
				m_UniqueID,
				true
				);
		}
	}

	void DelayedAction::Resume()
	{
		if(!m_HasStarted)
		{
			m_pParent->GetScene()->GetStopwatch()->PauseTimer(
				m_UniqueID,
				false
				);
		}
	}
	
	void DelayedAction::CreateTimer()
	{
		m_IsPaused = true;
		m_pParent->GetScene()->GetStopwatch()->CreateTimer(
			m_UniqueID, m_Seconds, false, false,
			[&] () {
				if(m_Callback)
				{
					m_Callback();
					m_IsPaused = false;
					m_HasStarted = true;
				}
				Destroy();
			}, false);
	}
}
