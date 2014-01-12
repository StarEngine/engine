#include "UIUserElement.h"
#include "../../Input/InputManager.h"
#include "../../Scenes/BaseScene.h"
#include "../../Sound/AudioManager.h"

namespace star
{
	UIUserElement::UIUserElement(const tstring & name)
		: UIObject(name)
		, m_ReleasedCallback(nullptr)
		, m_DownCallback(nullptr)
		, m_HoverCallback(nullptr)
		, m_UnhoverCallback(nullptr)
		, m_ElementState(ElementStates::IDLE)
	{
		m_Effects[HOVER_EFFECT].name = EMPTY_STRING;
		m_Effects[HOVER_EFFECT].volume = 1.0f;

		m_Effects[CLICK_EFFECT].name = EMPTY_STRING;
		m_Effects[CLICK_EFFECT].volume = 1.0f;
	}

	UIUserElement::~UIUserElement()
	{

	}
	
	void UIUserElement::SetLocked(bool locked)
	{
		bool isUnlocking =
			!locked && m_ElementState == ElementStates::LOCKED;
		m_ElementState = 
			locked ?
			ElementStates::LOCKED :
			ElementStates::IDLE;
		if(isUnlocking)
		{
			if(m_ReleasedCallback)
			{
				m_ReleasedCallback();
			}
			Reset();
		}
	}
	
	void UIUserElement::SetUIDisabled(bool disable)
	{
		//Use the 1 frame action here? seems safer imo
		GetScene()->GetTimerManager()->CreateTimer(
			m_UniqueUIObjectID + _T("_") + _T("DisableTimer"),
			TIMER_ONE_FRAME_DELAY,
			false,
			false,
			[&, disable]()
			{
				bool isEnabling =
					!disable && m_ElementState == ElementStates::DISABLED;
				auto elementAdress = &m_ElementState;
				m_ElementState = 
					disable ?
					ElementStates::DISABLED :
					ElementStates::IDLE;
				if(isEnabling)
				{
					GoIdle();
					return;
				}
				GoDisable();
			},
			false
			);
	}

	void UIUserElement::SetHoverSoundEffect(const tstring & name)
	{
		m_Effects[HOVER_EFFECT].name = name;
	}

	void UIUserElement::SetHoverSoundEffect(const tstring & name, float32 volume)
	{
		m_Effects[HOVER_EFFECT].name = name;
		m_Effects[HOVER_EFFECT].volume = volume;
	}

	void UIUserElement::SetClickSoundEffect(const tstring & name)
	{
		m_Effects[CLICK_EFFECT].name = name;
	}

	void UIUserElement::SetClickSoundEffect(const tstring & name, float32 volume)
	{
		m_Effects[CLICK_EFFECT].name = name;
		m_Effects[CLICK_EFFECT].volume = volume;
	}

	void UIUserElement::Update(const Context& context)
	{
		if(m_ElementState != ElementStates::DISABLED
			&& m_ElementState != ElementStates::LOCKED)
		{
			if(IsFingerWithinRange())
			{
				if(m_ElementState != ElementStates::CLICK
					&& InputManager::GetInstance()->IsFingerPressedCP(0))
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
					Reset();
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
			
			UIObject::Update(context);
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
		
		if(m_Effects[HOVER_EFFECT].name != EMPTY_STRING)
		{
			AudioManager::GetInstance()->PlayEffect(
				m_Effects[HOVER_EFFECT].name,
				m_Effects[HOVER_EFFECT].volume,
				0
				);
		}

		GetScene()->GetTimerManager()->CreateTimer(
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
		GetScene()->GetTimerManager()->CreateTimer(
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
		if(m_ReleasedCallback != nullptr)
		{
			m_ReleasedCallback();
		}

		if(m_Effects[CLICK_EFFECT].name != EMPTY_STRING)
		{
			AudioManager::GetInstance()->PlayEffect(
				m_Effects[CLICK_EFFECT].name,
				m_Effects[CLICK_EFFECT].volume,
				0
				);
		}

		GetScene()->GetTimerManager()->CreateTimer(
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

	bool UIUserElement::IsFingerWithinRange() const
	{
		auto fingerPos = InputManager::GetInstance()->GetCurrentFingerPosCP(0);
		auto buttonPos = GetTransform()->GetWorldPosition().pos2D();
		auto dimensions = GetDimensions();
		auto scale = GetTransform()->GetWorldScale();
		
		dimensions.x *= scale.x;
		dimensions.y *= scale.y;
		
		return 
			fingerPos.x >= buttonPos.x &&
			fingerPos.x <= buttonPos.x + dimensions.x &&
			fingerPos.y >= buttonPos.y &&
			fingerPos.y <= buttonPos.y + dimensions.y;
	}

	void UIUserElement::Reset()
	{
		if(m_ElementState != ElementStates::DISABLED)
		{
			GoIdle();
			m_ElementState = ElementStates::IDLE;
		}
		UIObject::Reset();
	}

	void UIUserElement::SetReleasedCallback(std::function<void()> callback)
	{
		m_ReleasedCallback = callback;
	}

	void UIUserElement::SetDownCallback(std::function<void()> callback)
	{
		m_DownCallback = callback;
	}

	void UIUserElement::SetHoverCallback(std::function<void()> callback)
	{
		m_HoverCallback = callback;
	}

	void UIUserElement::SetUnhoverCallback(std::function<void()> callback)
	{
		m_UnhoverCallback = callback;
	}

	bool UIUserElement::IsIdle() const
	{
		return m_ElementState == ElementStates::IDLE;
	}

	bool UIUserElement::IsHover() const
	{
		return m_ElementState == ElementStates::HOVER;
	}

	bool UIUserElement::IsDown() const
	{
		return m_ElementState == ElementStates::CLICK;
	}
}
