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

	void UIDock::Initialize()
	{
		UIObject::Initialize();
	}
	
	void UIDock::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		UIObject::SetHorizontalAlignment(alignment);

		switch(m_HorizontalAlignment)
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

	}

	void UIDock::SetVerticalAlignment(VerticalAlignment alignment)
	{
		UIObject::SetVerticalAlignment(alignment);

		switch(m_VerticalAlignment)
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
	}
	
	void UIDock::AddElement(UIObject * pElement)
	{
		pElement->SetUIDock(this);
		AddChild(pElement);
	}

	void UIDock::SetDimensions(const vec2 & dimensions)
	{
		m_Dimensions = dimensions;
	}

	void UIDock::SetDimensions(float32 x, float32 y)
	{
		m_Dimensions.x = x;
		m_Dimensions.y = y;
	}

	void UIDock::SetDimensionsX(float32 x)
	{
		m_Dimensions.x = x;
	}

	void UIDock::SetDimensionsY(float32 y)
	{
		m_Dimensions.y = y;
	}

	void UIDock::Reset()
	{
		for(auto child : m_pChildren)
		{
			auto element = dynamic_cast<UIObject*>(child);
			if(element != nullptr)
			{
				element->Reset();
			}
			else
			{
				Logger::GetInstance()->Log(LogLevel::Warning,
					_T("UIDock::Reset: Object '") +
					child->GetName() + _T("' is not a UI Object."));
			}
		}
	}

	const vec2 & UIDock::GetDimensions() const
	{
		return m_Dimensions;
	}

	void UIDock::Update(const Context& context)
	{
		UIObject::Update(context);
	}

	void UIDock::Draw()
	{
		UIObject::Draw();
	}
}
