#pragma once

#include "UIAnimatedButton.h"
#include "../Color.h"

namespace star
{
	class UITextField;

	class UIAnimatedTextButton : public UIAnimatedButton
	{
	public:
		UIAnimatedTextButton(
			const tstring & name,
			const tstring & file,
			const tstring & spritesheet,
			const tstring & text,
			const tstring & fontName,
			const Color & color
			);

		UIAnimatedTextButton(
			const tstring & name,
			const tstring & file,
			const tstring & spritesheet,
			const tstring & text,
			const tstring & fontName,
			const tstring & fontPath,
			uint32 fontSize,
			const Color & color
			);

		UIAnimatedTextButton(
			const tstring & name,
			const tstring & file,
			const tstring & spriteName,
			const tstring & spritesheet,
			const tstring & text,
			const tstring & fontName,
			const Color & color
			);

		UIAnimatedTextButton(
			const tstring & name,
			const tstring & file,
			const tstring & spriteName,
			const tstring & spritesheet,
			const tstring & text,
			const tstring & fontName,
			const tstring & fontPath,
			uint32 fontSize,
			const Color & color
			);

		virtual ~UIAnimatedTextButton();
		virtual void AfterInitialized();

		void SetIdleColor(const Color & color);
		void SetHoverColor(const Color & color);
		void SetClickColor(const Color & color);
		void SetDisableColor(const Color & color);

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
		virtual void GoIdle();
#ifdef DESKTOP
		virtual void GoHover();
#endif
		virtual void GoDown();
		virtual void GoDisable();
		
		UITextField * m_pTextField;
		Color m_StateColors[4];

	private:
		UIAnimatedTextButton(const UIAnimatedTextButton &);
		UIAnimatedTextButton(UIAnimatedTextButton &&);
		UIAnimatedTextButton & operator=(const UIAnimatedTextButton &);
		UIAnimatedTextButton & operator=(UIAnimatedTextButton &&);
	};
}
