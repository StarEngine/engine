#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "../../Objects/Object.h"
#include "../../Logger.h"
#include "../../Graphics/GraphicsManager.h"
#include "../Graphics/SpriteComponent.h"
#include "../../Helpers/Debug/DebugDraw.h"
#include "../../Graphics/ScaleSystem.h"
#include "../../Helpers/Helpers.h"

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
				m_CollisionRect.SetPoints(vec2(0,0),
					vec2(spriteComp->GetWidth(), 0), 
					vec2(0, spriteComp->GetHeight()), 
					vec2(spriteComp->GetWidth(), 
						spriteComp->GetHeight()));
			}
			else
			{
				ASSERT(false, _T("If you use the default constructor of the RectangleColliderComponent()\n\
								, make sure to also add a SpriteComponent or SpriteSheetComponent. \n\
								If you don't need this, please specify a width and height in the constructor of \n\
								the RectangleColliderComponent."));
			}
		}
	}

	bool RectangleColliderComponent::CollidesWithPoint(const vec2& point) const
	{
		if(GetTransform()->GetWorldRotation() == 0.0f)
		{
			Rect rect(GetCollisionRect());
			return !(rect.GetLeftTop().x > point.x || rect.GetRightTop().x < point.x
					|| rect.GetLeftTop().y < point.y || rect.GetLeftBottom().y > point.y);
		}
		else
		{
			//SAT with only the 2 axises of the OOBB, and compare the point
			Rect rect(GetCollisionRect());
			//SAT works with the perpendicular axises of the shapes, 
			//but for a rect, the perpendicular axises are the other axises (angles are 90°)
			vec2 axis1(rect.GetRightTop() - rect.GetLeftTop());
			vec2 axis2(rect.GetRightTop() - rect.GetRightBottom());

			if(!CalculateAxisSpecificCollision(rect, point, axis1))
			{
				return false;		
			}
			if(!CalculateAxisSpecificCollision(rect, point, axis2))
			{
				return false;
			}
			return true;
		}
		
	}

	bool RectangleColliderComponent::CollidesWithLine(const vec2& point1, const vec2& point2) const
	{
		ASSERT(point1 != point2, _T("Please provide 2 different points to make a line!"));

		if(GetTransform()->GetWorldRotation() == 0.0f && (point1.x == point2.x || point1.y == point2.y))
		{
			//If rect is AABB and line also AA
			Rect rect(GetCollisionRect());
			bool returnValue(false);
			if(point1.x == point2.x)
			{
				//Line is vertical
				//if lowest point of line is bigger than highest point of rect or
				//if highest point of line is smaller than lowest point of rect
				if(point1.y < point2.y)
				{
					returnValue = !(rect.GetLeftTop().x > point1.x || rect.GetRightTop().x < point1.x 
						|| rect.GetLeftTop().y < point1.y || rect.GetLeftBottom().y > point2.y);
				}
				else
				{
					returnValue = !(rect.GetLeftTop().x > point1.x || rect.GetRightTop().x < point1.x 
						|| rect.GetLeftTop().y < point2.y || rect.GetLeftBottom().y > point1.y);
				}
				return returnValue;;
			}
			else
			{
				if(point1.x < point2.x)
				{
					returnValue = !(rect.GetLeftTop().y < point1.y || rect.GetLeftBottom().y > point1.y 
						|| rect.GetRightBottom().x < point1.x || rect.GetLeftBottom().x > point2.x);
				}
				else
				{
					returnValue = !(rect.GetLeftTop().y < point1.y || rect.GetLeftBottom().y > point1.y 
						|| rect.GetRightBottom().x < point2.x || rect.GetLeftBottom().x > point1.x);
				}
				return returnValue;;
			}
		}
		else
		{
			Rect rect(GetCollisionRect());
			//perpendicular of a vec =  (-y , x) or (y, -x)
			vec2 axis1(-(point2 - point1).y , (point2 - point1).x);
			vec2 axis2(rect.GetRightTop() - rect.GetLeftTop());
			vec2 axis3(rect.GetRightTop() - rect.GetRightBottom());

			if(!CalculateAxisSpecificCollision(rect, point1, point2, axis1))
			{
				return false;
			}
			if(!CalculateAxisSpecificCollision(rect, point1, point2, axis2))
			{
				return false;
			}
			if(!CalculateAxisSpecificCollision(rect, point1, point2, axis3))
			{
				return false;
			}
			return true;
		}
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
		else if(otherCircleComp != nullptr)
		{
			if(GetTransform()->GetWorldRotation() == 0.0f)
			{
				if(RectangleCircleCollision(this, otherCircleComp))
				{

				}
			}
			else
			{
				//[TODO] OOBB - Circle Collision!
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
			vec2 axis1, axis2, axis3, axis4;
			axis1 = rect1.GetRightTop() - rect1.GetLeftTop();
			axis2 = rect1.GetRightTop() - rect1.GetRightBottom();
			axis3 = rect2.GetLeftTop() - rect2.GetLeftBottom();
			axis4 = rect2.GetLeftTop() - rect2.GetRightTop();

			if(!CalculateAxisSpecificCollision(rect1, rect2, axis1))
			{
				return false;
			}
			if(!CalculateAxisSpecificCollision(rect1, rect2, axis2))
			{
				return false;
			}
			if(!CalculateAxisSpecificCollision(rect1, rect2, axis3))
			{
				return false;
			}
			if(!CalculateAxisSpecificCollision(rect1, rect2, axis4))
			{
				return false;
			}
			return true;
		}									  
	}		

	bool RectangleColliderComponent::CalculateAxisSpecificCollision(const Rect& rect, 
		const vec2& point1, const vec2& point2, const vec2& axis) const
	{
		float AvecPosOnAxis1 = glm::dot(rect.GetLeftTop(),axis);
		float AvecPosOnAxis2 = glm::dot(rect.GetLeftBottom(),axis);
		float AvecPosOnAxis3 = glm::dot(rect.GetRightBottom(),axis);
		float AvecPosOnAxis4 = glm::dot(rect.GetRightTop(),axis);

		float BvecPosOnAxis1 = glm::dot(point1,axis);
		float BvecPosOnAxis2 = glm::dot(point2,axis);

		//Find Min and Max
		float vec1[4];
		vec1[0] = AvecPosOnAxis1;
		vec1[1] = AvecPosOnAxis2;
		vec1[2] = AvecPosOnAxis3;
		vec1[3] = AvecPosOnAxis4;

		float vec2[2];
		vec2[0] = BvecPosOnAxis1;
		vec2[1] = BvecPosOnAxis2;

		float AMinimum = CalculateMinimum(vec1, 4);
		float AMaximum = CalculateMaximum(vec1, 4);

		float BMinimum = CalculateMinimum(vec2, 2);
		float BMaximum = CalculateMaximum(vec2, 2);

		return (BMinimum <= AMaximum && BMaximum >= AMinimum);
	}

	bool RectangleColliderComponent::CalculateAxisSpecificCollision(const Rect& rect,
		const vec2& point, const vec2& axis) const
	{
		float AvecPosOnAxis1 = glm::dot(rect.GetLeftTop(), axis);
		float AvecPosOnAxis2 = glm::dot(rect.GetLeftBottom(), axis);
		float AvecPosOnAxis3 = glm::dot(rect.GetRightBottom(), axis);
		float AvecPosOnAxis4 = glm::dot(rect.GetRightTop(), axis);

		float BvecPosOnAxis1 =  glm::dot(point, axis);

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
		float AvecPosOnAxis1 = glm::dot(rect1.GetLeftTop(),axis);
		float AvecPosOnAxis2 = glm::dot(rect1.GetLeftBottom(),axis);
		float AvecPosOnAxis3 = glm::dot(rect1.GetRightBottom(),axis);
		float AvecPosOnAxis4 = glm::dot(rect1.GetRightTop(),axis);

		float BvecPosOnAxis1 = glm::dot(rect2.GetLeftTop(),axis);
		float BvecPosOnAxis2 = glm::dot(rect2.GetLeftBottom(),axis);
		float BvecPosOnAxis3 = glm::dot(rect2.GetRightBottom(),axis);
		float BvecPosOnAxis4 = glm::dot(rect2.GetRightTop(),axis);

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

		return BMinimum <= AMaximum && BMaximum >= AMinimum;
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
		Rect temp = (m_CollisionRect * GetTransform()->GetWorldMatrix()) 
			* GraphicsManager::GetInstance()->GetViewInverseMatrix();
		return temp;
	}

	void RectangleColliderComponent::Draw()
	{
		DebugDraw::GetInstance()->DrawScaledSolidRect(GetCollisionRect(),Color::White);
	}
}
