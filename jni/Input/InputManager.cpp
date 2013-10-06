#include "InputManager.h"

#ifdef _WIN32
#include "Window.h"
#include <future>
#else
#include "../Logger.h"
#include <cmath>
#include <algorithm>
#endif

namespace star
{
	//Initialize all static variables

#ifdef _WIN32
	const float InputManager::BYTE_TO_DOUBLE_VALUE = 255.0f;
#else
	const float InputManager::UNDEFINED_POINTER_POSITION = -123456.0f;
#endif

	//Make this a static object
	InputManager* InputManager::m_InputManagerPtr = nullptr;

	InputManager::InputManager(void)
	#ifdef _WIN32
		: m_ThreadAvailable(true)
		, m_pCurrKeyboardState(nullptr)
		, m_pOldKeyboardState(nullptr)
		, m_pKeyboardState0(nullptr)
		, m_pKeyboardState1(nullptr)
		, m_KeyboardState0Active(true)
		, m_OldMousePosition()
		, m_CurrMousePosition()
		, m_MouseMovement()
	#else
		: m_bMainIsDown(false)
		, m_bMainIsUp(false)
		, m_bPointerIsDown(false)
		, m_bPointerIsUp(false)
		, m_NumberOfPointers(0)
		, m_ActivePointerID(0)
		, m_PointerVec()
		, m_OldPointerVec()
	#endif
		, m_GestureManager(nullptr)
	{
		Initialize();
	}


	InputManager::~InputManager(void)
	{
#ifdef _WIN32
		//Make sure to delete the used memory
		if(m_pKeyboardState0 != nullptr)
		{
			delete [] m_pKeyboardState0;
			delete [] m_pKeyboardState1;

			m_pKeyboardState0 = nullptr;
			m_pKeyboardState1 = nullptr;
			m_pCurrKeyboardState = nullptr;
			m_pOldKeyboardState = nullptr;
		}
#endif
	}

	InputManager* InputManager::GetInstance()
	{
		if (m_InputManagerPtr == nullptr)
		{
			m_InputManagerPtr = new InputManager();
		}
		return (m_InputManagerPtr);
	}

	void InputManager::ResetSingleton()
	{
		delete m_InputManagerPtr;
		m_InputManagerPtr = nullptr;
	}
	
	//Initializes the keyboard states
	void InputManager::Initialize()
	{
#ifdef _WIN32
		//Init new keyboard states
		if(m_pKeyboardState0 == nullptr)
		{
			m_pKeyboardState0 = new BYTE[256];
			m_pKeyboardState1 = new BYTE[256];

			GetKeyboardState(m_pKeyboardState0);
			GetKeyboardState(m_pKeyboardState1);
		}
#else
#endif

		m_GestureManager = new GestureManager();
	}

#ifdef _WIN32
	//[TODO] add this for android

	//Adds an inputAction to the list of inputActions
	bool InputManager::AddInputAction(const InputAction& action)
	{
		auto it = m_InputActions.find(action.ActionID);
		if(it != m_InputActions.end())
		{
			return false;
		}
		m_InputActions[action.ActionID] = action;
		return true;
	}

	bool InputManager::IsActionTriggered(int actionID) const
	{
		return m_InputActions.at(actionID).IsTriggered;
	}
	//[TODO] -- end TODO

	void InputManager::UpdateGamepadStates()
	{
		DWORD dwResult;
		for(DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			m_OldGamepadState[i] = m_CurrGamepadState[i];

			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			//returns ERROR_DEVICE_NOT_CONNECTED if i is invalid
			dwResult = XInputGetState(i, &state);
			m_CurrGamepadState[i] = state;

			//If the gamepad was connected, update the "connected gamepad array
			if(dwResult == ERROR_SUCCESS)
			{
				m_ConnectedGamepads[i] = true;
			}
			else
			{
				m_ConnectedGamepads[i] = false;
			}
		}
	}

	bool InputManager::UpdateKeyboardStates()
	{
		//Get Current KeyboardState and set Old KeyboardState (needed for "released" checks)
		BOOL getKeyboardResult;
		if(m_KeyboardState0Active)
		{
			//GetKeyboardState is thread dependant! use AttachThreadInput to link them!
			getKeyboardResult = GetKeyboardState(m_pKeyboardState1);
			m_pOldKeyboardState = m_pKeyboardState0;
			m_pCurrKeyboardState = m_pKeyboardState1;
		}
		else
		{
			getKeyboardResult = GetKeyboardState(m_pKeyboardState0);
			m_pOldKeyboardState = m_pKeyboardState1;
			m_pCurrKeyboardState = m_pKeyboardState0;
		}

		m_KeyboardState0Active = !m_KeyboardState0Active;
		return getKeyboardResult > 0 ? true : false;
	}

	bool InputManager::IsKeyboardKeyDown(uint8 key, bool previousFrame) const
	{
		if(key > 0x07 && key <= 0xFE)
		{
			return IsKeyboardKeyDown_unsafe(key, previousFrame);
		}
		return false;
	}

	bool InputManager::IsMouseButtonTapWIN(uint8 button) const
	{
		if(IsMouseButtonDownWIN(button) && !IsMouseButtonDownWIN(button, true))
		{
			return true;
		}
		return false;
	}

	bool InputManager::IsMouseButtonDownWIN(uint8 button, bool previousFrame) const
	{
		if(button > 0x00 && button <= 0x06)
		{
			return IsMouseButtonDown_unsafe(button, previousFrame);
		}
		return false;
	}

	bool InputManager::IsMouseButtonUpWIN(uint8 button) const
	{
		if(!IsMouseButtonDownWIN(button) && IsMouseButtonDownWIN(button, true))
		{
			return true;
		}
		return false;
	}

	bool InputManager::IsGamepadButtonDown(WORD button, GamepadIndex playerIndex, bool previousFrame) const
	{
		if(button > 0x0000 && button<=0x8000)
		{
			return IsGamepadButtonDown_unsafe(button, playerIndex, previousFrame);
		}
		return false;
	}

	bool InputManager::IsAnyKeyDown() const
	{
		for (int i = 0; i < 256; ++i)
		{
			if( (char) (GetAsyncKeyState(i) >> 8))
				return true;
		}
		for(int index = 0; index < XUSER_MAX_COUNT; ++index)
		{
			if(m_ConnectedGamepads[index] == true)
			{
				for(WORD button = 0x00000001; button < 0x8000; button *= 2)
				{
					if(IsGamepadButtonDown(button,static_cast<GamepadIndex>(index)))
						return true;
				}
			}
		}
		return false;
	}

	//NO RANGE CHECKS
	bool InputManager::IsKeyboardKeyDown_unsafe(uint8 key, bool previousFrame) const
	{
		if(previousFrame)
		{
			return (m_pOldKeyboardState[key]&0xF0)!=0;
		}
		else
		{
			return (m_pCurrKeyboardState[key]&0xF0)!=0;
		}
	}

	//NO RANGE CHECKS
	bool InputManager::IsMouseButtonDown_unsafe(uint8 button, bool previousFrame) const
	{
		if(previousFrame)
		{
			return (m_pOldKeyboardState[button]&0xF0)!=0;
		}
		else
		{
			return (m_pCurrKeyboardState[button]&0xF0)!=0;
		}
	}

	//NO RANGE CHECKS
	bool InputManager::IsGamepadButtonDown_unsafe(WORD button, GamepadIndex playerIndex, bool previousFrame) const
	{
		if(!m_ConnectedGamepads[playerIndex])
		{
			return false;
		}
		if(previousFrame)
		{
			return (m_OldGamepadState[playerIndex].Gamepad.wButtons&button)!=0;
		}
		else
		{
			return (m_CurrGamepadState[playerIndex].Gamepad.wButtons&button)!=0;
		}
	}
	
	void InputManager::UpdateWin()
	{
		m_ThreadAvailable = false;

		UpdateKeyboardStates();
		UpdateGamepadStates();

		//Reset previous InputAction States
		for(auto elem : m_InputActions)
		{
			auto currAction = &(elem.second);
			//Reset the previous state before updating/checking the new state
			currAction->IsTriggered = false;

			switch(currAction->TriggerState)
			{
				//if the input wasnt down last frame, but it is now, it is pressed
			case InputTriggerState::Pressed:
				//KEYBOARD
				if(	currAction->KeyboardCode > MIN_KEYBOARD_VALUE && 
					currAction->KeyboardCode <= MAX_KEYBOARD_VALUE)
				{
					if(!IsKeyboardKeyDown_unsafe(currAction->KeyboardCode,true) && 
						IsKeyboardKeyDown_unsafe(currAction->KeyboardCode))
					{
						currAction->IsTriggered = true;
					}
				}

				//MOUSE
				if(!currAction->IsTriggered &&
					currAction->MouseButtonCode > MIN_MOUSE_BUTTON_VALUE &&
					currAction->MouseButtonCode <= MAX_MOUSE_BUTTON_VALUE)
				{
					if(!IsMouseButtonDown_unsafe(currAction->MouseButtonCode,true) &&
						IsMouseButtonDown_unsafe(currAction->MouseButtonCode))
					{
						currAction->IsTriggered = true;
						Logger::GetInstance()->Log(LogLevel::Info, 
							_T("Clicked mouse button."));
					}
				}

				//GAMEPADS
				if(!currAction->IsTriggered && currAction->GamepadButtonCode != 0)
					if(!IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex,true) &&
						IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex))
					{
						currAction->IsTriggered = true;
					}

				break;

				//if the input was down last frame, and is down now, it is down.
			case InputTriggerState::Down:
				//KEYBOARD
				if(currAction->KeyboardCode > MIN_KEYBOARD_VALUE && 
					currAction->KeyboardCode <= MAX_KEYBOARD_VALUE)
				{
					if(IsKeyboardKeyDown_unsafe(currAction->KeyboardCode,true) &&
						IsKeyboardKeyDown_unsafe(currAction->KeyboardCode))
					{
						currAction->IsTriggered = true;
					}
				}

				//MOUSE
				if(!currAction->IsTriggered &&
					currAction->MouseButtonCode > MIN_MOUSE_BUTTON_VALUE &&
					currAction->MouseButtonCode <= MAX_MOUSE_BUTTON_VALUE)
				{
					if(	IsMouseButtonDown_unsafe(currAction->MouseButtonCode,true) &&
						IsMouseButtonDown_unsafe(currAction->MouseButtonCode))
					{
						currAction->IsTriggered = true;
					}
				}
				//GAMEPADS
				if(!currAction->IsTriggered && currAction->GamepadButtonCode != 0)
				{
					if(	IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex,true) &&
						IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex))
					{
						currAction->IsTriggered = true;
					}
				}
				break;

				//If the input was down last frame, but isn't down anymore, it was released.
			case InputTriggerState::Released:
				//KEYBOARD
				if(	currAction->KeyboardCode > MIN_KEYBOARD_VALUE &&
					currAction->KeyboardCode <= MAX_KEYBOARD_VALUE)
				{
					if(	IsKeyboardKeyDown_unsafe(currAction->KeyboardCode,true) && 
						!IsKeyboardKeyDown_unsafe(currAction->KeyboardCode))
					{
						currAction->IsTriggered = true;
					}
				}

				//MOUSE
				if(!currAction->IsTriggered && 
					currAction->MouseButtonCode > MIN_MOUSE_BUTTON_VALUE && 
					currAction->MouseButtonCode <= MAX_MOUSE_BUTTON_VALUE)
				{
					if(	IsMouseButtonDown_unsafe(currAction->MouseButtonCode,true) && 
						!IsMouseButtonDown_unsafe(currAction->MouseButtonCode))
					{
						currAction->IsTriggered = true;
					}
				}

				//GAMEPADS
				if(!currAction->IsTriggered && 
					currAction->GamepadButtonCode > MIN_GAMEPAD_VALUE && 
					currAction->GamepadButtonCode <= MAX_GAMEPAD_VALUE)
				{
					if(	IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex,true) && 
						!IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex))
					{
						currAction->IsTriggered = true;
					}
				}
				break;
			}
		}

		//Mouse Position
		m_OldMousePosition = m_CurrMousePosition;
		POINT mousePos;
		mousePos.x = (LONG)m_CurrMousePosition.x;
		mousePos.y = (LONG)m_CurrMousePosition.y;
		if(GetCursorPos(&mousePos))
		{
			ScreenToClient(Window::GetInstance()->GetHandle(),&mousePos);
		}
		m_CurrMousePosition = vec2(mousePos.x , mousePos.y);
		m_MouseMovement.x = m_CurrMousePosition.x - m_OldMousePosition.x;
		m_MouseMovement.y = m_CurrMousePosition.y - m_OldMousePosition.y;

		m_GestureManager->OnUpdateWinInputState();

		m_ThreadAvailable = true;
	}
	
	vec2 InputManager::GetThumbstickPosition
				(bool leftThumbstick, GamepadIndex playerIndex) const
	{
		vec2 pos;
		if(leftThumbstick)
		{
			pos = vec2(	m_CurrGamepadState[playerIndex].Gamepad.sThumbLX, 
						m_CurrGamepadState[playerIndex].Gamepad.sThumbLY);
			if(	pos.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
				pos.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				pos.x = 0;
			}
			if(	pos.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
				pos.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				pos.y = 0;
			}
		}
		else
		{
			pos = vec2(	m_CurrGamepadState[playerIndex].Gamepad.sThumbRX, 
						m_CurrGamepadState[playerIndex].Gamepad.sThumbRY);
			if(	pos.x > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
				pos.x < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				pos.x = 0;
			}
			if(	pos.y > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
				pos.y < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				pos.y = 0;
			}
		}

		//Shorts have a range of 32768, so to convert that range to a double, devide it by that range
		if(pos.x < 0)
		{
			pos.x /= MAX_VALUE_OF_SHORT;
		}
		else
		{
			pos.x /= MAX_VALUE_OF_SHORT;
		}

		if(pos.y < 0)
		{
			pos.y /= MAX_VALUE_OF_SHORT;
		}
		else
		{
			pos.y /= MAX_VALUE_OF_SHORT;
		}

		return pos;
	}
	
	float InputManager::GetTriggerPressure(bool leftTrigger, GamepadIndex playerIndex) const
	{
		if(leftTrigger)
		{
			//bLeftTrigger returns a byte, div by 255 to cast to double
			return m_CurrGamepadState[playerIndex].Gamepad.bLeftTrigger 
					/ BYTE_TO_DOUBLE_VALUE;
		}
		else
		{
			return m_CurrGamepadState[playerIndex].Gamepad.bRightTrigger 
					/ BYTE_TO_DOUBLE_VALUE;
		}
	}

	void InputManager::SetVibration(float leftVibration, float rightVibration, GamepadIndex playerIndex)
	{
		XINPUT_VIBRATION vibration;
		glm::clamp<float>(leftVibration, 0.0f, 1.0f);
		glm::clamp<float>(rightVibration, 0.0f, 1.0f);
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		//convert from float to word -> float * lenght of word
		vibration.wLeftMotorSpeed = static_cast<WORD>(leftVibration * MAX_VALUE_OF_WORD);
		vibration.wRightMotorSpeed = static_cast<WORD>(rightVibration * MAX_VALUE_OF_WORD);
		XInputSetState(playerIndex, &vibration);
	}
#else

	bool InputManager::IsTouchTapANDR(uint8 fingerIndex) const
	{
		if(m_NumberOfPointers == fingerIndex && (m_bMainIsDown || m_bPointerIsDown))
		{
			return (true);
		}
		return (false);
	}

	bool InputManager::IsTouchDownANDR(uint8 fingerIndex) const
	{
		if(m_NumberOfPointers == fingerIndex)
		{
			return (true);
		}
		return (false);
	}

	bool InputManager::IsTouchUpANDR(uint8 fingerIndex) const
	{
		if(m_NumberOfPointers == fingerIndex -1 && (m_bMainIsUp || m_bPointerIsUp))
		{
			return (true);
		}
		return (false);
	}

	vec2 InputManager::GetCurrentTouchPosANDR(uint8 fingerIndex) const
	{
		if((fingerIndex <= m_PointerVec.size() && fingerIndex > 0) && !m_bMainIsUp)
		{
			return (m_PointerVec.at(fingerIndex-1).Position);
		}
		return (vec2(UNDEFINED_POINTER_POSITION, UNDEFINED_POINTER_POSITION));
	}

	vec2 InputManager::GetOldTouchPosANDR(uint8 fingerIndex) const
	{
		if(((fingerIndex <= m_OldPointerVec.size() && fingerIndex > 0) && 
			(fingerIndex <= m_PointerVec.size() && fingerIndex > 0)) && 
			!m_bMainIsUp)
		{
			if(m_OldPointerVec.at(fingerIndex-1).ID == m_PointerVec.at(fingerIndex-1).ID)
			{
				return (m_OldPointerVec.at(fingerIndex-1).Position);
			}
		}
		return (vec2(UNDEFINED_POINTER_POSITION, UNDEFINED_POINTER_POSITION));
	}

	void InputManager::OnTouchEvent(AInputEvent* pEvent)
	{
		m_GestureManager->OnTouchEvent(pEvent);
		int32 action = AMotionEvent_getAction(pEvent);
		uint32 flags = action & AMOTION_EVENT_ACTION_MASK;
		switch(flags)
		{
		case AMOTION_EVENT_ACTION_POINTER_UP:
		{
			int pointerIndex((action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) 
								>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT);
			int pointerID(AMotionEvent_getPointerId(pEvent,pointerIndex));
			if(pointerID == m_ActivePointerID)
			{
				//This was our active pointer going up. Choose a new active pointer and adjust
				int newPointerIndex = pointerIndex == 0? 1 : 0;
				m_ActivePointerID = AMotionEvent_getPointerId(pEvent, newPointerIndex);
			}
			--m_NumberOfPointers;
			m_bPointerIsUp = true;
			break;
		}
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
			++m_NumberOfPointers;
			m_bPointerIsDown = true;
			break;
		case AMOTION_EVENT_ACTION_DOWN:
			m_ActivePointerID = AMotionEvent_getPointerId(pEvent, 0);
			++m_NumberOfPointers;
			m_bMainIsDown = true;
			break;
		case AMOTION_EVENT_ACTION_UP:
			for(auto pointer : m_PointerVec)
			{
				pointer.Position = vec2();
				pointer.Pressure = 0;
				pointer.RawPosition = vec2();
			}
			m_ActivePointerID = INVALID_POINTER_ID;
			--m_NumberOfPointers;
			m_bMainIsUp = true;
			break;
		case AMOTION_EVENT_ACTION_CANCEL:
			m_ActivePointerID = INVALID_POINTER_ID;
			Logger::GetInstance()->Log(LogLevel::Info, _T("Canceled"));
			break;
		case AMOTION_EVENT_ACTION_OUTSIDE:
			Logger::GetInstance()->Log(LogLevel::Info, _T("Outside"));
			break;
		case AMOTION_EVENT_ACTION_MOVE:
			AMotionEvent_getDownTime(pEvent);
			AMotionEvent_getEdgeFlags(pEvent);
			AMotionEvent_getEventTime(pEvent);
			break;
		default:
			break;
		}

		m_OldPointerVec = m_PointerVec;
		m_PointerVec.clear();
		//Store every pointer in a vector, with their position and everything else we need
		for(int i = 0; i < AMotionEvent_getPointerCount(pEvent); ++i)
		{
			FingerPointerANDR temp = FingerPointerANDR();
			temp.ID = AMotionEvent_getPointerId(pEvent,i);
			temp.Position = vec2(AMotionEvent_getX(pEvent, i), AMotionEvent_getY(pEvent, i));
			temp.Pressure = AMotionEvent_getPressure(pEvent,i);
			temp.RawPosition = vec2(AMotionEvent_getRawX(pEvent, i), AMotionEvent_getRawY(pEvent, i));
			temp.ToolMajor = AMotionEvent_getToolMajor(pEvent, i);
			temp.ToolMinor = AMotionEvent_getToolMinor(pEvent, i);

			m_PointerVec.push_back(temp);
		}
		std::sort(m_PointerVec.begin(),m_PointerVec.end(),
					[] (const FingerPointerANDR& a, const FingerPointerANDR& b)
					{
						return (a.ID < b.ID);
					});
	}

	void InputManager::OnKeyboardEvent(AInputEvent* pEvent)
	{
		//[TODO] I will still clean this up later, might need this
		/*
		if(AKeyEvent_getAction(pEvent) == AKEY_EVENT_ACTION_DOWN)
		{
			switch(AKeyEvent_getKeyCode(pEvent))
			{
			case AKEYCODE_BACK:
				//return false;
			}
		}
		else
		{
			switch(AKeyEvent_getKeyCode(pEvent))
			{
			case AKEYCODE_MENU:
				//return false;
				break;
			case AKEYCODE_BACK:
				return false;
			}
		}*/
	}

	FingerPointerANDR InputManager::GetTouchPropertiesANDR(uint8 fingerIndex)const
	{
		if(fingerIndex <= m_PointerVec.size() && fingerIndex > 0)
		{
			return (m_PointerVec.at(fingerIndex - 1));
		}
		return (FingerPointerANDR());
	}
#endif

	void InputManager::Update()
	{
	#ifdef _WIN32
	/*	if(m_ThreadAvailable)
		{
			std::async(std::launch::async, [&] () 
			{*/
				UpdateWin();
			/*});
		}*/
	#endif
	}

	bool InputManager::IsFingerTapCP(uint8 finger) const
	{
#ifdef _WIN32
		return IsMouseButtonTapWIN(finger);
#else
		return (IsTouchTapANDR(finger));
#endif
	}

	bool InputManager::IsFingerDownCP(uint8 finger) const
	{
#ifdef _WIN32
		return IsMouseButtonDownWIN(finger);
#else
		return (IsTouchDownANDR(finger));
#endif
	}

	bool InputManager::IsFingerUpCP(uint8 finger) const
	{
#ifdef _WIN32
		return IsMouseButtonUpWIN(finger);
#else
		return (IsTouchUpANDR(finger));
#endif
	}

	vec2 InputManager::GetCurrentFingerPosCP(uint8 fingerIndex) const
	{
#ifdef _WIN32
		return GetCurrentMousePosition();
#else
		return (GetCurrentTouchPosANDR(fingerIndex));
#endif
	}

	vec2 InputManager::GetOldFingerPosCP(uint8 fingerIndex) const
	{
#ifdef _WIN32
		return GetOldMousePosition();
#else
		return (GetOldTouchPosANDR(fingerIndex));
#endif
	}


	void InputManager::EndUpdate()
	{
#ifndef _WIN32
		m_bMainIsDown = false;
		m_bMainIsUp = false;
		m_bPointerIsDown = false;
		m_bPointerIsUp = false;
#endif
	}
}
