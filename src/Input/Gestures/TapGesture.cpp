#include "TapGesture.h"
#include "../../StarEngine/jni/Logger.h"
#include "../../StarEngine/jni/defines.h"
#include "../../StarEngine/jni/Context.h"

#include "../../StarEngine/jni/Input/InputManager.h"
#define INPUT_MANAGER (InputManager::GetInstance())

namespace star
{
	TapGesture::TapGesture(): 
		star::BaseGesture(),
		m_StartTime(0),
		m_TimeSinceBeginning(0)
	{

	}

	TapGesture::~TapGesture()
	{

	}

	#ifdef _WIN32
	void TapGesture::OnUpdateWinInputState()
	{
		if(INPUT_MANAGER->IsMouseButtonPressedWIN(VK_LBUTTON))
		{
			m_StartTime = m_TimeSinceBeginning;
		}
		if(INPUT_MANAGER->IsMouseButtonReleasedWIN(VK_LBUTTON))
		{
			float64 timeSinceDown = m_TimeSinceBeginning - m_StartTime;
			if(timeSinceDown > MINIMUM_TAP_TIME && timeSinceDown < MAXIMUM_TAP_TIME)
			{
				m_bCompletedGesture = true;
			}
		}
	}
	#else
	void TapGesture::OnTouchEvent(AInputEvent* pEvent)
	{
		int32 action = AMotionEvent_getAction(pEvent);
		uint32 flags = action & AMOTION_EVENT_ACTION_MASK;
		switch(flags)
		{
		case AMOTION_EVENT_ACTION_DOWN:
			m_StartTime = m_TimeSinceBeginning;
			break;
		case AMOTION_EVENT_ACTION_UP:
		{
			float64 timeSinceDown = m_TimeSinceBeginning - m_StartTime;
			if(timeSinceDown > MINIMUM_TAP_TIME && 
				timeSinceDown < MAXIMUM_TAP_TIME)
			{
				m_bCompletedGesture = true;
			}
			break;
		}
		}
	}

	#endif
	void TapGesture::Update(const Context& context)
	{
		m_TimeSinceBeginning = context.time->TimeSinceStart().GetMilliSeconds();
	}
}
