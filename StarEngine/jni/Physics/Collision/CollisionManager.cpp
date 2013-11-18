#include "CollisionManager.h"
#include "../../StarComponents.h"
#include <algorithm>
#include "../../Components/Physics/BaseColliderComponent.h"

namespace star
{
	CollisionManager::CollisionManager(void)
		: m_CollisionMap()
	{
	}
	
	CollisionManager::~CollisionManager(void)
	{
		//Components get deleted by their parent objects,
		//which get deleted from the scene, don't delete them here
		m_CollisionMap.clear();
	}

	void CollisionManager::AddComponent(
		const BaseColliderComponent* component, 
		const tstring* layers, 
		uint8 n)
	{
		for(uint8 i = 0; i < n; ++i)
		{
			//If the layer already exists
			auto it = m_CollisionMap.find(layers[i]);
			if(it != m_CollisionMap.end())
			{
				//If the component isn't in the vector already
				auto vecIt = std::find((*it).second.begin(), (*it).second.end(), component);
				if(vecIt != (*it).second.end())
				{
					ASSERT(false, _T("CollisionManager::AddComponent \n\
						The component you tried to add is already in the CollisionManager"));
					Logger::GetInstance()->Log(LogLevel::Error, _T("CollisionManager::AddComponent \n\
						The component you tried to add is already in the CollisionManager"));
				}			
				else
				{
					(*it).second.push_back(component);					
				}
			}
			//make a new layer!
			else
			{
				m_CollisionMap.insert(
					std::pair<tstring, std::vector<const BaseColliderComponent*>>(
					layers[i],std::vector<const BaseColliderComponent*>()));
				m_CollisionMap.at(layers[i]).push_back(component);
			}
		}
	}

	void CollisionManager::RemoveComponent(
		const BaseColliderComponent* component, 
		const tstring* layers, 
		uint8 n)
	{
		for(uint8 i = 0; i < n; ++i)
		{
			auto it = m_CollisionMap.find(layers[i]);
			if(it != m_CollisionMap.end())
			{				
				auto vecIt = std::find((*it).second.begin(), (*it).second.end(), component);
				if(vecIt != (*it).second.end())
				{
					(*it).second.erase(
						std::remove(
							(*it).second.begin(),
							(*it).second.end(),
							component),
						(*it).second.end());
				}
				else
				{
					ASSERT(false, _T("CollisionManager::RemoveComponent \n\
						The component you tried to remove is not in the CollisionManager"));
					Logger::GetInstance()->Log(LogLevel::Error, _T("CollisionManager::RemoveComponent \n\
						The component you tried to remove is not in the CollisionManager"));
				}
			}
			else
			{
				ASSERT(false, _T("CollisionManager::RemoveComponent \n\
						The component you tried to remove is not in the CollisionManager"));
				Logger::GetInstance()->Log(LogLevel::Error, _T("CollisionManager::RemoveComponent \n\
						The component you tried to remove is not in the CollisionManager"));
			}
		}
	}
}
