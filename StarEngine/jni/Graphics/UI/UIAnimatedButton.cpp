#include "UIAnimatedButton.h"

#include "../../Components/Graphics/SpritesheetComponent.h"
#include "../../Graphics/SpriteAnimationManager.h"

namespace star
{
	UIAnimatedButton::UIAnimatedButton(
		const tstring & name,
		const tstring & file,
		const tstring & spritesheet
		)
		: UIUserElement(name)
		, m_pButtonSprite(nullptr)
	{
		m_pButtonSprite = new SpritesheetComponent(
			file,
			name,
			spritesheet
			);
		m_pButtonSprite->SetHUDOptionEnabled(true);
		AddComponent(m_pButtonSprite);
	}

	UIAnimatedButton::UIAnimatedButton(
		const tstring & name,
		const tstring & file,
		const tstring & spriteName,
		const tstring & spritesheet
		)
		: UIUserElement(name)
		, m_pButtonSprite(nullptr)
	{
		m_pButtonSprite = new SpritesheetComponent(
			file,
			spriteName,
			spritesheet
			);
		m_pButtonSprite->SetHUDOptionEnabled(true);
		AddComponent(m_pButtonSprite);
	}

	UIAnimatedButton::~UIAnimatedButton(void)
	{
		
	}

	void UIAnimatedButton::AfterInitialized()
	{
		GoIdle();

		UIUserElement::AfterInitialized();
	}
	
	void UIAnimatedButton::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		switch(alignment)
		{
			case HorizontalAlignment::Left:
				GetTransform()->SetCenterX(0);
				break;
			case HorizontalAlignment::Center:
				GetTransform()->SetCenterX(
					float32(m_pButtonSprite->GetWidth()) / 2.0f
					);
				break;
			case HorizontalAlignment::Right:
				GetTransform()->SetCenterX(
					float32(m_pButtonSprite->GetWidth())
					);
				break;
		}

		UIElement::SetHorizontalAlignment(alignment);
	}

	void UIAnimatedButton::SetVerticalAlignment(VerticalAlignment alignment)
	{
		switch(alignment)
		{
			case VerticalAlignment::Bottom:
				GetTransform()->SetCenterY(0);
				break;
			case VerticalAlignment::Center:
				GetTransform()->SetCenterY(
					float32(m_pButtonSprite->GetHeight()) / 2.0f
					);
				break;
			case VerticalAlignment::Top:
				GetTransform()->SetCenterY(
					float32(m_pButtonSprite->GetHeight())
					);
				break;
		}

		UIElement::SetVerticalAlignment(alignment);
	}

	void UIAnimatedButton::EnableContiniousAnimation(bool enabled)
	{
		m_ContiniousAnimation = enabled;
	}

	bool UIAnimatedButton::IsContiniousAnimationEnabled() const
	{
		return m_ContiniousAnimation;
	}

	vec2 UIAnimatedButton::GetDimensions() const
	{
		return vec2(m_pButtonSprite->GetWidth(), m_pButtonSprite->GetHeight());
	}

	void UIAnimatedButton::GoIdle()
	{
		if(m_pButtonSprite->GetCurrentAnimation() != UI_STATE_IDLE)
		{
			if(m_ContiniousAnimation)
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					UI_STATE_IDLE, m_pButtonSprite->GetCurrentFrame()))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoIdle: Animation '")
						+ tstring(UI_STATE_IDLE) +
						_T("' is not defined in the used spritesheet."),
						STARENGINE_LOG_TAG);
				}
			}
			else
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					UI_STATE_IDLE))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoIdle: Animation '")
						+ tstring(UI_STATE_IDLE) +
						_T("' is not defined in the used spritesheet."),
						STARENGINE_LOG_TAG);
				}
			}
		}

		UIUserElement::GoIdle();
	}

#ifdef DESKTOP
	void UIAnimatedButton::GoHover()
	{
		if(m_pButtonSprite->GetCurrentAnimation() != UI_STATE_HOVER)
		{
			if(m_ContiniousAnimation)
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					UI_STATE_HOVER, m_pButtonSprite->GetCurrentFrame()))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoHover: Animation '")
						+ tstring(UI_STATE_HOVER) +
						_T("' is not defined in the used spritesheet."),
						STARENGINE_LOG_TAG);
				}
			}
			else
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					UI_STATE_HOVER))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoHover: Animation '")
						+ tstring(UI_STATE_HOVER) +
						_T("' is not defined in the used spritesheet."),
						STARENGINE_LOG_TAG);
				}
			}
		}
		UIUserElement::GoHover();
	}
#endif

	void UIAnimatedButton::GoDown()
	{
		if(m_pButtonSprite->GetCurrentAnimation() != UI_STATE_CLICK)
		{
			if(m_ContiniousAnimation)
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					UI_STATE_CLICK, m_pButtonSprite->GetCurrentFrame()))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoDown: Animation '")
						+ tstring(UI_STATE_CLICK) +
						_T("' is not defined in the used spritesheet."),
						STARENGINE_LOG_TAG);
				}
			}
			else
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					UI_STATE_CLICK))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoDown: Animation '")
						+ tstring(UI_STATE_CLICK) +
						_T("' is not defined in the used spritesheet."),
						STARENGINE_LOG_TAG);
				}
			}
		}
		UIUserElement::GoDown();
	}

	void UIAnimatedButton::GoDisable()
	{
		if(m_pButtonSprite->GetCurrentAnimation() != UI_STATE_DISABLE)
		{
			if(m_ContiniousAnimation)
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					UI_STATE_DISABLE, m_pButtonSprite->GetCurrentFrame()))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoDisable: Animation '")
						+ tstring(UI_STATE_DISABLE) +
						_T("' is not defined in the used spritesheet."),
						STARENGINE_LOG_TAG);
				}
			}
			else
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					UI_STATE_DISABLE))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoFreeze: Animation '")
						+ tstring(UI_STATE_DISABLE) +
						_T("' is not defined in the used spritesheet."),
						STARENGINE_LOG_TAG);
				}
			}
		}
		UIUserElement::GoDisable();
	}
}
