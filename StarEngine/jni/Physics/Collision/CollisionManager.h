#pragma once

#include "../../defines.h"
#include <vector>
#include <functional>

namespace star
{
	struct Context;
	class Object;

	//[TODO] Make EraseAllCollisions function , now on reseting all objects keep being stored!!

	class CollisionManager
	{
	public:
		typedef std::function<void()> CollisionAction;

		~CollisionManager(void);
		static CollisionManager * GetInstance();
		bool CheckCollision(const Object* object1, const Object* object2) const;
		void OnCollisionEnter(const Object* object1, const Object* object2, CollisionAction onEnter);
		void OnCollisionStay(const Object* object1, const Object* object2, CollisionAction onStay);
		void OnCollisionLeave(const Object* object1, const Object* object2, CollisionAction onLeave);

	private:
		CollisionManager(void);

		static CollisionManager * m_pCollisionManager;

		enum CollisionType
		{
			Enter,
			Stay,
			Leave
		};

		bool RectangleCollision(const Object* object1, const Object* object2) const;
		bool CircleCollision(const Object* object1, const Object* object2) const;
		bool RectangleCircleCollision(const Object* object1, const Object* object2) const;

		void AddObjectsToCollisionCheck(const Object* object1, const Object* object2, 
										CollisionAction action, CollisionType type);

		void OnEnter();
		void OnStay();
		void OnLeave();

		CollisionAction m_OnEnter;
		CollisionAction m_OnStay;
		CollisionAction m_OnLeave;

		

		std::vector<const Object*> m_ObjectVec;
		std::vector<std::pair<std::pair<const Object* , const Object*>
					,std::pair<CollisionAction, CollisionType>>> m_CollisionCheckVec;

		//disabling default copy constructor
		CollisionManager(const CollisionManager& yRef);
		CollisionManager(CollisionManager&& yRef);
		CollisionManager& operator=(const CollisionManager& yRef);
		CollisionManager& operator=(CollisionManager&& yRef);
	};
}

