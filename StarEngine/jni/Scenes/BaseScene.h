#pragma once

#include "../defines.h"
#include "../Input/Gestures/GestureManager.h"
#include "../Helpers/Stopwatch.h"
#include <vector>
#include <memory>

namespace star 
{
	struct Context;
	class Object;
	class CameraComponent;
	class BaseCamera;

	class BaseScene
	{
	public:
		BaseScene(const tstring & name);
		virtual ~BaseScene();
		
		status BaseInitialize(const Context& contex);
		status BaseOnActivate();
		void BaseOnDeactivate();
		status BaseUpdate(const Context& context);
		status BaseDraw();

		virtual void OnSaveState(void** pData,size_t* pSize);
		virtual void OnConfigurationChanged();
		virtual void OnLowMemory();

		const tstring & GetName() const;
		bool IsInitialized() const;

		void AddObject(Object * object); 
		void RemoveObject(Object * object);

		void SetActiveCamera(CameraComponent* pCameraComp);
		BaseCamera* GetActiveCamera() const;

		std::shared_ptr<Stopwatch> GetStopwatch() const;

	protected:
		virtual status CreateObjects();
		virtual status AfterInitializedObjects(const Context& context);
		virtual status OnActivate();
		virtual status OnDeactivate();
		virtual status Update(const Context& context);
		virtual status Draw();
		void CalculateViewPort();

		std::shared_ptr<GestureManager> m_GestureManagerPtr;

		std::vector<Object*> m_Objects;
		BaseCamera* m_pDefaultCamera;
		std::shared_ptr<Stopwatch> m_pStopwatch;

	private:
		bool m_Initialized;
		tstring m_Name;
	
		BaseScene(const BaseScene& t);
		BaseScene(BaseScene&& t);
		BaseScene& operator=(const BaseScene& t);
	};
}
