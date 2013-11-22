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
			file, name + _T("_img"),
			isVertical ? 1 : 4,
			isVertical ? 4 : 1
			);
		m_pButtonSprite->SetHUDOptionEnabled(true);
		AddComponent(m_pButtonSprite);
	}

	UIButton::~UIButton(void)
	{
		
	}

	void UIButton::Initialize()
	{
		UIUserElement::Initialize();
	}
	
	void UIButton::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		UIElement::SetHorizontalAlignment(alignment);

		switch(m_HorizontalAlignment)
		{
			case HorizontalAlignment::Left:
				GetTransform()->SetCenterX(0);
				break;
			case HorizontalAlignment::Center:
				GetTransform()->SetCenterX(
					float32(m_pButtonSprite->GetWidth()) / 2.0f
					);
				break;
			case HorizontalAlignment::Right:
				GetTransform()->SetCenterX(
					float32(m_pButtonSprite->GetWidth())
					);
				break;
		}

	}

	void UIButton::SetVerticalAlignment(VerticalAlignment alignment)
	{
		UIElement::SetVerticalAlignment(alignment);

		switch(m_VerticalAlignment)
		{
			case VerticalAlignment::Bottom:
				GetTransform()->SetCenterY(0);
				break;
			case VerticalAlignment::Center:
				GetTransform()->SetCenterY(
					float32(m_pButtonSprite->GetHeight()) / 2.0f
					);
				break;
			case VerticalAlignment::Top:
				GetTransform()->SetCenterY(
					float32(m_pButtonSprite->GetHeight())
					);
				break;
		}
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

	vec2 UIButton::GetUserElementDimensions() const
	{
		vec2 dimensions(
			float32(m_pButtonSprite->GetWidth()),
			float32(m_pButtonSprite->GetHeight())
			);
		return dimensions;
	}
}
