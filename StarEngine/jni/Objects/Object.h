#pragma once
#include <vector>
#include <typeinfo>
#include "../defines.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Scenes/BaseScene.h"
#include "../Components/TransformComponent.h"
#include "../AI/Pathfinding/PathFindManager.h"

namespace star
{
	class BaseComponent;
	class PathFindNodeComponent;

	class Object
	{
	public:
		Object();
		virtual ~Object(void);

		Object* GetParent() const;

		void BaseInitialize();
		void BaseAfterInitialized();
		void BaseUpdate(const Context& context);
		void BaseDraw();

		const tstring& GetName() const;
		void SetName(const tstring& name);

		void AddComponent(BaseComponent* pComponent);

		void AddChild(Object* pObject);
		void RemoveChild(const Object* pObject);
		std::vector<Object*>& GetChildren();

		void SetVisible(bool visible);
		bool IsVisible() const;

		void Freeze(bool freeze);
		bool IsFrozen() const;

		void SetDisabled(bool disabled);
		bool IsDisabled() const;

		void SetScene(BaseScene * pScene);
		void UnsetScene(); 

		TransformComponent * GetTransform() const;

		BaseScene * GetScene() const;

		template<class T>
		void RemoveComponent();

		template<class T>
		T* GetComponent(bool searchChildren = false) const;

		template<class T>
		T* GetChild() const;

		template<class T>
		T* GetChild(const tstring & name) const;

	protected:
		virtual void Initialize();
		virtual void AfterInitialized();
		virtual void Update(const Context & context);
		virtual void Draw();

		bool m_bIsInitialized;
		bool m_IsVisible;
		bool m_IsFrozen;
		Object* m_pParentGameObject;
		PathFindNodeComponent* m_pPathFindComp;
		BaseScene *m_pScene;

		std::vector<BaseComponent*> m_pComponents;
		std::vector<BaseComponent*> m_pGarbageComponents;
		std::vector<Object*> m_pChildren;
		std::vector<Object*> m_pGarbageChildren;
		tstring m_Name, m_CollisionTag;

	private:

		void CollectGarbage();

		Object(const Object& t);
		Object(Object&& t);
		Object& operator=(const Object& t);
		Object& operator=(Object&& t);
	};

	template<class T>
	void Object::RemoveComponent()
	{
		const std::type_info& ti = typeid(T);
		for(auto component : m_pComponents)
		{
			if(component && typeid(*component) == ti)
			{
				m_pGarbageComponents.push_back(component);
			}
		}	
	}

	template<class T>
	T* Object::GetComponent(bool searchChildren) const
	{
		const std::type_info& ti = typeid(T);
		for(auto component : m_pComponents)
		{
			if(component && typeid(*component) == ti)
			{
				return ((T*)component);
			}
		}

		if(searchChildren)
		{
			for(auto child : m_pChildren)
			{
				return (child->GetComponent<T>(searchChildren));
			}
		}
		return (nullptr);
	}

	template<class T>
	T* Object::GetChild() const
	{
		const std::type_info& ti = typeid(T);
		for(auto child : m_pChildren)
		{
			if(child && typeid(*child) == ti)
			{
				return (dynamic_cast<T*>(child));
			}
		}
		return (nullptr);
	}

	template<class T>
	T* Object::GetChild(const tstring & name) const
	{
		const std::type_info& ti = typeid(T);
		for(auto child : m_pChildren)
		{
			if(child && typeid(*child) == ti
				&& child->GetName() == name)
			{
				return (dynamic_cast<T*>(child));
			}
		}
		return (nullptr);
	}

	
}
