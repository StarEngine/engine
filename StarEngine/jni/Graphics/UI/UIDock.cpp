#include "UIDock.h"
#include "UIElement.h"

#include "../GraphicsManager.h"

namespace star
{
	UIDock::UIDock(const tstring & name)
		: UIObject(name)
		, m_Dimensions(
			GraphicsManager::GetInstance()->GetScreenResolution().x,
			GraphicsManager::GetInstance()->GetScreenResolution().y)
	{

	}

	UIDock::UIDock(
			const tstring & name,
			float32 width,
			float32 height
			)
		: UIObject(name)
		, m_Dimensions(width, height)
	{

	}

	UIDock::~UIDock(void)
	{

	}
	
	void UIDock::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		switch(alignment)
		{
			case HorizontalAlignment::Left:
				GetTransform()->SetCenterX(0);
				break;
			case HorizontalAlignment::Center:
				GetTransform()->SetCenterX(
					m_Dimensions.x / 2.0f
					);
				break;
			case HorizontalAlignment::Right:
				GetTransform()->SetCenterX(
					m_Dimensions.x
					);
				break;
		}

		UIObject::SetHorizontalAlignment(alignment);
	}

	void UIDock::SetVerticalAlignment(VerticalAlignment alignment)
	{
		switch(alignment)
		{
			case VerticalAlignment::Bottom:
				GetTransform()->SetCenterY(0);
				break;
			case VerticalAlignment::Center:
				GetTransform()->SetCenterY(
					m_Dimensions.y / 2.0f
					);
				break;
			case VerticalAlignment::Top:
				GetTransform()->SetCenterY(
					m_Dimensions.y
					);
				break;

		}
		UIObject::SetVerticalAlignment(alignment);
	}

	void UIDock::SetDimensions(const vec2 & dimensions)
	{
		m_Dimensions = dimensions;
		RepositionChildren();
	}

	void UIDock::SetDimensions(float32 x, float32 y)
	{
		m_Dimensions.x = x;
		m_Dimensions.y = y;
		RepositionChildren();
	}

	void UIDock::SetDimensionsX(float32 x)
	{
		m_Dimensions.x = x;
		RepositionChildren();
	}

	void UIDock::SetDimensionsY(float32 y)
	{
		m_Dimensions.y = y;
		RepositionChildren();
	}

	vec2 UIDock::GetDimensions() const
	{
		return m_Dimensions;
	}
}
