#pragma once
#include "UIStaticButton.h"

namespace star
{
	class SpriteComponent;

	class UIButton : public UIStaticButton
	{
	public:
		UIButton(
			const tstring & name,
			const tstring & file,
			bool isVertical = true
			);
		virtual ~UIButton();

	protected:
		virtual void Update(const Context & context);

		bool m_IsVertical;

	private:
		UIButton(const UIButton &);
		UIButton(UIButton &&);
		UIButton & operator=(const UIButton &);
		UIButton & operator=(UIButton &&);
	};
}
