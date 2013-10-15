#include "BaseComponent.h"
#include "../SceneGraph\Object.h"
#include "../Context.h"
#include "../Logger.h"
#include "../SceneGraph/Object.h"

namespace star
{
	BaseComponent::BaseComponent():
		m_pParentObject(nullptr),
		m_bInitialized(false)
	{
	}

	BaseComponent::BaseComponent(Object* parent):
		m_pParentObject(parent),
		m_bInitialized(false)
	{
	}

	BaseComponent::~BaseComponent(void)
	{
	}

	void BaseComponent::Initialize()
	{
		if(m_bInitialized)
		{
#ifdef _DEBUG
			Logger::GetInstance()->Log(LogLevel::Warning, _T("Component Already Initialized!"));
#endif
			return;
		}
		InitializeComponent();
		m_bInitialized = true;
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
}
