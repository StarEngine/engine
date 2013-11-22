#pragma once
#include "UIElement.h"

namespace star
{
	class UIObject;

	class UIDock : public UIElement
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
		void AddElement(UIObject * pElement);

		void SetDimensions(const vec2 & dimensions);
		void SetDimensions(float32 x, float32 y);
		void SetDimensionsX(float32 x);
		void SetDimensionsY(float32 y);

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
