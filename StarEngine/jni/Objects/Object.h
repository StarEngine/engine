#pragma once
#include <vector>
#include <typeinfo>
#include "../defines.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Scenes/BaseScene.h"
#include "../Components/TransformComponent.h"
#include "../AI/Pathfinding/PathFindManager.h"
#include "../Helpers/HashTag.h"

namespace star
{
	class BaseComponent;
	class PathFindNodeComponent;

	class Object
	{
	public:
		Object();
		Object(const tstring & name);
		Object(
			const tstring & name,
			const tstring & groupTag
			);
		virtual ~Object(void);

		Object* GetParent() const;

		void BaseInitialize();
		void BaseAfterInitialized();
		void BaseUpdate(const Context& context);
		void BaseDraw();
		void BaseDrawWithCulling(
			float32 left,
			float32 right,
			float32 top,
			float32 bottom
			);

		const tstring& GetName() const;
		void SetName(const tstring& name);
		bool CompareName(const tstring & name);

		const tstring& GetPhysicsTag() const;
		void SetPhysicsTag(const tstring& tag);
		bool ComparePhysicsTag(const tstring & tag);

		const tstring& GetGroupTag() const;
		void SetGroupTag(const tstring& tag);
		bool CompareGroupTag(const tstring & tag);

		void AddComponent(BaseComponent* pComponent);

		virtual void AddChild(Object* pObject);
		void RemoveChild(const Object* pObject);
		void RemoveChild(const tstring & name);

		const std::vector<Object*>& GetChildren() const;

		void SetChildFrozen(const tstring & name, bool freeze);
		void SetChildDisabled(const tstring & name, bool disabled);
		void SetChildVisible(const tstring & name, bool visible);

		template <typename T>
		T * GetChildByName(const tstring & name);

		virtual void SetVisible(bool visible);
		bool IsVisible() const;

		virtual void Freeze(bool freeze);
		bool IsFrozen() const;

		virtual void SetDisabled(bool disabled);
		virtual bool IsDisabled() const;

		bool IsInitialized() const;

		void SetScene(BaseScene * pScene);
		void UnsetScene(); 

		TransformComponent * GetTransform() const;

		BaseScene * GetScene() const;

		template<class T>
		void RemoveComponent();

		template<class T>
		T* GetComponent(bool searchChildren = false) const;

		const std::vector<BaseComponent*>& GetComponents() const;

		template<class T>
		T* GetChild() const;

		template<class T>
		T* GetChild(const tstring & name) const;

	protected:
		virtual void Initialize();
		virtual void AfterInitialized();
		virtual void Update(const Context & context);
		virtual void Draw();

		bool BaseCheckCulling(
			float32 left, float32 right, float32 top, float32 bottom
			);

		virtual bool CheckCulling(
			float32 left,
			float32 right,
			float32 top,
			float32 bottom
			);

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
		HashTag m_Name, m_GroupTag, m_PhysicsTag;

	private:
		void CollectGarbage();

		Object(const Object& t);
		Object(Object&& t);
		Object& operator=(const Object& t);
		Object& operator=(Object&& t);
	};

	template <typename T>
	T * Object::GetChildByName(const tstring & name)
	{
		for(auto child : m_pChildren)
		{
			if(child->CompareName(name))
			{
				auto returnobject = dynamic_cast<T*>(child);
				if(returnobject == nullptr)
				{
					Logger::GetInstance()->Log(LogLevel::Error,
						_T("Object::GetChildByName: couldn't convert object '")
						+ name + _T("' to the requested type. Returning nullptr..."));
				}
				return returnobject;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Object::GetChildByName: \
Trying to get unknown child '")
				   + name + _T("'."));
		return nullptr;
	}

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
