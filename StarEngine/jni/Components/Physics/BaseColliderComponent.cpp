#include "BaseColliderComponent.h"
#include "../../Context.h"

namespace star
{
	BaseColliderComponent::BaseColliderComponent()
		: BaseComponent()
		, m_bIsTrigger(false)
		, m_bIsStatic(false)
		
	{
	}

	BaseColliderComponent::BaseColliderComponent(const tstring* layers, uint8 n)
		: BaseComponent()
		, m_bIsTrigger(false)
		, m_bIsStatic(false)
		
	{
	}

	BaseColliderComponent::~BaseColliderComponent(void)
	{
	}

	void BaseColliderComponent::InitializeComponent()
	{
		InitializeColliderComponent();
		m_bInitialized = true;
	}

	void BaseColliderComponent::Update(const Context& context)
	{
		if(!m_bInitialized)
		{
			return;
		}

		/*
		If the component is not static and is not a trigger, 
		then we need to update the force impacts of the object. 
		For example if the collider is hit by another collider 
		and by the force he moves and rotates a little bit. 
		IN this update we’ll handle that. 
		*/
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
}
