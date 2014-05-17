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
			file, name,
			widthSegements,
			heightSegements
			);
		m_pButtonSprite->SetHUDOptionEnabled(true);
		AddComponent(m_pButtonSprite);
	}

	UIStaticButton::UIStaticButton(
		const tstring & name,
		const tstring & file,
		const tstring & spriteName,
		uint32 widthSegements,
		uint32 heightSegements
		)
		: UIUserElement(name)
		, m_pButtonSprite(nullptr)
	{
		m_pButtonSprite = new SpriteComponent(
			file, spriteName,
			widthSegements,
			heightSegements
			);
		m_pButtonSprite->SetHUDOptionEnabled(true);
		AddComponent(m_pButtonSprite);
	}

	UIStaticButton::~UIStaticButton(void)
	{
		
	}
	
	void UIStaticButton::SetHorizontalAlignment(
		HorizontalAlignment alignment,
		bool redefineCenter
		)
	{
		if(redefineCenter)
		{
			switch(alignment)
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
		
		UIObject::SetHorizontalAlignment(
			alignment,
			redefineCenter
			);
	}

	void UIStaticButton::SetVerticalAlignment(
		VerticalAlignment alignment,
		bool redefineCenter
		)
	{
		if(redefineCenter)
		{
			switch(alignment)
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
		
		UIObject::SetVerticalAlignment(
			alignment,
			redefineCenter
			);
	}

	void UIStaticButton::SetCurrentSegement(uint32 segmentX, uint32 segmentY)
	{
		m_pButtonSprite->SetCurrentSegment(segmentX, segmentY);
	}

	void UIStaticButton::SetColorMultiplier(const Color & color)
	{
		m_pButtonSprite->SetColorMultiplier(color);
	}

	vec2 UIStaticButton::GetDimensions() const
	{
		return vec2(
			m_pButtonSprite->GetWidth(),
			m_pButtonSprite->GetHeight()
			);
	}
}
