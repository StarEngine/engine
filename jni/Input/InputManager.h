//----------------------------
//This class will bundle all input information
//In this case that is only 
//Keyboard and gamepad for WIN32. and Touch and keyboard events for ANDROID
//----------------------------
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

//ENUMS AND STRUCTS
	#ifdef _WIN32

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
		InputAction():
			ActionID(-1),
			TriggerState(InputTriggerState::Pressed),
			KeyboardCode(-1),
			MouseButtonCode(-1),
			GamepadButtonCode(0),
			PlayerIndex(GamepadIndex::PlayerOne),
			IsTriggered(false)
		{}

		InputAction(int actionID, InputTriggerState triggerState = InputTriggerState::Pressed, int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = GamepadIndex::PlayerOne):
			ActionID(actionID),
			TriggerState(triggerState),
			KeyboardCode(keyboardCode),
			MouseButtonCode(mouseButtonCode),
			GamepadButtonCode(gamepadButtonCode),
			PlayerIndex(playerIndex),
			IsTriggered(false)
		{}

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
		FingerPointerANDR():
			Position(),
			RawPosition(),
			Pressure(0.0f),
			ToolMajor(0.0f),
			ToolMinor(0.0f),
			ID(0)
		{}

		vec2 Position;
		vec2 RawPosition;
		float Pressure;
		float ToolMajor;
		float ToolMinor;
		int ID;
	};

#endif

	//CLASS
	class InputManager
	{
	public:
		virtual ~InputManager(void);

		// Static methods
		static InputManager* GetInstance();
		static void ResetSingleton();

		void Initialize();
		void Update();
		bool IsFingerTapCP(uint8 finger = 1) const;
		bool IsFingerDownCP(uint8 finger = 1) const;
		bool IsFingerUpCP(uint8 finger = 1) const;
		vec2 GetCurrentFingerPosCP(uint8 finger = 1) const;
		vec2 GetOldFingerPosCP(uint8 finger = 1) const;
		void EndUpdate();
		void SetGestureManager(GestureManager* gestureManager) {m_GestureManager = gestureManager;}
		const GestureManager* GetGestureManager() const {return m_GestureManager;}
#ifdef _WIN32
		
		//[TODO] add InputActions for android
		bool AddInputAction(const InputAction& action);
		bool IsActionTriggered(int actionID) const;
		//[TODO] -- END TODO
		void IsCursorVisible(bool visible) { ShowCursor(visible); }

		vec2 GetThumbstickPosition(bool leftThumbstick = true, GamepadIndex playerIndex = GamepadIndex::PlayerOne) const;
		float GetTriggerPressure(bool leftTrigger = true, GamepadIndex playerIndex = GamepadIndex::PlayerOne) const;
		void SetVibration(float leftVibration, float rightVibration, GamepadIndex playerIndex = GamepadIndex::PlayerOne);
		bool IsGamepadConnected(GamepadIndex index) const { return m_ConnectedGamepads[(DWORD)index]; }
		bool IsGamepadButtonDown(WORD button, GamepadIndex playerIndex = GamepadIndex::PlayerOne, bool previousFrame = false) const;

		vec2 GetCurrentMousePosition() const {return m_CurrMousePosition; }
		vec2 GetOldMousePosition() const {return m_OldMousePosition; }
		vec2 GetMouseMovement() const { return m_MouseMovement; }
		bool IsKeyboardKeyDown(uint8 key, bool previousFrame = false) const;
		bool IsAnyKeyDown() const;

		bool IsMouseButtonDownWIN(uint8 button , bool previousFrame = false) const;
		bool IsMouseButtonTapWIN(uint8 button) const;
		bool IsMouseButtonUpWIN(uint8 button) const;
#else
		bool IsTouchTapANDR(uint8 fingerIndex = 1) const;
		bool IsTouchDownANDR(uint8 fingerIndex = 1) const;
		bool IsTouchUpANDR(uint8 fingerIndex = 1) const;
		vec2 GetCurrentTouchPosANDR(uint8 fingerIndex = 1) const;
		vec2 GetOldTouchPosANDR(uint8 fingerIndex = 1) const;
		FingerPointerANDR GetTouchPropertiesANDR(uint8 fingerIndex = 1) const;

		void OnTouchEvent(AInputEvent* pEvent);
		void OnKeyboardEvent(AInputEvent* pEvent);
#endif

	private:

		//SINGLETON IMPLEMENTATION
		//----------------------------
		InputManager();
		static InputManager*  m_InputManagerPtr;
		//----------------------------
#ifdef _WIN32
		std::map<int,InputAction> m_InputActions;
		BYTE *m_pCurrKeyboardState, *m_pOldKeyboardState, *m_pKeyboardState0, *m_pKeyboardState1;
		bool m_KeyboardState0Active;
		vec2 m_CurrMousePosition, m_OldMousePosition, m_MouseMovement;
		XINPUT_STATE m_OldGamepadState[XUSER_MAX_COUNT], m_CurrGamepadState[XUSER_MAX_COUNT];
		bool m_ConnectedGamepads[XUSER_MAX_COUNT];
		bool m_ThreadAvailable;

		void UpdateGamepadStates();
		bool IsGamepadButtonDown_unsafe(WORD button, GamepadIndex playerIndex = GamepadIndex::PlayerOne, bool previousFrame = false) const;
		bool UpdateKeyboardStates();
		bool IsKeyboardKeyDown_unsafe(uint8 key, bool previousFrame = false) const;
		bool IsMouseButtonDown_unsafe(uint8 button, bool previousFrame = false) const;
		void UpdateWin();
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
		// -------------------------
		// Disabling default copy constructor and default
		// assignment operator.
		// -------------------------
		InputManager(const InputManager& t);
		InputManager& operator=(const InputManager& t);
	};
}

