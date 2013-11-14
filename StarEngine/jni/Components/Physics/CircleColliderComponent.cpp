#include "CircleColliderComponent.h"
#include "../../Context.h"
#include "../../Objects/Object.h"
#include "../../Helpers/HelpersMath.h"
#include "../../Helpers/Debug/DebugDraw.h"

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
		float realRadius = GetRealRadius();
		pos localPos = m_pParentObject->GetTransform()->GetLocalPosition();
		return (glm::length(point - localPos.pos2D()) <= realRadius);
	}

	bool CircleColliderComponent::CollidesWithLine(const vec2& point1, const vec2& point2) const
	{
		/*/Ref page for more details:
		http://blog.csharphelper.com/2010/03/28/determine-where-a-line-intersects-a-circle-in-c.aspx
		*/

		float realRadius = GetRealRadius();

		float A, B, C, det;
		vec2 c, d;

		c = m_pParentObject->GetTransform()->GetLocalPosition().pos2D();

		d = point2 - point1;

		A = d.x * d.x + d.y * d.y;
		B = 2 * (d.x * (point1.x - c.x) + d.y * (point1.y - c.y));
		C = (point1.x - c.x) * (point1.x - c.x) + (point1.y - c.y) * (point1.y - c.y) - realRadius * realRadius;

		det = B * B - 4 * A * C;

		return !((A <= EPSILON) || (det < 0));
	}

	void CircleColliderComponent::CollidesWith(const BaseColliderComponent* other) const
	{
		float realRadius = GetRealRadius();
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
		float radius1 = collider1->GetRealRadius();
		float radius2 = collider2->GetRealRadius();
		glm::vec2 object1Pos = collider1->GetParent()->GetTransform()->GetWorldPosition().pos2D();
		glm::vec2 object2Pos = collider2->GetParent()->GetTransform()->GetWorldPosition().pos2D();

		return !((object1Pos - object2Pos).length() > radius1 + radius2);
	}

	float CircleColliderComponent::GetRadius() const
	{
		return m_Radius;
	}

	void CircleColliderComponent::SetRadius(float radius)
	{
		m_Radius = radius;
	}

	float CircleColliderComponent::GetRealRadius() const
	{
		return m_Radius * m_pParentObject->GetTransform()->GetWorldPosition().x;
	}

	void CircleColliderComponent::Draw()
	{
		DebugDraw::GetInstance()->DrawSolidCircle(
			m_pParentObject->GetTransform()->GetWorldPosition().pos2D() + m_Offset,GetRealRadius(), Color::Red);
	}
}
