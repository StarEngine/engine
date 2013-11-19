#include "SwipeGesture.h"
#include "../../Logger.h"
#include "../../defines.h"
#include "../../Context.h"
#include "../../Helpers/Helpers.h"
#include "../../Helpers/Math.h"
#include "../InputManager.h"
#define INPUT_MANAGER (InputManager::GetInstance())

namespace star
{
	SwipeGesture::SwipeGesture(): 
		star::BaseGesture(),
		m_ElapsedTime(0),
		m_Speed(0),
		m_StartPos(),
		m_CurrentPos(),
		m_OldPos(),
		m_OldDirection(),
		m_bIsGestureOk(true),
		m_TotalDistance(0)
	{
	}

	SwipeGesture::~SwipeGesture()
	{

	}

	#ifdef _WIN32
	void SwipeGesture::OnUpdateWinInputState()
	{
		if(INPUT_MANAGER->IsMouseButtonPressedWIN(VK_LBUTTON))
		{
			InitializeAllVars();
		}
		if(INPUT_MANAGER->IsMouseButtonDownWIN(VK_LBUTTON))
		{
			//Analyze the movement, its only a swipe if it's a relatively straight line (dot product?)
			//Get the direction, check if it's different from the last one and add it to an average direction
			if(m_bIsGestureOk)
			{
				m_CurrentPos = INPUT_MANAGER->GetCurrentMousePosition();
				if(m_OldPos != m_CurrentPos)
				{
					//The mouse moved
					vec2 dir = m_CurrentPos - m_OldPos;
					dir = Normalize(dir);
					if(m_OldDirection != vec2())
					{
						if(Dot(dir, m_OldDirection) >= cos(DegreesToRadians(float32(ANGLE_FLEX))))
						{
							m_OldPos = INPUT_MANAGER->GetCurrentMousePosition();
							m_OldDirection = dir;
						}
						else
						{
							m_bIsGestureOk = false;
						}
					}
					else
					{
						m_OldPos = INPUT_MANAGER->GetCurrentMousePosition();
						m_OldDirection = dir;
					}
					//Check speed:
					m_TotalDistance = Mag(m_CurrentPos - m_StartPos);
					m_Speed = m_TotalDistance / float32(m_ElapsedTime);
				}
			}			

		}
		if(INPUT_MANAGER->IsMouseButtonReleasedWIN(VK_LBUTTON))
		{
			//Check if it really was a swipe: speed & distance
			//div average dir by amount of times it was down, calc speed, dir and length :)
			if(m_bIsGestureOk)
			{
				//[TODO] -- make distance in % of screen!
				if(m_Speed >= MIN_SWIPE_SPEED && m_TotalDistance >= MIN_SWIPE_DISTANCE)
				{
					m_bCompletedGesture = true;
				}
			}
		}
	}
	#else
	void SwipeGesture::OnTouchEvent(AInputEvent* pEvent)
	{
		int32 action = AMotionEvent_getAction(pEvent);
		uint32 flags = action & AMOTION_EVENT_ACTION_MASK;
		switch(flags)
		{
		case AMOTION_EVENT_ACTION_DOWN:
			InitializeAllVars();
			break;
		case AMOTION_EVENT_ACTION_MOVE:
			//Analyze the movement, its only a swipe if it's a relatively straight line (dot product?)
			//Get the direction, check if it's different from the last one and add it to an average direction
			if(m_bIsGestureOk)
			{
				m_CurrentPos = INPUT_MANAGER->GetCurrentTouchPosANDR();
				if(m_OldPos != m_CurrentPos)
				{
					vec2 dir = m_CurrentPos - m_OldPos;
					dir = Normalize(dir);
					if(m_OldDirection != vec2())
					{
						if(Dot(dir, m_OldDirection) >= cos(DegreesToRadians(float32(ANGLE_FLEX))))
						{
							m_OldPos = INPUT_MANAGER->GetCurrentTouchPosANDR();
							m_OldDirection = dir;
						}
						else
						{
							m_bIsGestureOk = false;
						}
					}
					else
					{
						m_OldPos = INPUT_MANAGER->GetCurrentTouchPosANDR();
						m_OldDirection = dir;
					}
					//Check speed:
					m_TotalDistance = Mag(m_CurrentPos - m_StartPos);
					m_Speed = m_TotalDistance / (float32)m_ElapsedTime ;
				}
			}
			break;
		case AMOTION_EVENT_ACTION_UP:
			//Check if it really was a swipe: speed & distance
			//div average dir by amount of times it was down, calc speed, dir and length :)
			if(m_bIsGestureOk)
			{
				if(m_Speed >= MIN_SWIPE_SPEED && m_TotalDistance >= MIN_SWIPE_DISTANCE)
				{
					m_bCompletedGesture = true;
				}
			}
			break;
		}
	}

	#endif
	void SwipeGesture::Update(const Context& context)
	{
		if(m_bIsGestureOk)
		{
			m_ElapsedTime += context.mTimeManager->GetSeconds();
		}
	}

	void SwipeGesture::InitializeAllVars()
	{
		//Start recording the move
		m_StartPos = INPUT_MANAGER->GetCurrentFingerPosCP();
		m_CurrentPos = m_StartPos;
		m_OldPos = m_StartPos;
		m_ElapsedTime = 0;
		m_Speed = 0;
		m_bIsGestureOk = true;
		m_OldDirection = vec2();
		m_TotalDistance = 0;
	}

	vec2 SwipeGesture::GetSwipeDirection() const
	{
		vec2 vec = m_CurrentPos - m_StartPos;
		if(vec != vec2())
		{
			return Normalize(vec);
		}
		return vec;
	}

	float32 SwipeGesture::GetSwipeSpeed() const
	{
		return m_Speed;
	}

	float32 SwipeGesture::GetSwipeLength() const
	{
		return m_TotalDistance;
	}
}
