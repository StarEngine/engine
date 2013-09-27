#include "CollisionManager.h"
#include "../SceneGraph/Object.h"
#include "../StarComponents.h"
#include <algorithm>

namespace star
{
	CollisionManager* CollisionManager::m_pCollisionManager = nullptr;

	CollisionManager::CollisionManager(void):
		m_ObjectList(),
		m_ActiveCollisionList()
	{
	}
	
	CollisionManager::~CollisionManager(void)
	{
	}

	CollisionManager* CollisionManager::GetInstance()
	{
		if(m_pCollisionManager == nullptr)
		{
			m_pCollisionManager = new CollisionManager();
		}
		return m_pCollisionManager;
	}

	void CollisionManager::CheckCollision(const tstring& tag)
	{
		Logger::GetSingleton()->Log(LogLevel::Info, _T("Entered CheckCollision"));
		//Check which objects need collisionchecking
		for(auto object : m_ObjectList)
		{
			if(object->GetCollisionTag() == tag)
			{
				m_ActiveCollisionList.push_back(object);
			}
		}

		//Check collision only on the active objects
		for(auto object : m_ActiveCollisionList)
		{
			for(auto otherObject : m_ActiveCollisionList)
			{
				if(object != otherObject)
				{
					Logger::GetSingleton()->Log(LogLevel::Info, _T("Element in ActiveCollisionList Checked on Collision"));
					object->CollisionCheck(otherObject);
				}
			}
		}
	}

	void CollisionManager::AddObject(Object* object)
	{
		if(object->GetComponent<RectangleColliderComponent>() != nullptr ||
			object->GetComponent<CircleColliderComponent>() != nullptr)
		{
			m_ObjectList.push_back(object);
		}
	}

	void CollisionManager::RemoveObject(const Object* object)
	{
		m_ObjectList.erase(find(m_ObjectList.begin(), m_ObjectList.end(), object));
	}
}
