#pragma once
#include "UIUserElement.h"

namespace star
{
	class SpriteComponent;

	class UIButton : public UIUserElement
	{
	public:
		UIButton(
			const tstring & name,
			const tstring & file,
			bool isVertical = true
			);
		virtual ~UIButton();

		virtual void Initialize();

		virtual void SetHorizontalAlignment(HorizontalAlignment alignment);
		virtual void SetVerticalAlignment(VerticalAlignment alignment);

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		virtual vec2 GetUserElementDimensions() const;

		bool m_IsVertical;
		SpriteComponent *m_pButtonSprite;

	private:
		UIButton(const UIButton &);
		UIButton(UIButton &&);
		UIButton & operator=(const UIButton &);
		UIButton & operator=(UIButton &&);
	};
}
