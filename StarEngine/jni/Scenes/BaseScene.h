#pragma once

#include "../defines.h"

#include "../Helpers/Stopwatch.h"

#include <vector>
#include <memory>

namespace star 
{
	struct Context;
	class Object;
	class CameraComponent;
	class CollisionManager;
	class GestureManager;
	class BaseCamera;

	class BaseScene
	{
	public:
		BaseScene(const tstring & name);
		virtual ~BaseScene();
		
		void	BaseInitialize();
		void	BaseAfterInitializedObjects();
		void	BaseOnActivate();
		void	BaseOnDeactivate();
		void	BaseUpdate(const Context& context);
		void	BaseDraw();

		virtual void OnSaveState(void** pData,size_t* pSize);
		virtual void OnConfigurationChanged();
		virtual void OnLowMemory();

		const tstring & GetName() const;
		bool IsInitialized() const;

		void AddObject(Object * object); 
		void RemoveObject(Object * object);

		void SetActiveCamera(BaseCamera* pCamera);
		BaseCamera* GetActiveCamera() const;

		void SetCullingOffset(int offset);
		void SetCullingOffset(int offsetX, int offsetY);

		std::shared_ptr<Stopwatch> GetStopwatch() const;

		std::shared_ptr<GestureManager> GetGestureManager() const;
		std::shared_ptr<CollisionManager> GetCollisionManager() const;

	protected:
		virtual void CreateObjects();
		virtual void AfterInitializedObjects();
		virtual void OnActivate();
		virtual void OnDeactivate();
		virtual void Update(const Context& context);
		virtual void Draw();
		bool CheckCulling(Object* object);

		std::shared_ptr<GestureManager> m_GestureManagerPtr;
		std::shared_ptr<CollisionManager> m_CollisionManagerPtr;

		std::vector<Object*> m_Objects;
		BaseCamera* m_pDefaultCamera;
		std::shared_ptr<Stopwatch> m_pStopwatch;

	private:
		int m_CullingOffsetX,
			m_CullingOffsetY;
		bool m_Initialized;
		tstring m_Name;
	
		BaseScene(const BaseScene& t);
		BaseScene(BaseScene&& t);
		BaseScene& operator=(const BaseScene& t);
		BaseScene& operator=(BaseScene&& t);
	};
}
