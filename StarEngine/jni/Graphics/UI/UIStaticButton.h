#pragma once
#include "UIUserElement.h"

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
		virtual ~UIStaticButton();

		virtual void Initialize();

		virtual void SetHorizontalAlignment(HorizontalAlignment alignment);
		virtual void SetVerticalAlignment(VerticalAlignment alignment);

		void SetCurrentHorizontalSegement(uint32 segment);
		void SetCurrentVerticalSegement(uint32 segment);
		void SetCurrentSegement(uint32 segmentX, uint32 segmentY);

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		virtual vec2 GetUserElementDimensions() const;

		SpriteComponent *m_pButtonSprite;

	private:
		UIStaticButton(const UIStaticButton &);
		UIStaticButton(UIStaticButton &&);
		UIStaticButton & operator=(const UIStaticButton &);
		UIStaticButton & operator=(UIStaticButton &&);
	};
}
