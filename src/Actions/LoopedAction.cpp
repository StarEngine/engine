#include "LoopedAction.h"
#include "../Helpers/Helpers.h"
#include "../Objects/Object.h"
#include "../Scenes/BaseScene.h"

namespace star
{
	uint64 LoopedAction::ID_COUNTER = 0;

	LoopedAction::LoopedAction(float32 seconds)
		: Action()
		, m_UniqueID(_T("LA_"))
		, m_Seconds(seconds)
		, m_Callback(nullptr)
	{
		m_UniqueID += string_cast<tstring>(ID_COUNTER++);
	}

	LoopedAction::LoopedAction(
		const tstring & name,
		float32 seconds
		)
		: Action(name)
		, m_UniqueID(_T("LA_"))
		, m_Seconds(seconds)
		, m_Callback(nullptr)
	{
		m_UniqueID += string_cast<tstring>(ID_COUNTER++);
	}

	LoopedAction::~LoopedAction()
	{

	}

	void LoopedAction::Initialize()
	{
		m_pParent->GetScene()->GetTimerManager()->CreateTimer(
			m_UniqueID, m_Seconds, false, true,
			[&] () {
				if(m_Callback)
				{
					m_Callback();
				}
			});
	}

	void LoopedAction::Restart()
	{
		m_pParent->GetScene()->GetTimerManager()->ResetTimer(
			m_UniqueID,
			false
			);
	}

	void LoopedAction::Pause()
	{
		m_pParent->GetScene()->GetTimerManager()->PauseTimer(
			m_UniqueID,
			true
			);
	}

	void LoopedAction::Resume()
	{
		m_pParent->GetScene()->GetTimerManager()->PauseTimer(
			m_UniqueID,
			false
			);
	}
}
