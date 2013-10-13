#pragma once

#include "../defines.h"
#include "../Input/Gestures/GestureManager.h"
#include <vector>

namespace star 
{
	struct Context;
	class Object;
	class CameraComponent;
	class FreeCamera;

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

		virtual void OnStart() {}
		virtual void OnResume() {}
		virtual void OnPause() {}
		virtual void OnStop() {}
		virtual void OnDestroy() {}

		virtual void OnSaveState(void** pData,size_t* pSize) {}
		virtual void OnConfigurationChanged() {}
		virtual void OnLowMemory() {}

		virtual void OnCreateWindow() {}
		virtual void OnDestroyWindow() {}
		virtual void OnGainFocus() {}
		virtual void OnLostFocus() {}

		const tstring & GetName() const { return m_Name; }
		bool IsInitialized() const { return m_Initialized; }

		void AddObject(Object * object); 
		void RemoveObject(Object * object);

		void SetActiveCamera(CameraComponent* pCameraComp);
		FreeCamera* GetActiveCamera() const {return m_pDefaultCamera;}

	protected:
		virtual status Initialize(const Context& context) { return STATUS_OK; }
		virtual status OnActivate() { return STATUS_OK; }
		virtual void OnDeactivate() {}
		virtual status Update(const Context& context) { return STATUS_OK; }
		virtual status Draw() {return STATUS_OK;}
		GestureManager* m_GestureManagerPtr;

		std::vector<Object*> m_Objects;
		//CameraComponent *m_pActiveCamera;
		FreeCamera* m_pDefaultCamera;

	private:
		bool m_Initialized;
		tstring m_Name;
		
	
		BaseScene(const BaseScene& t);
		BaseScene(BaseScene&& t);
		BaseScene& operator=(const BaseScene& t);
	};
}
