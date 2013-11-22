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

		if(m_ElementState != ElementStates::DISABLED)
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
							GetScene()->GetStopwatch()->CreateTimer(
								m_Name.GetTag() + _T("click_timer"),
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
		}
	}

	void UIUserElement::Draw()
	{
		UIElement::Draw();
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

	bool UIUserElement::IsFingerWithinRange() const
	{
		auto fingerPos = InputManager::GetInstance()->GetCurrentFingerPosCP(0);
		auto buttonPos = GetTransform()->GetWorldPosition().pos2D();
		auto dimensions = GetUserElementDimensions();
		
		return 
			fingerPos.x >= buttonPos.x &&
			fingerPos.x <= buttonPos.x + dimensions.x &&
			fingerPos.y >= buttonPos.y &&
			fingerPos.y <= buttonPos.y + dimensions.y;
	}

	bool UIUserElement::IsDisabled() const
	{
		return m_ElementState == ElementStates::DISABLED;
	}
	
	void UIUserElement::SetDisabled(bool disabled)
	{
		if(disabled && m_ElementState != ElementStates::DISABLED)
		{
			GoDisable();
		}
		m_ElementState = disabled ?
			ElementStates::DISABLED : ElementStates::IDLE;
	}

	void UIUserElement::Reset()
	{
		UIObject::Reset();

		GetScene()->GetStopwatch()->RemoveTimer(
			m_Name.GetTag() + _T("click_timer")
			);

		m_ElementState = ElementStates::IDLE;
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
