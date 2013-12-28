#include "TimedFadeAction.h"
#include "../Objects/Object.h"
#include "../Helpers/Math.h"
#include "../Components/Graphics/SpriteComponent.h"

namespace star
{
	TimedFadeAction::TimedFadeAction(
		float32 seconds,
		const Color & begin,
		const Color & end,
		const std::function<void()> & callback
		)
		: TimedAction(seconds, callback)
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
		const Color & end,
		const std::function<void()> & callback
		)
		: TimedAction(name, seconds, callback)
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
		ASSERT_LOG(m_pSpriteComponent != nullptr,
			_T("TimedFadeAction::Initialize: TimedFadeAction needs a SpriteComponent to work!"),
			STARENGINE_LOG_TAG);
		m_pSpriteComponent->SetColorMultiplier(m_StartColor);

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
