#pragma once

#include "../defines.h"

namespace star 
{
	class BaseScene
	{
	public:
		BaseScene(const tstring & name);
		virtual ~BaseScene() {}

		virtual status onActivate(){return STATUS_OK;}
		virtual void OnDeactivate() {}
		virtual status Update(){return STATUS_OK;}
		virtual status Draw(){return STATUS_OK;}

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

		const tstring & GetName() { return m_Name; }
		bool IsInitialized() { return m_Initialized; }

	private:
		tstring m_Name;
		bool m_Initialized;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		BaseScene(const BaseScene& t);
		BaseScene& operator=(const BaseScene& t);
	};
}
