#include "UIImage.h"
#include "../../Components/Graphics/SpriteComponent.h"

namespace star
{
	UIImage::UIImage(
		const tstring & name,
		const tstring & filePath,
		const tstring & imageName,
		uint32 horizontalSegements,
		uint32 verticalSegments
		)
		: UIElement(name)
	{
		m_pSprite = 
			new SpriteComponent(
			filePath,
			imageName,
			horizontalSegements,
			verticalSegments
			);
		m_pSprite->SetHUDOptionEnabled(true);
		
		AddComponent(m_pSprite);
	}

	UIImage::~UIImage(void)
	{

	}
	
	void UIImage::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		switch(alignment)
		{
			case HorizontalAlignment::Left:
				GetTransform()->SetCenterX(0);
				break;
			case HorizontalAlignment::Center:
				GetTransform()->SetCenterX(
					float32(m_pSprite->GetWidth()) / 2.0f
					);
				break;
			case HorizontalAlignment::Right:
				GetTransform()->SetCenterX(
					float32(m_pSprite->GetWidth())
					);
				break;
		}

		UIElement::SetHorizontalAlignment(alignment);
	}

	void UIImage::SetVerticalAlignment(VerticalAlignment alignment)
	{
		switch(alignment)
		{
			case VerticalAlignment::Bottom:
				GetTransform()->SetCenterY(0);
				break;
			case VerticalAlignment::Center:
				GetTransform()->SetCenterY(
					float32(m_pSprite->GetHeight()) / 2.0f
					);
				break;
			case VerticalAlignment::Top:
				GetTransform()->SetCenterY(
					float32(m_pSprite->GetHeight())
					);
				break;
		}

		UIElement::SetVerticalAlignment(alignment);
	}

	void UIImage::SetCurrentSegement(uint32 segmentX, uint32 segmentY)
	{
		m_pSprite->SetCurrentSegment(segmentX, segmentY);
	}

	void UIImage::SetColorMultiplier(const Color & color)
	{
		m_pSprite->SetColorMultiplier(color);
	}

	vec2 UIImage::GetDimensions() const
	{
		return vec2(
			m_pSprite->GetWidth(),
			m_pSprite->GetHeight()
			);
	}
}