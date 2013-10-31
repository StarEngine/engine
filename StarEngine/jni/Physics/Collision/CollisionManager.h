#pragma once

#include "../../defines.h"
#include <vector>

namespace star
{
	struct Context;
	class Object;

	//[TODO] Make EraseAllCollisions function , now on reseting all objects keep being stored!!

	class CollisionManager
	{
	public:
		~CollisionManager(void);
		static CollisionManager * GetInstance();
		bool CheckCollision(const Object* object1, const Object* object2) const;

	private:
		CollisionManager(void);

		static CollisionManager * m_pCollisionManager;

		bool RectangleCollision(const Object* object1, const Object* object2) const;
		bool CircleCollision(const Object* object1, const Object* object2) const;
		bool RectangleCircleCollision(const Object* object1, const Object* object2) const;

		//disabling default copy constructor
		CollisionManager(const CollisionManager& yRef);
		CollisionManager(CollisionManager&& yRef);
		CollisionManager& operator=(const CollisionManager& yRef);
		CollisionManager& operator=(CollisionManager&& yRef);
	};
}

