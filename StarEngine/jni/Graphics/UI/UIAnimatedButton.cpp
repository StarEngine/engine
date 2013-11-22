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

	void UIAnimatedButton::Initialize()
	{
		UIUserElement::Initialize();
	}
	
	void UIAnimatedButton::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		UIElement::SetHorizontalAlignment(alignment);

		switch(m_HorizontalAlignment)
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

	void UIAnimatedButton::SetVerticalAlignment(VerticalAlignment alignment)
	{
		UIElement::SetVerticalAlignment(alignment);

		switch(m_VerticalAlignment)
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

	void UIAnimatedButton::EnableContiniousAnimation(bool enabled)
	{
		m_ContiniousAnimation = enabled;
	}

	bool UIAnimatedButton::IsContiniousAnimationEnabled() const
	{
		return m_ContiniousAnimation;
	}

	void UIAnimatedButton::Update(const Context& context)
	{
		UIUserElement::Update(context);
	}

	void UIAnimatedButton::Draw()
	{
		UIUserElement::Draw();
	}

	void UIAnimatedButton::GoIdle()
	{
		UIUserElement::GoIdle();
		if(m_pButtonSprite->GetCurrentAnimation() != N_IDLE)
		{
			if(m_ContiniousAnimation)
			{
				m_pButtonSprite->PlayAnimation(N_IDLE, m_pButtonSprite->GetCurrentFrame());
			}
			else
			{
				m_pButtonSprite->PlayAnimation(N_IDLE);
			}
		}
	}

#ifdef DESKTOP
	void UIAnimatedButton::GoHover()
	{
		UIUserElement::GoHover();
		if(m_pButtonSprite->GetCurrentAnimation() != N_HOVER)
		{
			if(m_ContiniousAnimation)
			{
				m_pButtonSprite->PlayAnimation(N_HOVER, m_pButtonSprite->GetCurrentFrame());
			}
			else
			{
				m_pButtonSprite->PlayAnimation(N_HOVER);
			}
		}
	}
#endif

	void UIAnimatedButton::GoClick()
	{
		UIUserElement::GoClick();
		if(m_pButtonSprite->GetCurrentAnimation() != N_CLICK)
		{
			if(m_ContiniousAnimation)
			{
				m_pButtonSprite->PlayAnimation(N_CLICK, m_pButtonSprite->GetCurrentFrame());
			}
			else
			{
				m_pButtonSprite->PlayAnimation(N_CLICK);
			}
		}
	}

	void UIAnimatedButton::GoDisable()
	{
		UIUserElement::GoDisable();
		if(m_pButtonSprite->GetCurrentAnimation() != N_DISABLED)
		{
			if(m_ContiniousAnimation)
			{
				m_pButtonSprite->PlayAnimation(N_DISABLED, m_pButtonSprite->GetCurrentFrame());
			}
			else
			{
				m_pButtonSprite->PlayAnimation(N_DISABLED);
			}
		}
	}

	vec2 UIAnimatedButton::GetUserElementDimensions() const
	{
		vec2 dimensions(
			float32(m_pButtonSprite->GetWidth()),
			float32(m_pButtonSprite->GetHeight())
			);
		return dimensions;
	}
}
