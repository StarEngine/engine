#pragma once
#include <vector>
#include "../defines.h"

namespace star
{
	struct Context;
	class Object;

	//[TODO] Make EraseAllCollisions function , now on reseting all objects keep being stored!!

	class CollisionManager
	{
	public:
		~CollisionManager(void);
		static CollisionManager* GetInstance();

		void CheckCollision(const tstring& tag);
		void AddObject(Object* object);
		void RemoveObject(const Object* object);

	private:
		CollisionManager(void);

		static CollisionManager* m_pCollisionManager;
		std::vector<Object*> m_ObjectList, m_ActiveCollisionList;

		//disabling default copy constructor
		CollisionManager(const CollisionManager& yRef);
		CollisionManager(CollisionManager&& yRef);
		CollisionManager& operator=(const CollisionManager& yRef);
	};
}

