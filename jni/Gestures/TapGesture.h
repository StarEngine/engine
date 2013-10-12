#pragma once
#include "../../StarEngine/jni/Input/BaseGesture.h"
#ifndef _WIN32
#include <android_native_app_glue.h>
#endif

class TapGesture : public star::BaseGesture
{
public:
	TapGesture();
	virtual ~TapGesture();

	virtual void Update(const star::Context& context);
private:
#ifdef _WIN32
	virtual void OnUpdateWinInputState();
#else
	virtual void OnTouchEvent(AInputEvent* pEvent);
#endif
	double m_StartTime;
	double m_TimeSinceBeginning;
	static const int MINIMUM_TAP_TIME = 10;
	static const int MAXIMUM_TAP_TIME = 500;

	TapGesture(const TapGesture& t);
	TapGesture(TapGesture&& t);
	TapGesture& operator=(const TapGesture& t);
};

