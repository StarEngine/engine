#include "TimedFadeAction.h"
#include "../Objects/Object.h"
#include "../Helpers/Math.h"
#include "../Components/Graphics/SpriteComponent.h"

namespace star
{
	TimedFadeAction::TimedFadeAction(
		float32 seconds,
		const Color & begin,
		const Color & end
		)
		: TimedAction(seconds)
		, m_StartColor(begin)
		, m_EndColor(end)
		, m_CurrentSeconds(0)
		, m_pSpriteComponent(nullptr)
	{

	}

	TimedFadeAction::TimedFadeAction(
		const tstring & name,
		float32 seconds,
		const Color & begin,
		const Color & end
		)
		: TimedAction(name, seconds)
		, m_StartColor(begin)
		, m_EndColor(end)
		, m_CurrentSeconds(0)
		, m_pSpriteComponent(nullptr)
	{

	}

	TimedFadeAction::~TimedFadeAction()
	{

	}

	void TimedFadeAction::Initialize()
	{
		m_pSpriteComponent = m_pParent->GetComponent<SpriteComponent>();
		Logger::GetInstance()->Log(m_pSpriteComponent != nullptr,
			_T("TimedFadeAction::Initialize: TimedFadeAction needs a SpriteComponent to work!"));
		m_pSpriteComponent->SetColorMultiplier(m_StartColor);
		m_Callback = [&] () 
		{
			m_pSpriteComponent->SetColorMultiplier(m_EndColor);
		};

		TimedAction::Initialize();
	}

	void TimedFadeAction::Update(const Context & context)
	{
		float32 dt = float32(context.mTimeManager->GetSeconds());
		m_CurrentSeconds += dt;
		m_pSpriteComponent->SetColorMultiplier(
			Lerp(m_StartColor, m_EndColor, m_CurrentSeconds / m_Seconds)
			);
	}

	void TimedFadeAction::Restart()
	{
		m_pSpriteComponent->SetColorMultiplier(m_StartColor);
		m_CurrentSeconds = 0;
	}
}
