#include "UIStaticButton.h"

#include "../../Components/Graphics/SpriteComponent.h"

namespace star
{
	UIStaticButton::UIStaticButton(
		const tstring & name,
		const tstring & file,
		uint32 widthSegements,
		uint32 heightSegements
		)
		: UIUserElement(name)
		, m_pButtonSprite(nullptr)
	{
		m_pButtonSprite = new SpriteComponent(
			file, name + _T("_img"),
			widthSegements,
			heightSegements
			);
		m_pButtonSprite->SetHUDOptionEnabled(true);
		AddComponent(m_pButtonSprite);
	}

	UIStaticButton::~UIStaticButton(void)
	{
		
	}

	void UIStaticButton::Initialize()
	{
		UIUserElement::Initialize();
	}
	
	void UIStaticButton::SetHorizontalAlignment(HorizontalAlignment alignment)
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

	void UIStaticButton::SetVerticalAlignment(VerticalAlignment alignment)
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

	void UIStaticButton::SetCurrentHorizontalSegement(uint32 segment)
	{
		m_pButtonSprite->SetCurrentHorizontalSegment(segment);
	}

	void UIStaticButton::SetCurrentVerticalSegement(uint32 segment)
	{
		m_pButtonSprite->SetCurrentVerticalSegment(segment);
	}

	void UIStaticButton::SetCurrentSegement(uint32 segmentX, uint32 segmentY)
	{
		m_pButtonSprite->SetCurrentSegment(segmentX, segmentY);
	}

	void UIStaticButton::Update(const Context& context)
	{
		UIUserElement::Update(context);
	}

	void UIStaticButton::Draw()
	{
		UIUserElement::Draw();
	}

	vec2 UIStaticButton::GetUserElementDimensions() const
	{
		vec2 dimensions(
			float32(m_pButtonSprite->GetWidth()),
			float32(m_pButtonSprite->GetHeight())
			);
		return dimensions;
	}
}
