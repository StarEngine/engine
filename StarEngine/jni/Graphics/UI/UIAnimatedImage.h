#pragma once
#include "UIElement.h"

namespace star
{
	class SpritesheetComponent;

	class UIAnimatedImage : public UIElement
	{
	public:
		UIAnimatedImage(
			const tstring & name,
			const tstring & filePath,
			const tstring & imageName,
			const tstring & spritesheet
			);

		virtual ~UIAnimatedImage(void);

		virtual void Initialize();

		virtual void SetHorizontalAlignment(HorizontalAlignment alignment);
		virtual void SetVerticalAlignment(VerticalAlignment alignment);

		void Play();
		void Restart();
		void Pause();
		void Stop();

		void PushAnimation(const tstring & animation);
		void PlayAnimation(const tstring & animation);
		void PlayAnimation(const tstring & animation, int32 startFrame);
		void PlayNextAnimation();
		void PlayNextAnimation(int32 startFrame);
		void Reset();

		void SetSpritesheet(const tstring & spritesheet);

		tstring GetCurrentAnimation() const;
		const tstring & GetcurrentSpritesheet() const;

		int32 GetCurrentFrame() const;

		int32 GetFramesHorizontal() const;
		int32 GetFramesVertical() const;
		int32 GetWidth() const;
		int32 GetHeight() const;

		void SetCallbackAnimations(const std::function<void()> & callback);

		bool IsPlaying();

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		SpritesheetComponent * m_pSprite;

	private:
		UIAnimatedImage(const UIAnimatedImage &);
		UIAnimatedImage(UIAnimatedImage &&);
		UIAnimatedImage & operator=(const UIAnimatedImage &);
		UIAnimatedImage & operator=(UIAnimatedImage &&);
	};
}
