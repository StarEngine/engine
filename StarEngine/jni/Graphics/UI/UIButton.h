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
		virtual ~UIButton();

		virtual void AfterInitialized();

	protected:
		virtual void GoIdle();
#ifdef DESKTOP
		virtual void GoHover();
#endif
		virtual void GoDown();
		virtual void GoFreeze();

		bool m_IsVertical;

	private:
		UIButton(const UIButton &);
		UIButton(UIButton &&);
		UIButton & operator=(const UIButton &);
		UIButton & operator=(UIButton &&);
	};
}
