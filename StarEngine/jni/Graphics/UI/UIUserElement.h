#pragma once
#include "../../defines.h"
#include "../../Context.h"
#include "../../Objects/Object.h"

#include <functional>

namespace star
{
	class UIUserElement : public Object
	{
	public:
		enum class ElementStates : byte
		{
			IDLE = 0,
#ifdef DESKTOP
			HOVER = 1,
#endif
			CLICK = 2,
			TOGGLE = 3,
			DISABLED = 4
		};

		UIUserElement(void);
		virtual ~UIUserElement(void);

		virtual void Initialize();

		bool IsToggled() const;
		bool IsDisabled() const;

		void SetSelectCallback(std::function<void()> callback);

#ifdef DESKTOP
		void SetHoverCallback(std::function<void()> callback);
		void SetUnhoverCallback(std::function<void()> callback);
#endif

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		std::function<void()>
			m_SelectCallback;

#ifdef DESKTOP
		std::function<void()>
			m_HoverCallback,
			m_UnhoverCallback;
#endif

		ElementStates m_ElementState;

	private:
		UIUserElement(const UIUserElement &);
		UIUserElement(UIUserElement &&);
		UIUserElement & operator=(const UIUserElement &);
		UIUserElement & operator=(UIUserElement &&);
	};
}
