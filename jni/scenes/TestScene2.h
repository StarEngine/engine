#pragma once

#include "../../StarEngine/jni/defines.h"
#include "../../StarEngine/jni/SceneManaging/BaseScene.h"
#include "../../StarEngine/jni/Logger.h"
#include "../../StarEngine/jni/Context.h"
#include "../../StarEngine/jni/SceneGraph/Object.h"
#include "../../StarEngine/jni/StarComponents.h"
#include "../../StarEngine/jni/Shaders/Shader.h"
#include "../../StarEngine/jni/Objects/QuadCol.h"
#include "../../StarEngine/jni/Input/XMLContainer.h"

class TestScene2 : public star::BaseScene
{
public:
	TestScene2(const tstring& name);
	virtual ~TestScene2();

	status Initialize(const star::Context& context);
	status Update(const star::Context& context);
	status Draw();

private:
	int m_TotalFrames;
	int m_Step;
	int m_FPS;
	int m_CurrentAnimation;
	float m_PassedMiliseconds;
	star::XMLContainer mTestXMLFile;

	star::Object	*m_pObjectOne, 
					*m_pObjectTwo, 
					*m_pObjectThree,
					*m_pObjectFour, 
					*m_pObjectFive, 
					*m_pObjectSix,
					*m_pSpriteObject;

	star::RectangleColliderComponent* m_pRectCompOne;
	star::CircleColliderComponent *m_pRectCompTwo;

	star::PathFindNodeComponent	*m_pPathFindComp, 
								*m_pPathFindCompTwo, 
								*m_pPathFindCompThree, 
								*m_pPathFindCompFour, 
								*m_pPathFindCompFive, 
								*m_pPathFindCompSix;

	star::SpriteComponent * m_pSpriteComp1;
		
	TestScene2(const TestScene2& t);
	TestScene2(TestScene2&& t);
	TestScene2& operator=(const TestScene2& t);
};
