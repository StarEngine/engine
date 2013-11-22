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
		
		AddComponent(m_pSprite);
	}

	UIImage::~UIImage(void)
	{

	}

	void UIImage::Initialize()
	{
		UIElement::Initialize();
	}
	
	void UIImage::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		UIElement::SetHorizontalAlignment(alignment);

		switch(m_HorizontalAlignment)
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

	}

	void UIImage::SetVerticalAlignment(VerticalAlignment alignment)
	{
		UIElement::SetVerticalAlignment(alignment);

		switch(m_VerticalAlignment)
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
	}

	void UIImage::SetCurrentHorizontalSegement(uint32 segment)
	{
		m_pSprite->SetCurrentHorizontalSegment(segment);
	}

	void UIImage::SetCurrentVerticalSegement(uint32 segment)
	{
		m_pSprite->SetCurrentVerticalSegment(segment);
	}

	void UIImage::SetCurrentSegement(uint32 segmentX, uint32 segmentY)
	{
		m_pSprite->SetCurrentSegment(segmentX, segmentY);
	}

	void UIImage::Update(const Context& context)
	{
		UIElement::Update(context);
	}

	void UIImage::Draw()
	{
		UIElement::Draw();
	}
}