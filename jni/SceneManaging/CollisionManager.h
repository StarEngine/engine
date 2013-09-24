#pragma once
#include <vector>
#include "../defines.h"

namespace star
{
	struct Context;
	class Object;

	class CollisionManager
	{
	public:
		CollisionManager(void);
		~CollisionManager(void);

		void CheckCollision(const tstring& tag);
		void AddObject(Object* object);
		void RemoveObject(const Object* object);

	private:
		std::vector<Object*> m_ObjectList, m_ActiveCollisionList;
	};
}

