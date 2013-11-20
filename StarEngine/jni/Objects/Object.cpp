#include "Object.h"
#include "../StarComponents.h"
#include "../Components/TransformComponent.h"
#include "../Graphics/GraphicsManager.h"
#include "../Scenes/BaseScene.h"
#include "../Physics/Collision/CollisionManager.h"
#include <algorithm>
#include <typeinfo>

namespace star
{
	Object::Object(void):
		m_bIsInitialized(false),
		m_IsVisible(true),
		m_IsFrozen(false),
		m_pParentGameObject(nullptr),
		m_pPathFindComp(nullptr),
		m_pScene(nullptr),
		m_pComponents(),
		m_pChildren(),
		m_Name(_T("Default")),
		m_CollisionTag(_T("Default"))
	{
		m_pComponents.push_back(new TransformComponent(this));
	}

	Object::~Object(void)
	{
		for(auto comp : m_pComponents)
		{
			delete comp;
		}
		m_pComponents.clear();

		for(auto child : m_pChildren)
		{
			delete child;
		}
		m_pChildren.clear();
	}
	
	Object* Object::GetParent() const
	{
		return (m_pParentGameObject);
	}

	void Object::BaseInitialize()
	{
		if (m_bIsInitialized)
		{
			return;
		}

		Initialize();
		for(auto comp : m_pComponents)
		{
			if(comp && !comp->IsInitialized())
			{
				comp->Initialize();
			}
		}

		for(auto child : m_pChildren)
		{
			if(child && !child->m_bIsInitialized)
			{
				child->BaseInitialize();
			}
		}
		BaseAfterInitialized();
		m_bIsInitialized = true;
	}

	void Object::Initialize()
	{
		//DO nothing, unless a derived class overrides this
	}

	void Object::BaseAfterInitialized()
	{
		AfterInitialized();
	}

	void Object::AfterInitialized()
	{
		//DO nothing, unless a derived class overrides this
	}

	void Object::Update(const Context& context)
	{
		//DO nothing, unless a derived class overrides this
	}
	
	void Object::BaseUpdate(const Context & context)
	{
		if(!m_IsFrozen)
		{
			Update(context);
			for(auto component : m_pComponents)
			{
				if(component)
				{
					component->BaseUpdate(context);
				}
			}

			for(auto child : m_pChildren)
			{
				if(child)
				{
					child->BaseUpdate(context);
				}
			}
		}
	}

	void Object::Draw()
	{
		//DO nothing, unless a derived class overrides this
	}

	void Object::BaseDraw()
	{
		if(m_IsVisible)
		{
			Draw();
			for(auto component : m_pComponents)
			{
				if(component)
				{
					component->BaseDraw();
				} 
			}
		}
	}

	const tstring& Object::GetName() const
	{
		return m_Name;
	}

	void Object::SetName(const tstring& name)
	{
		m_Name = name;
	}

	void Object::AddComponent(BaseComponent *pComponent)
	{
		bool isValid(true);
		for(auto comp : m_pComponents)
		{
			if(typeid(*comp) == typeid(*pComponent))
			{
				isValid = false;
				break;
			}
		}

		ASSERT(isValid, _T("Adding 2 components of the same type to the same object is illegal."));

		if(isValid)
		{
			pComponent->SetParent(this);

			if(m_bIsInitialized && ! pComponent->IsInitialized())
			{
				pComponent->Initialize();
			}

			m_pComponents.push_back(pComponent);
		}
	}

	void Object::RemoveComponent(const BaseComponent* pComponent)
	{
		m_pComponents.erase(std::find(m_pComponents.begin(), m_pComponents.end(), pComponent));
		/*auto baseColComp = dynamic_cast<const BaseColliderComponent*>(pComponent);
		if(baseColComp)
		{
			GetScene()->GetCollisionManager()->RemoveComponent(baseColComp);
		}*/
		delete pComponent;

		Logger::GetInstance()->Log(LogLevel::Info, _T("Component Removed"));
	}

	void Object::AddChild(Object *pChild)
	{
		pChild->m_pParentGameObject = this;

		if(m_bIsInitialized && !pChild->m_bIsInitialized)
		{
			pChild->BaseInitialize();
		}

		m_pChildren.push_back(pChild);

		//Logger::GetInstance()->Log(LogLevel::Info, _T("Child Added"));
	}

	void Object::RemoveChild(const Object* pObject)
	{
		m_pChildren.erase(std::find(m_pChildren.begin(), m_pChildren.end(), pObject));
		delete pObject;

		Logger::GetInstance()->Log(LogLevel::Info, _T("Child Removed"));
	}

	std::vector<Object*>& Object::GetChildren()
	{
		return m_pChildren;
	}

	void Object::SetVisible(bool visible)
	{
		m_IsVisible = visible;
		for(auto child : m_pChildren)
		{
			child->SetVisible(visible);
		}
	}

	bool Object::IsVisible() const
	{
		return m_IsVisible;
	}

	void Object::Freeze(bool freeze)
	{
		m_IsFrozen = freeze;
		for(auto child : m_pChildren)
		{
			child->Freeze(freeze);
		}
	}

	bool Object::IsFrozen() const
	{
		return m_IsFrozen;
	}

	void Object::SetDisabled(bool disabled)
	{
		m_IsVisible = !disabled;
		m_IsFrozen = disabled;

		for(auto child : m_pChildren)
		{
			child->SetDisabled(disabled);
		}
	}

	bool Object::IsDisabled() const
	{
		return !m_IsVisible && m_IsFrozen;
	}

	void Object::SetScene(BaseScene * pScene)
	{
		m_pScene = pScene;
	}

	void Object::UnsetScene()
	{
		m_pScene = nullptr;
	}
	
	TransformComponent * Object::GetTransform() const
	{
		return GetComponent<TransformComponent>();
	}
	
	BaseScene * Object::GetScene() const
	{
		return m_pScene;
	}
}
