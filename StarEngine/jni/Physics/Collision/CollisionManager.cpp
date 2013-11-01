#include "CollisionManager.h"
#include "../../Objects/Object.h"
#include "../../StarComponents.h"
#include <algorithm>

namespace star
{
	CollisionManager * CollisionManager::m_pCollisionManager = nullptr;

	CollisionManager::CollisionManager(void)
		: m_ObjectVec()
	{
	}
	
	CollisionManager::~CollisionManager(void)
	{
		//Objects are managed by the scenes, don't delete them here!
		m_ObjectVec.clear();
	}

	CollisionManager * CollisionManager::GetInstance()
	{
		if(m_pCollisionManager == nullptr)
		{
			m_pCollisionManager = new CollisionManager();
		}
		return m_pCollisionManager;
	}

	bool CollisionManager::CheckCollision(const Object* object1, const Object* object2) const
	{
		/*
		auto rectComp1 = object1->GetComponent<RectangleColliderComponent>();
		auto circleComp1 = object1->GetComponent<CircleColliderComponent>();
		auto rectComp2 = object2->GetComponent<RectangleColliderComponent>();
		auto circleComp2 = object2->GetComponent<CircleColliderComponent>();
		if((rectComp1 == nullptr && circleComp1 == nullptr) || (rectComp2 == nullptr && circleComp2 == nullptr))
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Checking collision where one of your object has no collider!"));
		}
		
		if(rectComp1 != nullptr)
		{
			if(rectComp2 != nullptr)
			{
				return RectangleCollision(object1, object2);
			}
			if(circleComp2 != nullptr)
			{
				return RectangleCircleCollision(object1, object2);
			}
		}
		if(circleComp1 != nullptr)
		{
			if(rectComp2 != nullptr)
			{
				return RectangleCircleCollision(object1, object2);
			}
			if(circleComp2 != nullptr)
			{
				return CircleCollision(object1, object2);
			}
		}*/
		return false;
	}

	void CollisionManager::OnEnter()
	{
		if(m_OnEnter) 
		{
			m_OnEnter();
		}
	}

	void CollisionManager::OnStay()
	{
		if(m_OnStay) 
		{
			m_OnStay();
		}
	}

	void CollisionManager::OnLeave()
	{
		if(m_OnLeave) 
		{
			m_OnLeave();
		}
		
	}

	void CollisionManager::OnCollisionEnter(const Object* object1, const Object* object2, CollisionAction onEnter)
	{
		AddObjectsToCollisionCheck(object1, object2, onEnter, CollisionType::Enter);
	}

	void CollisionManager::OnCollisionStay(const Object* object1, const Object* object2, CollisionAction onStay)
	{
		AddObjectsToCollisionCheck(object1, object2, onStay, CollisionType::Stay);
	}

	void CollisionManager::OnCollisionLeave(const Object* object1, const Object* object2, CollisionAction onLeave)
	{
		AddObjectsToCollisionCheck(object1, object2, onLeave, CollisionType::Leave);
	}

	void CollisionManager::AddObjectsToCollisionCheck(const Object* object1, const Object* object2, CollisionAction action, CollisionType type)
	{

	}

}
