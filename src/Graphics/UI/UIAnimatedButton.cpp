#include "UIAnimatedButton.h"

#include "../../Components/Graphics/SpriteSheetComponent.h"
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
		m_pButtonSprite = new SpriteSheetComponent(
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
		m_pButtonSprite = new SpriteSheetComponent(
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
	
	void UIAnimatedButton::SetHorizontalAlignment(
		HorizontalAlignment alignment,
		bool redefineCenter
		)
	{
		if(redefineCenter)
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
		}

		UIObject::SetHorizontalAlignment(
			alignment,
			redefineCenter
			);
	}

	void UIAnimatedButton::SetVerticalAlignment(
		VerticalAlignment alignment,
		bool redefineCenter
		)
	{
		if(redefineCenter)
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
		}

		UIObject::SetVerticalAlignment(
			alignment,
			redefineCenter
			);
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
				m_pButtonSprite->PlayAnimation(
					UI_STATE_IDLE, 
					m_pButtonSprite->GetCurrentFrame()
					);
			}
			else
			{
				m_pButtonSprite->PlayAnimation(
					UI_STATE_IDLE
					);
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
				m_pButtonSprite->PlayAnimation(
					UI_STATE_HOVER, 
					m_pButtonSprite->GetCurrentFrame()
					);
			}
			else
			{
				m_pButtonSprite->PlayAnimation(
					UI_STATE_HOVER
					);
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
				m_pButtonSprite->PlayAnimation(
					UI_STATE_CLICK, m_pButtonSprite->GetCurrentFrame()
					);
			}
			else
			{
				m_pButtonSprite->PlayAnimation(
					UI_STATE_CLICK
					);
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
				m_pButtonSprite->PlayAnimation(
					UI_STATE_DISABLE, 
					m_pButtonSprite->GetCurrentFrame()
					);
			}
			else
			{
				m_pButtonSprite->PlayAnimation(
					UI_STATE_DISABLE
					);
			}
		}
		UIUserElement::GoDisable();
	}
}
