#include "BaseColliderComponent.h"
#include "../../Context.h"
#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "../TransformComponent.h"
#include "../../Helpers/Math.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/BaseScene.h"
#include "../../Physics/Collision/CollisionManager.h"

namespace star
{
	const tstring BaseColliderComponent::DEFAULT_LAYER_NAME = _T("default");
	BaseColliderComponent::BaseColliderComponent()
		: BaseComponent()
		, m_bIsTrigger(false)
		, m_bIsStatic(false)
		, m_Entered(false)
		, m_Exited(true)
		, m_OnEnter(nullptr)
		, m_OnStay(nullptr)
		, m_OnExit(nullptr)
	{
		m_Layers.amount = 1;
		m_Layers.elements = new tstring[1];
		m_Layers.elements[0] = DEFAULT_LAYER_NAME;
	}

	BaseColliderComponent::BaseColliderComponent(const tstring* layers, uint8 n)
		: BaseComponent()
		, m_bIsTrigger(false)
		, m_bIsStatic(false)
		, m_Entered(false)
		, m_Exited(true)
		, m_OnEnter(nullptr)
		, m_OnStay(nullptr)
		, m_OnExit(nullptr)
	{
		m_Layers.amount = n;
		m_Layers.elements = new tstring[m_Layers.amount];
		for(uint8 i = 0; i < m_Layers.amount; ++i)
		{
			m_Layers.elements[i] = layers[i];
		}
	}

	BaseColliderComponent::~BaseColliderComponent()
	{
		SceneManager::GetInstance()->GetActiveScene()->GetCollisionManager()->RemoveComponent(this);
		delete[] m_Layers.elements;
	}

	void BaseColliderComponent::InitializeComponent()
	{
		InitializeColliderComponent();
	}

	void BaseColliderComponent::Update(const Context& context)
	{
		/*
		If the component is not static and is not a trigger, 
		then we need to update the force impacts of the object. 
		For example if the collider is hit by another collider 
		and by the force he moves and rotates a little bit. 
		IN this update we’ll handle that. 
		*/
		/*if(!m_bIsStatic && !m_bIsTrigger)
		{

		}*/
	}

	void BaseColliderComponent::SetOnEnterCallback(Callback onEnter)
	{
		m_OnEnter = onEnter;
	}

	void BaseColliderComponent::SetOnStayCallback(Callback onStay)
	{
		m_OnStay = onStay;
	}

	void BaseColliderComponent::SetOnExitCallback(Callback onExit)
	{
		m_OnExit = onExit;
	}

	void BaseColliderComponent::TriggerOnEnter()
	{
		if(m_OnEnter)
		{
			m_OnEnter();		
		}
	}

	void BaseColliderComponent::TriggerOnStay()
	{
		if(m_OnStay)
		{
			m_OnStay();
		}
	}

	void BaseColliderComponent::TriggerOnExit()
	{
		if(m_OnExit)
		{
			m_OnExit();
		}
	}

	void BaseColliderComponent::Draw()
	{
		//empty
	}
	
	void BaseColliderComponent::SetAsTrigger(bool isTrigger)
	{
		m_bIsTrigger = isTrigger;
	}

	bool BaseColliderComponent::IsTrigger() const
	{
		return m_bIsTrigger;
	}

	void BaseColliderComponent::SetAsStatic(bool isStatic)
	{
		m_bIsStatic = isStatic;
	}

	bool BaseColliderComponent::IsStatic() const
	{
		return m_bIsStatic;
	}

	void BaseColliderComponent::SetEntered(bool hasEntered)
	{
		m_Entered = hasEntered;
	}

	bool BaseColliderComponent::GetEntered() const
	{
		return m_Entered;
	}

	void BaseColliderComponent::SetExited(bool hasLeft)
	{
		m_Exited = hasLeft;
	}

	bool BaseColliderComponent::GetExited() const
	{
		return m_Exited;
	}

	const PointerArray<tstring> & BaseColliderComponent::GetLayers() const
	{
		return m_Layers;
	}

	bool BaseColliderComponent::RectangleCircleCollision(
		const RectangleColliderComponent* rect, 
		const CircleColliderComponent* circle) const
	{
		Rect realRect = rect->GetCollisionRect();
		float32 radius = circle->GetRealRadius();

		vec2 circleObjectPos = circle->GetPosition();
		if(rect->GetTransform()->GetWorldRotation() == 0.0f)
		{
			// Find the closest point to the circle within the rectangle
			vec2 closestPos(
				Clamp(circleObjectPos.x, realRect.GetRealLeft(), realRect.GetRealRight()),
				Clamp(circleObjectPos.y, realRect.GetRealBottom(), realRect.GetRealTop()));

			// Calculate the distance between the circle's center and this closest point
			vec2 distance(circleObjectPos - closestPos);

			// If the distance is less than the circle's radius, an intersection occurs
			return Mag(distance) < radius;
		}
		else
		{			
			//Check with SAT
			Logger::GetInstance()->
				Log(LogLevel::Warning, _T("CollisionChecking between OOBB and Circle is not yet implemented"));
			return false;
			/*
			vec2 closestPoint(FindClosestPointToOOBB(circleObjectPos,rect));
			return Mag(closestPoint) < radius;*/
		}
	}

	vec2 BaseColliderComponent::FindClosestPointToOOBB(
		const vec2& point, 
		const RectangleColliderComponent* oobb
		) const
	{
		//http://notmagi.me/closest-point-on-line-aabb-and-obb-to-point/
		vec2 pos = oobb->GetCenterPoint();
		vec2 distVec = point - pos;
		vec2 u0 = oobb->GetOrientatedUnitVecX();
		vec2 u1(-u0.y , u0.x);
		float32 distance = Dot(distVec, u0);
		float32 halfWidth = oobb->GetCollisionRectWidth() / 2.0f;
		if(distance > halfWidth)
		{
			distance = halfWidth;
		}
		else if(distance < -halfWidth)
		{
			distance = -halfWidth;
		}
		pos += u0 * distance;
		distance = Dot(distVec, u1);
		float32 halfHeight = oobb->GetCollisionRectHeight() / 2.0f;
		if(distance > halfHeight)
		{
			distance = halfHeight;
		}
		else if(distance < -halfHeight)
		{
			distance = -halfHeight;
		}
		pos += u1 * distance;
		return pos;
	}
}
