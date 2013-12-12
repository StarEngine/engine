#include "UIAnimatedImage.h"
#include "../../Components/Graphics/SpritesheetComponent.h"

namespace star
{
	UIAnimatedImage::UIAnimatedImage(
		const tstring & name,
		const tstring & filePath,
		const tstring & spritesheet
		)
		: UIElement(name)
	{
		m_pSprite = 
			new SpritesheetComponent(
			filePath,
			name,
			spritesheet
			);
		m_pSprite->SetHUDOptionEnabled(true);
		
		AddComponent(m_pSprite);
	}

	UIAnimatedImage::UIAnimatedImage(
		const tstring & name,
		const tstring & filePath,
		const tstring & spriteName,
		const tstring & spritesheet
		)
		: UIElement(name)
	{
		m_pSprite = 
			new SpritesheetComponent(
			filePath,
			spriteName,
			spritesheet
			);
		m_pSprite->SetHUDOptionEnabled(true);
		
		AddComponent(m_pSprite);
	}

	UIAnimatedImage::~UIAnimatedImage(void)
	{

	}
	
	void UIAnimatedImage::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		switch(alignment)
		{
			case HorizontalAlignment::Left:
				GetTransform()->SetCenterX(0);
				break;
			case HorizontalAlignment::Center:
				GetTransform()->SetCenterX(
					float32(m_pSprite->GetWidth()) / 2.0f
					);
				break;
			case HorizontalAlignment::Right:
				GetTransform()->SetCenterX(
					float32(m_pSprite->GetWidth())
					);
				break;
		}
		UIElement::SetHorizontalAlignment(alignment);
	}

	void UIAnimatedImage::SetVerticalAlignment(VerticalAlignment alignment)
	{
		switch(alignment)
		{
			case VerticalAlignment::Bottom:
				GetTransform()->SetCenterY(0);
				break;
			case VerticalAlignment::Center:
				GetTransform()->SetCenterY(
					float32(m_pSprite->GetHeight()) / 2.0f
					);
				break;
			case VerticalAlignment::Top:
				GetTransform()->SetCenterY(
					float32(m_pSprite->GetHeight())
					);
				break;
		}
		UIElement::SetVerticalAlignment(alignment);
	}

	void UIAnimatedImage::Play()
	{
		m_pSprite->Play();
	}

	void UIAnimatedImage::Restart()
	{
		m_pSprite->Restart();
	}

	void UIAnimatedImage::Pause()
	{
		m_pSprite->Pause();
	}

	void UIAnimatedImage::Stop()
	{
		m_pSprite->Stop();
	}

	void UIAnimatedImage::PushAnimation(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		m_pSprite->PushAnimation(animation, callback);
	}

	void UIAnimatedImage::PlayAnimation(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		m_pSprite->PlayAnimation(animation, callback);
	}

	void UIAnimatedImage::PlayAnimation(
		const tstring & animation,
		int32 startFrame,
		const std::function<void()> & callback
		)
	{
		m_pSprite->PlayAnimation(animation, startFrame, callback);
	}

	bool UIAnimatedImage::PushAnimationSafe(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		return m_pSprite->PushAnimationSafe(animation, callback);
	}

	bool UIAnimatedImage::PlayAnimationSafe(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		return m_pSprite->PlayAnimationSafe(animation, callback);
	}

	bool UIAnimatedImage::PlayAnimationSafe(
		const tstring & animation,
		int32 startFrame,
		const std::function<void()> & callback
		)
	{
		return m_pSprite->PlayAnimationSafe(animation, startFrame, callback);
	}

	void UIAnimatedImage::PlayNextAnimation()
	{
		m_pSprite->PlayNextAnimation();
	}

	void UIAnimatedImage::PlayNextAnimation(int32 startFrame)
	{
		m_pSprite->PlayNextAnimation(startFrame);
	}

	void UIAnimatedImage::Reset()
	{
		m_pSprite->Reset();
	}

	void UIAnimatedImage::SetSpritesheet(const tstring & spritesheet)
	{
		m_pSprite->SetSpritesheet(spritesheet);
	}

	tstring UIAnimatedImage::GetCurrentAnimation() const
	{
		return m_pSprite->GetCurrentAnimation();
	}

	const tstring & UIAnimatedImage::GetcurrentSpritesheet() const
	{
		return m_pSprite->GetcurrentSpritesheet();
	}

	int32 UIAnimatedImage::GetCurrentFrame() const
	{
		return m_pSprite->GetCurrentFrame();
	}

	int32 UIAnimatedImage::GetFramesHorizontal() const
	{
		return m_pSprite->GetFramesHorizontal();
	}

	int32 UIAnimatedImage::GetFramesVertical() const
	{
		return m_pSprite->GetFramesVertical();
	}

	int32 UIAnimatedImage::GetWidth() const
	{
		return m_pSprite->GetWidth();
	}

	int32 UIAnimatedImage::GetHeight() const
	{
		return m_pSprite->GetHeight();
	}

	void UIAnimatedImage::SetCallbackAnimations(const std::function<void()> & callback)
	{
		m_pSprite->SetCallbackAnimations(callback);
	}

	bool UIAnimatedImage::IsPlaying()
	{
		return m_pSprite->IsPlaying();
	}
}