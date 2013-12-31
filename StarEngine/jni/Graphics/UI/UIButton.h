#pragma once
#include "UIStaticButton.h"

namespace star
{
	class UIButton : public UIStaticButton
	{
	public:
		UIButton(
			const tstring & name,
			const tstring & file,
			bool isVertical = true
			);

		UIButton(
			const tstring & name,
			const tstring & file,
			const tstring & spriteName,
			bool isVertical = true
			);

		virtual ~UIButton();

		virtual void AfterInitialized();

	protected:
		virtual void GoIdle();
#ifdef DESKTOP
		virtual void GoHover();
#endif
		virtual void GoDown();
		virtual void GoDisable();

		bool m_IsVertical;

	private:
		UIButton(const UIButton &);
		UIButton(UIButton &&);
		UIButton & operator=(const UIButton &);
		UIButton & operator=(UIButton &&);
	};
}
