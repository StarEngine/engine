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

	void UIButton::Update(const Context& context)
	{
		UIStaticButton::Update(context);

		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : int32(m_ElementState),
			m_IsVertical ? int32(m_ElementState) : 0
			);
	}
}
