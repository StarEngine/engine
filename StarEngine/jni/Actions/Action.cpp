#include "Action.h"
#include "../Objects/Object.h"

namespace star
{
	Action::Action()
		: Entity()
		, m_pParent(nullptr)
		, m_IsPaused(false)
	{

	}

	Action::Action(const tstring & name)
		: Entity(name)
		, m_pParent(nullptr)
		, m_IsPaused(false)
	{

	}

	Action::~Action()
	{

	}

	void Action::Destroy()
	{
		m_pParent->RemoveAction(this);
	}

	void Action::Restart()
	{
		m_IsPaused = false;
	}

	void Action::Pause()
	{
		m_IsPaused = true;
	}

	void Action::Resume()
	{
		m_IsPaused = false;
	}

	void Action::BaseUpdate(const Context & context)
	{
		if(!m_IsPaused)
		{
			Update(context);
		}
	}

	void Action::SetParent(Object * parent)
	{
		m_pParent = parent;
	}

	Object * Action::GetParent() const
	{
		return m_pParent;
	}
}
