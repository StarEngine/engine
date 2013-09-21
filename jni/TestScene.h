/*
 * TestScene.h
 *
 *  Created on: 19-sep.-2013
 *      Author: Simon Vanhauwaert
 */

#ifndef _TEST_SCENE
#define _TEST_SCENE

#include "defines.h"
#include "SceneManaging/BaseScene.h"
#include "Logger.h"

class TestScene : public star::BaseScene
{
public:

	TestScene(tstring Name);
	virtual ~TestScene(){}

	status Update();
	status Draw();

private:

};


#endif
