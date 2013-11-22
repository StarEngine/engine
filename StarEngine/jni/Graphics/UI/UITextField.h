#pragma once
#include "UIElement.h"

namespace star
{
	class TextComponent;

	struct Color;

	class UITextField : public UIElement
	{
	public:
		UITextField(
			const tstring & name,
			const tstring & text,
			const tstring & fontName,
			const Color & color
			);

		UITextField(
			const tstring & name,
			const tstring & text,
			const tstring & fontName,
			const tstring & fontPath,
			float32 fontSize,
			const Color & color
			);

		virtual ~UITextField(void);

		virtual void Initialize();

		virtual void SetHorizontalAlignment(HorizontalAlignment alignment);
		virtual void SetVerticalAlignment(VerticalAlignment alignment);

		void SetText(const tstring & text);
		const tstring & GetText() const;

		void SetColor(const Color & color);

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		TextComponent * m_pTextComponent;

	private:
		UITextField(const UITextField &);
		UITextField(UITextField &&);
		UITextField & operator=(const UITextField &);
		UITextField & operator=(UITextField &&);
	};
}
