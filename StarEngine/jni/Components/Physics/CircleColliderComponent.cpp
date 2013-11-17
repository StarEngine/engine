#include "CircleColliderComponent.h"
#include "../../Context.h"
#include "../../Objects/Object.h"
#include "../../Helpers/HelpersMath.h"
#include "../../Helpers/Debug/DebugDraw.h"
#include "../../Graphics/GraphicsManager.h"

namespace star
{
	CircleColliderComponent::CircleColliderComponent()
		: BaseColliderComponent()
		, m_Radius(0)
		, m_Offset()
		, m_bDefaultInitialized(true)
	{

	}

	CircleColliderComponent::CircleColliderComponent(const tstring* layers, uint8 n)
		: BaseColliderComponent(layers, n)
		, m_Radius(0)
		, m_Offset()
		, m_bDefaultInitialized(true)
	{

	}

	CircleColliderComponent::CircleColliderComponent(float radius)
		: BaseColliderComponent()
		, m_Radius(radius)
		, m_Offset()
		, m_bDefaultInitialized(false)
	{
	}

	CircleColliderComponent::CircleColliderComponent(float radius, const tstring* layers, uint8 tag)
		: BaseColliderComponent(layers, tag)
		, m_Radius(radius)
		, m_Offset()
		, m_bDefaultInitialized(false)
	{
	}

	CircleColliderComponent::CircleColliderComponent(float radius, const vec2& offset)
		: BaseColliderComponent()
		, m_Radius(radius)
		, m_Offset(offset)
		, m_bDefaultInitialized(false)
	{
	}

	CircleColliderComponent::CircleColliderComponent(float radius, const vec2& offset,
		const tstring* layers, uint8 tag)
			: BaseColliderComponent(layers, tag)
			, m_Radius(radius)
			, m_Offset(offset)
			, m_bDefaultInitialized(false)
	{
	}


	CircleColliderComponent::~CircleColliderComponent(void)
	{
	}

	void CircleColliderComponent::InitializeColliderComponent()
	{
		if(m_bDefaultInitialized)
		{
			//Initialize the rectangle with the values of the visible part of the sprite
			SpriteComponent* spriteComp = GetParent()->GetComponent<SpriteComponent>();
			if(spriteComp)
			{
				ASSERT(spriteComp->IsInitialized(),_T("First add the spriteComponent and then the rectColliderComp"));
				if(spriteComp->GetWidth() > spriteComp->GetHeight())
				{
					m_Radius = float(spriteComp->GetWidth() / 2.0f);
				}
				else
				{
					m_Radius = float(spriteComp->GetHeight() / 2.0f);
				}
				m_Offset.x = spriteComp->GetWidth() / 2.0f;
				m_Offset.y = spriteComp->GetHeight() / 2.0f;
			}
			else
			{
				ASSERT(false, _T("If you use the default constructor of the CircleColliderComponent()\n\
								, make sure to also add a SpriteComponent or SpriteSheetComponent. \n\
								If you don't need this, please specify a radius in the constructor of \n\
								the CircleColliderComponent."));
			}
		}
		ASSERT(m_Radius > 0, _T("Invalid Radius: Radius has to be > 0"));
	}

	bool CircleColliderComponent::CollidesWithPoint(const vec2& point) const
	{
		
		return (glm::length(point - GetPosition()) <= m_Radius);
	}

	bool CircleColliderComponent::CollidesWithLine(const vec2& point1, const vec2& point2) const
	{
		//Check if circle is inside of boundaries of the line.
		vec2 circlePos(GetPosition());
		//Check smallest point in x and y
		if(point1.x < point2.x)
		{
			if(circlePos.x + m_Radius < point1.x)
			{
				return false;
			}
			if(circlePos.x - m_Radius > point2.x)
			{
				return false;
			}
		}
		else
		{
			if(circlePos.x + m_Radius < point2.x)
			{
				return false;
			}
			if(circlePos.x - m_Radius > point1.x)
			{
				return false;
			}
		}

		if(point1.y < point2.y)
			{
				if(circlePos.y + m_Radius < point1.y)
				{
					return false;
				}
				if(circlePos.y - m_Radius > point2.y)
				{
					return false;
				}
			}
			else
			{
				if(circlePos.y + m_Radius < point2.y)
				{
					return false;
				}
				if(circlePos.y - m_Radius > point1.y)
				{
					return false;
				}
			}
		//The circle is inside the boundaries of the line!
		vec2 lineVec(glm::normalize(point2 - point1));
		float closestPointOnLineSize(glm::dot(circlePos - point1,lineVec));
		vec2 closestPointOnLine(closestPointOnLineSize * lineVec);
		closestPointOnLine = point1 + closestPointOnLine;

		return glm::length(circlePos - closestPointOnLine) <= m_Radius;
		
	}

	void CircleColliderComponent::CollidesWith(const BaseColliderComponent* other) const
	{
		auto otherCircleComp = dynamic_cast<const CircleColliderComponent*>(other);
		auto otherRectComp = dynamic_cast<const RectangleColliderComponent*>(other);

		if(otherCircleComp != nullptr)
		{
			if(CircleCircleCollision(this, otherCircleComp))
			{
				
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

	bool CircleColliderComponent::CircleCircleCollision(const CircleColliderComponent* collider1, 
		const CircleColliderComponent* collider2) const
	{
		float radius1 = collider1->GetRadius();
		float radius2 = collider2->GetRadius();
		glm::vec2 object1Pos = collider1->GetParent()->GetTransform()->GetWorldPosition().pos2D();
		glm::vec2 object2Pos = collider2->GetParent()->GetTransform()->GetWorldPosition().pos2D();

		return !((object1Pos - object2Pos).length() > radius1 + radius2);
	}

	float CircleColliderComponent::GetRadius() const
	{
		return m_Radius;
	}

	vec2 CircleColliderComponent::GetPosition() const
	{
		vec4 realPos(m_Offset.x, m_Offset.y, 0, 1);
		realPos = glm::mul(realPos, TransposeMatrix(GetTransform()->GetWorldMatrix()));
		realPos = glm::mul(realPos, TransposeMatrix(
			GraphicsManager::GetInstance()->GetViewInverseMatrix()));
		return vec2(realPos.x, realPos.y);
	}

	void CircleColliderComponent::GetPosition(vec2& posOut)
	{
		vec4 realPos(m_Offset.x, m_Offset.y, 0, 1);
		realPos = glm::mul(realPos, TransposeMatrix(GetTransform()->GetWorldMatrix()));
		realPos = glm::mul(realPos, TransposeMatrix(
			GraphicsManager::GetInstance()->GetViewInverseMatrix()));
		posOut.x = realPos.x;
		posOut.y = realPos.y;
	}

	void CircleColliderComponent::SetRadius(float radius)
	{
		m_Radius = radius;
	}

	void CircleColliderComponent::Draw()
	{
		
		DebugDraw::GetInstance()->DrawSolidCircle(GetPosition()
			, m_Radius, Color::Blue);
	}
}
