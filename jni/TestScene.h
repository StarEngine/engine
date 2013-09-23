/*
 * TestScene.h
 *
 *  Created on: 19-sep.-2013
 *      Author: Simon Vanhauwaert
 */

#ifndef _TEST_SCENE
#define _TEST_SCENE

#include "defines.h"
#include "Context.h"
#include "Logger.h"
#include "SceneManaging\BaseScene.h"
#include "SceneGraph\Object.h"
#include "StarComponents.h"

class TestScene : public star::BaseScene
{
public:

	TestScene(tstring Name);
	virtual ~TestScene(){}

	status Update(star::Context& context);
	status Draw();

private:
	int m_TotalFrames;
	int m_FPS;
	float m_PassedMiliseconds;

	Object* m_pTestObject;
	RectangleColliderComponent* mRectCompPtr;
};


#endif
