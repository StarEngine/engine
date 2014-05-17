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
		SwipeGesture(
			int32 minSwipeDistance = 200, 
			int32 minSwipeSpeed = 1000,
			bool enableAngleFlex = false, 
			int32 angleFlex = 20);
		virtual ~SwipeGesture();

		virtual void Update(const Context& context);
		vec2 GetSwipeDirection() const;
		float32 GetSwipeSpeed() const;
		float32 GetSwipeLength() const;

		void SetAngleCheck(bool angleCheck);
		void SetAngleFlex(float32 degrees);
		void SetMinSwipeSpeed(float32 speed);
		void SetMinSwipeDistane(float32 distance);

	private:
	#ifdef _WIN32
		virtual void OnUpdateWinInputState();
	#else
		virtual void OnTouchEvent(AInputEvent* pEvent);
	#endif
		void InitializeAllVars();

		float64 m_ElapsedTime;
		float32 m_Speed;
		vec2 m_StartPos;
		vec2 m_CurrentPos;
		vec2 m_OldPos;
		vec2 m_OldDirection;
		int32 m_AngleFlex;
		int32 m_MinSwipeSpeed;
		int32 m_MinSwipeDistance;
		bool m_bEnableAngleFlex;
		bool m_bIsGestureOk;
		float32 m_TotalDistance;

		SwipeGesture(const SwipeGesture& t);
		SwipeGesture(SwipeGesture&& t);
		SwipeGesture& operator=(const SwipeGesture& t);
		SwipeGesture& operator=(SwipeGesture&& t);
	};
}
