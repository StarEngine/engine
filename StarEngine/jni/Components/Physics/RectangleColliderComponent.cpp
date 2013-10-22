#include "RectangleColliderComponent.h"
#include "../../Logger.h"

namespace star
{
	RectangleColliderComponent::RectangleColliderComponent(uint16 width, uint16 height):
		m_CollisionRect(0,0, width, height),
		m_bIsTrigger(false),
		BaseComponent()
	{

	}

	RectangleColliderComponent::~RectangleColliderComponent(void)
	{
	}

	void RectangleColliderComponent::InitializeComponent()
	{
		m_bInitialized = true;
	}

	void RectangleColliderComponent::Update(const Context& context)
	{
		if(!m_bInitialized)
		{
			return;
		}
	}

	void RectangleColliderComponent::Draw()
	{
	}
	
	void RectangleColliderComponent::SetAsTrigger(bool isTrigger)
	{
		m_bIsTrigger = isTrigger;
	}

	bool RectangleColliderComponent::IsTrigger() const
	{
		return m_bIsTrigger;
	}

	const Rect & RectangleColliderComponent::GetCollisionRect() const
	{
		return m_CollisionRect;
	}
}
