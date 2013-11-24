#pragma once
#include "UIElement.h"

namespace star
{
	class SpriteComponent;

	class UIImage : public UIElement
	{
	public:
		UIImage(
			const tstring & name,
			const tstring & filePath,
			const tstring & imageName,
			uint32 horizontalSegements = 1,
			uint32 verticalSegments = 1
			);

		virtual ~UIImage(void);

		virtual void Initialize();

		virtual void SetHorizontalAlignment(HorizontalAlignment alignment);
		virtual void SetVerticalAlignment(VerticalAlignment alignment);

		void SetCurrentHorizontalSegement(uint32 segment);
		void SetCurrentVerticalSegement(uint32 segment);
		void SetCurrentSegement(uint32 segmentX, uint32 segmentY);

		virtual vec2 GetDimensions() const;

	protected:
		SpriteComponent * m_pSprite;

	private:
		UIImage(const UIImage &);
		UIImage(UIImage &&);
		UIImage & operator=(const UIImage &);
		UIImage & operator=(UIImage &&);
	};
}
