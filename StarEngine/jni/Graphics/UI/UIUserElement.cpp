#include "UIUserElement.h"

namespace star
{
	UIUserElement::UIUserElement(const tstring & name)
		: UIElement(name)
		, m_SelectCallback(nullptr)
#ifdef DESKTOP
		, m_HoverCallback(nullptr)
		, m_UnhoverCallback(nullptr)
#endif
		, m_ElementState(ElementStates::IDLE)
	{

	}

	UIUserElement::~UIUserElement()
	{

	}

	void UIUserElement::Initialize()
	{
		UIElement::Initialize();
	}

	void UIUserElement::Update(const Context& context)
	{
		UIElement::Update(context);
	}

	void UIUserElement::Draw()
	{
		UIElement::Draw();
	}

	bool UIUserElement::IsDisabled() const
	{
		return m_ElementState == ElementStates::DISABLED;
	}

	void UIUserElement::SetSelectCallback(std::function<void()> callback)
	{
		m_SelectCallback = callback;
	}

#ifdef DESKTOP
	void UIUserElement::SetHoverCallback(std::function<void()> callback)
	{
		m_HoverCallback = callback;
	}

	void UIUserElement::SetUnhoverCallback(std::function<void()> callback)
	{
		m_UnhoverCallback = callback;
	}
#endif
}
