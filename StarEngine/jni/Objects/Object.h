#pragma once
#include <vector>
#include <typeinfo>
#include "../Entity.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Components/TransformComponent.h"
#include "../AI/Pathfinding/PathFindManager.h"
#include "../Helpers/HashTag.h"

namespace star
{
	class BaseComponent;
	class PathFindNodeComponent;
	class BaseScene;
	class Action;

	class Object : public Entity
	{
	public:
		Object();
		explicit Object(const tstring & name);
		Object(
			const tstring & name,
			const tstring & groupTag
			);
		virtual ~Object(void);

		void Destroy();

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

		void AddAction(Action * pAction);
		void RemoveAction(Action *pAction);
		void RemoveAction(const tstring & name);
		void RestartAction(const tstring & name);
		void PauseAction(const tstring & name);
		void ResumeAction(const tstring & name);

		void RemoveComponent(BaseComponent * pComponent);

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

		virtual void Reset();

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
		enum class GarbageType : byte
		{
			ComponentType = 0,
			ObjectType = 1,
			ActionType = 2
		};

		struct GarbageInfo
		{
			GarbageInfo(
				Entity* pEntity,
				GarbageType type
				);

			Entity *Element;
			GarbageType Type;
		};

		void DestroyGarbageElement(const GarbageInfo & info);

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
		
		std::vector<GarbageInfo> m_pGarbageContainer;

		std::vector<BaseComponent*> m_pComponents;
		std::vector<Object*> m_pChildren;
		std::vector<Action*> m_pActions;

		HashTag m_GroupTag, m_PhysicsTag;

	private:
		void CollectGarbage();

		Object(const Object& t);
		Object(Object&& t);
		Object& operator=(const Object& t);
		Object& operator=(Object&& t);
	};
}

#include "Object.inl"
