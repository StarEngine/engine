#include "UIUserElement.h"
#include "../../Input/InputManager.h"
#include "../../Scenes/BaseScene.h"

namespace star
{
	UIUserElement::UIUserElement(const tstring & name)
		: UIElement(name)
		, m_SelectCallback(nullptr)
		, m_DownCallback(nullptr)
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
				if(m_ElementState != ElementStates::CLICK
					&& InputManager::GetInstance()->IsFingerDownCP(0))
				{
					if(!GetScene()->IsActiveCursorLocked())
					{
						m_ElementState = ElementStates::CLICK;
						GoDown();
					}
				}
				else if(m_ElementState == ElementStates::CLICK
				&& InputManager::GetInstance()->IsFingerReleasedCP(0))
				{
					GoUp();
				#ifdef DESKTOP
					m_ElementState = ElementStates::HOVER;
				#else
					m_ElementState = ElementStates::IDLE;
				#endif
				}
			#ifdef DESKTOP
				else if(m_ElementState == ElementStates::IDLE
					&& !GetScene()->IsActiveCursorLocked())
				{
					m_ElementState = ElementStates::HOVER;
					GoHover();
				}
			#endif
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
		GetScene()->SetStateActiveCursor(UI_STATE_IDLE);
	}

#ifdef DESKTOP
	void UIUserElement::GoHover()
	{
		if(m_HoverCallback != nullptr)
		{
			m_HoverCallback();
		}

		GetScene()->GetStopwatch()->CreateTimer(
			_T("HCT"),
			0.1f,
			false,
			false,
			[&] ()
			{
				GetScene()->SetStateActiveCursor(UI_STATE_HOVER);
			}, false);
	}
#endif
	void UIUserElement::GoDown()
	{
		GetScene()->GetStopwatch()->CreateTimer(
			_T("HCT"),
			0.1f,
			false,
			false,
			[&] ()
			{
				GetScene()->SetStateActiveCursor(UI_STATE_CLICK);
			}, false);
		if(m_DownCallback != nullptr)
		{
			m_DownCallback();
		}
	}

	void UIUserElement::GoUp()
	{
		if(m_SelectCallback != nullptr)
		{
			m_SelectCallback();
		}
		GetScene()->GetStopwatch()->CreateTimer(
			_T("HCT"),
			0.1f,
			false,
			false,
			[&] ()
			{
				GetScene()->SetStateActiveCursor(UI_STATE_HOVER);
			}, false);
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
		GoIdle();
		m_ElementState = ElementStates::IDLE;
		UIObject::Reset();
	}

	void UIUserElement::SetSelectCallback(std::function<void()> callback)
	{
		m_SelectCallback = callback;
	}

	void UIUserElement::SetDownCallback(std::function<void()> callback)
	{
		m_DownCallback = callback;
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

	bool UIUserElement::IsIdle() const
	{
		return m_ElementState == ElementStates::IDLE;
	}

#ifdef DESKTOP
	bool UIUserElement::IsHover() const
	{
		return m_ElementState == ElementStates::HOVER;
	}

#endif
	bool UIUserElement::IsDown() const
	{
		return m_ElementState == ElementStates::CLICK;
	}
}
