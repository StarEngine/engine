#include "TimedAction.h"
#include "../Helpers/Helpers.h"
#include "../Objects/Object.h"
#include "../Scenes/BaseScene.h"

namespace star
{
	uint64 TimedAction::ID_COUNTER = 0;

	TimedAction::TimedAction(
		float32 seconds,
		const std::function<void()> & callback
		)
		: Action()
		, m_UniqueID(_T("TA_"))
		, m_Seconds(seconds)
		, m_Callback(callback)
	{
		m_UniqueID += string_cast<tstring>(ID_COUNTER++);
	}

	TimedAction::TimedAction(
		const tstring & name,
		float32 seconds,
		const std::function<void()> & callback
		)
		: Action(name)
		, m_UniqueID(_T("TA_"))
		, m_Seconds(seconds)
		, m_Callback(callback)
	{
		m_UniqueID += string_cast<tstring>(ID_COUNTER++);
	}

	TimedAction::~TimedAction()
	{

	}

	void TimedAction::Initialize()
	{
		m_pParent->GetScene()->GetTimerManager()->CreateTimer(
			m_UniqueID, m_Seconds, false, false,
			[&] () {
				if(m_Callback)
				{
					m_Callback();
					}
				Destroy();
			});
	}

	void TimedAction::Restart()
	{
		m_pParent->GetScene()->GetTimerManager()->ResetTimer(
			m_UniqueID,
			false
			);
	}

	void TimedAction::Pause()
	{
		m_pParent->GetScene()->GetTimerManager()->PauseTimer(
			m_UniqueID,
			true
			);
	}

	void TimedAction::Resume()
	{
		m_pParent->GetScene()->GetTimerManager()->PauseTimer(
			m_UniqueID,
			false
			);
	}
		
	void TimedAction::SetCallback(const std::function<void()> & callback)
	{
		m_Callback = callback;
		if(m_pParent && m_pParent->GetScene())
		{
			m_pParent->GetScene()->GetTimerManager()->SetFunctionTimer(
				m_UniqueID,
				m_Callback
				);
		}
	}
}
