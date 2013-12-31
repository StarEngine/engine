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
		BaseColliderComponent* component, 
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
					ASSERT_LOG(false, _T("CollisionManager::AddComponent \
The component you tried to add is already in the CollisionManager"), STARENGINE_LOG_TAG);
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
					std::pair<tstring, std::vector<BaseColliderComponent*>>(
					layers[i],std::vector<BaseColliderComponent*>()));
				m_CollisionMap.at(layers[i]).push_back(component);
			}
		}
	}

	void CollisionManager::RemoveComponent(const BaseColliderComponent* component)
	{
		const tstring* layers = component->GetLayers().elements;
		uint8 n = component->GetLayers().amount;
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
					ASSERT_LOG(false, _T("CollisionManager::RemoveComponent: \
The component you tried to remove is not in the CollisionManager"), STARENGINE_LOG_TAG);
				}
			}
			else
			{
				ASSERT_LOG(false, _T("CollisionManager::RemoveComponent: \
The component you tried to remove is not in the CollisionManager"), STARENGINE_LOG_TAG);
			}
		}
	}

	void CollisionManager::Update(const Context& context)
	{
		for(auto& key : m_CollisionMap)
		{

			for(auto iter1 = key.second.begin(); iter1 != key.second.end(); ++iter1)
			{
				for(auto iter2 = iter1 +1; iter2 != key.second.end(); ++iter2)
				{
					if(iter1 != iter2)
					{
						if((*iter1)->CollidesWith(*iter2))
						{
							if(!(*iter1)->GetEntered())
							{
								(*iter1)->SetEntered(true);
								(*iter2)->SetEntered(true);
								(*iter1)->SetExited(false);
								(*iter2)->SetExited(false);
								(*iter1)->TriggerOnEnter(*iter2);
								(*iter2)->TriggerOnEnter(*iter1);
								continue;
							}
							else
							{
								(*iter1)->TriggerOnStay(*iter2);
								(*iter2)->TriggerOnStay(*iter1);
							}
						}
						else
						{
							if(!(*iter1)->GetExited())
							{
								(*iter1)->SetEntered(false);
								(*iter2)->SetEntered(false);
								(*iter1)->SetExited(true);
								(*iter2)->SetExited(true);
								(*iter1)->TriggerOnExit(*iter2);
								(*iter2)->TriggerOnExit(*iter1);
							}
						}
					}
				}
			}
		}
	}
}
