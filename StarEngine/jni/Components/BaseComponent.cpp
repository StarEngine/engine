#include "BaseComponent.h"
#include "../Objects/Object.h"
#include "../Context.h"
#include "../Logger.h"

namespace star
{
	BaseComponent::BaseComponent()
		: Entity()
		, m_pParentObject(nullptr)
		, m_bInitialized(false)
		, m_bIsEnabled(true)
		, m_bIsVisible(true)
		, m_Dimensions(0,0)
	{
	}

	BaseComponent::BaseComponent(Object* parent)
		: Entity()
		, m_pParentObject(parent)
		, m_bInitialized(false)
		, m_bIsEnabled(true)
		, m_bIsVisible(true)
		, m_Dimensions(0,0)
	{
	}

	BaseComponent::~BaseComponent(void)
	{
	}

	void BaseComponent::Destroy()
	{
		m_pParentObject->RemoveComponent(this);
	}

	void BaseComponent::Initialize()
	{
		if(m_bInitialized)
		{
			DEBUG_LOG(LogLevel::Warning,
				_T("Component Already Initialized!"), STARENGINE_LOG_TAG);
			return;
		}
		m_bInitialized = true;
		InitializeComponent();
	}

	void BaseComponent::BaseUpdate(const Context& context)
	{
		if(m_bIsEnabled)
		{
			Update(context);
		}
	}

	void BaseComponent::BaseDraw()
	{
		if(m_bIsEnabled && m_bIsVisible)
		{
			Draw();
		}
	}
	
	bool BaseComponent::IsInitialized() const
	{
		return m_bInitialized;
	}

	Object* BaseComponent::GetParent() const
	{
		return m_pParentObject;
	}
	
	void BaseComponent::SetParent(Object* parent)
	{
		m_pParentObject = parent;
	}

	BaseScene* BaseComponent::GetGameScene() const
	{ 
		return m_pParentObject->GetScene();
	}

	TransformComponent* BaseComponent::GetTransform() const
	{
		 return m_pParentObject->GetComponent<TransformComponent>();
	}

	bool BaseComponent::CheckCulling(
		float left,
		float right,
		float top,
		float bottom
		) const
	{
		return false;
	}

	void BaseComponent::SetEnabled(bool bEnabled)
	{
		m_bIsEnabled = bEnabled;
	}

	bool BaseComponent::IsEnabled() const
	{
		return m_bIsEnabled;
	}

	void BaseComponent::SetVisible(bool bVisible)
	{
		m_bIsVisible = bVisible;
	}

	bool BaseComponent::IsVisible() const
	{
		return m_bIsVisible;
	}
	
	const ivec2 & BaseComponent::GetDimensions() const
	{
		return m_Dimensions;
	}

	int32 BaseComponent::GetWidth() const
	{
		return m_Dimensions.x;
	}

	int32 BaseComponent::GetHeight() const
	{
		return m_Dimensions.y; 
	}
}
