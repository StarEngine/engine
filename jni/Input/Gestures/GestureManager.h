#pragma once
#include <android_native_app_glue.h>
#include <vector>
#include "BaseGesture.h"

namespace star
{
	class GestureManager {
	public:
		GestureManager();
		~GestureManager();
		void UpdateTime(double dTime) {m_dTime = dTime;}
		void OnTouchEvent(AInputEvent* pEvent);
		void AddGesture(BaseGesture* gesture);
		bool RemoveGesture(BaseGesture* gesture);
	private:
		std::vector<BaseGesture*> m_GestureVec;
		double m_dTime;
	};
}
