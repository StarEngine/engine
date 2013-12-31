#pragma once
#include "UIUserElement.h"

namespace star
{
	class SpriteSheetComponent;

	class UIAnimatedButton : public UIUserElement
	{
	public:
		UIAnimatedButton(
			const tstring & name,
			const tstring & file,
			const tstring & spritesheet
			);

		UIAnimatedButton(
			const tstring & name,
			const tstring & file,
			const tstring & spriteName,
			const tstring & spritesheet
			);

		virtual ~UIAnimatedButton();

		virtual void AfterInitialized();

		virtual void SetHorizontalAlignment(
			HorizontalAlignment alignment,
			bool redefineCenter = true
			);
		virtual void SetVerticalAlignment(
			VerticalAlignment alignment,
			bool redefineCenter = true
			);

		void EnableContiniousAnimation(bool enabled);
		bool IsContiniousAnimationEnabled() const;

		virtual vec2 GetDimensions() const;

	protected:
		virtual void GoIdle();
#ifdef DESKTOP
		virtual void GoHover();
#endif
		virtual void GoDown();
		virtual void GoDisable();

		SpriteSheetComponent *m_pButtonSprite;
		bool m_ContiniousAnimation;

	private:
		UIAnimatedButton(const UIAnimatedButton &);
		UIAnimatedButton(UIAnimatedButton &&);
		UIAnimatedButton & operator=(const UIAnimatedButton &);
		UIAnimatedButton & operator=(UIAnimatedButton &&);
	};
}
