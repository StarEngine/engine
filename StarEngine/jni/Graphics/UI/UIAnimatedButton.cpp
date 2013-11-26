#include "UIAnimatedButton.h"

#include "../../Components/Graphics/SpritesheetComponent.h"
#include "../../Graphics/SpriteAnimationManager.h"

namespace star
{
	const tstring UIAnimatedButton::N_CLICK = _T("click");
	const tstring UIAnimatedButton::N_IDLE = _T("idle");
#ifdef DESKTOP
	const tstring UIAnimatedButton::N_HOVER = _T("hover");
#endif
	const tstring UIAnimatedButton::N_DISABLED = _T("disable");

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
			name + _T("_img"),
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
		if(m_pButtonSprite->GetCurrentAnimation() != N_IDLE)
		{
			if(m_ContiniousAnimation)
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					N_IDLE, m_pButtonSprite->GetCurrentFrame()))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoIdle: Animation '")
						+ N_IDLE + _T("' is not defined in the used spritesheet."));
				}
			}
			else
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					N_IDLE))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoIdle: Animation '")
						+ N_IDLE + _T("' is not defined in the used spritesheet."));
				}
			}
		}

		UIUserElement::GoIdle();
	}

#ifdef DESKTOP
	void UIAnimatedButton::GoHover()
	{
		if(m_pButtonSprite->GetCurrentAnimation() != N_HOVER)
		{
			if(m_ContiniousAnimation)
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					N_HOVER, m_pButtonSprite->GetCurrentFrame()))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoHover: Animation '")
						+ N_HOVER + _T("' is not defined in the used spritesheet."));
				}
			}
			else
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					N_HOVER))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoHover: Animation '")
						+ N_HOVER + _T("' is not defined in the used spritesheet."));
				}
			}
		}
		UIUserElement::GoHover();
	}
#endif

	void UIAnimatedButton::GoDown()
	{
		if(m_pButtonSprite->GetCurrentAnimation() != N_CLICK)
		{
			if(m_ContiniousAnimation)
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					N_CLICK, m_pButtonSprite->GetCurrentFrame()))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoDown: Animation '")
						+ N_CLICK + _T("' is not defined in the used spritesheet."));
				}
			}
			else
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					N_CLICK))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoDown: Animation '")
						+ N_CLICK + _T("' is not defined in the used spritesheet."));
				}
			}
		}
		UIUserElement::GoDown();
	}

	void UIAnimatedButton::GoFreeze()
	{
		if(m_pButtonSprite->GetCurrentAnimation() != N_DISABLED)
		{
			if(m_ContiniousAnimation)
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					N_DISABLED, m_pButtonSprite->GetCurrentFrame()))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoFreeze: Animation '")
						+ N_DISABLED + _T("' is not defined in the used spritesheet."));
				}
			}
			else
			{
				if(!m_pButtonSprite->PlayAnimationSafe(
					N_DISABLED))
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("UIAnimatedButton::GoFreeze: Animation '")
						+ N_DISABLED + _T("' is not defined in the used spritesheet."));
				}
			}
		}
		UIUserElement::GoFreeze();
	}
}
