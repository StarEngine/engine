#pragma once
#include <vector>
#include <typeinfo>
#include "../defines.h"
#include "../Logger.h"
#include "../Context.h"
#include "../SceneManaging/BaseScene.h"
#include "../Components/TransformComponent.h"
#include "../SceneManaging/PathFindManager.h"

namespace star
{
	class BaseComponent;
	class PathFindNodeComponent;
	using namespace std;

	class Object
	{
	public:
		Object(void);
		virtual ~Object(void);

		Object* GetParent() const {return m_pParentGameObject;}

		virtual void Initialize();
		virtual void Update(const Context& context);
		virtual void Draw();

		const tstring& GetName() const {return m_Name;};
		void SetName(const tstring& name) {m_Name = name;};

		void AddComponent(BaseComponent* pComponent);
		void RemoveComponent(const BaseComponent* pComponent);

		void AddChild(Object* pObject);
		void RemoveChild(const Object* pObject);

		void SetCollisionTag(const tstring& tag) {m_CollisionTag = tag;};
		const tstring& GetCollisionTag() const {return m_CollisionTag;};

		void CollisionCheck(Object* otherObject);
		bool RectangleCollision(Object* object, Object* otherObject);
		bool CircleCollision(Object* object, Object* otherObject);
		bool RectangleCircleCollision(Object* object, Object* otherObject);

		//Template functions
		//-----------------------------
		template<class T>
		T* GetComponent(bool searchChildren = false)
		{
			const type_info& ti = typeid(T);
			for(auto *component : m_pComponents)
			{
				if(component && typeid(*component) == ti)
				{
					return (T*)component;
				}
			}

			if(searchChildren)
			{
				for(auto *child : m_pChildren)
				{
					return child->GetComponent<T>(searchChildren);
				}
			}
			return nullptr;
		}

		template<class T>
		T* GetChild()
		{
			const type_info& ti = typeid(T);
			for(auto *child : m_pChildren)
			{
				if(child && typeid(*child) == ti)
				{
					return (T*)child;
				}
			}
			return nullptr;
		}

	protected:
		bool m_bIsInitialized;
		Object* m_pParentGameObject;
		PathFindNodeComponent* m_pPathFindComp;

		std::vector<BaseComponent*> m_pComponents;
		std::vector<Object*> m_pChildren;
		tstring m_Name, m_CollisionTag;

	private:
		// -------------------------
		// Disabling default copy constructor and default
		// assignment operator.
		// -------------------------
		Object(const Object& t);
		Object(Object&& t);
		Object& operator=(const Object& t);
	};
}
