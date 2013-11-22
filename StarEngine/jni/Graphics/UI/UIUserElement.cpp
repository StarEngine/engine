#include "UIUserElement.h"
#include "../../Input/InputManager.h"

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

		if(m_ElementState != ElementStates::DISABLED
			&& m_ElementState != ElementStates::CLICK)
		{
			if(IsFingerWithinRange())
			{
				if(InputManager::GetInstance()->IsFingerPressedCP(0))
				{
					m_ElementState = ElementStates::CLICK;
					if(m_SelectCallback != nullptr)
					{
						m_SelectCallback();
					}
					GetScene()->GetStopwatch()->CreateTimer(
						m_Name.GetTag() + _T("click_timer"),
						0.5f, false, false, [&]() {
							m_ElementState = ElementStates::HOVER;
						});
				}
				else if(m_ElementState != ElementStates::HOVER)
				{
					m_ElementState = ElementStates::HOVER;
					if(m_HoverCallback != nullptr)
					{
						m_HoverCallback();
					}
				}
			}
			else if(m_ElementState != ElementStates::IDLE)
			{
				m_ElementState = ElementStates::IDLE;
				if(m_UnhoverCallback != nullptr)
				{
					m_UnhoverCallback();
				}
			}
		}
	}

	void UIUserElement::Draw()
	{
		UIElement::Draw();
	}

	bool UIUserElement::IsFingerWithinRange() const
	{
		auto fingerPos = InputManager::GetInstance()->GetCurrentFingerPosCP(0);
		auto buttonPos = GetLeftCorner();
		auto dimensions = GetUserElementDimensions();
		
		return 
			fingerPos.x >= buttonPos.x &&
			fingerPos.x <= buttonPos.x + dimensions.x &&
			fingerPos.y >= buttonPos.y &&
			fingerPos.y <= buttonPos.y + dimensions.y;
	}
	
	vec2 UIUserElement::GetLeftCorner() const
	{
		vec2 leftCorner = GetTransform()->GetWorldPosition().pos2D();
		auto dimensions = GetUserElementDimensions();
		
		switch(m_HorizontalAlignment)
		{
			case HorizontalAlignment::Center:
				leftCorner.x -= dimensions.x / 2.0f;
				break;
			case HorizontalAlignment::Right:
				leftCorner.x -= dimensions.x;
				break;
		}

		switch(m_VerticalAlignment)
		{
		case VerticalAlignment::Center:
				leftCorner.y -= dimensions.y / 2.0f;
				break;
			case VerticalAlignment::Top:
				leftCorner.y -= dimensions.y;
				break;
		}

		return leftCorner;
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
