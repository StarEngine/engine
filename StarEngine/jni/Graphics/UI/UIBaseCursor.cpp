#include "UIBaseCursor.h"
#include "../../Scenes/BaseScene.h"

namespace star
{
	UIBaseCursor::UIBaseCursor(const tstring & name)
		: Object(name)
		, m_IsLocked(false)
		, m_State(UI_STATE_IDLE)
	{
	}

	UIBaseCursor::~UIBaseCursor()
	{
	}

	void UIBaseCursor::SetLocked(bool locked)
	{
		m_IsLocked = locked;
	}

	bool UIBaseCursor::IsLocked() const
	{
		return m_IsLocked;
	}

	bool UIBaseCursor::IsIdle() const
	{
		return m_State == UI_STATE_IDLE;
	}

	bool UIBaseCursor::IsHover() const
	{
		return m_State == UI_STATE_HOVER;
	}

	bool UIBaseCursor::IsClick() const
	{
		return m_State == UI_STATE_CLICK;
	}

	void UIBaseCursor::SetState(const tstring & state)
	{
		if(!m_IsLocked)
		{
			m_State = state;
		}
	}
}
