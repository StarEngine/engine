#include "TestScene.h"
#include "../../StarEngine/jni/Helpers/Helpers.h"
#include "../../StarEngine/jni/SceneManaging/CollisionManager.h"
#include "../../StarEngine/jni/SceneManaging/PathFindManager.h"
#include "../../StarEngine/jni/Input/InputManager.h"
#include "../../StarEngine/jni/GraphicsManager.h"
#include "../../StarEngine/jni/SceneManaging/SceneManager.h"
#include "../../StarEngine/jni/Helpers/Filepath.h"
#include "../../StarEngine/jni/Sound/SoundService.h"

#ifdef _WIN32
#include <glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#define INPUT_MANAGER (star::InputManager::GetInstance())
#define LOGGER (star::Logger::GetInstance())

TestScene::TestScene(const tstring & Name):
	BaseScene(Name),
	m_TotalFrames(0),
	m_FPS(0),
	m_Step(0),
	m_PassedMiliseconds(0),
	mRed(1.0),
	mGreen(0),
	mBlue(0),
	m_pTestSprite(nullptr),
	m_pObjectOne(nullptr),
	m_pObjectTwo(nullptr),
	m_pObjectThree(nullptr),
	m_pObjectFour(nullptr),
	m_pObjectFive(nullptr),
	m_pObjectSix(nullptr),
	m_pRectCompOne(nullptr),
	m_pRectCompTwo(nullptr),
	m_pPathFindComp(nullptr),
	m_pPathFindCompTwo(nullptr),
	m_pPathFindCompThree(nullptr), 
	m_pPathFindCompFour(nullptr),
	m_pPathFindCompFive(nullptr),
	m_pPathFindCompSix(nullptr),
	m_TapGesture(nullptr)
{
		
}

status TestScene::Initialize( const star::Context& context)
{

	m_TapGesture = new star::TapGesture();
	m_GestureManagerPtr->AddGesture(m_TapGesture);

	star::Filepath tex1path(_T(""),_T("Awesome.png"));
	m_pTestSprite = new star::Sprite(tex1path.GetFullPath(),_T("Awesome"));

	m_pObjectOne = new star::Object();
	m_pRectCompOne = new star::RectangleColliderComponent(10,10);
	m_pPathFindComp = new star::PathFindNodeComponent();
	m_pObjectOne->AddComponent(m_pRectCompOne);
	m_pObjectOne->AddComponent(m_pPathFindComp);

	m_pObjectTwo = new star::Object();
	m_pRectCompTwo = new star::CircleColliderComponent(10);
	m_pPathFindCompTwo = new star::PathFindNodeComponent();
	m_pObjectTwo->AddComponent(m_pRectCompTwo);
	m_pObjectTwo->AddComponent(m_pPathFindCompTwo);
	m_pObjectTwo->GetComponent<star::TransformComponent>()->Translate(1,0,0);
		
	m_pObjectThree = new star::Object();
	m_pPathFindCompThree = new star::PathFindNodeComponent();
	m_pObjectThree->AddComponent(m_pPathFindCompThree);
	m_pObjectThree->GetComponent<star::TransformComponent>()->Translate(1,1,0);

	m_pObjectFour = new star::Object();
	m_pPathFindCompFour = new star::PathFindNodeComponent();
	m_pObjectFour->AddComponent(m_pPathFindCompFour);
	m_pObjectFour->GetComponent<star::TransformComponent>()->Translate(2,1,0);

	m_pObjectFive = new star::Object();
	m_pPathFindCompFive = new star::PathFindNodeComponent();
	m_pObjectFive->AddComponent(m_pPathFindCompFive);
	m_pObjectFive->GetComponent<star::TransformComponent>()->Translate(3,1,0);

	m_pObjectSix = new star::Object();
	m_pPathFindCompSix = new star::PathFindNodeComponent();
	m_pObjectSix->AddComponent(m_pPathFindCompSix);
	m_pObjectSix->GetComponent<star::TransformComponent>()->Translate(3,2,0);

	star::CollisionManager::GetInstance()->AddObject(m_pObjectOne);
	star::CollisionManager::GetInstance()->AddObject(m_pObjectTwo);

	star::CollisionManager::GetInstance()->CheckCollision(_T("Default"));

	star::Filepath soundspath(_T("Sounds/"),_T("StereoTest.mp3"));
	star::SoundService::GetInstance()->LoadMusic(soundspath.GetFullPath(),_T("Stereo"));
	star::SoundService::GetInstance()->AddToBackgroundQueue(_T("Stereo"));

	star::Filepath soundspath2(_T("Sounds/"),_T("Silly.mp3"));
	star::SoundService::GetInstance()->LoadMusic(soundspath2.GetFullPath(),_T("Silly"));
	star::SoundService::GetInstance()->AddToBackgroundQueue(_T("Silly"));

	star::Filepath effectpath(_T("Sounds/"),_T("Explosion.wav"));
	star::SoundService::GetInstance()->LoadSoundEffect(effectpath.GetFullPath(),_T("Explosion"));

	star::Filepath effectpath2(_T("Sounds/"),_T("Electric.wav"));
	star::SoundService::GetInstance()->LoadSoundEffect(effectpath2.GetFullPath(),_T("Electric"));
	return STATUS_OK;
	}

	status TestScene::Update(const star::Context& context)
	{
		if(m_TapGesture->CompletedGesture())
		{
			LOGGER->Log(star::LogLevel::Info, _T("Tapped!"));
			star::SoundService::GetInstance()->PlayBackgroundQueue();
			
		}
		auto pos = INPUT_MANAGER->GetCurrentFingerPosCP();

		if(INPUT_MANAGER->IsFingerTapCP(1))
		{
			star::SoundService::GetInstance()->PlaySoundEffect(_T("Explosion"));
		}
		if(INPUT_MANAGER->IsFingerTapCP(2))
		{
			star::SoundService::GetInstance()->PlaySoundEffect(_T("Electric"));
		}
		//tstringstream posBuffer;
		//posBuffer << _T("Current Mouse Pos: ( ") << pos.x << _T(" , ") << pos.y << _T(" )");
		//LOGGER->Log(LogLevel::Warning, posBuffer.str());

	++m_TotalFrames;
	m_PassedMiliseconds += float(context.mTimeManager->GetMicroSeconds());
	if(m_PassedMiliseconds >= 1000000)
	{
		m_FPS = m_TotalFrames;
		m_TotalFrames = 0;
		m_PassedMiliseconds -= 1000000;

		tstringstream str;
		str << "FPS: " << m_FPS;
		//LOGGER->Log(LogLevel::Info, str.str());

		m_pObjectOne->GetComponent<star::TransformComponent>()->Translate(star::PathFindManager::GetInstance()->GetStep(m_Step));
		vec3 pos = m_pObjectOne->GetComponent<star::TransformComponent>()->GetWorldPosition();
		//tstringstream tstr;
		//tstr << _T("PlayerPos : (") << pos.x << _T(", ") << pos.y << _T(")");
		//LOGGER->Log(LogLevel::Info, tstr.str());
		++m_Step;
	}
	star::PathFindManager::GetInstance()->FindPath(m_pObjectOne->GetComponent<star::TransformComponent>()->GetWorldPosition(), vec3(3,2,0));

	if(pos.y>(star::GraphicsManager::GetInstance()->GetScreenHeight()/2) && pos.y< star::GraphicsManager::GetInstance()->GetScreenHeight())
	{
		star::SceneManager::GetInstance()->SetActiveScene(_T("TestScene2"));
	}

	if(mRed>=1.0 && mGreen <1.0 && mBlue <1.0)
	{
		mGreen += static_cast<float>(context.mTimeManager->GetSeconds());
	}
	if(mGreen>=1.0 && mRed > 0 && mBlue <1.0)
	{
		mRed -= static_cast<float>(context.mTimeManager->GetSeconds());
	}
	if(mGreen>=1.0 && mRed<=0.0 && mBlue<1.0)
	{
		mBlue += static_cast<float>(context.mTimeManager->GetSeconds());
	}
	if(mBlue>=1.0 && mGreen>0 && mRed <1.0)
	{
		mGreen -= static_cast<float>(context.mTimeManager->GetSeconds());
	}
	if(mBlue >=1.0 && mGreen<=0.0 && mRed <1.0)
	{
		mRed += static_cast<float>(context.mTimeManager->GetSeconds());
	}
	if(mRed >=1.0 && mBlue >0 && mGreen <1.0)
	{
		mBlue -= static_cast<float>(context.mTimeManager->GetSeconds());
	}

	return STATUS_OK;
}

status TestScene::Draw()
{
	glClearColor(mRed,mGreen,mBlue, 1.0f); // Clear the background of our window to red

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	glViewport(0,0, 1920, 1080);

	m_pTestSprite->Draw();

	return STATUS_OK;
}
