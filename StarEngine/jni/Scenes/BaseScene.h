#pragma once

#include "../Entity.h"

#include "../Helpers/TimerManager.h"
#include "../Helpers/Stopwatch.h"
#include "../Objects/Object.h"
#include "../Input/Gestures/GestureManager.h"

#include <vector>
#include <memory>

namespace star 
{
	struct Context;
	class CameraComponent;
	class CollisionManager;
	class BaseCamera;
	class UIBaseCursor;
	class BaseGesture;

	class BaseScene : public Entity
	{
	public:
		explicit BaseScene(const tstring & name);
		virtual ~BaseScene();

		void Destroy();
		
		void BaseInitialize();
		void BaseAfterInitializedObjects();
		void BaseOnActivate();
		void BaseOnDeactivate();
		void BaseUpdate(const Context& context);
		void BaseDraw();

		virtual void OnSaveState(void** pData, size_t* pSize);
		virtual void OnConfigurationChanged();
		virtual void OnLowMemory();

		bool IsInitialized() const;

		virtual void AddObject(Object * pObject); 
		void AddObject(Object * pObject, const tstring & name); 
		virtual void RemoveObject(Object * pObject);
		void RemoveObject(const tstring & name);

		void AddGesture(BaseGesture* pGesture);
		void AddGesture(BaseGesture* pGesture, const tstring & name);
		void RemoveGesture(BaseGesture* pGesture);
		void RemoveGesture(const tstring & name);

		template <typename T>
		T * GetGestureByName(const tstring & name) const;

		template <typename T>
		T * GetObjectByName(const tstring & name) const;

		void SetObjectFrozen(const tstring & name, bool freeze);
		void SetObjectDisabled(const tstring & name, bool disabled);
		void SetObjectVisible(const tstring & name, bool visible);

		void SetGroupFrozen(const tstring & tag, bool freeze);
		void SetGroupDisabled(const tstring & tag, bool disabled);
		void SetGroupVisible(const tstring & tag, bool visable);
		void GetGroup(const tstring & tag, std::vector<Object*> & group);

		void SetActiveCamera(BaseCamera* pCamera);
		BaseCamera* GetActiveCamera() const;

		static void SetCullingIsEnabled(bool enabled);
		static bool IsCullingEnabled();

		bool IsObjectNameAlreadyInUse(const tstring & name) const;

		void SetCursorHidden(bool hidden);
		void SetSystemCursorHidden(bool hidden);

		void SetCursor(UIBaseCursor * pCursor);
		void UnsetCursor(bool showSystemCursor = true);

		void SetStateActiveCursor(const tstring & state);
		void SetActiveCursorLocked(bool locked);
		bool IsActiveCursorLocked() const;

		void SetCullingOffset(int32 offset);
		void SetCullingOffset(int32 offsetX, int32 offsetY);

		std::shared_ptr<TimerManager> GetTimerManager() const;

		std::shared_ptr<GestureManager> GetGestureManager() const;
		std::shared_ptr<CollisionManager> GetCollisionManager() const;

	protected:
		virtual void CreateObjects() = 0;
		virtual void AfterInitializedObjects() = 0;
		virtual void OnActivate() = 0;
		virtual void OnDeactivate() = 0;
		virtual void Update(const Context& context) = 0;
		virtual void Draw() = 0;

		void SetOSCursorHidden(bool hidden);

		std::shared_ptr<GestureManager> m_pGestureManager;
		std::shared_ptr<CollisionManager> m_pCollisionManager;

		std::vector<Object*> m_pObjects;
		std::vector<Object*> m_pGarbage;
		BaseCamera *m_pDefaultCamera, *m_pActiveCamera;
		std::shared_ptr<TimerManager> m_pTimerManager;
		UIBaseCursor *m_pCursor;

	private:
		void CollectGarbage();

		int32 m_CullingOffsetX,
			m_CullingOffsetY;
		bool m_Initialized;
		static bool CULLING_IS_ENABLED;
		bool m_CursorIsHidden, m_SystemCursorIsHidden;
		uint32 m_GestureID;
	
		BaseScene(const BaseScene& t);
		BaseScene(BaseScene&& t);
		BaseScene& operator=(const BaseScene& t);
		BaseScene& operator=(BaseScene&& t);
	};
}

#include "BaseScene.inl"
