#pragma once

#ifdef _WIN32
#include <windows.h>
#include <memory>
#include <XInput.h>
#include <map>

#pragma comment(lib, "XInput9_1_0.lib")
#else
#include <vector>
#include <android/input.h>
#include <android_native_app_glue.h>
#include <functional>
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
		InputAction(int32 actionID, InputTriggerState triggerState = InputTriggerState::Pressed,
					int32 keyboardCode = -1, int32 mouseButtonCode = -1, WORD gamepadButtonCode = 0,
					GamepadIndex playerIndex = GamepadIndex::PlayerOne);

		int32 ActionID;
		InputTriggerState TriggerState;
		int32 KeyboardCode; //VK_... (Range 0x07 <> 0xFE)
		int32 MouseButtonCode; //VK_... (Range 0x00 <> 0x06)
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
		float32 Pressure;
		float32 ToolMajor;
		float32 ToolMinor;
		int32 ID;
	};

	typedef std::function<void()> CallBack;
#endif

	class InputManager
	{
	public:
		virtual ~InputManager(void);

		static InputManager * GetInstance();

		void UpdateGestures(const Context & context);

		bool IsFingerPressedCP(uint8 finger = 0) const;
		bool IsFingerDownCP(uint8 finger = 0) const;
		bool IsFingerReleasedCP(uint8 finger = 0) const;
		vec2 GetCurrentFingerPosCP(uint8 finger = 0);
		vec2 GetOldFingerPosCP(uint8 finger = 0);
		void EndUpdate();

		void SetGestureManager(std::shared_ptr<GestureManager> gestureManager);
		std::shared_ptr<GestureManager> GetGestureManager() const;

		void AddGlobalGesture(BaseGesture* gesture);
		void AddGlobalGesture(BaseGesture* gesture, const tstring & name);
		void RemoveGlobalGesture(BaseGesture* gesture);
		void RemoveGlobalGesture(const tstring & name);

		template <typename T>
		T * GetGlobalGesture(const tstring & name) const;
#ifdef DESKTOP
		
		//[TODO] add InputActions for android
		bool AddInputAction(const InputAction& action);
		bool IsActionTriggered(int32 actionID) const;
		//[TODO] -- END TODO
		void IsCursorVisible(bool visible);

		vec2 GetThumbstickPosition(bool leftThumbstick = true, 
			GamepadIndex playerIndex = GamepadIndex::PlayerOne) const;

		float32 GetTriggerPressure(bool leftTrigger = true, 
			GamepadIndex playerIndex = GamepadIndex::PlayerOne) const;

		void SetVibration(float32 leftVibration, float32 rightVibration, 
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
		bool IsMouseButtonPressedWIN(uint8 button) const;
		bool IsMouseButtonReleasedWIN(uint8 button) const;

		void SetWindowsHandle(const HWND hWnd);
		DWORD UpdateWin();
		void StartKeyboardThread();
		void StopKeyboardThread();

		uint8 ConvertIndexToVK(uint8 fingerIndex) const;
#else
		bool IsTouchPressedANDR(uint8 fingerIndex = 0) const;
		bool IsTouchDownANDR(uint8 fingerIndex = 0) const;
		bool IsTouchReleasedANDR(uint8 fingerIndex = 0) const;
		vec2 GetCurrentTouchPosANDR(uint8 fingerIndex = 1);
		vec2 GetOldTouchPosANDR(uint8 fingerIndex = 1);
		FingerPointerANDR GetTouchPropertiesANDR(uint8 fingerIndex = 0) const;

		void OnTouchEvent(AInputEvent* pEvent);
		bool OnKeyboardEvent(AInputEvent* pEvent);

		void SetOnBackButtonCallback(CallBack callback);
		void SetOnMenuButtonCallback(CallBack callback);
#endif

	private:

		InputManager();
		static InputManager*  m_InputManagerPtr;

#ifdef DESKTOP
		static const int32 NUMBER_OF_KEYBOARDKEYS = 256;
		static const int32 MIN_KEYBOARD_VALUE = 0x07;
		static const int32 MAX_KEYBOARD_VALUE = 0xFE;
		static const int32 MIN_MOUSE_BUTTON_VALUE = 0x00;
		static const int32 MAX_MOUSE_BUTTON_VALUE = 0x06;
		static const WORD  MIN_GAMEPAD_VALUE = 0x0000;
		static const WORD  MAX_GAMEPAD_VALUE = 0x8000;
		static const int32 MAX_VALUE_OF_SHORT = 32768;
		static const int32 MAX_VALUE_OF_WORD = 65535;
		static const float32 BYTE_TO_DOUBLE_VALUE;

		std::map<int32,InputAction> m_InputActions;
		BYTE	m_pCurrKeyboardState[NUMBER_OF_KEYBOARDKEYS],
				m_pOldKeyboardState[NUMBER_OF_KEYBOARDKEYS],
				m_pKeyboardState0[NUMBER_OF_KEYBOARDKEYS],
				m_pKeyboardState1[NUMBER_OF_KEYBOARDKEYS];
		bool m_KeyboardState0Active;
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
		static const int32 INVALID_POINTER_ID = -1;
		static const float32 UNDEFINED_POINTER_POSITION;
		bool m_bMainIsDown;
		bool m_bPointerIsDown;
		bool m_bMainIsUp;
		bool m_bPointerIsUp;
		uint8 m_NumberOfPointers;
		uint8 m_NumberOfPointersOLD;
		uint32 m_ActivePointerID;
		std::vector<FingerPointerANDR> m_PointerVec;
		std::vector<FingerPointerANDR> m_OldPointerVec;
		CallBack m_OnBackButtonDown;
		CallBack m_OnMenuButtonDown;
#endif
		vec2 m_CurrMousePosition, m_OldMousePosition, m_MouseMovement;
		std::shared_ptr<GestureManager> m_GestureManager;
		GestureManager* m_IndependantGestureManager;
		uint32 m_GestureID;

		InputManager(const InputManager& t);
		InputManager(InputManager&& t);
		InputManager& operator=(const InputManager& t);
		InputManager& operator=(InputManager&& t);
	};
}

#include "InputManager.inl"
