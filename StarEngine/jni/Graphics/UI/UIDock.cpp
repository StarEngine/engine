#include "UIDock.h"
#include "UIElement.h"

#include "../GraphicsManager.h"

namespace star
{
	UIDock::UIDock(const tstring & name)
		: UIElement(name)
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
		: UIElement(name)
		, m_Dimensions(width, height)
	{

	}

	UIDock::~UIDock(void)
	{

	}

	void UIDock::Initialize()
	{
		UIElement::Initialize();
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

	const vec2 & UIDock::GetDimensions() const
	{
		return m_Dimensions;
	}

	void UIDock::Update(const Context& context)
	{
		UIElement::Update(context);
	}

	void UIDock::Draw()
	{
		UIElement::Draw();
	}
}
