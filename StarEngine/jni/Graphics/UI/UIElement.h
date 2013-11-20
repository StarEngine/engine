#pragma once
#include "../../defines.h"
#include "../../Context.h"
#include "../../Objects/Object.h"

#include <functional>

namespace star
{
	class UIElement : public Object
	{
	public:
		UIElement(const tstring & name);
		virtual ~UIElement();

		virtual void Initialize();

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		tstring m_Name;

	private:
		UIElement(const UIElement &);
		UIElement(UIElement &&);
		UIElement & operator=(const UIElement &);
		UIElement & operator=(UIElement &&);
	};
}
