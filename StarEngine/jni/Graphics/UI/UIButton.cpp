#include "UIButton.h"

#include "../../Components/Graphics/SpriteComponent.h"

namespace star
{
	UIButton::UIButton(
		const tstring & name,
		const tstring & file,
		bool isVertical
		)
		: UIUserElement(name)
		, m_IsVertical(isVertical)
		, m_pButtonSprite(nullptr)
	{
		m_pButtonSprite = new SpriteComponent(
			file, name + _T("_btn"),
			isVertical ? 1 : 4,
			isVertical ? 4 : 1
			);
		AddComponent(m_pButtonSprite);
	}

	UIButton::~UIButton(void)
	{
		
	}

	void UIButton::Initialize()
	{
		UIUserElement::Initialize();
	}

	void UIButton::Update(const Context& context)
	{
		UIUserElement::Update(context);

		m_pButtonSprite->SetCurrentSegment(
			m_IsVertical ? 0 : int32(m_ElementState),
			m_IsVertical ? int32(m_ElementState) : 0
			);
	}

	void UIButton::Draw()
	{
		UIUserElement::Draw();
	}
}
