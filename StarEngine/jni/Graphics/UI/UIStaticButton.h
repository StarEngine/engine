#pragma once
#include "UIUserElement.h"
#include "../Color.h"

namespace star
{
	class SpriteComponent;

	class UIStaticButton : public UIUserElement
	{
	public:
		UIStaticButton(
			const tstring & name,
			const tstring & file,
			uint32 widthSegements = 1,
			uint32 heightSegements = 1
			);

		UIStaticButton(
			const tstring & name,
			const tstring & file,
			const tstring & spriteName,
			uint32 widthSegements = 1,
			uint32 heightSegements = 1
			);

		virtual ~UIStaticButton();

		virtual void SetHorizontalAlignment(
			HorizontalAlignment alignment,
			bool redefineCenter = true
			);
		virtual void SetVerticalAlignment(
			VerticalAlignment alignment,
			bool redefineCenter = true
			);

		void SetCurrentSegement(uint32 segmentX, uint32 segmentY);

		void SetColorMultiplier(const Color & color);

		virtual vec2 GetDimensions() const;

	protected:
		SpriteComponent *m_pButtonSprite;

	private:
		UIStaticButton(const UIStaticButton &);
		UIStaticButton(UIStaticButton &&);
		UIStaticButton & operator=(const UIStaticButton &);
		UIStaticButton & operator=(UIStaticButton &&);
	};
}
