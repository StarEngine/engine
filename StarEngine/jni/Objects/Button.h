#pragma once

#include "../defines.h"
#include "Object.h"
#include <functional>

namespace star
{
	struct Context;

	class Button final : public Object
	{
	public:
		typedef std::function<void()> ButtonAction;

		Button(tstring assetFile, bool isSpriteSheet);
		~Button();

		void SetOnHoverCallback(ButtonAction onHover);
		void SetOnClickCallback(ButtonAction onClick);
		void SetOnLeaveCallback(ButtonAction onLeave);

	protected:
		void Initialize();
		void Update(const Context& context);
		void Draw(const Context& context);

		void OnClick();
		void OnHover();
		void OnLeave();

	private:
		bool m_IsSpriteSheet;
		bool m_IsHovered;

		ButtonAction m_OnHover;
		ButtonAction m_OnClick;
		ButtonAction m_OnLeave;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		Button(const Button& yRef);				
		Button(Button&& yRef);
		Button& operator=(const Button& yRef);
		Button& operator=(Button&& yRef);
	};
}
