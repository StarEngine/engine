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

	void UIButton::Initialize()
	{
		UIStaticButton::Initialize();
		GoIdle();
	}

	void UIButton::GoIdle()
	{
		UIUserElement::GoIdle();

		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : int8(m_ElementState),
			m_IsVertical ? int8(m_ElementState) : 0
			);
	}

#ifdef DESKTOP
	void UIButton::GoHover()
	{
		UIUserElement::GoHover();

		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : int8(m_ElementState),
			m_IsVertical ? int8(m_ElementState) : 0
			);
	}
#endif

	void UIButton::GoClick()
	{
		UIUserElement::GoClick();

		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : int8(m_ElementState),
			m_IsVertical ? int8(m_ElementState) : 0
			);
	}

	void UIButton::GoFreeze()
	{
		UIUserElement::GoFreeze();

		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : DISABLE_STATE_ID,
			m_IsVertical ? DISABLE_STATE_ID : 0
			);
	}
}
