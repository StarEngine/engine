#pragma once
#include "../../StarEngine/jni/Input/BaseGesture.h"
#ifndef _WIN32
#include <android_native_app_glue.h>
#endif

class DoubleTapGesture : public star::BaseGesture
{
public:
	DoubleTapGesture();
	virtual ~DoubleTapGesture();

	virtual void Update(const star::Context& context);
private:
#ifdef _WIN32
	virtual void OnUpdateWinInputState();
#else
	virtual void OnTouchEvent(AInputEvent* pEvent);
#endif
	double m_StartTime;
	double m_TimeSinceBeginning;
	double m_TimeBetweenTaps;
	static const int MINIMUM_TAP_TIME = 10;
	static const int MAXIMUM_TAP_TIME = 500;
	static const int MAXIMUM_TIME_BETWEEN_TAPS = 300;
	int m_Count;

	DoubleTapGesture(const DoubleTapGesture& t);
	DoubleTapGesture(DoubleTapGesture&& t);
	DoubleTapGesture& operator=(const DoubleTapGesture& t);
};
