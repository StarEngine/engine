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

		virtual void Initialize();
		void Update(const Context& context);
		void Draw();

		const tstring& GetName() const;
		void SetName(const tstring& name);

		void AddComponent(BaseComponent* pComponent);
		void RemoveComponent(const BaseComponent* pComponent);

		void AddChild(Object* pObject);
		void RemoveChild(const Object* pObject);

		void SetCollisionTag(const tstring& tag);
		const tstring& GetCollisionTag() const;

		void SetVisible(bool visible);
		bool IsVisible() const;

		void Freeze(bool freeze);
		bool IsFrozen() const;

		void SetDisabled(bool disabled);
		bool IsDisabled() const;

		void CollisionCheck(Object* otherObject);
		bool RectangleCollision(Object* object, Object* otherObject);
		bool CircleCollision(Object* object, Object* otherObject);
		bool RectangleCircleCollision(Object* object, Object* otherObject);

		void SetScene(BaseScene * pScene);
		void UnsetScene(); 

		TransformComponent * GetTransform() const;

		BaseScene * GetScene() const;

		template<class T>
		T* GetComponent(bool searchChildren = false) const;

		template<class T>
		T* GetChild() const;

		template<class T>
		T* GetChild(const tstring & name) const;

	protected:
		virtual void BaseUpdate(const Context & context);
		virtual void BaseDraw();

		bool m_bIsInitialized;
		bool m_IsVisible;
		bool m_IsFrozen;
		Object* m_pParentGameObject;
		PathFindNodeComponent* m_pPathFindComp;
		BaseScene *m_pScene;

		std::vector<BaseComponent*> m_pComponents;
		std::vector<Object*> m_pChildren;
		tstring m_Name, m_CollisionTag;

	private:
		Object(const Object& t);
		Object(Object&& t);
		Object& operator=(const Object& t);
	};

	template<class T>
	T* Object::GetComponent(bool searchChildren) const
	{
		const std::type_info& ti = typeid(T);
		for(auto *component : m_pComponents)
		{
			if(component && typeid(*component) == ti)
			{
				return ((T*)component);
			}
		}

		if(searchChildren)
		{
			for(auto *child : m_pChildren)
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
		for(auto *child : m_pChildren)
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
		for(auto *child : m_pChildren)
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
