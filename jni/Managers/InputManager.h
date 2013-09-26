//----------------------------
//This class will bundle all input information
//In this case that is only 
//Keyboard and gamepad.
//Heavily based on the input manager from the overlord engine.
//----------------------------

#pragma once
#ifdef _WIN32
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "XInput.lib")
#else
#include <android/input.h>
#include <android_native_app_glue.h>
#endif



//----------------------------
//Include files
//----------------------------

#include <map>
#include "../defines.h"

namespace star
{
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


	struct InputAction
	{
		InputAction():
			ActionID(-1),
			TriggerState(InputTriggerState::Pressed),
			KeyboardCode(-1),
			MouseButtonCode(-1),
			GamepadButtonCode(0),
			PlayerIndex(GamepadIndex::PlayerOne),
			IsTriggered(false){}

		InputAction(int actionID, InputTriggerState triggerState = InputTriggerState::Pressed, int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = GamepadIndex::PlayerOne):
			ActionID(actionID),
			TriggerState(triggerState),
			KeyboardCode(keyboardCode),
			MouseButtonCode(mouseButtonCode),
			GamepadButtonCode(gamepadButtonCode),
			PlayerIndex(playerIndex),
			IsTriggered(false){}

		int ActionID;
		InputTriggerState TriggerState;
		int KeyboardCode; //VK_... (Range 0x07 <> 0xFE)
		int MouseButtonCode; //VK_... (Range 0x00 <> 0x06)
		WORD GamepadButtonCode; //XINPUT_GAMEPAD_...
		GamepadIndex PlayerIndex;
		bool IsTriggered;
	};

	#endif

	class InputManager
	{
	public:
		virtual ~InputManager(void);

		// Static methods
		static InputManager*  GetSingleton();
		static void ResetSingleton();

#ifdef _WIN32
		void Initialize();
#else
		void InitializeAndroid(android_app* pApplication, const int32& pWidth, const int32& pHeight);
		float getHorizontal() const {return m_Horizontal;}
		float getVertical() const {return m_Vertical;}
		void SetRefPoint(Location* pTouchReference);

		bool OnTouchEvent(AInputEvent* pEvent);
		bool OnKeyboardEvent(AInputEvent* pEvent);
#endif
		void Update(double deltaTime);

		//[TODO] add this for android
	#ifdef _WIN32
		bool AddInputAction(const InputAction& action);
		bool IsActionTriggered(int actionID) const;
	#endif

		//Can't be done for android
	#ifdef _WIN32
		void IsCursorVisible(bool visible) { ShowCursor(visible); }
	#endif


		//XINPUT -- WINDOWS ONLY
	#ifdef _WIN32
		vec2 GetThumbstickPosition(bool leftThumbstick = true, GamepadIndex playerIndex = GamepadIndex::PlayerOne) const;
		float GetTriggerPressure(bool leftTrigger = true, GamepadIndex playerIndex = GamepadIndex::PlayerOne) const;
		void SetVibration(float leftVibration, float rightVibration, GamepadIndex playerIndex = GamepadIndex::PlayerOne);
		bool IsGamepadConnected(GamepadIndex index) const { return m_ConnectedGamepads[(DWORD)index]; }
		bool IsGamepadButtonDown(WORD button, GamepadIndex playerIndex = GamepadIndex::PlayerOne, bool previousFrame = false) const;
	#endif

		//[TODO] make these switchable for android (touch)
	#ifdef _WIN32
		POINT GetMousePosition(bool previousFrame = false) const {return (previousFrame)?m_OldMousePosition:m_CurrMousePosition; }
		POINT GetMouseMovement() const { return m_MouseMovement; }
		bool IsKeyboardKeyDown(int key, bool previousFrame = false) const;
		bool IsMouseButtonDown(int button, bool previousFrame = false) const;
		bool IsAnyKeyDown() const;
	#endif

	private:

		//SINGLETON IMPLEMENTATION
		//----------------------------
		InputManager();
		static InputManager*  m_InputManagerPtr;
		//----------------------------


	#ifdef _WIN32
		std::map<int,InputAction> m_InputActions;


		static BYTE *m_pCurrKeyboardState, *m_pOldKeyboardState, *m_pKeyboardState0, *m_pKeyboardState1;
		static bool m_KeyboardState0Active;
		static POINT m_CurrMousePosition, m_OldMousePosition, m_MouseMovement;

		static XINPUT_STATE m_OldGamepadState[XUSER_MAX_COUNT], m_CurrGamepadState[XUSER_MAX_COUNT];
		static bool m_ConnectedGamepads[XUSER_MAX_COUNT];
		void UpdateGamepadStates();
		bool IsGamepadButtonDown_unsafe(WORD button, GamepadIndex playerIndex = GamepadIndex::PlayerOne, bool previousFrame = false) const;
	#endif
	

		//WIN only
	#ifdef _WIN32
		bool UpdateKeyboardStates();
		bool IsKeyboardKeyDown_unsafe(int key, bool previousFrame = false) const;
		bool IsMouseButtonDown_unsafe(int button, bool previousFrame = false) const;
	#else
		android_app* mApplication;

		float m_Horizontal, m_Vertical;

		vec2 m_RefPoint;
		const int32& m_Width, m_Height;
	#endif
	
		// -------------------------
		// Disabling default copy constructor and default
		// assignment operator.
		// -------------------------
		InputManager(const InputManager& t);
		InputManager& operator=(const InputManager& t);
	};
}
