#pragma once

#include "defines.h"
#include "SceneManaging\BaseScene.h"
#include "Logger.h"
#include "Context.h"
#include "SceneGraph/Object.h"
#include "StarComponents.h"
#include "SceneManaging\CollisionManager.h"

namespace star 
{
	class Texture2D;

	class TestScene : public BaseScene
	{
	public:
		TestScene(const tstring& name);
		virtual ~TestScene() {}

		status Initialize(const Context& contex);
		status Update(const Context& context);
		status Draw();

	private:
		int m_TotalFrames;
		int m_FPS;
		float m_PassedMiliseconds;

		Object *m_pObjectOne, *m_pObjectTwo, *m_pObjectThree;
		RectangleColliderComponent *m_pRectColCompOne;
		CircleColliderComponent *m_pCircleColCompOne, *m_pCircleColCompTwo;

		CollisionManager* m_pColMan;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		TestScene(const TestScene& t);
		TestScene& operator=(const TestScene& t);
	};
}
