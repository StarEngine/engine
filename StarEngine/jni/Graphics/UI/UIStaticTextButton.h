#pragma once

#include "UIStaticButton.h"
#include "../Color.h"

namespace star
{
	class UITextField;

	class UIStaticTextButton : public UIStaticButton
	{
	public:
		UIStaticTextButton(
			const tstring & name,
			const tstring & file,
			const tstring & text,
			const tstring & fontName,
			const Color & color,
			uint32 widthSegements = 1,
			uint32 heightSegements = 1
			);

		UIStaticTextButton(
			const tstring & name,
			const tstring & file,
			const tstring & text,
			const tstring & fontName,
			const tstring & fontPath,
			uint32 fontSize,
			const Color & color,
			uint32 widthSegements = 1,
			uint32 heightSegements = 1
			);

		virtual ~UIStaticTextButton();
		virtual void AfterInitialized();

		void SetTextColor(const Color & color);

		void SetText(const tstring & text);
		const tstring & GetText() const;

		void TranslateText(const vec2& translation);
		void TranslateText(float32 x, float32 y);
		void TranslateTextX(float32 x);
		void TranslateTextY(float32 y);
		void SetHorizontalAlignmentText(
			HorizontalAlignment alignment,
			bool redefineCenter = true
			);
		void SetVerticalAlignmentText(
			VerticalAlignment alignment,
			bool redefineCenter = true
			);

		void SetTextCentered();

	protected:
		UITextField * m_pTextField;

	private:
		UIStaticTextButton(const UIStaticTextButton &);
		UIStaticTextButton(UIStaticTextButton &&);
		UIStaticTextButton & operator=(const UIStaticTextButton &);
		UIStaticTextButton & operator=(UIStaticTextButton &&);
	};
}
