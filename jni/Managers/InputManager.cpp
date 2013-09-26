//----------------------------
//Heavily based on the input manager from the overlord engine.
//----------------------------

//----------------------------
//Include files
//----------------------------
#include "InputManager.h"
#ifdef _WIN32
#include "Window.h"
#else
#include "../Logger.h"
#include <cmath>
#endif

namespace star
{
	//Initialize all static variables

	#ifdef _WIN32
	PBYTE InputManager::m_pCurrKeyboardState = nullptr;
	PBYTE InputManager::m_pOldKeyboardState = nullptr;
	PBYTE InputManager::m_pKeyboardState0 = nullptr;
	PBYTE InputManager::m_pKeyboardState1 = nullptr;
	bool InputManager::m_KeyboardState0Active = true;
	POINT InputManager::m_OldMousePosition = POINT();
	POINT InputManager::m_CurrMousePosition = POINT();
	POINT InputManager::m_MouseMovement = POINT();
	XINPUT_STATE InputManager::m_OldGamepadState[XUSER_MAX_COUNT];
	XINPUT_STATE InputManager::m_CurrGamepadState[XUSER_MAX_COUNT];
	bool InputManager::m_ConnectedGamepads[XUSER_MAX_COUNT];
	#endif

	//Make this a static object
	InputManager* InputManager::m_InputManagerPtr = nullptr;

	InputManager::InputManager(void)
	{
	#ifndef _WIN32
		m_Application = nullptr;
		m_Horizontal = 0.0f;
		m_Vertical = 0.0f;
		m_RefPoint = vec2(0,0);
		m_Width = 0;
		m_Height = 0;
	#endif
	}


	InputManager::~InputManager(void)
	{
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
	}

	InputManager* InputManager::GetSingleton()
	{
		if (m_InputManagerPtr == nullptr)
		{
			m_InputManagerPtr = new InputManager();
		}
		return m_InputManagerPtr;
	}


	void InputManager::ResetSingleton()
	{
		delete m_InputManagerPtr; // REM : it works even if the pointer is NULL (does nothing then)
		m_InputManagerPtr = nullptr; // so GetInstance will still work.
	}
	
#ifdef _WIN32
	//Initializes the keyboard states
	void InputManager::Initialize()
	{

		//Init new keyboard states
		if(m_pKeyboardState0 == nullptr)
		{
			m_pKeyboardState0 = new BYTE[256];
			m_pKeyboardState1 = new BYTE[256];


			GetKeyboardState(m_pKeyboardState0);
			GetKeyboardState(m_pKeyboardState1);
		}
	}
#else
	void InitializeAndroid(android_app* pApplication, const int32& pWidth, const int32& pHeight)
	{

	}
#endif
	//[TODO] add this for android
	#ifdef _WIN32
	//Adds an inputAction to the list of inputActions
	bool InputManager::AddInputAction(const InputAction& action)
	{

		auto it = m_InputActions.find(action.ActionID);
		if(it != m_InputActions.end()) return false;

		m_InputActions[action.ActionID] = action;

		return true;
	}

	//Returns if an action was triggered.
	bool InputManager::IsActionTriggered(int actionID) const
	{
		return m_InputActions.at(actionID).IsTriggered;
	}

	#endif

	//XInput -- windows only
	#ifdef _WIN32
	//Update the gamepad states
	void InputManager::UpdateGamepadStates()
	{
		DWORD dwResult;
		//For each possible user
		for(DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			m_OldGamepadState[i] = m_CurrGamepadState[i];

			//Zeroise the input state
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

		//if GetKeyboardState fails, it returns 0
		return getKeyboardResult > 0 ? true : false;
	}

	#else

	bool InputManager::UpdateAndroidInputStates()
	{

	}
	#endif
	void InputManager::Update(double deltaTime)
	{
	#ifdef _WIN32
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
				if(currAction->KeyboardCode > 0x07 && currAction->KeyboardCode <= 0xFE)
					if(!IsKeyboardKeyDown_unsafe(currAction->KeyboardCode,true) && IsKeyboardKeyDown_unsafe(currAction->KeyboardCode))
						currAction->IsTriggered = true;

				//MOUSE
				if(!currAction->IsTriggered && currAction->MouseButtonCode > 0x00 && currAction->MouseButtonCode <= 0x06)
					if(!IsMouseButtonDown_unsafe(currAction->MouseButtonCode,true) && IsMouseButtonDown_unsafe(currAction->MouseButtonCode))
						currAction->IsTriggered = true;

				//GAMEPADS
				if(!currAction->IsTriggered && currAction->GamepadButtonCode != 0)
					if(!IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex,true) && IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex))
						currAction->IsTriggered = true;

				break;

				//if the input was down last frame, and is down now, it is down.
			case InputTriggerState::Down:
				//KEYBOARD
				if(currAction->KeyboardCode > 0x07 && currAction->KeyboardCode <= 0xFE)
					if(IsKeyboardKeyDown_unsafe(currAction->KeyboardCode,true) && IsKeyboardKeyDown_unsafe(currAction->KeyboardCode))
						currAction->IsTriggered = true;

				//MOUSE
				if(!currAction->IsTriggered && currAction->MouseButtonCode > 0x00 && currAction->MouseButtonCode <= 0x06)
					if(IsMouseButtonDown_unsafe(currAction->MouseButtonCode,true) && IsMouseButtonDown_unsafe(currAction->MouseButtonCode))
						currAction->IsTriggered = true;

				//GAMEPADS
				if(!currAction->IsTriggered && currAction->GamepadButtonCode != 0)
					if(IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex,true) && IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex))
						currAction->IsTriggered = true;
				break;

				//If the input was down last frame, but isn't down anymore, it was released.
			case InputTriggerState::Released:
				//KEYBOARD
				if(currAction->KeyboardCode > 0x07 && currAction->KeyboardCode <= 0xFE)
					if(IsKeyboardKeyDown_unsafe(currAction->KeyboardCode,true) && !IsKeyboardKeyDown_unsafe(currAction->KeyboardCode))
						currAction->IsTriggered = true;

				//MOUSE
				if(!currAction->IsTriggered && currAction->MouseButtonCode > 0x00 && currAction->MouseButtonCode <= 0x06)
					if(IsMouseButtonDown_unsafe(currAction->MouseButtonCode,true) && !IsMouseButtonDown_unsafe(currAction->MouseButtonCode))
						currAction->IsTriggered = true;

				//GAMEPADS
				if(!currAction->IsTriggered && currAction->GamepadButtonCode > 0x0000 && currAction->GamepadButtonCode<=0x8000)
					if(IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex,true) && !IsGamepadButtonDown_unsafe(currAction->GamepadButtonCode,currAction->PlayerIndex))
						currAction->IsTriggered = true;
				break;
			}
		}


		//Mouse Position
		m_OldMousePosition = m_CurrMousePosition;
		if(GetCursorPos(&m_CurrMousePosition))
		{
			ScreenToClient(Window::handle,&m_CurrMousePosition);
		}

		m_MouseMovement.x = m_CurrMousePosition.x - m_OldMousePosition.x;
		m_MouseMovement.y = m_CurrMousePosition.y - m_OldMousePosition.y;

	#else
		UpdateAndroidInputStates();
	#endif

	}

	#ifdef _WIN32
	bool InputManager::IsKeyboardKeyDown(int key, bool previousFrame) const
	{

		//If the key value is a value on the keyboard
		if(key > 0x07 && key <= 0xFE)
			return IsKeyboardKeyDown_unsafe(key, previousFrame);

		return false;
	}

	bool InputManager::IsMouseButtonDown(int button, bool previousFrame) const
	{
		//If the button value is a value on the mouse
		if(button > 0x00 && button <= 0x06)
			return IsMouseButtonDown_unsafe(button, previousFrame);

		return false;
	}

	bool InputManager::IsGamepadButtonDown(WORD button, GamepadIndex playerIndex, bool previousFrame) const
	{
		//if the button value is a value on the gamepad
		if(button > 0x0000 && button<=0x8000)
			return IsGamepadButtonDown_unsafe(button, playerIndex, previousFrame);

		return false;
	}

	#else

	bool InputManager::OnTouchEvent(AInputEvent* pEvent)
	{

	}
	bool InputManager::OnKeyboardEvent(AInputEvent* pEvent)
	{
		if(AKeyEvent_getAction(pEvent) == AKEY_EVENT_ACTION_DOWN)
		{
			switch(AKeyEvent_getKeyCode(pEvent))
			{
			case AKEYCODE_BACK:
				return false;
			}
		}
		else
		{
			switch(AKeyEvent_getKeyCode(pEvent))
			{
			case AKEYCODE_MENU:
				return false;
				break;
			case AKEYCODE_BACK:
				return false;
			}
		}
	}
	#endif
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

	#ifdef _WIN32
	//NO RANGE CHECKS
	bool InputManager::IsKeyboardKeyDown_unsafe(int key, bool previousFrame) const
	{
		if(previousFrame)
			return (m_pOldKeyboardState[key]&0xF0)!=0;
		else
			return (m_pCurrKeyboardState[key]&0xF0)!=0;
	}

	//NO RANGE CHECKS
	bool InputManager::IsMouseButtonDown_unsafe(int button, bool previousFrame) const
	{
		if(previousFrame)
			return (m_pOldKeyboardState[button]&0xF0)!=0;
		else
			return (m_pCurrKeyboardState[button]&0xF0)!=0;
	}

	//NO RANGE CHECKS
	bool InputManager::IsGamepadButtonDown_unsafe(WORD button, GamepadIndex playerIndex, bool previousFrame) const
	{
		if(!m_ConnectedGamepads[playerIndex])
			return false;

		if(previousFrame)
			return (m_OldGamepadState[playerIndex].Gamepad.wButtons&button)!=0;
		else
			return (m_CurrGamepadState[playerIndex].Gamepad.wButtons&button)!=0;
	}

	vec2 InputManager::GetThumbstickPosition(bool leftThumbstick, GamepadIndex playerIndex) const
	{
		vec2 pos;
		if(leftThumbstick)
		{
			pos = vec2(m_CurrGamepadState[playerIndex].Gamepad.sThumbLX, m_CurrGamepadState[playerIndex].Gamepad.sThumbLY);

			if(pos.x>-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pos.x<XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)pos.x = 0;
			if(pos.y>-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pos.y<XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)pos.y = 0;
		}
		else
		{
			pos = vec2(m_CurrGamepadState[playerIndex].Gamepad.sThumbRX, m_CurrGamepadState[playerIndex].Gamepad.sThumbRY);

			if(pos.x>-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pos.x<XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)pos.x = 0;
			if(pos.y>-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pos.y<XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)pos.y = 0;
		}

		//Shorts have a range of 32768, so to convert that range to a double, devide it by that range
		if(pos.x<0)pos.x/=32768;
		else pos.x/=32767;

		if(pos.y<0)pos.y/=32768;
		else pos.y/=32767;

		return pos;
	}
	
	float InputManager::GetTriggerPressure(bool leftTrigger, GamepadIndex playerIndex) const
	{
		if(leftTrigger)
		{
			//bLeftTrigger returns a byte, div by 255 to cast to double
			return m_CurrGamepadState[playerIndex].Gamepad.bLeftTrigger/255.0f;
		}
		else
		{
			return m_CurrGamepadState[playerIndex].Gamepad.bRightTrigger/255.0f;
		}
	}

	void InputManager::SetVibration(float leftVibration, float rightVibration, GamepadIndex playerIndex)
	{
		XINPUT_VIBRATION vibration;
		glm::clamp<float>(leftVibration, 0.0f, 1.0f);
		glm::clamp<float>(rightVibration, 0.0f, 1.0f);

		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

		//convert from float to word -> float * lenght of word
		vibration.wLeftMotorSpeed = static_cast<WORD>(leftVibration * 65535);
		vibration.wRightMotorSpeed = static_cast<WORD>(rightVibration * 65535);

		XInputSetState(playerIndex, &vibration);
	}

	#endif
}
