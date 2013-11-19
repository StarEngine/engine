#include "CircleColliderComponent.h"
#include "../../Context.h"
#include "../../Objects/Object.h"
#include "../../Helpers/HelpersMath.h"
#include "../../Helpers/Debug/DebugDraw.h"
#include "../../Graphics/GraphicsManager.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/BaseScene.h"
#include "../../Physics/Collision/CollisionManager.h"

namespace star
{
#define COLLISION_MANAGER (SceneManager::GetInstance()->GetActiveScene()->GetCollisionManager())

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

		COLLISION_MANAGER->AddComponent(this, m_Layers.elements, m_Layers.amount);
	}

	bool CircleColliderComponent::CollidesWithPoint(const vec2& point) const
	{
		
		return (glm::length(point - GetPosition()) <= GetRealRadius());
	}

	bool CircleColliderComponent::CollidesWithLine(const vec2& point1, const vec2& point2) const
	{
		//Check if circle is inside of boundaries of the line.
		vec2 circlePos(GetPosition());
		float radius = GetRealRadius();
		//Check smallest point in x and y
		if(point1.x < point2.x)
		{
			if(circlePos.x + radius < point1.x)
			{
				return false;
			}
			if(circlePos.x - radius > point2.x)
			{
				return false;
			}
		}
		else
		{
			if(circlePos.x + radius < point2.x)
			{
				return false;
			}
			if(circlePos.x - radius > point1.x)
			{
				return false;
			}
		}

		if(point1.y < point2.y)
			{
				if(circlePos.y + radius < point1.y)
				{
					return false;
				}
				if(circlePos.y - radius > point2.y)
				{
					return false;
				}
			}
			else
			{
				if(circlePos.y + radius < point2.y)
				{
					return false;
				}
				if(circlePos.y - radius > point1.y)
				{
					return false;
				}
			}
		//The circle is inside the boundaries of the line!
		vec2 lineVec(glm::normalize(point2 - point1));
		float closestPointOnLineSize(glm::dot(circlePos - point1,lineVec));
		vec2 closestPointOnLine(closestPointOnLineSize * lineVec);
		closestPointOnLine = point1 + closestPointOnLine;

		return glm::length(circlePos - closestPointOnLine) <= radius;
		
	}

	bool CircleColliderComponent::CollidesWith(const BaseColliderComponent* other) const
	{
		ASSERT(other != nullptr, 
			_T("CircleColliderComponent::CollidesWith: \
			   The collierComponent to check is a nullptr"));

		auto otherCircleComp = dynamic_cast<const CircleColliderComponent*>(other);
		auto otherRectComp = dynamic_cast<const RectangleColliderComponent*>(other);

		if(otherCircleComp != nullptr)
		{
			return CircleCircleCollision(this, otherCircleComp);
		}
		else if(otherRectComp != nullptr)
		{
			return RectangleCircleCollision(otherRectComp, this);
		}
	}

	bool CircleColliderComponent::CircleCircleCollision(const CircleColliderComponent* collider1, 
		const CircleColliderComponent* collider2) const
	{
		float radius1 = collider1->GetRealRadius();
		float radius2 = collider2->GetRealRadius();
		vec2 object1Pos(collider1->GetPosition());
		vec2 object2Pos(collider2->GetPosition());

		return !(glm::abs(glm::length((object1Pos - object2Pos))) > (radius1 + radius2));
	}

	float CircleColliderComponent::GetRadius() const
	{
		return m_Radius;
	}

	float CircleColliderComponent::GetRealRadius() const
	{
		float xScale(m_Radius * GetTransform()->GetWorldScale().x);
		float yScale(m_Radius * GetTransform()->GetWorldScale().y);

		return (xScale > yScale ? xScale : yScale);
	}

	vec2 CircleColliderComponent::GetPosition() const
	{
		vec4 realPos(m_Offset.x, m_Offset.y, 0, 1);
		realPos = glm::mul(realPos, TransposeMatrix(GetTransform()->GetWorldMatrix()));
		realPos = glm::mul(realPos, TransposeMatrix(
			GraphicsManager::GetInstance()->GetViewInverseMatrix()));
		return vec2(realPos.x, realPos.y);
	}

	void CircleColliderComponent::GetPosition(vec2& posOut) const
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
			, GetRealRadius(), Color::Blue);
	}
}
