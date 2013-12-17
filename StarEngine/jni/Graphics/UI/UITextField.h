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
			uint32 fontSize,
			const Color & color
			);

		virtual ~UITextField(void);

		virtual void Initialize();

		virtual void SetHorizontalAlignment(
			HorizontalAlignment alignment,
			bool redefineCenter = true
			);
		virtual void SetVerticalAlignment(
			VerticalAlignment alignment,
			bool redefineCenter = true
			);

		void SetText(const tstring & text);
		const tstring & GetText() const;

		void SetColor(const Color & color);

		virtual vec2 GetDimensions() const;

		int32 GetWidth() const;
		int32 GetHeight() const;

	protected:
		TextComponent * m_pTextComponent;

	private:
		UITextField(const UITextField &);
		UITextField(UITextField &&);
		UITextField & operator=(const UITextField &);
		UITextField & operator=(UITextField &&);
	};
}
