#include "Entity.h"

namespace star
{
	Entity::Entity()
		: m_Name(EMPTY_STRING)
	{

	}

	Entity::Entity(const tstring & name)
		: m_Name(name)
	{

	}

	Entity::~Entity()
	{

	}

	const tstring & Entity::GetName() const
	{
		return m_Name.GetTag();
	}
	
	void Entity::SetName(const tstring & name)
	{
		m_Name.SetTag(name);
	}

	bool Entity::CompareName(const tstring & name)
	{
		return m_Name == name;
	}
}
