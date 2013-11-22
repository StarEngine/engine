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
	Object::Object(void)
		: m_bIsInitialized(false)
		, m_IsVisible(true)
		, m_IsFrozen(false)
		, m_pParentGameObject(nullptr)
		, m_pPathFindComp(nullptr)
		, m_pScene(nullptr)
		, m_pComponents()
		, m_pGarbageComponents()
		, m_pChildren()
		, m_pGarbageChildren()
		, m_Name(_T("Default"))
		, m_GroupTag(_T("Default"))
		, m_PhysicsTag(_T("Default"))
	{
		m_pComponents.push_back(new TransformComponent(this));
	}

	Object::Object(const tstring & name)
		: m_bIsInitialized(false)
		, m_IsVisible(true)
		, m_IsFrozen(false)
		, m_pParentGameObject(nullptr)
		, m_pPathFindComp(nullptr)
		, m_pScene(nullptr)
		, m_pComponents()
		, m_pGarbageComponents()
		, m_pChildren()
		, m_pGarbageChildren()
		, m_Name(name)
		, m_GroupTag(_T("Default"))
		, m_PhysicsTag(_T("Default"))
	{
		m_pComponents.push_back(new TransformComponent(this));
	}

	Object::Object(
		const tstring & name,
		const tstring & groupTag
		)
		: m_bIsInitialized(false)
		, m_IsVisible(true)
		, m_IsFrozen(false)
		, m_pParentGameObject(nullptr)
		, m_pPathFindComp(nullptr)
		, m_pScene(nullptr)
		, m_pComponents()
		, m_pGarbageComponents()
		, m_pChildren()
		, m_pGarbageChildren()
		, m_Name(name)
		, m_GroupTag(groupTag)
		, m_PhysicsTag(_T("Default"))
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
		CollectGarbage();
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
		return m_Name.GetTag();
	}

	void Object::SetName(const tstring& name)
	{
		m_Name.SetTag(name);
	}
	
	bool Object::CompareName(const tstring & name)
	{
		return m_Name == name;
	}

	const tstring& Object::GetPhysicsTag() const
	{
		return m_PhysicsTag.GetTag();
	}

	void Object::SetPhysicsTag(const tstring& tag)
	{
		m_PhysicsTag.SetTag(tag);
	}

	bool Object::ComparePhysicsTag(const tstring & tag)
	{
		return m_PhysicsTag == tag;
	}

	bool CompareName(const tstring & name);

	const tstring& Object::GetGroupTag() const
	{
		return m_GroupTag.GetTag();
	}

	void Object::SetGroupTag(const tstring& tag)
	{
		m_GroupTag.SetTag(tag);
	}
	
	bool Object::CompareGroupTag(const tstring & tag)
	{
		return m_GroupTag == tag;
	}

	void Object::AddComponent(BaseComponent *pComponent)
	{
		for(auto comp : m_pComponents)
		{
			ASSERT(typeid(*comp) != typeid(*pComponent), 
				_T("Object::AddComponent: \
Adding 2 components of the same type \
to the same object is illegal."));
		}

		pComponent->SetParent(this);

		if(m_bIsInitialized && ! pComponent->IsInitialized())
		{
			pComponent->Initialize();
		}

		m_pComponents.push_back(pComponent);
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
		auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pObject);
		ASSERT(it != m_pChildren.end(),
			_T("Object::RemoveChild: The object you tried \
to remove is not a child of this object!"));
		m_pGarbageChildren.push_back(*it);
	}
	
	void Object::RemoveChild(const tstring & name)
	{
		for(auto child : m_pChildren)
		{
			if(child->CompareName(name))
			{
				RemoveChild(child);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Object::RemoveChild: \
Trying to remove unknown child '")
				   + name + _T("'."));
	}

	const std::vector<Object*>& Object::GetChildren() const
	{
		return m_pChildren;
	}

	Object * Object::GetChildByName(const tstring & name)
	{
		for(auto child : m_pChildren)
		{
			if(child->CompareName(name))
			{
				return child;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Object::GetChildByName: \
Trying to get unknown child '")
				   + name + _T("'."));
		return nullptr;
	}

	void Object::SetChildFrozen(const tstring & name, bool freeze)
	{
		for(auto child : m_pChildren)
		{
			if(child->CompareName(name))
			{
				child->Freeze(freeze);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Object::SetChildFrozen: \
Trying to (un)freeze unknown child '")
				   + name + _T("'."));
	}

	void Object::SetChildDisabled(const tstring & name, bool disabled)
	{
		for(auto child : m_pChildren)
		{
			if(child->CompareName(name))
			{
				child->SetDisabled(disabled);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Object::SetChildDisabled: \
Trying to enable/disable unknown child '")
				   + name + _T("'."));
	}

	void Object::SetChildVisible(const tstring & name, bool visible)
	{
		for(auto child : m_pChildren)
		{
			if(child->CompareName(name))
			{
				child->SetVisible(visible);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Object::SetChildVisible: \
Trying to (un)hide unknown child '")
				   + name + _T("'."));
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

	bool Object::IsInitialized() const
	{
		return m_bIsInitialized;
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

	const std::vector<BaseComponent*>& Object::GetComponents() const
	{
		return m_pComponents;
	}

	void Object::CollectGarbage()
	{
		for(auto component : m_pGarbageComponents)
		{
			auto it = std::find(m_pComponents.begin(), m_pComponents.end(), component);
			ASSERT(it != m_pComponents.end(), _T("Object::CollectGarbage: trying to delete unknown object!"));
			m_pComponents.erase(it);
			delete component;
			Logger::GetInstance()->Log(LogLevel::Info, _T("Component Removed"));
		}
		m_pGarbageComponents.clear();		

		for(auto child : m_pGarbageChildren)
		{
			auto it = std::find(m_pChildren.begin(), m_pChildren.end(), child);
			ASSERT(it != m_pChildren.end(), _T("Object::CollectGarbage: trying to delete unknown child!"));
			m_pChildren.erase(it);
			delete child;
			Logger::GetInstance()->Log(LogLevel::Info, _T("Child Removed"));
		}
		m_pGarbageChildren.clear();
	}
}
