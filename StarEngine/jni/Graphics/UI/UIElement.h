#pragma once

#include "UIObject.h"
#include <functional>

namespace star
{
	class UIElement : public UIObject
	{
	public:
		UIElement(const tstring & name);
		virtual ~UIElement();

		virtual void Initialize();

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

	private:
		UIElement(const UIElement &);
		UIElement(UIElement &&);
		UIElement & operator=(const UIElement &);
		UIElement & operator=(UIElement &&);
	};
}
