#pragma once

#ifdef _WIN32
#include <windows.h>
#include <XInput.h>
#include <map>

#pragma comment(lib, "XInput.lib")
#else
#include <vector>
#include <android/input.h>
#include <android_native_app_glue.h>
#endif

#include "../defines.h"
#include "Gestures/GestureManager.h"

namespace star
{
#ifdef DESKTOP

	enum GamepadIndex : byte
	{
		PlayerOne = 0,
		PlayerTwo = 1,
		PlayerThree = 2,
		PlayerFour = 3
	};

	enum InputTriggerState : byte
	{
		Pressed,
		Released,
		Down
	};

//[TODO] - Add for android
	struct InputAction
	{
		InputAction();
		InputAction(int actionID, InputTriggerState triggerState = InputTriggerState::Pressed,
					int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0,
					GamepadIndex playerIndex = GamepadIndex::PlayerOne);

		int ActionID;
		InputTriggerState TriggerState;
		int KeyboardCode; //VK_... (Range 0x07 <> 0xFE)
		int MouseButtonCode; //VK_... (Range 0x00 <> 0x06)
		WORD GamepadButtonCode; //XINPUT_GAMEPAD_...
		GamepadIndex PlayerIndex;
		bool IsTriggered;
	};

#else
	struct FingerPointerANDR
	{
		FingerPointerANDR();

		vec2 Position;
		vec2 RawPosition;
		float Pressure;
		float ToolMajor;
		float ToolMinor;
		int ID;
	};
#endif

	class InputManager
	{
	public:
		virtual ~InputManager(void);

		static InputManager * GetInstance();

		bool IsFingerTapCP(uint8 finger = 0) const;
		bool IsFingerDownCP(uint8 finger = 0) const;
		bool IsFingerUpCP(uint8 finger = 0) const;
		vec2 GetCurrentFingerPosCP(uint8 finger = 0) const;
		vec2 GetOldFingerPosCP(uint8 finger = 0) const;
		void EndUpdate();
		void SetGestureManager(GestureManager* gestureManager);
		const GestureManager* GetGestureManager() const;
#ifdef DESKTOP
		
		//[TODO] add InputActions for android
		bool AddInputAction(const InputAction& action);
		bool IsActionTriggered(int actionID) const;
		//[TODO] -- END TODO
		void IsCursorVisible(bool visible);

		vec2 GetThumbstickPosition(bool leftThumbstick = true, 
			GamepadIndex playerIndex = GamepadIndex::PlayerOne) const;

		float GetTriggerPressure(bool leftTrigger = true, 
			GamepadIndex playerIndex = GamepadIndex::PlayerOne) const;

		void SetVibration(float leftVibration, float rightVibration, 
			GamepadIndex playerIndex = GamepadIndex::PlayerOne);

		bool IsGamepadConnected(GamepadIndex index) const { return m_ConnectedGamepads[(DWORD)index]; }
		bool IsGamepadButtonDown(WORD button, 
			GamepadIndex playerIndex = GamepadIndex::PlayerOne, bool previousFrame = false) const;

		const vec2 & GetCurrentMousePosition() const;
		const vec2 & GetOldMousePosition() const;
		const vec2 & GetMouseMovement() const;
		bool IsKeyboardKeyDown(uint8 key, bool previousFrame = false) const;
		bool IsAnyKeyDown() const;

		bool IsMouseButtonDownWIN(uint8 button , bool previousFrame = false) const;
		bool IsMouseButtonTapWIN(uint8 button) const;
		bool IsMouseButtonUpWIN(uint8 button) const;

		void SetWindowsHandle(const HWND hWnd);
		DWORD UpdateWin();
		void StartKeyboardThread();
		void StopKeyboardThread();

		uint8 ConvertIndexToVK(uint8 fingerIndex) const;
#else
		bool IsTouchTapANDR(uint8 fingerIndex = 0) const;
		bool IsTouchDownANDR(uint8 fingerIndex = 0) const;
		bool IsTouchUpANDR(uint8 fingerIndex = 0) const;
		vec2 GetCurrentTouchPosANDR(uint8 fingerIndex = 0) const;
		vec2 GetOldTouchPosANDR(uint8 fingerIndex = 0) const;
		FingerPointerANDR GetTouchPropertiesANDR(uint8 fingerIndex = 0) const;

		void OnTouchEvent(AInputEvent* pEvent);
		bool OnKeyboardEvent(AInputEvent* pEvent);
#endif

	private:

		InputManager();
		static InputManager*  m_InputManagerPtr;

#ifdef DESKTOP
		static const int NUMBER_OF_KEYBOARDKEYS = 256;
		static const int MIN_KEYBOARD_VALUE = 0x07;
		static const int MAX_KEYBOARD_VALUE = 0xFE;
		static const int MIN_MOUSE_BUTTON_VALUE = 0x00;
		static const int MAX_MOUSE_BUTTON_VALUE = 0x06;
		static const WORD  MIN_GAMEPAD_VALUE = 0x0000;
		static const WORD  MAX_GAMEPAD_VALUE = 0x8000;
		static const int MAX_VALUE_OF_SHORT = 32768;
		static const int MAX_VALUE_OF_WORD = 65535;
		static const float BYTE_TO_DOUBLE_VALUE;

		std::map<int,InputAction> m_InputActions;
		BYTE	m_pCurrKeyboardState[NUMBER_OF_KEYBOARDKEYS],
				m_pOldKeyboardState[NUMBER_OF_KEYBOARDKEYS],
				m_pKeyboardState0[NUMBER_OF_KEYBOARDKEYS],
				m_pKeyboardState1[NUMBER_OF_KEYBOARDKEYS];
		bool m_KeyboardState0Active;
		vec2 m_CurrMousePosition, m_OldMousePosition, m_MouseMovement;
		XINPUT_STATE m_OldGamepadState[XUSER_MAX_COUNT], m_CurrGamepadState[XUSER_MAX_COUNT];
		bool m_ConnectedGamepads[XUSER_MAX_COUNT];
		bool m_ThreadAvailable;
		HWND mWindowsHandle;

		void UpdateGamepadStates();
		bool IsGamepadButtonDown_unsafe(WORD button, 
			GamepadIndex playerIndex = GamepadIndex::PlayerOne, 
			bool previousFrame = false) const;
		bool UpdateKeyboardStates();
		bool IsKeyboardKeyDown_unsafe(uint8 key, bool previousFrame = false) const;
		bool IsMouseButtonDown_unsafe(uint8 button, bool previousFrame = false) const;
#else
		static const int INVALID_POINTER_ID = -1;
		static const float UNDEFINED_POINTER_POSITION;
		bool m_bMainIsDown;
		bool m_bPointerIsDown;
		bool m_bMainIsUp;
		bool m_bPointerIsUp;
		uint8 m_NumberOfPointers;
		uint8 m_NumberOfPointersOLD;
		uint32 m_ActivePointerID;
		std::vector<FingerPointerANDR> m_PointerVec;
		std::vector<FingerPointerANDR> m_OldPointerVec;
#endif
		GestureManager* m_GestureManager;

		InputManager(const InputManager& t);
		InputManager(InputManager&& t);
		InputManager& operator=(const InputManager& t);
	};
}

