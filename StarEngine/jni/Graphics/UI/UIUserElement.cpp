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

	void UIUserElement::Update(const Context& context)
	{
		if(!IsDisabled())
		{
			if(IsFingerWithinRange())
			{
				if(m_ElementState != ElementStates::CLICK)
				{
					if(InputManager::GetInstance()->IsFingerPressedCP(0))
					{
						if(m_ElementState != ElementStates::CLICK)
						{
							m_ElementState = ElementStates::CLICK;
							GoClick();
							GetScene()->GetStopwatch()->RemoveTimer(
								m_Name.GetTag() + _T("_click_timer")
								);
							GetScene()->GetStopwatch()->CreateTimer(
								m_Name.GetTag() + _T("_click_timer"),
								0.25f, false, false, [&]() {
								#ifdef DESKTOP
									GoHover();
									m_ElementState = ElementStates::HOVER;
								#else
									GoIdle();
									m_ElementState = ElementStates::IDLE;
								#endif
								});
						}
					}
				#ifdef DESKTOP
					else if(m_ElementState != ElementStates::HOVER)
					{
						m_ElementState = ElementStates::HOVER;
						GoHover();
					}
				#endif
				}
			}
			else if(m_ElementState != ElementStates::IDLE)
			{
				m_ElementState = ElementStates::IDLE;
				GoIdle();
			}

			UIElement::Update(context);
		}
	}

	void UIUserElement::GoIdle()
	{
#ifdef DESKTOP
		if(m_UnhoverCallback != nullptr)
		{
			m_UnhoverCallback();
		}
#endif
	}

#ifdef DESKTOP
	void UIUserElement::GoHover()
	{
		if(m_HoverCallback != nullptr)
		{
			m_HoverCallback();
		}
	}
#endif

	void UIUserElement::GoClick()
	{
		if(m_SelectCallback != nullptr)
		{
			m_SelectCallback();
		}
	}

	void UIUserElement::GoDisable()
	{

	}

	void UIUserElement::GoFreeze()
	{

	}

	bool UIUserElement::IsFingerWithinRange() const
	{
		auto fingerPos = InputManager::GetInstance()->GetCurrentFingerPosCP(0);
		auto buttonPos = GetTransform()->GetWorldPosition().pos2D();
		auto dimensions = GetDimensions();
		
		return 
			fingerPos.x >= buttonPos.x &&
			fingerPos.x <= buttonPos.x + dimensions.x &&
			fingerPos.y >= buttonPos.y &&
			fingerPos.y <= buttonPos.y + dimensions.y;
	}
	
	void UIUserElement::SetDisabled(bool disabled)
	{
		if(disabled && !IsDisabled())
		{
			GoDisable();
		}

		UIElement::SetDisabled(disabled);
	}

	void UIUserElement::Reset()
	{
		GetScene()->GetStopwatch()->RemoveTimer(
			m_Name.GetTag() + _T("_click_timer")
			);

		m_ElementState = ElementStates::IDLE;

		UIObject::Reset();
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
