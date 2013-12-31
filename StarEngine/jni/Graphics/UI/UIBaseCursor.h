#pragma once
#include "../../defines.h"
#include "../../Context.h"
#include "../../Objects/Object.h"

namespace star
{
	class UIBaseCursor : public Object
	{
	public:
		UIBaseCursor(const tstring & name);
		virtual ~UIBaseCursor();

		void SetLocked(bool locked);
		bool IsLocked() const;

		bool IsIdle() const;
		bool IsHover() const;
		bool IsClick() const;

		virtual void SetState(const tstring & state);

	protected:
		bool m_IsLocked;
		tstring m_State;

	private:
		UIBaseCursor(const UIBaseCursor &);
		UIBaseCursor(UIBaseCursor &&);
		UIBaseCursor & operator=(const UIBaseCursor &);
		UIBaseCursor & operator=(UIBaseCursor&&);
	};
}
