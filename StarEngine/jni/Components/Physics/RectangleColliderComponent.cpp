#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "../../Objects/Object.h"
#include "../../Logger.h"
namespace star
{
	RectangleColliderComponent::RectangleColliderComponent(const vec2& leftTop, 
			const vec2& rightTop, const vec2& leftBottom, const vec2& rightBottom)
		: BaseColliderComponent()
		, m_CollisionRect(leftTop,rightTop, leftBottom, rightBottom)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(const Rect& rect)
		: BaseColliderComponent()
		, m_CollisionRect(rect)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(const vec2& leftTop, const vec2& rightTop,
			const vec2& leftBottom, const vec2& rightBottom, const tstring* layers, uint8 n)
		: BaseColliderComponent(layers, n)
		, m_CollisionRect(leftTop,rightTop, leftBottom, rightBottom)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(const Rect& rect, 
			const tstring* layers, uint8 n)
		: BaseColliderComponent(layers, n)
		, m_CollisionRect(rect)
	{

	}

	RectangleColliderComponent::~RectangleColliderComponent()
	{
	}

	void RectangleColliderComponent::InitializeColliderComponent()
	{
		
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
			if(RectangleRectangleCollision(GetCollisionRect(), otherRectComp->GetCollisionRect()))
			{
				Logger::GetInstance()->Log(LogLevel::Info, _T("Collision Detected"));
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

	bool RectangleColliderComponent::RectangleRectangleCollision(const Rect& rect1, 
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

	const Rect& RectangleColliderComponent::GetCollisionRect() const
	{
		return m_CollisionRect;
	}

	void RectangleColliderComponent::SetCollisionRect(const Rect& rect)
	{
		m_CollisionRect = rect;
	}


}
