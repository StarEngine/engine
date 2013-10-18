#pragma once

#include "defines.h"
#include "Scenes/BaseScene.h"
#include "Logger.h"
#include "Context.h"
#include "Objects/Object.h"
#include "StarComponents.h"
#include "Graphics/Shader.h"
#include "Objects/QuadCol.h"
#include "Input/XMLContainer.h"

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
