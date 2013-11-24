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

	private:
		UIElement(const UIElement &);
		UIElement(UIElement &&);
		UIElement & operator=(const UIElement &);
		UIElement & operator=(UIElement &&);
	};
}
