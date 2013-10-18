#include "TestScene2.h"
#include "Helpers/Helpers.h"
#include "Physics/Collision/CollisionManager.h"
#include "AI/Pathfinding/PathFindManager.h"
#include "Input/InputManager.h"
#include "Graphics/GraphicsManager.h"
#include "Scenes/SceneManager.h"
#include "Input/XMLFileParser.h"
#include "Input/XMLFileSerializer.h"
#include "Graphics/SpriteAnimationManager.h"
#include "Components/Graphics/SpritesheetComponent.h"
#include "Components/TransformComponent.h"
#include "Graphics/ScaleSystem.h"

#ifdef DESKTOP
#include <glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#define INPUT_MANAGER (star::InputManager::GetInstance())
#define LOGGER (star::Logger::GetInstance())

TestScene2::TestScene2(const tstring & Name):
	BaseScene(Name),
	m_TotalFrames(0),
	m_FPS(0),
	m_Step(0),
	m_CurrentAnimation(0),
	m_PassedMiliseconds(0),
	m_pObjectOne(nullptr),
	m_pObjectTwo(nullptr),
	m_pObjectThree(nullptr),
	m_pObjectFour(nullptr),
	m_pObjectFive(nullptr),
	m_pObjectSix(nullptr),
	m_pSpriteObject(nullptr),
	m_pRectCompOne(nullptr),
	m_pRectCompTwo(nullptr),
	m_pPathFindComp(nullptr),
	m_pPathFindCompTwo(nullptr),
	m_pPathFindCompThree(nullptr), 
	m_pPathFindCompFour(nullptr),
	m_pPathFindCompFive(nullptr),
	m_pPathFindCompSix(nullptr),
	m_pSpriteComp1(nullptr),
	mTestXMLFile()
{
		
}

TestScene2::~TestScene2()
{
}

status TestScene2::CreateObjects()
{
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
	m_pObjectTwo->GetTransform()->Translate(1,0);
		
	m_pObjectThree = new star::Object();
	m_pPathFindCompThree = new star::PathFindNodeComponent();
	m_pObjectThree->AddComponent(m_pPathFindCompThree);
	m_pObjectThree->GetTransform()->Translate(1,1);
	
	m_pObjectFour = new star::Object();
	m_pPathFindCompFour = new star::PathFindNodeComponent();
	m_pObjectFour->AddComponent(m_pPathFindCompFour);
	m_pObjectFour->GetTransform()->Translate(2,1);

	m_pObjectFive = new star::Object();
	m_pPathFindCompFive = new star::PathFindNodeComponent();
	m_pObjectFive->AddComponent(m_pPathFindCompFive);
	m_pObjectFive->GetTransform()->Translate(3,1);

	m_pObjectSix = new star::Object();
	m_pPathFindCompSix = new star::PathFindNodeComponent();
	m_pObjectSix->AddComponent(m_pPathFindCompSix);
	m_pObjectSix->GetTransform()->Translate(3,2);
	
	AddObject(m_pObjectOne);
	AddObject(m_pObjectTwo);
	AddObject(m_pObjectThree);
	AddObject(m_pObjectFour);
	AddObject(m_pObjectFive);
	AddObject(m_pObjectSix); 
	
	star::CollisionManager::GetInstance()->AddObject(m_pObjectOne);
	star::CollisionManager::GetInstance()->AddObject(m_pObjectTwo);

	//CollisionManager::GetInstance()->CheckCollision(_T("Default"));
	
	star::XMLFileParser parser(_T("book_catalog.xml"));
	LOGGER->Log(star::LogLevel::Info,_T("Loading XML File..."));
	parser.Read(mTestXMLFile);
	LOGGER->Log(star::LogLevel::Info,_T("Book #1 ID:"));
	LOGGER->Log(star::LogLevel::Info,mTestXMLFile[_T("book")]->GetAttributes()[_T("id")]);
	star::XMLFileSerializer serializer(_T("book_catalog_v2.xml"));
	mTestXMLFile[_T("book")]->GetAttributes()[_T("id")] = _T("bki10092");
	LOGGER->Log(star::LogLevel::Info,_T("Writing XML File..."));
	serializer.Write(mTestXMLFile);
	LOGGER->Log(star::LogLevel::Info,_T("Writing Done!"));
	
	star::SpriteAnimationManager::GetInstance()->AddSpritesheet(_T("RPGCharacterSpritesheet.xml"));
	
	m_pSpriteObject = new star::Object();
	auto sprComponent = new star::SpritesheetComponent(_T("MainGuySpriteSheet_0.png"),_T("MainGuySpritesheet"), _T("RPGCharacter"));
	m_pSpriteObject->AddComponent(sprComponent);
	m_pSpriteObject->GetTransform()->Scale(10,10);
	
	AddObject(m_pSpriteObject);
	
	return STATUS_OK;
	
}

status TestScene2::AfterInitializedObjects(const star::Context& context)
{
	m_pSpriteObject->GetTransform()->Translate(star::ScaleSystem::GetInstance()->GetWorkingResolution().x /2- (m_pSpriteObject->GetComponent<star::SpritesheetComponent>()->GetWidth()/2),100);
	return STATUS_OK;
}

status TestScene2::Update(const star::Context& context)
{
	
	auto pos = INPUT_MANAGER->GetCurrentFingerPosCP();
	//tstringstream posBuffer;
	//posBuffer << _T("Current Mouse Pos: ( ") << pos.x << _T(" , ") << pos.y << _T(" )");
	//LOGGER->Log(LogLevel::Warning, posBuffer.str());

	//ASSERT(false, _T("Assert Test."));

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
		//[TODO] % --> This function should return in % probably
		/*
		m_pObjectOne->GetComponent<star::TransformComponent>()->
			Translate(star::PathFindManager::GetInstance()->GetStep(m_Step));*/
		//vec2 pos = m_pObjectOne->GetTransform()->GetWorldPosition();
		//tstringstream tstr;
		//tstr << _T("PlayerPos : (") << pos.x << _T(", ") << pos.y << _T(")");
		//LOGGER->Log(LogLevel::Info, tstr.str());
		++m_Step;
	}
	
	star::PathFindManager::GetInstance()->FindPath(m_pObjectOne->
		GetComponent<star::TransformComponent>()->GetWorldPosition(), vec2(3,2));
	
	if(pos.y < (star::GraphicsManager::GetInstance()->GetWindowHeight()/2)
		&& pos.y > 0)
	{
		star::SceneManager::GetInstance()->SetActiveScene(_T("TestScene"));
	}
	else
	{
		if(m_CurrentAnimation != 4 && pos.x > (float)star::GraphicsManager::GetInstance()->GetWindowWidth() * 0.8f)
		{
			m_CurrentAnimation = 4;
			m_pSpriteObject->GetComponent<star::SpritesheetComponent>()->PlayAnimation(_T("run left"));
			m_pSpriteObject->SetVisible(true);
			m_pSpriteObject->Freeze(false);
		}
		else if(m_CurrentAnimation != 3 && pos.x > (float)star::GraphicsManager::GetInstance()->GetWindowWidth() * 0.6f
			&& pos.x < (float)star::GraphicsManager::GetInstance()->GetWindowWidth() * 0.8f)
		{
			m_CurrentAnimation = 3;
			m_pSpriteObject->GetComponent<star::SpritesheetComponent>()->PlayAnimation(_T("run up"));
			m_pSpriteObject->SetVisible(true);
			m_pSpriteObject->Freeze(true);
		}
		else if(m_CurrentAnimation != 2 && pos.x > (float)star::GraphicsManager::GetInstance()->GetWindowWidth() * 0.4f
			&& pos.x < (float)star::GraphicsManager::GetInstance()->GetWindowWidth() * 0.6f)
		{
			m_CurrentAnimation = 2;
			m_pSpriteObject->GetComponent<star::SpritesheetComponent>()->PlayAnimation(_T("run right"));
			m_pSpriteObject->SetVisible(false);
			m_pSpriteObject->Freeze(false);
		}
		else if(m_CurrentAnimation != 1 && pos.x > (float)star::GraphicsManager::GetInstance()->GetWindowWidth() * 0.2f
			&& pos.x < (float)star::GraphicsManager::GetInstance()->GetWindowWidth() * 0.4f)
		{
			m_CurrentAnimation = 1;
			m_pSpriteObject->GetComponent<star::SpritesheetComponent>()->PlayAnimation(_T("run down"));
			m_pSpriteObject->SetVisible(true);
			m_pSpriteObject->Freeze(false);
		}
		else if(m_CurrentAnimation != 0 && pos.x < (float)star::GraphicsManager::GetInstance()->GetWindowWidth() * 0.2f)
		{
			m_CurrentAnimation = 0;
			m_pSpriteObject->GetComponent<star::SpritesheetComponent>()->PlayAnimation(_T("idle"));
			m_pSpriteObject->SetVisible(true);
			m_pSpriteObject->Freeze(false);
		}
	}
	
	return STATUS_OK;
}

status TestScene2::Draw()
{
	return STATUS_OK;
}
