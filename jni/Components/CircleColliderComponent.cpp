#include "CircleColliderComponent.h"
#include "..\Context.h"

namespace star
{
	CircleColliderComponent::CircleColliderComponent(float radius):
		m_Radius(radius),
		m_bIsTrigger(false)
	{
	}

	CircleColliderComponent::~CircleColliderComponent(void)
	{
	}

	void CircleColliderComponent::Initialize()
	{
	}

	void CircleColliderComponent::InitializeComponent()
	{
		//Assert(m_Radius > 0, _T("Negative Radius"));
		m_bInitialized = true;
	}

	void CircleColliderComponent::Update(const Context& context)
	{
		if(!m_bInitialized)
		{
			return;
		}

		//[TODO]Start CollisionChecking
		//If m_bIsTrigger == true -> Callbacks
	}

	void CircleColliderComponent::Draw()
	{
	}
}
