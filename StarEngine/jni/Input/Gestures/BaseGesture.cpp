#include "BaseGesture.h"
#include "../../Logger.h"
#include "../../Context.h"

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
		}

		void BaseGesture::OnTouchEvent(AInputEvent* pEvent)
		{
			//***********************************************
			// This is the base layout of this function. 
			// Please copy paste this into your child class
			// If you want to use Gestures for android.
			//***********************************************

			/*

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

			*/
		}

#endif
		void BaseGesture::Update(const Context& context)
		{
			
		}

		void BaseGesture::EndUpdate()
		{
			if(m_bCompletedGesture)
			{
				m_bCompletedGesture = false;
			}
		}

		bool BaseGesture::CompletedGesture()
		{
			 return m_bCompletedGesture;
		}
}
