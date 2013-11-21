#include "UIElement.h"

namespace star
{
	UIElement::UIElement(const tstring & name)
		: Object()
		, m_Name(name)
	{

	}

	UIElement::~UIElement()
	{

	}

	void UIElement::Initialize()
	{
		Object::Initialize();
	}

	void UIElement::Update(const Context& context)
	{
		Object::Update(context);
	}

	void UIElement::Draw()
	{
		Object::Draw();
	}
}
