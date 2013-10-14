#include "TestScene.h"
#include "../../StarEngine/jni/Helpers/Helpers.h"
#include "../../StarEngine/jni/SceneManaging/CollisionManager.h"
#include "../../StarEngine/jni/SceneManaging/PathFindManager.h"
#include "../../StarEngine/jni/StarComponents.h"
#include "../../StarEngine/jni/Input/InputManager.h"
#include "../../StarEngine/jni/GraphicsManager.h"
#include "../../StarEngine/jni/SceneManaging/SceneManager.h"
#include "../../StarEngine/jni/Sound/SoundService.h"

#ifdef _WIN32
#include <glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#define INPUT_MANAGER (star::InputManager::GetInstance())
#define LOGGER (star::Logger::GetInstance())

const vec3 TestScene::NO_PATH_AVAILBLE = vec3(-123456.0f, -123456.0f, -123456.0f);

TestScene::TestScene(const tstring & Name):
	BaseScene(Name),
	m_TotalFrames(0),
	m_FPS(0),
	m_Step(0),
	m_PassedMiliseconds(0),
	mRed(1.0),
	mGreen(0),
	mBlue(0),
	m_pObjectOne(nullptr),
	m_pObjectTwo(nullptr),
	m_pRectCompOne(nullptr),
	m_pRectCompTwo(nullptr),
	m_pSpriteComp1(nullptr),
	m_TapGesture(nullptr),
	m_pActiveCamera(nullptr),
	m_Angle(0),
	m_Scale(1),
	m_ScaleSign(1),
	m_XPos(0)
{
		
}

TestScene::~TestScene()
{
	m_GestureManagerPtr->RemoveGesture(m_TapGesture);
}

status TestScene::Initialize( const star::Context& context)
{

	m_TapGesture = new star::DoubleTapGesture();
	m_GestureManagerPtr->AddGesture(m_TapGesture);

	m_pObjectOne = new star::Object();
	m_pRectCompOne = new star::RectangleColliderComponent(200,215);
	m_pSpriteComp1 = new star::SpriteComponent(_T("pikachu.png"),_T("Pikachu"));
	m_pObjectOne->AddComponent(m_pRectCompOne);
	m_pObjectOne->AddComponent(m_pSpriteComp1);

	m_pObjectOne->GetTransform()->Rotate(m_Angle);

	m_pObjectTwo = new star::Object();
	m_pRectCompTwo = new star::RectangleColliderComponent(200,215);
	m_pSpriteComp2 = new star::SpriteComponent(_T("Pikachu.png"),_T("Awesome"));
	m_pObjectTwo->AddComponent(m_pRectCompTwo);
	m_pObjectTwo->AddComponent(m_pSpriteComp2);
	m_pObjectTwo->GetTransform()->Translate(400,0);

	m_pActiveCamera = new star::FreeCamera();
	AddObject(m_pActiveCamera);

	star::CollisionManager::GetInstance()->AddObject(m_pObjectOne);
	star::CollisionManager::GetInstance()->AddObject(m_pObjectTwo);
	
	star::SoundService::GetInstance()->LoadMusic(_T("Sounds/StereoTest.mp3"),_T("Stereo"));
	star::SoundService::GetInstance()->AddToBackgroundQueue(_T("Stereo"));

	star::SoundService::GetInstance()->LoadMusic(_T("Sounds/Silly.mp3"),_T("Silly"));
	star::SoundService::GetInstance()->AddToBackgroundQueue(_T("Silly"));

	star::SoundService::GetInstance()->LoadSoundEffect(_T("Sounds/Explosion.wav"),_T("Explosion"));

	star::SoundService::GetInstance()->LoadSoundEffect(_T("Sounds/Electric.wav"),_T("Electric"));

	AddObject(m_pObjectOne);
	AddObject(m_pObjectTwo); 

	return STATUS_OK;
	}

	status TestScene::Update(const star::Context& context)
	{
		
		if(!m_pActiveCamera->GetComponent<star::CameraComponent>()->IsActive())
		{
			m_pActiveCamera->GetComponent<star::CameraComponent>()->SetActive();
		}

		if(m_TapGesture->CompletedGesture())
		{
			LOGGER->Log(star::LogLevel::Info, _T("Tapped!"));
			star::SoundService::GetInstance()->PlayBackgroundQueue();
		}
		

		if(INPUT_MANAGER->IsFingerTapCP(1))
		{
			star::SoundService::GetInstance()->PlaySoundEffect(_T("Explosion"));
		}
		if(INPUT_MANAGER->IsFingerTapCP(2))
		{
			star::SoundService::GetInstance()->PlaySoundEffect(_T("Electric"));
		}

	++m_TotalFrames;
	m_PassedMiliseconds += float(context.mTimeManager->GetMicroSeconds());
	if(m_PassedMiliseconds >= 1000000)
	{
		m_FPS = m_TotalFrames;
		m_TotalFrames = 0;
		m_PassedMiliseconds -= 1000000;
	}

	star::PathFindManager::GetInstance()->
		FindPath(m_pObjectOne->GetTransform()->GetWorldPosition(), vec2(3,2));

	auto pos = INPUT_MANAGER->GetCurrentFingerPosCP();
	if(pos.y>(star::GraphicsManager::GetInstance()->GetWindowHeight()/2) && 
		pos.y< star::GraphicsManager::GetInstance()->GetWindowHeight())
	{
		star::SceneManager::GetInstance()->SetActiveScene(_T("TestScene2"));
	}

	m_Angle += static_cast<float>(context.mTimeManager->GetSeconds());
	m_pObjectTwo->GetTransform()->Rotate(m_Angle);
	
	//[COMMENT] need better way of collision... this is really really bad -_-
	//if(star::CollisionManager::GetInstance()->CheckCollision(_T("Default")) == true);
	//{
	//	m_ScaleSign *= -1;
	//}

	m_Scale += m_ScaleSign * static_cast<float>(context.mTimeManager->GetSeconds());
	m_pObjectOne->GetTransform()->Scale(m_Scale, m_Scale);

	m_XPos += static_cast<int>(m_ScaleSign * 300 * context.mTimeManager->GetSeconds());
	m_pObjectOne->GetTransform()->Translate(static_cast<float>(m_XPos), 0);

	return STATUS_OK;
}

status TestScene::Draw()
{
	return STATUS_OK;
}
