#include "UIElement.h"

namespace star
{
	UIElement::UIElement(const tstring & name)
		: UIObject(name)
	{

	}

	UIElement::~UIElement()
	{

	}

	void UIElement::Initialize()
	{
		UIObject::Initialize();
	}

	void UIElement::Update(const Context& context)
	{
		UIObject::Update(context);
	}

	void UIElement::Draw()
	{
		UIObject::Draw();
	}
}
