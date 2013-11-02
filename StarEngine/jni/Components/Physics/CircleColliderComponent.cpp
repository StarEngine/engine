#include "CircleColliderComponent.h"
#include "../../Context.h"
#include "../../Objects/Object.h"
#include "../../Helpers/HelpersMath.h"

namespace star
{
	CircleColliderComponent::CircleColliderComponent(float radius)
		: BaseColliderComponent()
		, m_Radius(radius)
	{
	}

	CircleColliderComponent::CircleColliderComponent(float radius, const tstring* layer, uint8 tag)
		: BaseColliderComponent(layer, tag)
		, m_Radius(radius)
	{
	}


	CircleColliderComponent::~CircleColliderComponent(void)
	{
	}

	void CircleColliderComponent::InitializeColliderComponent()
	{
		ASSERT(m_Radius > 0, _T("Invalid Radius: Radius has to be > 0"));
	}

	bool CircleColliderComponent::CollidesWithPoint(const pos& point) const
	{
		float realRadius = GetRealRadius();
		pos localPos = m_pParentObject->GetTransform()->GetLocalPosition();
		return (glm::length(point.pos2D() - localPos.pos2D()) <= realRadius);
	}

	bool CircleColliderComponent::CollidesWithLine(const pos& point1, const pos& point2) const
	{
		/*/Ref page for more details:
		http://blog.csharphelper.com/2010/03/28/determine-where-a-line-intersects-a-circle-in-c.aspx
		*/

		float realRadius = GetRealRadius();

		float A, B, C, det;
		vec2 c, d;

		c = m_pParentObject->GetTransform()->GetLocalPosition().pos2D();

		d = point2.pos2D() - point1.pos2D();

		A = d.x * d.x + d.y * d.y;
		B = 2 * (d.x * (point1.x - c.x) + d.y * (point1.y - c.y));
		C = (point1.x - c.x) * (point1.x - c.x) + (point1.y - c.y) * (point1.y - c.y) - realRadius * realRadius;

		det = B * B - 4 * A * C;

		return !((A <= EPSILON) || (det < 0));
	}

	void CircleColliderComponent::CollidesWith(const BaseColliderComponent* other) const
	{
		float realRadius = GetRealRadius();
		auto otherCircleComp = reinterpret_cast<const CircleColliderComponent*>(other);
		auto otherRectComp = reinterpret_cast<const RectangleColliderComponent*>(other);

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
		return m_Radius * m_pParentObject->GetTransform()->GetLocalScale().x;
	}
}
