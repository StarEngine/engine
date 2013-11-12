#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "../../Objects/Object.h"
#include "../../Logger.h"
#include "../../Scenes/SceneManager.h"
#include "../../Objects/BaseCamera.h"
#include "../CameraComponent.h"
#include "../Graphics/SpriteComponent.h"

namespace star
{

	RectangleColliderComponent::RectangleColliderComponent()
		: BaseColliderComponent()
		, m_CollisionRect()
		, m_bDefaultInitialized(true)
	{
	}
	
	RectangleColliderComponent::RectangleColliderComponent(const vec2& size)
		: BaseColliderComponent()
		, m_CollisionRect(vec2(),vec2(size.x, 0),vec2(0, size.y), vec2(size.x, size.y))
		, m_bDefaultInitialized(false)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(float width, float height)
		: BaseColliderComponent()
		, m_CollisionRect(vec2(),vec2(width, 0),vec2(0, height), vec2(width, height))
		, m_bDefaultInitialized(false)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(const tstring* layers, uint8 n)
		: BaseColliderComponent(layers, n)
		, m_CollisionRect()
		, m_bDefaultInitialized(true)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(const vec2& size, 
		const tstring* layers, uint8 n)
		: BaseColliderComponent(layers, n)
		, m_CollisionRect(vec2(),vec2(size.x, 0),vec2(0, size.y), vec2(size.x, size.y))
		, m_bDefaultInitialized(false)
	{

	}
	RectangleColliderComponent::RectangleColliderComponent(float width, float height, 
		const tstring* layers, uint8 n)
		: BaseColliderComponent(layers, n)
		, m_CollisionRect(vec2(),vec2(width, 0),vec2(0, height), vec2(width, height))
		, m_bDefaultInitialized(false)
	{

	}

	RectangleColliderComponent::~RectangleColliderComponent()
	{
	}

	void RectangleColliderComponent::InitializeColliderComponent()
	{
		if(m_bDefaultInitialized)
		{
			//Initialize the rectangle with the values of the visible part of the sprite
			SpriteComponent* spriteComp = GetParent()->GetComponent<SpriteComponent>();
			if(spriteComp)
			{
				ASSERT(spriteComp->IsInitialized(),_T("First add the spriteComponent and then the rectColliderComp"));
				m_CollisionRect.SetPoints(vec2(0,0),vec2(spriteComp->GetWidth(), 0), 
					vec2(0, spriteComp->GetHeight() ), vec2(spriteComp->GetWidth(), spriteComp->GetHeight()));
			}
		}
	}

	bool RectangleColliderComponent::CollidesWithPoint(const vec2& point) const
	{
		if(GetTransform()->GetWorldRotation() == 0.0f)
		{
			Rect rect = GetCollisionRect();
			return !(rect.GetLeftTop().x > point.x || rect.GetRightTop().x < point.x
					|| rect.GetLeftTop().y < point.y || rect.GetLeftBottom().y > point.y);
		}
		else
		{
			//[TODO] implement OOBB - Point collision
			return false;
		}
		
	}

	bool RectangleColliderComponent::CollidesWithLine(const vec2& point1, const vec2& point2) const
	{
		Rect rect = GetCollisionRect();
		//perpendicular of a vec =  (-y , x) or (y, -x)
		vec2 axis(-(point2 - point1).y , (point2 - point1).x);

		return (CalculateAxisSpecificCollision(rect, point1, point2, axis));
	}

	void RectangleColliderComponent::CollidesWith(const BaseColliderComponent* other) const
	{
		const CircleColliderComponent* otherCircleComp = dynamic_cast<const CircleColliderComponent*>(other);
		const RectangleColliderComponent* otherRectComp = dynamic_cast<const RectangleColliderComponent*>(other);

		if(otherRectComp != nullptr)
		{
			Rect thisRect = GetCollisionRect();
			Rect otherRect = otherRectComp->GetCollisionRect();
			//Check to perform AABB or OOBB CollisionCheck!
			if(GetTransform()->GetWorldRotation() == 0.0f && otherRectComp->GetTransform()->GetWorldRotation() == 0.0f)
			{
				if(AABBRectangleRectangleCollision(thisRect, otherRect))
				{
					//Logger::GetInstance()->Log(LogLevel::Info, _T("AABB - Collision Detected"));
				}
			}
			else
			{
				if(OOBBRectangleRectangleCollision(thisRect, otherRect))
				{
					//Logger::GetInstance()->Log(LogLevel::Info, _T("OOBB - Collision Detected"));
				}
			}
			
		}
		else if(otherCircleComp != nullptr)
		{
			if(GetTransform()->GetWorldRotation() == 0.0f && otherRectComp->GetTransform()->GetWorldRotation() == 0.0f)
			{
				if(RectangleCircleCollision(this, otherCircleComp))
				{

				}
			}
		}
	}

	bool RectangleColliderComponent::AABBRectangleRectangleCollision(const Rect& rect1,
		const Rect& rect2) const
	{
		return !(rect1.GetLeftTop().x > rect2.GetRightTop().x || rect1.GetRightTop().x < rect2.GetLeftTop().x 
			|| rect1.GetLeftTop().y < rect2.GetLeftBottom().y || rect1.GetLeftBottom().y > rect2.GetLeftTop().y);
	}

	bool RectangleColliderComponent::OOBBRectangleRectangleCollision(const Rect& rect1, 
		const Rect& rect2) const
	{
		//First check if the rects are colliding as aabb
		if(rect1.GetRealLeft() > rect2.GetRealRight() || rect1.GetRealRight() < rect2.GetRealLeft() 
			|| rect1.GetRealTop() < rect2.GetRealBottom() || rect1.GetRealBottom() > rect2.GetRealTop())
		{
			return false;
		}
		else
		{
			/*
		Based on this: http://www.gamedev.net/page/resources/_/technical/game-programming/2d-rotated-rectangle-collision-r2604
		*/
			vec2 axis1, axis2, axis3, axis4;
			axis1 = rect1.GetRightTop() - rect1.GetLeftTop();
			axis2 = rect1.GetRightTop() - rect1.GetRightBottom();
			axis3 = rect2.GetLeftTop() - rect2.GetLeftBottom();
			axis4 = rect2.GetLeftTop() - rect2.GetRightTop();

			return (CalculateAxisSpecificCollision(rect1, rect2, axis1) ||
			CalculateAxisSpecificCollision(rect1, rect2, axis2) ||
			CalculateAxisSpecificCollision(rect1, rect2, axis3) ||
			CalculateAxisSpecificCollision(rect1, rect2, axis4));			
		}									  
	}		

	bool RectangleColliderComponent::CalculateAxisSpecificCollision(const Rect& rect1, 
		const vec2& point1, const vec2& point2, const vec2& axis) const
	{
		vec2 Aproj1 = ((rect1.GetLeftTop() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Aproj2 = ((rect1.GetLeftBottom() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Aproj3 = ((rect1.GetRightBottom() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Aproj4 = ((rect1.GetRightTop() * axis)/(glm::length(axis)*glm::length(axis)))*axis;

		vec2 Bproj1 = ((point1 * axis)/(glm::length(axis)*glm::length(axis)))*axis;

		float AvecPosOnAxis1 = glm::dot(Aproj1,axis);
		float AvecPosOnAxis2 = glm::dot(Aproj2,axis);
		float AvecPosOnAxis3 = glm::dot(Aproj3,axis);
		float AvecPosOnAxis4 = glm::dot(Aproj4,axis);

		float BvecPosOnAxis1 = glm::dot(Bproj1,axis);

		//Find Min and Max
		float vec1[4];
		vec1[0] = AvecPosOnAxis1;
		vec1[1] = AvecPosOnAxis2;
		vec1[2] = AvecPosOnAxis3;
		vec1[3] = AvecPosOnAxis4;

		float AMinimum = CalculateMinimum(vec1, 4);
		float AMaximum = CalculateMaximum(vec1, 4);

		return (BvecPosOnAxis1 <= AMaximum && BvecPosOnAxis1 >= AMinimum);
	}

	bool RectangleColliderComponent::CalculateAxisSpecificCollision(const Rect& rect1, 
		const Rect& rect2, const vec2& axis) const
	{
		vec2 Aproj1 = ((rect1.GetLeftTop() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Aproj2 = ((rect1.GetLeftBottom() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Aproj3 = ((rect1.GetRightBottom() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Aproj4 = ((rect1.GetRightTop() * axis)/(glm::length(axis)*glm::length(axis)))*axis;

		vec2 Bproj1 = ((rect2.GetLeftTop() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Bproj2 = ((rect2.GetLeftBottom() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Bproj3 = ((rect2.GetRightBottom() * axis)/(glm::length(axis)*glm::length(axis)))*axis;
		vec2 Bproj4 = ((rect2.GetRightTop() * axis)/(glm::length(axis)*glm::length(axis)))*axis;

		float AvecPosOnAxis1 = glm::dot(Aproj1,axis);
		float AvecPosOnAxis2 = glm::dot(Aproj2,axis);
		float AvecPosOnAxis3 = glm::dot(Aproj3,axis);
		float AvecPosOnAxis4 = glm::dot(Aproj4,axis);

		float BvecPosOnAxis1 = glm::dot(Bproj1,axis);
		float BvecPosOnAxis2 = glm::dot(Bproj2,axis);
		float BvecPosOnAxis3 = glm::dot(Bproj3,axis);
		float BvecPosOnAxis4 = glm::dot(Bproj4,axis);

		//Find Min and Max
		float vec1[4];
		vec1[0] = AvecPosOnAxis1;
		vec1[1] = AvecPosOnAxis2;
		vec1[2] = AvecPosOnAxis3;
		vec1[3] = AvecPosOnAxis4;

		float vec2[4]; 
		vec2[0] = BvecPosOnAxis1;
		vec2[1] = BvecPosOnAxis2;
		vec2[2] = BvecPosOnAxis3;
		vec2[3] = BvecPosOnAxis4;

		float AMinimum = CalculateMinimum(vec1, 4);
		float BMinimum = CalculateMinimum(vec2, 4);
		float AMaximum = CalculateMaximum(vec1, 4);
		float BMaximum = CalculateMaximum(vec2, 4);

		return BMinimum <= AMaximum || BMaximum >= AMinimum;
	}

	float RectangleColliderComponent::CalculateMinimum(const float* vec, uint8 size) const
	{
		ASSERT(size != 0, _T("You can't calculate the minimum of 0 elements!"));
		float minimum = vec[0];
		for(int i = 1; i < size; ++i)
		{
			if(vec[i] < minimum)
			{
				minimum = vec[i];
			}
		}
		return minimum;
	}

	float RectangleColliderComponent::CalculateMaximum(const float* vec, uint8 size) const
	{
		ASSERT(size != 0, _T("You can't calculate the maximum of 0 elements!"));
		float maximum = vec[0];
		for(int i = 1; i < size; ++i)
		{
			if(vec[i] > maximum)
			{
				maximum = vec[i];
			}
		}
		return maximum;
	}

	bool RectangleColliderComponent::RectangleCircleCollision(const RectangleColliderComponent* collider1, 
		const CircleColliderComponent* collider2) const
	{
		Rect rect = collider1->GetCollisionRect();
		float radius = collider2->GetRadius();

		glm::vec2 rectObjectPos = collider1->GetTransform()->GetWorldPosition().pos2D();
		glm::vec2 circleObjectPos = collider2->GetTransform()->GetWorldPosition().pos2D();

		// Find the closest point to the circle within the rectangle
		float closestX = glm::clamp(circleObjectPos.x, rect.GetRealLeft(), rect.GetRealRight());
		float closestY = glm::clamp(circleObjectPos.y, rect.GetRealBottom(), rect.GetRealTop());

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

	float RectangleColliderComponent::GetCollisionRectWidth() const
	{
		return m_CollisionRect.GetWidth();
	}

	float RectangleColliderComponent::GetCollisionRectHeight() const
	{
		return m_CollisionRect.GetHeight();
	}

	void RectangleColliderComponent::GetColliisonRectSize(vec2& outputVec) const
	{
		outputVec.x = m_CollisionRect.GetWidth();
		outputVec.y = m_CollisionRect.GetHeight();
	}

	void RectangleColliderComponent::SetCollisionRectSize(float width, float height)
	{
		m_CollisionRect.SetPoints(vec2(0, 0), vec2(width, 0), vec2(0, height), vec2(width, height));
	}

	void RectangleColliderComponent::SetCollisionRectSize(const vec2& size)
	{
		m_CollisionRect.SetPoints(vec2(0, 0), vec2(size.x, 0), vec2(0, size.y), vec2(size.x, size.y));
	}

	Rect RectangleColliderComponent::GetCollisionRect() const
	{
		auto projectionObject = SceneManager::GetInstance()->GetActiveScene()->GetActiveCamera();
		mat4x4 viewInverse = projectionObject->GetComponent<CameraComponent>()->GetViewInverse();
		Rect temp = m_CollisionRect * ( viewInverse * GetTransform()->GetWorldMatrix());
		return temp;
	}
}
