#pragma once

#include "../Entity.h"

#include "../Helpers/Stopwatch.h"
#include "../Objects/Object.h"

#include <vector>
#include <memory>

namespace star 
{
	struct Context;
	class CameraComponent;
	class CollisionManager;
	class GestureManager;
	class BaseCamera;
	class UIBaseCursor;

	class BaseScene : public Entity
	{
	public:
		explicit BaseScene(const tstring & name);
		virtual ~BaseScene();

		void Destroy();
		
		void	BaseInitialize();
		void	BaseAfterInitializedObjects();
		void	BaseOnActivate();
		void	BaseOnDeactivate();
		void	BaseUpdate(const Context& context);
		void	BaseDraw();

		virtual void OnSaveState(void** pData,size_t* pSize);
		virtual void OnConfigurationChanged();
		virtual void OnLowMemory();

		bool IsInitialized() const;

		void AddObject(Object * object); 
		void AddObject(Object * object, const tstring & name); 
		void RemoveObject(Object * object);
		void RemoveObject(const tstring & name);

		template <typename T>
		T * GetObjectByName(const tstring & name);

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

		void SetCursorHidden(bool hidden);
		void SetSystemCursorHidden(bool hidden);

		void SetCursor(UIBaseCursor * cursor);
		void UnsetCursor(bool showSystemCursor = true);

		void SetStateActiveCursor(const tstring & state);
		void SetActiveCursorLocked(bool locked);
		bool IsActiveCursorLocked() const;

		void SetCullingOffset(int32 offset);
		void SetCullingOffset(int32 offsetX, int32 offsetY);

		std::shared_ptr<Stopwatch> GetStopwatch() const;

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

		std::shared_ptr<GestureManager> m_GestureManagerPtr;
		std::shared_ptr<CollisionManager> m_CollisionManagerPtr;

		std::vector<Object*> m_Objects;
		std::vector<Object*> m_Garbage;
		BaseCamera* m_pDefaultCamera;
		std::shared_ptr<Stopwatch> m_pStopwatch;
		UIBaseCursor *m_pCursor;

	private:
		void CollectGarbage();

		int32 m_CullingOffsetX,
			m_CullingOffsetY;
		bool m_Initialized;
		static bool CULLING_IS_ENABLED;
		bool m_CursorIsHidden, m_SystemCursorIsHidden;
	
		BaseScene(const BaseScene& t);
		BaseScene(BaseScene&& t);
		BaseScene& operator=(const BaseScene& t);
		BaseScene& operator=(BaseScene&& t);
	};
}

#include "BaseScene.inl"
