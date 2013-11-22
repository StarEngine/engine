#pragma once

#include "../../defines.h"
#include <vector>
#include <map>

namespace star
{
	struct Context;
	class Object;
	class BaseColliderComponent;

	class CollisionManager final
	{
	public:

		CollisionManager();
		~CollisionManager();
		void AddComponent(BaseColliderComponent* component, const tstring* layers, uint8 n);
		void RemoveComponent(const BaseColliderComponent* component);
		void Update(const Context& context);

	private:

		std::map<tstring, std::vector<BaseColliderComponent*>> m_CollisionMap;

		CollisionManager(const CollisionManager& yRef);
		CollisionManager(CollisionManager&& yRef);
		CollisionManager& operator=(const CollisionManager& yRef);
		CollisionManager& operator=(CollisionManager&& yRef);
	};
}
