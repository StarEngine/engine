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

	// [COMMENT] Gesture-Tags
	// Gestures should also be given a user-defined tag 
	// when added to the the manager.

	// this way the user can look them up by tag, rather then
	// on pointer ( for adding one, or removing one, or getting one )
	// Part of the beauty of this kind of managing concept is
	// that the user doesn't have to bother about the pointers
	// as that's all managed inside the manager.

	// On a side note... It's probably a good practice that the user defines
	// these gestures in the Game class, as scenes get created
	// and deleted everytime the screen rotates on android.

	class GestureManager {
	public:
		GestureManager();
		~GestureManager();
		void Update(const Context& context);
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
		double m_dTime;
		double m_TotalTime;

		GestureManager(const GestureManager& t);
		GestureManager(GestureManager&& t);
		GestureManager& operator=(const GestureManager& t);
		GestureManager& operator=(GestureManager&& t);
	};
}
