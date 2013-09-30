#pragma once

#include "defines.h"

namespace star
{
	struct Context;
	class SceneManager;
	class BaseScene;
	class TestScene;
	class TestScene2;

	class MainGame
	{
	public:
		MainGame();
		~MainGame() {}

		status Initialize(int32 windowWidth, int32 windowHeight);
		status Run(const Context& context);
		status End();
	
	private:
		SceneManager* mSceneManager;
		TestScene* mTestScene;
		TestScene2* mTestScene2;
		int32 mWindowWidth,
			  mWindowHeight;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		MainGame(const MainGame& t);
		MainGame(MainGame&& t);
		MainGame& operator=(const MainGame& t);
	};
}
