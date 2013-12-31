#pragma once

#include "UIUserElement.h"
#include "../Color.h"

namespace star
{
	class UITextField;

	class UISimpleTextButton : public UIUserElement
	{
	public:
		UISimpleTextButton(
			const tstring & name,
			float width,
			float height,
			const tstring & text,
			const tstring & fontName,
			const Color & color
			);

		UISimpleTextButton(
			const tstring & name,
			float width,
			float height,
			const tstring & text,
			const tstring & fontName,
			const tstring & fontPath,
			uint32 fontSize,
			const Color & color
			);

		UISimpleTextButton(
			const tstring & name,
			const tstring & text,
			const tstring & fontName,
			const Color & color
			);

		UISimpleTextButton(
			const tstring & name,
			const tstring & text,
			const tstring & fontName,
			const tstring & fontPath,
			uint32 fontSize,
			const Color & color
			);

		virtual ~UISimpleTextButton();
		
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

		void SetDimensions(const vec2 & dimensions);
		void SetDimensions(float32 x, float32 y);
		void SetDimensionsX(float32 x);
		void SetDimensionsY(float32 y);

		virtual vec2 GetDimensions() const;

	protected:
		virtual void GoIdle();
#ifdef DESKTOP
		virtual void GoHover();
#endif
		virtual void GoDown();
		virtual void GoDisable();

		UITextField * m_pTextField;
		vec2 m_Dimensions;
		Color m_StateColors[4];

	private:
		UISimpleTextButton(const UISimpleTextButton &);
		UISimpleTextButton(UISimpleTextButton &&);
		UISimpleTextButton & operator=(const UISimpleTextButton &);
		UISimpleTextButton & operator=(UISimpleTextButton &&);
	};
}
