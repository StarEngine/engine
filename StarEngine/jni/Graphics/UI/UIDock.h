#pragma once
#include "UIObject.h"

namespace star
{
	class UIDock : public UIObject
	{
	public:
		UIDock(const tstring & name);

		UIDock(
			const tstring & name,
			float32 width,
			float32 height
			);
		virtual ~UIDock(void);

		virtual void Initialize();

		virtual void SetHorizontalAlignment(HorizontalAlignment alignment);
		virtual void SetVerticalAlignment(VerticalAlignment alignment);

		void AddElement(UIObject * pElement);

		void SetDimensions(const vec2 & dimensions);
		void SetDimensions(float32 x, float32 y);
		void SetDimensionsX(float32 x);
		void SetDimensionsY(float32 y);

		virtual void Reset();

		const vec2 & GetDimensions() const;

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		vec2 m_Dimensions;

	private:
		UIDock(const UIDock &);
		UIDock(UIDock &&);
		UIDock & operator=(const UIDock &);
		UIDock & operator=(UIDock &&);
	};
}
