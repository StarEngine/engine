#include "Object.h"
#include "../Actions/Action.h"
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
		: Entity()
		, m_bIsInitialized(false)
		, m_IsVisible(true)
		, m_IsFrozen(false)
		, m_pParentGameObject(nullptr)
		, m_pPathFindComp(nullptr)
		, m_pScene(nullptr)
		, m_pGarbageContainer()
		, m_pComponents()
		, m_pChildren()
		, m_pActions()
		, m_GroupTag(_T("Default"))
		, m_PhysicsTag(_T("Default"))
	{
		m_pComponents.push_back(new TransformComponent(this));
	}

	Object::Object(const tstring & name)
		: Entity(name)
		, m_bIsInitialized(false)
		, m_IsVisible(true)
		, m_IsFrozen(false)
		, m_pParentGameObject(nullptr)
		, m_pPathFindComp(nullptr)
		, m_pScene(nullptr)
		, m_pGarbageContainer()
		, m_pComponents()
		, m_pChildren()
		, m_pActions()
		, m_GroupTag(_T("Default"))
		, m_PhysicsTag(_T("Default"))
	{
		m_pComponents.push_back(new TransformComponent(this));
	}

	Object::Object(
		const tstring & name,
		const tstring & groupTag
		)
		: Entity(name)
		, m_bIsInitialized(false)
		, m_IsVisible(true)
		, m_IsFrozen(false)
		, m_pParentGameObject(nullptr)
		, m_pPathFindComp(nullptr)
		, m_pScene(nullptr)
		, m_pGarbageContainer()
		, m_pComponents()
		, m_pChildren()
		, m_pActions()
		, m_GroupTag(groupTag)
		, m_PhysicsTag(_T("Default"))
	{
		m_pComponents.push_back(new TransformComponent(this));
	}

	Object::~Object(void)
	{
		for(auto & info : m_pGarbageContainer)
		{
			DestroyGarbageElement(info);
		}
		m_pGarbageContainer.clear();

		for(auto comp : m_pComponents)
		{
			SafeDelete(comp);
		}
		m_pComponents.clear();

		for(auto child : m_pChildren)
		{
			SafeDelete(child);
		}
		m_pChildren.clear();

		for(auto action : m_pActions)
		{
			SafeDelete(action);
		}
		m_pActions.clear();
	}

	void Object::Destroy()
	{
		if(m_pParentGameObject)
		{
			m_pParentGameObject->RemoveChild(this);
		}
		else
		{
			m_pScene->RemoveObject(this);
		}
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
		for(auto action : m_pActions)
		{
			if(action)
			{
				action->BaseInitialize();
			}
		}

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
				child->SetScene(GetScene());
				child->BaseInitialize();
			}
		}
		BaseAfterInitialized();
		m_bIsInitialized = true;
	}

	Object::GarbageInfo::GarbageInfo(
		Entity* pEntity,
		GarbageType type
		)
		: Element(pEntity)
		, Type(type)
	{
	}
	
	void Object::DestroyGarbageElement(const GarbageInfo & info)
	{
		switch(info.Type)
		{
			case GarbageType::ActionType:
			{
				auto action = dynamic_cast<Action*>(info.Element);
				auto it = std::find(m_pActions.begin(), m_pActions.end(), action);
				m_pActions.erase(it);
			}
			break;
			case GarbageType::ObjectType:
			{
				auto object = dynamic_cast<Object*>(info.Element);
				auto it = std::find(m_pChildren.begin(), m_pChildren.end(), object);
				m_pChildren.erase(it);
			}
			break;
			case GarbageType::ComponentType:
			{
				auto component = dynamic_cast<BaseComponent*>(info.Element);
				auto it = std::find(m_pComponents.begin(), m_pComponents.end(), component);
				m_pComponents.erase(it);
				RecalculateDimensions();
			}
			break;
		}
		delete info.Element;
	}
	
	void Object::RecalculateDimensions()
	{
		ivec2 dim(0,0);
		auto transform = GetTransform();
		for(auto comp : m_pComponents)
		{
			if(comp != transform)
			{
				ivec2 temp = comp->GetDimensions();
				if(temp.x > dim.x)
				{
					dim.x = temp.x;
				}
				if(temp.y > dim.y)
				{
					dim.y = temp.y;
				}
			}
		}
		transform->SetDimensions(dim);
	}

	void Object::Initialize()
	{
	}

	void Object::BaseAfterInitialized()
	{
		AfterInitialized();
	}

	void Object::AfterInitialized()
	{
	}

	void Object::Update(const Context& context)
	{
	}
	
	void Object::BaseUpdate(const Context & context)
	{
		CollectGarbage();
		if(!m_IsFrozen)
		{
			Update(context);

			for(auto action : m_pActions)
			{
				if(action)
				{
					action->BaseUpdate(context);
				}
				else
				{
					m_pActions.erase(
						std::find(
						m_pActions.begin(),
						m_pActions.end(),
						action)
						);
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("Trying to update nullptr action from object '")
						+ GetName() + _T("'."), STARENGINE_LOG_TAG);
				}
			}

			for(auto component : m_pComponents)
			{
				if(component)
				{
					component->BaseUpdate(context);
				}
				else
				{
					m_pComponents.erase(
						std::find(
						m_pComponents.begin(),
						m_pComponents.end(),
						component)
						);
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("Trying to update nullptr component from object '")
						+ GetName() + _T("'."), STARENGINE_LOG_TAG);
				}
			}

			for(auto child : m_pChildren)
			{
				if(child)
				{
					child->BaseUpdate(context);
				}
				else
				{
					m_pChildren.erase(
						std::find(
						m_pChildren.begin(),
						m_pChildren.end(),
						child)
						);
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("Trying to update nullptr child from object '")
						+ GetName() + _T("'."), STARENGINE_LOG_TAG);
				}
			}
		}
	}

	void Object::Draw()
	{
	}

	bool Object::BaseCheckCulling(
		float32 left, float32 right, float32 top, float32 bottom
		)
	{
		for ( auto component : m_pComponents)
		{
			if(component->CheckCulling(left, right, top, bottom))
			{
				return true;
			}
		}

		return CheckCulling(left, right, top, bottom);
	}

	bool Object::CheckCulling(
		float32 left,
		float32 right,
		float32 top,
		float32 bottom
		)
	{
		return false;
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
				else
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("Trying to draw nullptr component from object '")
						+ GetName() + _T("'."), STARENGINE_LOG_TAG);
				}
			}

			for(auto child : m_pChildren)
			{
				if(child)
				{
					child->BaseDraw();
				}
				else
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("Trying to draw nullptr object child from object '")
						+ GetName() + _T("'."), STARENGINE_LOG_TAG);
				}
			}
		}
	}

	void Object::BaseDrawWithCulling(
		float32 left,
		float32 right,
		float32 top,
		float32 bottom
		)
	{
		if(m_IsVisible)
		{
			if(BaseCheckCulling(left, right, top, bottom))
			{
				Draw();

				for(auto component : m_pComponents)
				{
					if(component)
					{
						component->BaseDraw();
					} 
					else
					{
						Logger::GetInstance()->Log(LogLevel::Warning,
							_T("Trying to draw nullptr component from object '")
							+ GetName() + _T("'."), STARENGINE_LOG_TAG);
					}
				}
			}

			for(auto child : m_pChildren)
			{
				if(child)
				{
					child->BaseDrawWithCulling(left, right, top, bottom);
				}
				else
				{
					Logger::GetInstance()->Log(LogLevel::Warning,
						_T("Trying to draw nullptr object child from object '")
						+ GetName() + _T("'."), STARENGINE_LOG_TAG);
				}
			}
		}
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
			Logger::GetInstance()->Log(typeid(*comp) != typeid(*pComponent), 
				_T("Object::AddComponent: \
Adding 2 components of the same type \
to the same object is illegal."), STARENGINE_LOG_TAG);
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

		if(IsChildNameAlreadyInUse(pChild->GetName()))
		{
			Logger::GetInstance()->DebugLog(LogLevel::Warning,
				_T("Object::AddChild: a child with the name '")
				+ pChild->GetName() + _T("' already exists. \
Child gets added but beware, duplicate names can become the cause of problems."),
				STARENGINE_LOG_TAG);
		}

		if(m_bIsInitialized && !pChild->m_bIsInitialized)
		{
			pChild->SetScene(GetScene());
			pChild->BaseInitialize();
		}

		m_pChildren.push_back(pChild);
	}

	void Object::RemoveChild(const Object* pObject)
	{
		auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pObject);
		bool isOK = it != m_pChildren.end();
		if(isOK)
		{
			m_pGarbageContainer.push_back(
				GarbageInfo(
					*it,
					GarbageType::ObjectType
					)
				);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("Object::RemoveChild: The object you tried \
to remove is not a child of this object!"), STARENGINE_LOG_TAG);
		}
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
		Logger::GetInstance()->Log(LogLevel::Error,
			_T("Object::RemoveChild: The object you tried \
to remove is not a child of this object!"), STARENGINE_LOG_TAG);
	}

	const std::vector<Object*>& Object::GetChildren() const
	{
		return m_pChildren;
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
				   + name + _T("'."), STARENGINE_LOG_TAG);
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
				   + name + _T("'."), STARENGINE_LOG_TAG);
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
				+ name + _T("'."), STARENGINE_LOG_TAG);
	}

	void Object::SetChildrenFrozen(bool freeze)
	{
		for(auto child : m_pChildren)
		{
			child->Freeze(freeze);
			child->SetChildrenFrozen(freeze);
		}
	}

	void Object::SetChildrenDisabled(bool disable)
	{
		for(auto child : m_pChildren)
		{
			child->SetDisabled(disable);
			child->SetChildrenDisabled(disable);
		}
	}

	void Object::SetChildrenVisible(bool visible)
	{
		for(auto child : m_pChildren)
		{
			child->SetVisible(visible);
			child->SetChildrenVisible(visible);
		}
	}

	void Object::AddAction(Action * pAction)
	{
		for(auto action : m_pActions)
		{
			if(action == pAction)
			{
				Logger::GetInstance()->Log(LogLevel::Warning,
					_T("Object::AddAction: Trying to add a duplicate action."),
					STARENGINE_LOG_TAG);
				return;
			}
		}
		if(IsActionNameAlreadyInUse(pAction->GetName()))
		{
			Logger::GetInstance()->DebugLog(LogLevel::Warning,
			_T("Object::AddAction: an action with the name '")
			+ pAction->GetName() + _T("' already exists. \
Action gets added but beware, duplicate names can become the cause of problems."),
			STARENGINE_LOG_TAG);
		}
		m_pActions.push_back(pAction);
		pAction->SetParent(this);
		if(m_bIsInitialized)
		{
			pAction->BaseInitialize();
		}
	}

	void Object::RemoveAction(Action *pAction)
	{
		auto it = std::find(m_pActions.begin(), m_pActions.end(), pAction);
		bool isOK = it != m_pActions.end();
		Logger::GetInstance()->Log(isOK,
			_T("Object::RemoveAction: The action you tried \
to remove could not be found."), STARENGINE_LOG_TAG);
		if(isOK)
		{
			m_pGarbageContainer.push_back(
				GarbageInfo(
					*it,
					GarbageType::ActionType
					)
				);
		}
	}

	void Object::RemoveAction(const tstring & name)
	{
		for(auto action : m_pActions)
		{
			if(action->CompareName(name))
			{
				RemoveAction(action);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("Object::RemoveAction: Action '")
			+ name + _T("' could not be found."), STARENGINE_LOG_TAG);
	}

	void Object::RestartAction(const tstring & name)
	{
		for(auto action : m_pActions)
		{
			if(action->CompareName(name))
			{
				action->Restart();
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("Object::RestartAction: Action '")
			+ name + _T("' could not be found."), STARENGINE_LOG_TAG);
	}

	void Object::PauseAction(const tstring & name)
	{
		for(auto action : m_pActions)
		{
			if(action->CompareName(name))
			{
				action->Pause();
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("Object::PauseAction: Action '")
			+ name + _T("' could not be found."), STARENGINE_LOG_TAG);
	}

	void Object::ResumeAction(const tstring & name)
	{
		for(auto action : m_pActions)
		{
			if(action->CompareName(name))
			{
				action->Resume();
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("Object::ResumeAction: Action '")
			+ name + _T("' could not be found."), STARENGINE_LOG_TAG);
	}

	void Object::RemoveComponent(BaseComponent * pComponent)
	{
		auto it = std::find(m_pComponents.begin(), m_pComponents.end(), pComponent);
		bool isOK = it != m_pComponents.end();
		Logger::GetInstance()->Log(isOK,
			_T("Object::RemoveComponent: The component you tried \
to remove could not be found."));
		if(isOK)
		{
			m_pGarbageContainer.push_back(
				GarbageInfo(
					*it,
					GarbageType::ComponentType
					)
				);
		}
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

	bool Object::IsChildNameAlreadyInUse(const tstring & name) const
	{
		for(auto pChild : m_pChildren)
		{
			if(pChild->CompareName(name))
			{
				return true;
			}
		}
		return false;
	}
	
	bool Object::IsActionNameAlreadyInUse(const tstring & name) const
	{
		for(auto pAction : m_pActions)
		{
			if(pAction->CompareName(name))
			{
				return true;
			}
		}
		return false;
	}

	void Object::SetDisabled(bool disabled)
	{
		m_IsVisible = !disabled;
		m_IsFrozen = disabled;
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

	void Object::Reset()
	{
		for(auto child : m_pChildren)
		{
			child->Reset();
		}
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
		for(auto & info : m_pGarbageContainer)
		{
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("Object::CollectGarbage: Removed entity '")
				+ info.Element->GetName() + _T("'."), STARENGINE_LOG_TAG);
			DestroyGarbageElement(info);
		}
		m_pGarbageContainer.clear();
	}
}
