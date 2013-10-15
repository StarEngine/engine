#pragma once

#include "../../StarEngine/jni/defines.h"
#include "../../StarEngine/jni/Scenes/BaseScene.h"
#include "../../StarEngine/jni/Logger.h"
#include "../../StarEngine/jni/Context.h"
#include "../../StarEngine/jni/Objects/Object.h"
#include "../../StarEngine/jni/StarComponents.h"
#include "../../StarEngine/jni/Input/Gestures/DoubleTapGesture.h"
#include "../../StarEngine/jni/Objects/FreeCamera.h"

class TestScene : public star::BaseScene
{
public:
	TestScene(const tstring& name);
	virtual ~TestScene();

	status Initialize(const star::Context& context);
	status Update(const star::Context& context);
	status Draw();

private:
	star::DoubleTapGesture* m_TapGesture;
	int m_TotalFrames;
	int m_Step;
	int m_FPS;
	float m_PassedMiliseconds;

	float mRed, mGreen, mBlue;

	star::Object	*m_pObjectOne, 
					*m_pObjectTwo;

	star::FreeCamera *m_pActiveCamera;

	star::RectangleColliderComponent* m_pRectCompOne, *m_pRectCompTwo;
	star::CircleColliderComponent *m_pCircleCompOne, *m_pCircleCompTwo;

	star::SpriteComponent *m_pSpriteComp1,
						  *m_pSpriteComp2;

	float m_Angle, m_Scale, m_ScaleSign;
	int m_XPos;

	static const vec3 NO_PATH_AVAILBLE;
		
	TestScene(const TestScene& t);
	TestScene(TestScene&& t);
	TestScene& operator=(const TestScene& t);
};
