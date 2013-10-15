#include "State.h"

namespace star
{
	State::~State()
	{

	}

	void State::Draw()
	{

	}

	void State::Activate()
	{
		m_Active = true;
	}

	void State::Deactivate()
	{
		m_Active = false;
	}

	bool State::IsActive() const
	{
		return m_Active;
	}

	State::State()
		: m_Active(false)
	{

	}
}
