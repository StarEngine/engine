#include "UIButton.h"

#include "../../Components/Graphics/SpriteComponent.h"

namespace star
{
	UIButton::UIButton(
		const tstring & name,
		const tstring & file,
		bool isVertical
		)
		: UIStaticButton(
			name,
			file,
			isVertical ? 1 : 4,
			isVertical ? 4 : 1
			)
		, m_IsVertical(isVertical)
	{
	}

	UIButton::~UIButton(void)
	{
		
	}

	void UIButton::AfterInitialized()
	{
		GoIdle();
		UIStaticButton::AfterInitialized();
	}

	void UIButton::GoIdle()
	{
		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : int8(m_ElementState),
			m_IsVertical ? int8(m_ElementState) : 0
			);
		UIUserElement::GoIdle();
	}

#ifdef DESKTOP
	void UIButton::GoHover()
	{
		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : int8(m_ElementState),
			m_IsVertical ? int8(m_ElementState) : 0
			);
		UIUserElement::GoHover();
	}
#endif

	void UIButton::GoDown()
	{
		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : int8(m_ElementState),
			m_IsVertical ? int8(m_ElementState) : 0
			);
		UIUserElement::GoDown();
	}

	void UIButton::GoFreeze()
	{
		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : DISABLE_STATE_ID,
			m_IsVertical ? DISABLE_STATE_ID : 0
			);
		UIUserElement::GoFreeze();
	}
}
