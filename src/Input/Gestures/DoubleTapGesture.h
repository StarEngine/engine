#pragma once
#include "BaseGesture.h"
#ifdef ANDROID
#include <android_native_app_glue.h>
#endif

namespace star
{
	class DoubleTapGesture : public BaseGesture
	{
	public:
		DoubleTapGesture();
		virtual ~DoubleTapGesture();

		virtual void Update(const Context& context);
	private:
	#ifdef _WIN32
		virtual void OnUpdateWinInputState();
	#else
		virtual void OnTouchEvent(AInputEvent* pEvent);
	#endif
		float64 m_StartTime;
		float64 m_TimeSinceBeginning;
		float64 m_TimeBetweenTaps;
		vec2 m_StartPos;
		bool m_bIsGestureOk;
		static const int32 MINIMUM_TAP_TIME = 10;
		static const int32 MAXIMUM_TAP_TIME = 500;
		static const int32 MAXIMUM_TIME_BETWEEN_TAPS = 300;
		static const int32 MAXIMUM_MOVEMENT_RANGE = 50;
		int32 m_Count;

		DoubleTapGesture(const DoubleTapGesture& t);
		DoubleTapGesture(DoubleTapGesture&& t);
		DoubleTapGesture& operator=(const DoubleTapGesture& t);
		DoubleTapGesture& operator=(DoubleTapGesture&& t);
	};
}
