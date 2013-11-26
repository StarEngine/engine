#pragma once

#include "defines.h"
#include "Helpers/HashTag.h"

namespace star
{
	class Entity
	{
	public:
		Entity();
		Entity(const tstring & name);
		virtual ~Entity();

		const tstring & GetName() const;
		void SetName(const tstring & name);
		bool CompareName(const tstring & name);

		virtual void Destroy() = 0;

	protected:
		HashTag m_Name;

	private:
		Entity(const Entity&);
		Entity(Entity&&);
		Entity & operator=(const Entity&);
		Entity & operator=(Entity&&);
	};
}
