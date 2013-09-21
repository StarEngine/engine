/*
 * TestScene.h
 *
 *  Created on: 19-sep.-2013
 *      Author: Simon Vanhauwaert
 */

#ifndef _MAIN_GAME_
#define _MAIN_GAME_

#include "defines.h"
#include "SceneManaging/SceneManager.h"
#include "SceneManaging/BaseScene.h"
#include "TestScene.h"

class MainGame
{
public:

	MainGame();
	virtual ~MainGame(){}

	status Initialize();
	status Run();
	status End();
	

private:
	star::SceneManager* mSceneManager;
	TestScene* mTestScene;

};


#endif
