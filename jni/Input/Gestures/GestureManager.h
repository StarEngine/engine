#pragma once
#ifdef _WIN32
#else
#include <android_native_app_glue.h>
#endif
#include <vector>
#include "BaseGesture.h"

namespace star
{
	struct WinInputState;

	class GestureManager {
	public:
		GestureManager();
		~GestureManager();
		void Update(const Context& context);
		void AddGesture(BaseGesture* gesture);
		void RemoveGesture(BaseGesture* gesture);

#ifdef _WIN32
		void OnUpdateWinInputState();
#else
		void OnTouchEvent(AInputEvent* pEvent);
#endif
	private:
		std::vector<BaseGesture*> m_GestureVec;
		double m_dTime;
		double m_TotalTime;

		GestureManager(const GestureManager& t);
		GestureManager(GestureManager&& t);
		GestureManager& operator=(const GestureManager& t);
	};
}
