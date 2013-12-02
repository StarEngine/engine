#include "CircleColliderComponent.h"
#include "../../Context.h"
#include "../../Objects/Object.h"
#include "../../Helpers/Math.h"
#include "../../Helpers/Debug/DebugDraw.h"
#include "../../Graphics/GraphicsManager.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/BaseScene.h"
#include "../../Physics/Collision/CollisionManager.h"

namespace star
{
	CircleColliderComponent::CircleColliderComponent()
		: BaseColliderComponent()
		, m_Radius(0)
		, m_Offset()
		, m_bDefaultInitialized(true)
	{

	}

	CircleColliderComponent::CircleColliderComponent(
		const tstring* layers, 
		uint8 n)
		: BaseColliderComponent(layers, n)
		, m_Radius(0)
		, m_Offset()
		, m_bDefaultInitialized(true)
	{

	}

	CircleColliderComponent::CircleColliderComponent(float32 radius)
		: BaseColliderComponent()
		, m_Radius(radius)
		, m_Offset()
		, m_bDefaultInitialized(false)
	{
	}

	CircleColliderComponent::CircleColliderComponent(
		float32 radius, 
		const tstring* layers, 
		uint8 tag)
		: BaseColliderComponent(layers, tag)
		, m_Radius(radius)
		, m_Offset()
		, m_bDefaultInitialized(false)
	{
	}

	CircleColliderComponent::CircleColliderComponent
		(float32 radius, 
		const vec2& offset)
		: BaseColliderComponent()
		, m_Radius(radius)
		, m_Offset(offset)
		, m_bDefaultInitialized(false)
	{
	}

	CircleColliderComponent::CircleColliderComponent(
		float32 radius, 
		const vec2& offset,
		const tstring* layers, 
		uint8 tag)
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
				Logger::GetInstance()->Log(spriteComp->IsInitialized(),
					_T("First add the spriteComponent and then the rectColliderComp"),
					STARENGINE_LOG_TAG);
				if(spriteComp->GetWidth() > spriteComp->GetHeight())
				{
					m_Radius = float32(spriteComp->GetWidth() / 2.0f);
				}
				else
				{
					m_Radius = float32(spriteComp->GetHeight() / 2.0f);
				}
				m_Offset.x = spriteComp->GetWidth() / 2.0f;
				m_Offset.y = spriteComp->GetHeight() / 2.0f;
			}
			else
			{
				Logger::GetInstance()->Log(false,
					_T("If you use the default constructor of the CircleColliderComponent()\
, make sure to also add a SpriteComponent or SpriteSheetComponent. \
If you don't need this, please specify a radius in the constructor of \
the CircleColliderComponent."), STARENGINE_LOG_TAG);
			}
		}
		Logger::GetInstance()->Log(m_Radius > 0,
			_T("Invalid Radius: Radius has to be > 0"), STARENGINE_LOG_TAG);

		GetParent()->GetScene()->GetCollisionManager()->
			AddComponent(this, m_Layers.elements, m_Layers.amount);
	}

	bool CircleColliderComponent::CollidesWithPoint(const vec2& point) const
	{
		
		return (Mag(point - GetPosition()) <= GetRealRadius());
	}

	bool CircleColliderComponent::CollidesWithLine(
		const vec2& point1,
		const vec2& point2
		) const
	{
		//Check if circle is inside of boundaries of the line.
		vec2 circlePos(GetPosition());
		float32 radius = GetRealRadius();
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
		vec2 lineVec(Normalize(point2 - point1));
		float32 closestPointOnLineSize(Dot(circlePos - point1, lineVec));
		vec2 closestPointOnLine(closestPointOnLineSize * lineVec);
		closestPointOnLine = point1 + closestPointOnLine;

		return Mag(circlePos - closestPointOnLine) <= radius;
		
	}

	bool CircleColliderComponent::CollidesWith(const BaseColliderComponent* other) const
	{
		Logger::GetInstance()->Log(other != nullptr, 
			_T("CircleColliderComponent::CollidesWith: \
The collierComponent to check is a nullptr"), STARENGINE_LOG_TAG);

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
		else
		{
			Logger::GetInstance()->
				Log(LogLevel::Warning, _T("Checking collision with an unknown collider type!"));
			return false;
		}
	}

	bool CircleColliderComponent::CircleCircleCollision(
		const CircleColliderComponent* collider1, 
		const CircleColliderComponent* collider2
		) const
	{
		float32 radius1 = collider1->GetRealRadius();
		float32 radius2 = collider2->GetRealRadius();
		vec2 object1Pos(collider1->GetPosition());
		vec2 object2Pos(collider2->GetPosition());

		return !(abs(Mag((object1Pos - object2Pos))) > (radius1 + radius2));
	}

	float32 CircleColliderComponent::GetRadius() const
	{
		return m_Radius;
	}

	float32 CircleColliderComponent::GetRealRadius() const
	{
		float32 xScale(m_Radius * GetTransform()->GetWorldScale().x);
		float32 yScale(m_Radius * GetTransform()->GetWorldScale().y);

		return (xScale > yScale ? xScale : yScale);
	}

	vec2 CircleColliderComponent::GetPosition() const
	{
		vec4 realPos(m_Offset.x, m_Offset.y, 0, 1);
		realPos = Mul(realPos, Transpose(GetTransform()->GetWorldMatrix()));
		realPos = Mul(realPos, Transpose(
			GraphicsManager::GetInstance()->GetViewInverseMatrix()));
		return vec2(realPos.x, realPos.y);
	}

	void CircleColliderComponent::GetPosition(vec2& posOut) const
	{
		vec4 realPos(m_Offset.x, m_Offset.y, 0, 1);
		realPos = Mul(realPos, Transpose(GetTransform()->GetWorldMatrix()));
		realPos = Mul(realPos, Transpose(
			GraphicsManager::GetInstance()->GetViewInverseMatrix()));
		posOut.x = realPos.x;
		posOut.y = realPos.y;
	}

	void CircleColliderComponent::SetRadius(float32 radius)
	{
		m_Radius = radius;
	}

	void CircleColliderComponent::Draw()
	{		
		DebugDraw::GetInstance()->DrawSolidCircle(GetPosition()
			, GetRealRadius(), Color::Blue);
	}
}
