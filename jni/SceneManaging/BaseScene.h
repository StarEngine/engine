#pragma once

#include "../defines.h"

namespace star 
{
	struct Context;

	class BaseScene
	{
	public:
		BaseScene(const tstring & name);
		virtual ~BaseScene() {}
		
		status BaseInitialize(const Context& contex);
		virtual status OnActivate() {return STATUS_OK;}
		virtual void OnDeactivate() {}
		virtual status Update(const Context& context) {return STATUS_OK;}
		virtual status Draw() {return STATUS_OK;}

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

	protected:
		virtual status Initialize(const Context& context) =0;



	private:
		bool m_Initialized;
		tstring m_Name;
		

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		BaseScene(const BaseScene& t);
		BaseScene(BaseScene&& t);
		BaseScene& operator=(const BaseScene& t);
	};
}
