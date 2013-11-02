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

	bool RectangleColliderComponent::CollidesWithPoint(const pos& point) const
	{
		/*
		if(rect1.GetLeft() > rect2.GetRight() || rect1.GetRight() < rect2.GetLeft() 
			|| rect1.GetTop() > rect2.GetBottom() || rect1.GetBottom() < rect2.GetTop())
		{
			return false;
		}*/
		return false;
	}

	bool RectangleColliderComponent::CollidesWithLine(const pos& point1, const pos& point2) const
	{
		return false;
	}

	void RectangleColliderComponent::CollidesWith(const BaseColliderComponent* other) const
	{
		const CircleColliderComponent* otherCircleComp = reinterpret_cast<const CircleColliderComponent*>(other);
		const RectangleColliderComponent* otherRectComp = reinterpret_cast<const RectangleColliderComponent*>(other);

		if(otherRectComp != nullptr)
		{
			Rect thisRect = GetCollisionRect();
			Rect otherRect = otherRectComp->GetCollisionRect();
			//Check to perform AABB or OOBB CollisionCheck!
			if(GetTransform()->GetWorldRotation() == 0.0f && otherRectComp->GetTransform()->GetWorldRotation() == 0.0f)
			{
				if(AABBRectangleRectangleCollision(thisRect, otherRect))
				{
					Logger::GetInstance()->Log(LogLevel::Info, _T("AABB - Collision Detected"));
				}
			}
			else
			{
				if(OOBBRectangleRectangleCollision(thisRect, otherRect))
				{
					Logger::GetInstance()->Log(LogLevel::Info, _T("OOBB - Collision Detected"));
				}
			}
			
		}
		else if(otherRectComp != nullptr)
		{
			/*
			if(RectangleCircleCollision(otherRectComp->GetRealCollisionRect(), realRadius))
			{

			}*/
		}
	}

	bool RectangleColliderComponent::AABBRectangleRectangleCollision(const Rect& rect1,
		const Rect& rect2) const
	{
		if(rect1.GetRealLeft() > rect2.GetRealRight() || rect1.GetRealRight() < rect2.GetRealLeft() 
			|| rect1.GetRealTop() < rect2.GetRealBottom() || rect1.GetRealBottom() > rect2.GetRealTop())
		{
			return false;
		}
		return true;
	}

	bool RectangleColliderComponent::OOBBRectangleRectangleCollision(const Rect& rect1, 
		const Rect& rect2) const
	{
		//First check if the rects are colliding as aabb
		if(!AABBRectangleRectangleCollision(rect1, rect2))
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

			if(CalculateAxisSpecificCollision(rect1, rect2, axis1) ||
			CalculateAxisSpecificCollision(rect1, rect2, axis2) ||
			CalculateAxisSpecificCollision(rect1, rect2, axis3) ||
			CalculateAxisSpecificCollision(rect1, rect2, axis4))
			{
				return true;
			}
			return false;
			
		}									  
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
		std::vector<float> vec1;
		vec1.push_back(AvecPosOnAxis1);
		vec1.push_back(AvecPosOnAxis2);
		vec1.push_back(AvecPosOnAxis3);
		vec1.push_back(AvecPosOnAxis4);
		std::vector<float> vec2; 
		vec2.push_back(BvecPosOnAxis1);
		vec2.push_back(BvecPosOnAxis2);
		vec2.push_back(BvecPosOnAxis3);
		vec2.push_back(BvecPosOnAxis4);

		float AMinimmum = CalculateMinimum(vec1);
		float BMinimmum = CalculateMinimum(vec2);
		float AMaximmum = CalculateMaximum(vec1);
		float BMaximmum = CalculateMaximum(vec2);

		if(BMinimmum <= AMinimmum || BMaximmum >= AMaximmum)
		{
			return true;
		}
		return false;
	}

	float RectangleColliderComponent::CalculateMinimum(std::vector<float> vec) const
	{
		ASSERT(vec.size() != 0,_T("Passed vector is empty"));

		float minimum = vec[0];
		for(auto elem : vec)
		{
			if(elem < minimum)
			{
				minimum = elem;
			}
		}
		return minimum;
	}

	float RectangleColliderComponent::CalculateMaximum(std::vector<float> vec) const
	{
		ASSERT(vec.size() != 0,_T("Passed vector is empty"));

		float minimum = vec[0];
		for(auto elem : vec)
		{
			if(elem > minimum)
			{
				minimum = elem;
			}
		}
		return minimum;
	}

	float RectangleColliderComponent::GetCollisionRectWidth() const
	{
		return m_CollisionRect.GetWidth();
	}

	float RectangleColliderComponent::GetCollisionRectHeight() const
	{
		return m_CollisionRect.GetHeight();
	}

	vec2 RectangleColliderComponent::GetColliisonRectSize() const
	{
		return vec2(m_CollisionRect.GetWidth(), m_CollisionRect.GetHeight());
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
		//mat4x4 projection = projectionObject->GetComponent<CameraComponent>()->GetProjection();
		mat4x4 viewInverse = projectionObject->GetComponent<CameraComponent>()->GetViewInverse();
		Rect temp = m_CollisionRect * ( viewInverse * GetTransform()->GetWorldMatrix());
		return temp;
	}
}
