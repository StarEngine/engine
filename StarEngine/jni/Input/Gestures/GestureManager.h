#pragma once
#ifdef _WIN32
#else
#include <android_native_app_glue.h>
#endif
#include <map>
#include <memory>
#include "BaseGesture.h"

namespace star
{
	struct WinInputState;

	class GestureManager 
	{
	public:
		GestureManager();
		~GestureManager();
		void Update(const Context& context);
		void EndUpdate();
		void AddGesture(BaseGesture* gesture, const tstring& tag);
		void RemoveGesture(BaseGesture* gesture);
		void RemoveGesture(const tstring& tag);
		const BaseGesture* GetGesture(const tstring& tag);

#ifdef _WIN32
		void OnUpdateWinInputState();
#else
		void OnTouchEvent(AInputEvent* pEvent);
#endif
	private:
		std::map<tstring, std::shared_ptr<BaseGesture>> m_GestureMap;
		float64 m_dTime;
		float64 m_TotalTime;

		GestureManager(const GestureManager& t);
		GestureManager(GestureManager&& t);
		GestureManager& operator=(const GestureManager& t);
		GestureManager& operator=(GestureManager&& t);
	};
}
