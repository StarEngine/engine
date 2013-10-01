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

	void TapGesture::OnTouchEvent(AInputEvent* pEvent)
	{
		int32 action = AMotionEvent_getAction(pEvent);
		uint32 flags = action & AMOTION_EVENT_ACTION_MASK;
		switch(flags)
		{
		case AMOTION_EVENT_ACTION_DOWN:
			break;
		case AMOTION_EVENT_ACTION_UP:
		{
		}
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
