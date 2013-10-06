#include "BaseGesture.h"
#include "../../Logger.h"




namespace star
{
		BaseGesture::BaseGesture():
				m_bCompletedGesture(false)
		{

		}

		BaseGesture::~BaseGesture()
		{

		}

#ifdef _WIN32
		void BaseGesture::OnUpdateWinInputStateBase()
		{
			m_bCompletedGesture = false;
			OnUpdateWinInputState();
		}

		void BaseGesture::OnUpdateWinInputState()
		{
			//Use everything from the WinInputState struct at your will to define your gestures.
		}
#else
		void BaseGesture::OnTouchEventBase(AInputEvent* pEvent)
		{
			m_bCompletedGesture = false;
			OnTouchEvent(pEvent);
			//[TODO] What does this do?
			DefineMouseBehaviour();
		}

		void BaseGesture::OnTouchEvent(AInputEvent* pEvent)
		{
			int32 action = AMotionEvent_getAction(pEvent);
			uint32 flags = action & AMOTION_EVENT_ACTION_MASK;
			switch(flags)
			{
			case AMOTION_EVENT_ACTION_DOWN:
				break;
			case AMOTION_EVENT_ACTION_UP:
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

#endif
		void BaseGesture::Update(const Context& context)
		{

		}

		bool BaseGesture::CompletedGesture()
		{
			if(m_bCompletedGesture)
			{
				m_bCompletedGesture = !m_bCompletedGesture;
				return (true);
			}
			 return false;
		}
}
