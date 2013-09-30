#include "TapGesture.h"
#include "../../Logger.h"
#include "../../defines.h"

namespace star
{
	TapGesture::TapGesture(): BaseGesture()
	{

	}

	TapGesture::~TapGesture()
	{

	}

	void OnTouchEvent(AInputEvent* pEvent)
	{
		int32 action = AMotionEvent_getAction(pEvent);
		uint32 flags = action & AMOTION_EVENT_ACTION_MASK;
		switch(flags)
		{
		case AMOTION_EVENT_ACTION_DOWN:
			break;
		case AMOTION_EVENT_ACTION_UP:
			std::tstringstream buffer;
			buffer <<  _T("Down time: ") << AMotionEvent_getDownTime(pEvent);
			Logger::GetSingleton()->Log(LogLevel::Info, buffer.str());
			break;
		case AMOTION_EVENT_ACTION_MOVE:
			break;
		case AMOTION_EVENT_ACTION_CANCEL:
			break;
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
			break;
		case AMOTION_EVENT_ACTION_POINTER_UP:
			break;
		case AMOTION_EVENT_ACTION_OUTSIDE:
			break;
		}
	}
}
