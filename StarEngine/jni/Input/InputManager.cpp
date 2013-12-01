#include "InputManager.h"

#ifdef DESKTOP
#include <future>
#else
#include <cmath>
#include <algorithm>
#endif
#include "../Logger.h"
#include "../StarEngine.h"
#include "../Graphics/GraphicsManager.h"
#include "../Graphics/ScaleSystem.h"
#include "../Scenes/SceneManager.h"
#include "../Components/CameraComponent.h"
#include "../Scenes/BaseScene.h"
#include "../Objects/BaseCamera.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/Math.h"

namespace star
{
#ifdef DESKTOP
	const float32 InputManager::BYTE_TO_DOUBLE_VALUE = 255.0f;
#else
	const float32 InputManager::UNDEFINED_POINTER_POSITION = -123456.0f;
#endif

	InputManager * InputManager::m_InputManagerPtr = nullptr;

#ifdef DESKTOP
	InputAction::InputAction():
		ActionID(-1),
		TriggerState(InputTriggerState::Pressed),
		KeyboardCode(-1),
		MouseButtonCode(-1),
		GamepadButtonCode(0),
		PlayerIndex(GamepadIndex::PlayerOne),
		IsTriggered(false)
	{
	}

	InputAction::InputAction(int32 actionID, InputTriggerState triggerState,
				int32 keyboardCode, int32 mouseButtonCode, WORD gamepadButtonCode,
				GamepadIndex playerIndex):
		ActionID(actionID),
		TriggerState(triggerState),
		KeyboardCode(keyboardCode),
		MouseButtonCode(mouseButtonCode),
		GamepadButtonCode(gamepadButtonCode),
		PlayerIndex(playerIndex),
		IsTriggered(false)
	{
	}
#else
	FingerPointerANDR::FingerPointerANDR():
		Position(),
		RawPosition(),
		Pressure(0.0f),
		ToolMajor(0.0f),
		ToolMinor(0.0f),
		ID(0)
	{
	}
#endif

	InputManager::InputManager(void)
	#ifdef DESKTOP
		: m_ThreadAvailable(false)
		, m_KeyboardState0Active(true)
		, mWindowsHandle()
	#else
		: m_bMainIsDown(false)
		, m_bMainIsUp(false)
		, m_bPointerIsDown(false)
		, m_bPointerIsUp(false)
		, m_NumberOfPointers(0)
		, m_NumberOfPointersOLD(0)
		, m_ActivePointerID(0)
		, m_PointerVec()
		, m_OldPointerVec()
	#endif
		, m_GestureManager(nullptr)
		, m_OldMousePosition()
		, m_CurrMousePosition()
		, m_MouseMovement()
	{
#ifdef DESKTOP
		//Init new keyboard states
		GetKeyboardState(m_pKeyboardState0);
		GetKeyboardState(m_pKeyboardState1);
#endif
	}

	InputManager::~InputManager(void)
	{
		m_GestureManager = nullptr;
	}

	InputManager * InputManager::GetInstance()
	{
		if (m_InputManagerPtr == nullptr)
		{
			m_InputManagerPtr = new InputManager();
		}
		return (m_InputManagerPtr);
	}

	void InputManager::UpdateGestures(const Context & context)
	{
		m_GestureManager->Update(context);
	}

#ifdef DESKTOP
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

	bool InputManager::IsActionTriggered(int32 actionID) const
	{
		return m_InputActions.at(actionID).IsTriggered;
	}
	//[TODO] -- end TODO

	void InputManager::IsCursorVisible(bool visible)
	{
		ShowCursor(visible);
	}

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
			for(int32 i = 0 ; i < NUMBER_OF_KEYBOARDKEYS ; ++i)
			{
				m_pOldKeyboardState[i] = m_pKeyboardState0[i];
				m_pCurrKeyboardState[i] = m_pKeyboardState1[i];
			}
		}
		else
		{
			getKeyboardResult = GetKeyboardState(m_pKeyboardState0);
			for(int32 i = 0 ; i < NUMBER_OF_KEYBOARDKEYS ; ++i)
			{
				m_pOldKeyboardState[i] = m_pKeyboardState1[i];
				m_pCurrKeyboardState[i] = m_pKeyboardState0[i];
			}
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

	bool InputManager::IsMouseButtonPressedWIN(uint8 button) const
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

	bool InputManager::IsMouseButtonReleasedWIN(uint8 button) const
	{
		if(!IsMouseButtonDownWIN(button) && IsMouseButtonDownWIN(button, true))
		{
			return true;
		}
		return false;
	}

	void InputManager::SetWindowsHandle(HWND hWnd)
	{
		mWindowsHandle = hWnd;
	}

	bool InputManager::IsGamepadButtonDown(WORD button, GamepadIndex playerIndex, bool previousFrame) const
	{
		if(button > 0x0000 && button<=0x8000)
		{
			return IsGamepadButtonDown_unsafe(button, playerIndex, previousFrame);
		}
		return false;
	}

	const vec2 & InputManager::GetCurrentMousePosition() const
	{
		return m_CurrMousePosition;
	}

	const vec2 & InputManager::GetOldMousePosition() const
	{
		return m_OldMousePosition;
	}

	const vec2 & InputManager::GetMouseMovement() const
	{
		return m_MouseMovement;
	}

	bool InputManager::IsAnyKeyDown() const
	{
		for (uint8 i = 0; i < NUMBER_OF_KEYBOARDKEYS; ++i)
		{
			if( (schar) (GetAsyncKeyState(i) >> 8))
			{
				return true;
			}
		}
		for(uint8 index = 0; index < XUSER_MAX_COUNT; ++index)
		{
			if(m_ConnectedGamepads[index] == true)
			{
				for(WORD button = 0x00000001; button < MAX_GAMEPAD_VALUE; button *= 2)
				{
					if(IsGamepadButtonDown(button,static_cast<GamepadIndex>(index)))
					{
						return true;
					}
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
			return (m_pOldKeyboardState[key] & 0xF0) != 0;
		}
		else
		{
			return (m_pCurrKeyboardState[key] & 0xF0) != 0;
		}
	}

	//NO RANGE CHECKS
	bool InputManager::IsMouseButtonDown_unsafe(uint8 button, bool previousFrame) const
	{
		if(previousFrame)
		{
			return (m_pOldKeyboardState[button ]& 0xF0) != 0;
		}
		else
		{
			return (m_pCurrKeyboardState[button] & 0xF0) != 0;
		}
	}

	//NO RANGE CHECKS
	bool InputManager::IsGamepadButtonDown_unsafe(WORD button, GamepadIndex playerIndex, 
		bool previousFrame) const
	{
		if(!m_ConnectedGamepads[playerIndex])
		{
			return false;
		}
		if(previousFrame)
		{
			return (m_OldGamepadState[playerIndex].Gamepad.wButtons&button) != 0;
		}
		else
		{
			return (m_CurrGamepadState[playerIndex].Gamepad.wButtons&button) != 0;
		}
	}
	
	DWORD InputManager::UpdateWin()
	{
		//while(m_ThreadAvailable)
		{

			UpdateKeyboardStates();
			UpdateGamepadStates();

			//Reset previous InputAction States
			for(auto it = m_InputActions.begin() ; it != m_InputActions.end() ; ++it)
			{
				auto currAction = &(it->second);
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
								_T("Clicked mouse button."), STARENGINE_LOG_TAG);
						}
					}

					//GAMEPADS
					if(!currAction->IsTriggered && currAction->GamepadButtonCode != 0)
						if(!IsGamepadButtonDown_unsafe(
							currAction->GamepadButtonCode,currAction->PlayerIndex,true) &&
							IsGamepadButtonDown_unsafe(
							currAction->GamepadButtonCode,currAction->PlayerIndex))
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
						if(	IsGamepadButtonDown_unsafe(
							currAction->GamepadButtonCode,currAction->PlayerIndex,true) &&
							IsGamepadButtonDown_unsafe(
							currAction->GamepadButtonCode,currAction->PlayerIndex))
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
						if(	IsGamepadButtonDown_unsafe(
							currAction->GamepadButtonCode,currAction->PlayerIndex,true) && 
							!IsGamepadButtonDown_unsafe(
							currAction->GamepadButtonCode,currAction->PlayerIndex))
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
			if(GetCursorPos(&mousePos))
			{
				ScreenToClient(mWindowsHandle,&mousePos);
			}
			
			m_CurrMousePosition = vec2(
				mousePos.x , 
				float32(GraphicsManager::GetInstance()->GetWindowHeight() - mousePos.y));
			m_CurrMousePosition -= vec2(
				float32(GraphicsManager::GetInstance()->GetHorizontalViewportOffset()),
				float32(GraphicsManager::GetInstance()->GetVerticalViewportOffset()));
			m_CurrMousePosition /= GraphicsManager::GetInstance()->GetViewportResolution();
			m_CurrMousePosition *= GraphicsManager::GetInstance()->GetScreenResolution();
			
			if(SceneManager::GetInstance()->GetActiveScene())
			{
				BaseCamera* projectionObject = SceneManager::GetInstance()->
					GetActiveScene()->GetActiveCamera();
				if(projectionObject)
				{
					m_CurrMousePosition += projectionObject->GetTransform()->
						GetWorldPosition().pos2D();
				}
			}

			m_MouseMovement.x = m_CurrMousePosition.x - m_OldMousePosition.x;
			m_MouseMovement.y = m_CurrMousePosition.y - m_OldMousePosition.y;

			if(m_GestureManager != nullptr)
			{
				m_GestureManager->OnUpdateWinInputState();
			}
			//Sleep(1000/60);
		}
		return 0;
	}
	
	void InputManager::StartKeyboardThread()
	{
		m_ThreadAvailable = true;
	}

	void InputManager::StopKeyboardThread()
	{
		m_ThreadAvailable = false;
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

		//Shorts have a range of 32768, so to convert that range to a float64, 
		//devide it by that range
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
	
	float32 InputManager::GetTriggerPressure(bool leftTrigger, GamepadIndex playerIndex) const
	{
		if(leftTrigger)
		{
			//bLeftTrigger returns a byte, div by 255 to cast to float64
			return m_CurrGamepadState[playerIndex].Gamepad.bLeftTrigger 
					/ BYTE_TO_DOUBLE_VALUE;
		}
		else
		{
			return m_CurrGamepadState[playerIndex].Gamepad.bRightTrigger 
					/ BYTE_TO_DOUBLE_VALUE;
		}
	}

	void InputManager::SetVibration(float32 leftVibration, float32 rightVibration, 
		GamepadIndex playerIndex)
	{
		XINPUT_VIBRATION vibration;
		Clamp(leftVibration, 0.0f, 1.0f);
		Clamp(rightVibration, 0.0f, 1.0f);
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		//convert from float32 to word -> float32 * lenght of word
		vibration.wLeftMotorSpeed = static_cast<WORD>(leftVibration * MAX_VALUE_OF_WORD);
		vibration.wRightMotorSpeed = static_cast<WORD>(rightVibration * MAX_VALUE_OF_WORD);
		XInputSetState(playerIndex, &vibration);
	}

	uint8 InputManager::ConvertIndexToVK(uint8 fingerIndex) const
	{
		switch(fingerIndex)
		{
		case 1:
			return VK_LBUTTON;
		case 2:
			return VK_RBUTTON;
		case 3:
			return VK_MBUTTON;
		case 4:
			return VK_XBUTTON1;
		case 5:
			return VK_XBUTTON2;
		default:
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Only 5 (0 - 4) finger Indices supported for mouse. Using VK_XBUTTON2"),
				STARENGINE_LOG_TAG);
			return VK_XBUTTON2;
		}
	}
#else

	bool InputManager::IsTouchPressedANDR(uint8 fingerIndex) const
	{
		if(m_NumberOfPointers >= fingerIndex && (m_bMainIsDown || m_bPointerIsDown))
		{
			return (true);
		}
		return (false);
	}

	bool InputManager::IsTouchDownANDR(uint8 fingerIndex) const
	{
		if(m_NumberOfPointers >= fingerIndex)
		{
			return (true);
		}
		return (false);
	}

	bool InputManager::IsTouchReleasedANDR(uint8 fingerIndex) const
	{
		if(m_NumberOfPointers >= fingerIndex -1 && (m_bMainIsUp || m_bPointerIsUp))
		{
			return (true);
		}
		return (false);
	}

	vec2 InputManager::GetCurrentTouchPosANDR(uint8 fingerIndex)
	{
		if((fingerIndex <= m_PointerVec.size() && fingerIndex > 0))
		{
			m_CurrMousePosition = m_PointerVec.at(fingerIndex-1).Position;
			m_CurrMousePosition = vec2(
				m_CurrMousePosition.x , 
				(float32)GraphicsManager::GetInstance()->GetWindowHeight() - m_CurrMousePosition.y);
			m_CurrMousePosition -= vec2(
				float32(GraphicsManager::GetInstance()->GetHorizontalViewportOffset()),
				float32(GraphicsManager::GetInstance()->GetVerticalViewportOffset()));
			m_CurrMousePosition /= GraphicsManager::GetInstance()->GetViewportResolution();
			m_CurrMousePosition *= GraphicsManager::GetInstance()->GetScreenResolution();
			
			if(SceneManager::GetInstance()->GetActiveScene())
			{
				BaseCamera* projectionObject = SceneManager::GetInstance()->
					GetActiveScene()->GetActiveCamera();
				if(projectionObject)
				{
					m_CurrMousePosition += projectionObject->GetTransform()->
						GetWorldPosition().pos2D();
				}
			}
		}
		return m_CurrMousePosition;
	}

	vec2 InputManager::GetOldTouchPosANDR(uint8 fingerIndex)
	{
		if(((fingerIndex <= m_OldPointerVec.size() && fingerIndex > 0) &&
			(fingerIndex <= m_PointerVec.size() && fingerIndex > 0)))
		{
			if(m_OldPointerVec.at(fingerIndex-1).ID == m_PointerVec.at(fingerIndex-1).ID)
			{
				m_OldMousePosition = m_OldPointerVec.at(fingerIndex-1).Position;
				m_OldMousePosition = vec2(
				m_OldMousePosition.x , 
					(float32)GraphicsManager::GetInstance()->GetWindowHeight() - m_OldMousePosition.y);
				m_OldMousePosition -= vec2(
					float32(GraphicsManager::GetInstance()->GetHorizontalViewportOffset()),
					float32(GraphicsManager::GetInstance()->GetVerticalViewportOffset()));
				m_OldMousePosition /= GraphicsManager::GetInstance()->GetViewportResolution();
				m_OldMousePosition *= GraphicsManager::GetInstance()->GetScreenResolution();
			
				//[BUG] if camera moves, this might be a bad idea..
				if(SceneManager::GetInstance()->GetActiveScene())
				{
					BaseCamera* projectionObject = SceneManager::GetInstance()->
						GetActiveScene()->GetActiveCamera();
					if(projectionObject)
					{
						m_OldMousePosition += projectionObject->GetTransform()->
							GetWorldPosition().pos2D();
					}
				}
			}
		}
		return m_OldMousePosition;
	}

	void InputManager::OnTouchEvent(AInputEvent* pEvent)
	{
		m_NumberOfPointersOLD = m_NumberOfPointers;
		int32 action = AMotionEvent_getAction(pEvent);
		uint32 flags = action & AMOTION_EVENT_ACTION_MASK;
		switch(flags)
		{
		case AMOTION_EVENT_ACTION_POINTER_UP:
		{
			int32 pointerIndex((action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) 
								>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT);
			int32 pointerID(AMotionEvent_getPointerId(pEvent,pointerIndex));
			if(pointerID == m_ActivePointerID)
			{
				//This was our active pointer going up. Choose a new active pointer and adjust
				int32 newPointerIndex = pointerIndex == 0? 1 : 0;
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
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("Canceled"), STARENGINE_LOG_TAG);
			break;
		case AMOTION_EVENT_ACTION_OUTSIDE:
			Logger::GetInstance()->Log(LogLevel::Info,
			_T("Outside"), STARENGINE_LOG_TAG);
			break;
		case AMOTION_EVENT_ACTION_MOVE:
			break;
		default:
			break;
		}

		m_OldPointerVec = m_PointerVec;
		m_PointerVec.clear();
		//Store every pointer in a vector, with their position and everything else we need
		for(int32 i = 0; i < AMotionEvent_getPointerCount(pEvent); ++i)
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
		if(m_GestureManager != nullptr)
		{
			m_GestureManager->OnTouchEvent(pEvent);
		}
	}

	bool InputManager::OnKeyboardEvent(AInputEvent* pEvent)
	{
		//[TODO] I will still clean this up later, might need this

		if(AKeyEvent_getAction(pEvent) == AKEY_EVENT_ACTION_DOWN)
		{
			//Try: (schar) cast the keycode
			switch(AKeyEvent_getKeyCode(pEvent))
			{
			case AKEYCODE_HOME:
				break;
			case AKEYCODE_BACK:
				break;
			case AKEYCODE_VOLUME_DOWN:
				break;
			}
			return false;
		}
		else
		{
			switch(AKeyEvent_getKeyCode(pEvent))
			{
			case AKEYCODE_MENU:
				//return false;
				break;
			case AKEYCODE_BACK:
				break;
			}
			return false;
		}
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

	bool InputManager::IsFingerPressedCP(uint8 fingerIndex) const
	{
		++fingerIndex;
#ifdef _WIN32
		return IsMouseButtonPressedWIN(ConvertIndexToVK(fingerIndex));
#else
		return (IsTouchPressedANDR(fingerIndex));
#endif
	}

	bool InputManager::IsFingerDownCP(uint8 fingerIndex) const
	{
		++fingerIndex;
#ifdef _WIN32
		return IsMouseButtonDownWIN(ConvertIndexToVK(fingerIndex));
#else
		return (IsTouchDownANDR(fingerIndex));
#endif
	}

	bool InputManager::IsFingerReleasedCP(uint8 fingerIndex) const
	{
		++fingerIndex;
#ifdef _WIN32
		return IsMouseButtonReleasedWIN(ConvertIndexToVK(fingerIndex));
#else
		return (IsTouchReleasedANDR(fingerIndex));
#endif
	}

	vec2 InputManager::GetCurrentFingerPosCP(uint8 fingerIndex)
	{
		++fingerIndex;
#ifdef DESKTOP
		return GetCurrentMousePosition();
#else
		return GetCurrentTouchPosANDR(fingerIndex);
#endif
	}

	vec2 InputManager::GetOldFingerPosCP(uint8 fingerIndex)
	{
		++fingerIndex;
#ifdef DESKTOP
		return GetOldMousePosition();
#else
		return (GetOldTouchPosANDR(fingerIndex));
#endif
	}

	void InputManager::EndUpdate()
	{
		m_GestureManager->EndUpdate();
#ifndef DESKTOP
		m_bMainIsDown = false;
		m_bMainIsUp = false;
		m_bPointerIsDown = false;
		m_bPointerIsUp = false;
#endif
	}

	void InputManager::SetGestureManager(std::shared_ptr<GestureManager> gestureManager)
	{
		m_GestureManager = gestureManager;
	}

	std::shared_ptr<GestureManager> InputManager::GetGestureManager() const
	{
		return m_GestureManager;
	}
}
