#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "../../Objects/Object.h"
#include "../../Logger.h"
#include "../../Graphics/GraphicsManager.h"
#include "../Graphics/SpriteComponent.h"
#include "../../Helpers/Debug/DebugDraw.h"
#include "../../Helpers/Helpers.h"
#include "../../Helpers/Math.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/BaseScene.h"
#include "../../Physics/Collision/CollisionManager.h"

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
		, m_CollisionRect(
			vec2(),
			vec2(size.x, 0),
			vec2(0, size.y), 
			vec2(size.x, size.y)
		)
		, m_bDefaultInitialized(false)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(
		float32 width, 
		float32 height)
		: BaseColliderComponent()
		, m_CollisionRect
			(vec2(),
			vec2(width, 0),
			vec2(0, height), 
			vec2(width, height)
		)
		, m_bDefaultInitialized(false)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(
		const tstring* layers, 
		uint8 n)
		: BaseColliderComponent(layers, n)
		, m_CollisionRect()
		, m_bDefaultInitialized(true)
	{

	}

	RectangleColliderComponent::RectangleColliderComponent(
		const vec2& size, 
		const tstring* layers, 
		uint8 n)
		: BaseColliderComponent(layers, n)
		, m_CollisionRect(
			vec2(),
			vec2(size.x, 0),
			vec2(0, size.y), 
			vec2(size.x, size.y)
		)
		, m_bDefaultInitialized(false)
	{

	}
	RectangleColliderComponent::RectangleColliderComponent(
		float32 width, 
		float32 height, 
		const tstring* layers, 
		uint8 n)
		: BaseColliderComponent(layers, n)
		, m_CollisionRect(
			vec2(),
			vec2(width, 0),
			vec2(0, height), 
			vec2(width, height))
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
				Logger::GetInstance()->Log(spriteComp->IsInitialized(),
					_T("First add the spriteComponent and then the rectColliderComp"),
					STARENGINE_LOG_TAG);
				m_CollisionRect.SetPoints(
					vec2(0, 0),
					vec2(spriteComp->GetWidth(), 0), 
					vec2(0, spriteComp->GetHeight()), 
					vec2(spriteComp->GetWidth(), spriteComp->GetHeight())
					);
			}
			else
			{
				Logger::GetInstance()->Log(false, 
					_T("If you use the default constructor of the RectangleColliderComponent()\
, make sure to also add a SpriteComponent or SpriteSheetComponent. \
If you don't need this, please specify a width and height in the constructor of \
								If you don't need this, please specify a width \
								and height in the constructor of \n\
								the RectangleColliderComponent."),
								STARENGINE_LOG_TAG);
			}
		}

		GetParent()->GetScene()->GetCollisionManager()->AddComponent(this, m_Layers.elements, m_Layers.amount);
	}

	bool RectangleColliderComponent::CollidesWithPoint(const vec2& point) const
	{
		if(GetTransform()->GetWorldRotation() == 0.0f)
		{
			Rect rect(GetCollisionRect());
			return !(rect.GetLeftTop().x > point.x 
					|| rect.GetRightTop().x < point.x
					|| rect.GetLeftTop().y < point.y 
					|| rect.GetLeftBottom().y > point.y);
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

	bool RectangleColliderComponent::CollidesWithLine(
		const vec2& point1, 
		const vec2& point2
		) const
	{
		Logger::GetInstance()->Log(point1 != point2,
			_T("Please provide 2 different points to make a line!"),
			STARENGINE_LOG_TAG);

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
					returnValue = !(rect.GetLeftTop().x > point1.x 
								|| rect.GetRightTop().x < point1.x 
								|| rect.GetLeftTop().y < point1.y 
								|| rect.GetLeftBottom().y > point2.y);
				}
				else
				{
					returnValue = !(rect.GetLeftTop().x > point1.x 
								|| rect.GetRightTop().x < point1.x 
								|| rect.GetLeftTop().y < point2.y 
								|| rect.GetLeftBottom().y > point1.y);
				}
				return returnValue;;
			}
			else
			{
				if(point1.x < point2.x)
				{
					returnValue = !(rect.GetLeftTop().y < point1.y 
								|| rect.GetLeftBottom().y > point1.y 
								|| rect.GetRightBottom().x < point1.x 
								|| rect.GetLeftBottom().x > point2.x);
				}
				else
				{
					returnValue = !(rect.GetLeftTop().y < point1.y 
								|| rect.GetLeftBottom().y > point1.y 
								|| rect.GetRightBottom().x < point2.x 
								|| rect.GetLeftBottom().x > point1.x);
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

	bool RectangleColliderComponent::CollidesWith(const BaseColliderComponent* other) const
	{
		Logger::GetInstance()->Log(other != nullptr,
			_T("RectangleColliderComponent::CollidesWith: \
The collierComponent to check is a nullptr"), STARENGINE_LOG_TAG);
		const CircleColliderComponent* otherCircleComp = 
			dynamic_cast<const CircleColliderComponent*>(other);
		const RectangleColliderComponent* otherRectComp = 
			dynamic_cast<const RectangleColliderComponent*>(other);

		if(otherRectComp != nullptr)
		{
			Rect thisRect = GetCollisionRect();
			Rect otherRect = otherRectComp->GetCollisionRect();
			//Check to perform AABB or OOBB CollisionCheck!
			if(	GetTransform()->GetWorldRotation() == 0.0f && 
				otherRectComp->GetTransform()->GetWorldRotation() == 0.0f)
			{
				return AABBRectangleRectangleCollision(thisRect, otherRect);
			}
			else
			{
				return OOBBRectangleRectangleCollision(thisRect, otherRect);
			}
			
		}
		else if(otherCircleComp != nullptr)
		{

			return RectangleCircleCollision(this, otherCircleComp);
		}
		else
		{
			Logger::GetInstance()->
				Log(LogLevel::Warning, 
				_T("Checking collision with an unknown collider type!"));
			return false;
		}
	}

	bool RectangleColliderComponent::AABBRectangleRectangleCollision(const Rect& rect1,
		const Rect& rect2) const
	{
		return !(  rect1.GetLeftTop().x > rect2.GetRightTop().x 
				|| rect1.GetRightTop().x < rect2.GetLeftTop().x 
				|| rect1.GetLeftTop().y < rect2.GetLeftBottom().y 
				|| rect1.GetLeftBottom().y > rect2.GetLeftTop().y);
	}

	bool RectangleColliderComponent::OOBBRectangleRectangleCollision(const Rect& rect1, 
		const Rect& rect2) const
	{
		//First check if the rects are colliding as aabb
		if(	   rect1.GetRealLeft() > rect2.GetRealRight() 
			|| rect1.GetRealRight() < rect2.GetRealLeft() 
			|| rect1.GetRealTop() < rect2.GetRealBottom() 
			|| rect1.GetRealBottom() > rect2.GetRealTop())
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

	bool RectangleColliderComponent::CalculateAxisSpecificCollision(
		const Rect& rect,
		const vec2& point1,
		const vec2& point2,
		const vec2& axis
		) const
	{
		float32 AvecPosOnAxis1 = Dot(rect.GetLeftTop(), axis);
		float32 AvecPosOnAxis2 = Dot(rect.GetLeftBottom(), axis);
		float32 AvecPosOnAxis3 = Dot(rect.GetRightBottom(), axis);
		float32 AvecPosOnAxis4 = Dot(rect.GetRightTop(), axis);

		float32 BvecPosOnAxis1 = Dot(point1, axis);
		float32 BvecPosOnAxis2 = Dot(point2, axis);

		//Find Min and Max
		float32 vec1[4];
		vec1[0] = AvecPosOnAxis1;
		vec1[1] = AvecPosOnAxis2;
		vec1[2] = AvecPosOnAxis3;
		vec1[3] = AvecPosOnAxis4;

		float32 vec2[2];
		vec2[0] = BvecPosOnAxis1;
		vec2[1] = BvecPosOnAxis2;

		float32 AMinimum = CalculateMinimum(vec1, 4);
		float32 AMaximum = CalculateMaximum(vec1, 4);

		float32 BMinimum = CalculateMinimum(vec2, 2);
		float32 BMaximum = CalculateMaximum(vec2, 2);

		return (BMinimum <= AMaximum && BMaximum >= AMinimum);
	}

	bool RectangleColliderComponent::CalculateAxisSpecificCollision(
		const Rect& rect,
		const vec2& point, 
		const vec2& axis
		) const
	{
		float32 AvecPosOnAxis1 = Dot(rect.GetLeftTop(), axis);
		float32 AvecPosOnAxis2 = Dot(rect.GetLeftBottom(), axis);
		float32 AvecPosOnAxis3 = Dot(rect.GetRightBottom(), axis);
		float32 AvecPosOnAxis4 = Dot(rect.GetRightTop(), axis);

		float32 BvecPosOnAxis1 =  Dot(point, axis);

		float32 vec1[4];
		vec1[0] = AvecPosOnAxis1;
		vec1[1] = AvecPosOnAxis2;
		vec1[2] = AvecPosOnAxis3;
		vec1[3] = AvecPosOnAxis4;

		float32 AMinimum = CalculateMinimum(vec1, 4);
		float32 AMaximum = CalculateMaximum(vec1, 4);

		return (BvecPosOnAxis1 <= AMaximum && BvecPosOnAxis1 >= AMinimum);
	}

	bool RectangleColliderComponent::CalculateAxisSpecificCollision(
		const Rect& rect1,
		const Rect& rect2,
		const vec2& axis
		) const
	{
		float32 AvecPosOnAxis1 = Dot(rect1.GetLeftTop(), axis);
		float32 AvecPosOnAxis2 = Dot(rect1.GetLeftBottom(), axis);
		float32 AvecPosOnAxis3 = Dot(rect1.GetRightBottom(), axis);
		float32 AvecPosOnAxis4 = Dot(rect1.GetRightTop(), axis);

		float32 BvecPosOnAxis1 = Dot(rect2.GetLeftTop(), axis);
		float32 BvecPosOnAxis2 = Dot(rect2.GetLeftBottom(), axis);
		float32 BvecPosOnAxis3 = Dot(rect2.GetRightBottom(), axis);
		float32 BvecPosOnAxis4 = Dot(rect2.GetRightTop(), axis);

		float32 vec1[4];
		vec1[0] = AvecPosOnAxis1;
		vec1[1] = AvecPosOnAxis2;
		vec1[2] = AvecPosOnAxis3;
		vec1[3] = AvecPosOnAxis4;

		float32 vec2[4]; 
		vec2[0] = BvecPosOnAxis1;
		vec2[1] = BvecPosOnAxis2;
		vec2[2] = BvecPosOnAxis3;
		vec2[3] = BvecPosOnAxis4;

		float32 AMinimum = CalculateMinimum(vec1, 4);
		float32 BMinimum = CalculateMinimum(vec2, 4);
		float32 AMaximum = CalculateMaximum(vec1, 4);
		float32 BMaximum = CalculateMaximum(vec2, 4);

		return BMinimum <= AMaximum && BMaximum >= AMinimum;
	}

	float32 RectangleColliderComponent::CalculateMinimum(
		const float32* vec, 
		uint8 size
		) const
	{
		Logger::GetInstance()->Log(size != 0,
			_T("You can't calculate the minimum of 0 elements!"),
			STARENGINE_LOG_TAG);
		float32 minimum = vec[0];
		for(int32 i = 1; i < size; ++i)
		{
			if(vec[i] < minimum)
			{
				minimum = vec[i];
			}
		}
		return minimum;
	}

	float32 RectangleColliderComponent::CalculateMaximum(
		const float32* vec, 
		uint8 size
		) const
	{
		Logger::GetInstance()->Log(size != 0, 
			_T("You can't calculate the maximum of 0 elements!"),
			STARENGINE_LOG_TAG);
		float32 maximum = vec[0];
		for(int32 i = 1; i < size; ++i)
		{
			if(vec[i] > maximum)
			{
				maximum = vec[i];
			}
		}
		return maximum;
	}

	float32 RectangleColliderComponent::GetCollisionRectWidth() const
	{
		return GetCollisionRect().GetWidth();
	}

	float32 RectangleColliderComponent::GetCollisionRectHeight() const
	{
		return GetCollisionRect().GetHeight();
	}

	void RectangleColliderComponent::GetColliisonRectSize(vec2& outputVec) const
	{
		outputVec.x = GetCollisionRectWidth();
		outputVec.y = GetCollisionRectHeight();
	}

	void RectangleColliderComponent::SetCollisionRectSize(
		float32 width, 
		float32 height)
	{
		m_CollisionRect.SetPoints
			(vec2(0, 0), 
			vec2(width, 0), 
			vec2(0, height), 
			vec2(width, height));
	}

	void RectangleColliderComponent::SetCollisionRectSize(const vec2& size)
	{
		m_CollisionRect.SetPoints(
			vec2(0, 0), 
			vec2(size.x, 0), 
			vec2(0, size.y), 
			vec2(size.x, size.y));
	}

	Rect RectangleColliderComponent::GetCollisionRect() const
	{
		Rect temp((m_CollisionRect * GetTransform()->GetWorldMatrix()) 
			* GraphicsManager::GetInstance()->GetViewInverseMatrix());
		return temp;
	}

	vec2 RectangleColliderComponent::GetCenterPoint() const
	{
		vec4 pos;
		pos.x = m_CollisionRect.GetCenterPoint().x;
		pos.y = m_CollisionRect.GetCenterPoint().y;
		pos.w = 1;
		pos = Mul(pos, Transpose(GetTransform()->GetWorldMatrix()));
		pos = Mul(pos, 
			Transpose(GraphicsManager::GetInstance()->GetViewInverseMatrix()));
		return vec2(pos.x, pos.y);
	}

	vec2 RectangleColliderComponent::GetOrientatedUnitVecX() const
	{
		vec4 unitVec(1, 0, 0, 1);
		unitVec = Mul(unitVec, Transpose(GetTransform()->GetWorldMatrix()));
		unitVec = Mul(unitVec, 
			Transpose(GraphicsManager::GetInstance()->GetViewInverseMatrix()));
		unitVec = Normalize(unitVec);
		return vec2(unitVec.x, unitVec.y);
	}

	vec2 RectangleColliderComponent::GetOrientatedUnitVecY() const
	{
		vec4 unitVec(0, 1, 0, 1);
		unitVec = Mul(unitVec, Transpose(GetTransform()->GetWorldMatrix()));
		unitVec = Mul(unitVec, 
			Transpose(GraphicsManager::GetInstance()->GetViewInverseMatrix()));
		unitVec = Normalize(unitVec);
		return vec2(unitVec.x, unitVec.y);
	}

	void RectangleColliderComponent::Draw()
	{
		DebugDraw::GetInstance()->DrawSolidRect(GetCollisionRect(),Color::White);
	}
}
