#include "CollisionManager.h"
#include "../../Objects/Object.h"
#include "../../StarComponents.h"
#include <algorithm>

namespace star
{
	CollisionManager * CollisionManager::m_pCollisionManager = nullptr;

	CollisionManager::CollisionManager(void)
	{
	}
	
	CollisionManager::~CollisionManager(void)
	{
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
		}
		return false;
	}

	bool CollisionManager::RectangleCollision(const Object* object1, const Object* object2) const
	{
		Rect rect1 = object1->GetComponent<RectangleColliderComponent>()->GetCollisionRect();
		Rect rect2 = object2->GetComponent<RectangleColliderComponent>()->GetCollisionRect();
		glm::vec2 object1Pos = object1->GetComponent<TransformComponent>()->GetWorldPosition().pos2D();
		glm::vec2 object2Pos = object2->GetComponent<TransformComponent>()->GetWorldPosition().pos2D();

		int left = rect1.GetLeft() + static_cast<int>(object1Pos.x);
		int right = rect1.GetRight() + static_cast<int>(object1Pos.x);
		int top = rect1.GetTop() + static_cast<int>(object1Pos.y); 
		int bottom = rect1.GetBottom() + static_cast<int>(object1Pos.y);

		int otherLeft = rect2.GetLeft() + static_cast<int>(object2Pos.x);
		int	otherRight = rect2.GetRight() + static_cast<int>(object2Pos.x);
		int otherTop = rect2.GetTop() + static_cast<int>(object2Pos.y);
		int otherBottom = rect2.GetBottom() + static_cast<int>(object2Pos.y);

		if(left > otherRight || right < otherLeft || top > otherBottom || bottom < otherTop)
		{
			return false;
		}
		return true;
	}

	bool CollisionManager::CircleCollision(const Object* object1, const Object* object2) const
	{
		float radius1 = object1->GetComponent<CircleColliderComponent>()->GetRadius();
		float radius2 = object2->GetComponent<CircleColliderComponent>()->GetRadius();
		glm::vec2 object1Pos = object1->GetComponent<TransformComponent>()->GetWorldPosition().pos2D();
		glm::vec2 object2Pos = object2->GetComponent<TransformComponent>()->GetWorldPosition().pos2D();

		if((object1Pos - object2Pos).length() > radius1 + radius2)
		{
			return false;
		}
		return true;
	}

	bool CollisionManager::RectangleCircleCollision(const Object* object1, const Object* object2) const
	{
		//Check which object1 has the rect collider component and which has the circle collider component
		const Object *rectObject = new Object();
		const Object *circleObject = new Object();
		Rect rect = Rect();
		float radius = 0.0f;

		if(object1->GetComponent<RectangleColliderComponent>() != nullptr)
		{
			rect = object1->GetComponent<RectangleColliderComponent>()->GetCollisionRect();
			rectObject = object1;
		}
		if(object2->GetComponent<RectangleColliderComponent>() != nullptr)
		{
			rect = object2->GetComponent<RectangleColliderComponent>()->GetCollisionRect();
			rectObject = object2;
		}
		if(object1->GetComponent<CircleColliderComponent>() != nullptr)
		{
			radius = object1->GetComponent<CircleColliderComponent>()->GetRadius();
			circleObject = object1;
		}
		if(object2->GetComponent<CircleColliderComponent>() != nullptr)
		{	
			radius = object2->GetComponent<CircleColliderComponent>()->GetRadius();
			circleObject = object2;
		}

		ASSERT(rectObject != circleObject, _T("Object has both CircleColliderComponent and RectangleComponent"));

		glm::vec2 rectObjectPos =rectObject->GetComponent<TransformComponent>()->GetWorldPosition().pos2D();
		glm::vec2 circleObjectPos = circleObject->GetComponent<TransformComponent>()->GetWorldPosition().pos2D();

		int left = rect.GetLeft() + static_cast<int>(rectObjectPos.x);
		int right = rect.GetRight() + static_cast<int>(rectObjectPos.x);
		int top = rect.GetTop() + static_cast<int>(rectObjectPos.y); 
		int bottom = rect.GetBottom() + static_cast<int>(rectObjectPos.y);

		// Find the closest point to the circle within the rectangle
		float closestX = glm::clamp(circleObjectPos.x, static_cast<float>(left), static_cast<float>(right));
		float closestY = glm::clamp(circleObjectPos.y, static_cast<float>(top), static_cast<float>(top));

		// Calculate the distance between the circle's center and this closest point
		float distanceX = circleObjectPos.x - closestX;
		float distanceY = circleObjectPos.y - closestY;

		// If the distance is less than the circle's radius, an intersection occurs
		float doubleDistanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
		if( doubleDistanceSquared < (radius * radius))
		{
			return true;
		}
		return false;
	}
}
