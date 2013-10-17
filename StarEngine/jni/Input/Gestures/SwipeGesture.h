#pragma once
#include "BaseGesture.h"
#ifdef ANDROID
#include <android_native_app_glue.h>
#endif

namespace star
{
	class SwipeGesture : public BaseGesture
	{
	public:
		SwipeGesture();
		virtual ~SwipeGesture();

		virtual void Update(const Context& context);
		vec2 GetSwipeDirection() const;
		float GetSwipeSpeed() const;
		float GetSwipeLength() const;
	private:
	#ifdef _WIN32
		virtual void OnUpdateWinInputState();
	#else
		virtual void OnTouchEvent(AInputEvent* pEvent);
	#endif
		void InitializeAllVars();

		double m_ElapsedTime;
		float m_Speed;
		vec2 m_StartPos;
		vec2 m_CurrentPos;
		vec2 m_OldPos;
		vec2 m_OldDirection;
		static const int ANGLE_FLEX = 20;
		static const int MIN_SWIPE_SPEED = 1000;
		static const int MIN_SWIPE_DISTANCE = 200;
		bool m_bIsGestureOk;
		float m_TotalDistance;

		SwipeGesture(const SwipeGesture& t);
		SwipeGesture(SwipeGesture&& t);
		SwipeGesture& operator=(const SwipeGesture& t);
	};
}
