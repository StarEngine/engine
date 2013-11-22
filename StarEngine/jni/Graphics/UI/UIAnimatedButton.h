#pragma once
#include "UIUserElement.h"

namespace star
{
	class SpritesheetComponent;

	class UIAnimatedButton : public UIUserElement
	{
	public:
		UIAnimatedButton(
			const tstring & name,
			const tstring & file,
			const tstring & spritesheet
			);
		virtual ~UIAnimatedButton();

		virtual void Initialize();

		virtual void SetHorizontalAlignment(HorizontalAlignment alignment);
		virtual void SetVerticalAlignment(VerticalAlignment alignment);

		void EnableContiniousAnimation(bool enabled);
		bool IsContiniousAnimationEnabled() const;

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		virtual void GoIdle();
#ifdef DESKTOP
		virtual void GoHover();
#endif
		virtual void GoClick();
		virtual void GoDisable();

		virtual vec2 GetUserElementDimensions() const;

		const static tstring	N_CLICK,
								N_IDLE,
#ifdef DESKTOP
								N_HOVER,
#endif
								N_DISABLED;

		SpritesheetComponent *m_pButtonSprite;
		bool m_ContiniousAnimation;

	private:
		UIAnimatedButton(const UIAnimatedButton &);
		UIAnimatedButton(UIAnimatedButton &&);
		UIAnimatedButton & operator=(const UIAnimatedButton &);
		UIAnimatedButton & operator=(UIAnimatedButton &&);
	};
}
