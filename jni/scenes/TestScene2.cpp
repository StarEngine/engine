#include "TestScene2.h"
#include "../../StarEngine/jni/Helpers/Helpers.h"
#include "../../StarEngine/jni/SceneManaging/CollisionManager.h"
#include "../../StarEngine/jni/SceneManaging/PathFindManager.h"
#include "../../StarEngine/jni/Input/InputManager.h"
#include "../../StarEngine/jni/GraphicsManager.h"
#include "../../StarEngine/jni/SceneManaging/SceneManager.h"
#include "../../StarEngine/jni/Input/XMLFileParser.h"
#include "../../StarEngine/jni/Input/XMLFileSerializer.h"

#ifdef _WIN32
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
	m_PassedMiliseconds(0),
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
	mTestXMLFile()
{
		
}

status TestScene2::Initialize(const star::Context& context)
{
	star::Filepath tex1path(_T(""),_T("TestDaPng.png"));
	m_pTestSprite = new star::Sprite(tex1path.GetFullPath(),_T("TestDaPng"));

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

	//CollisionManager::GetInstance()->CheckCollision(_T("Default"));

	star::XMLFileParser parser(EMPTY_STRING, _T("book_catalog.xml"));
	LOGGER->Log(star::LogLevel::Info,_T("Loading XML File..."));
	parser.Read(mTestXMLFile);
	LOGGER->Log(star::LogLevel::Info,_T("Book #1 ID:"));
	LOGGER->Log(star::LogLevel::Info,mTestXMLFile[_T("book")]->GetAttributes()[_T("id")]);
	star::XMLFileSerializer serializer(EMPTY_STRING, _T("book_catalog_v2.xml"));
	mTestXMLFile[_T("book")]->GetAttributes()[_T("id")] = _T("bki10092");
	LOGGER->Log(star::LogLevel::Info,_T("Writing XML File..."));
	serializer.Write(mTestXMLFile);
	LOGGER->Log(star::LogLevel::Info,_T("Writing Done!"));

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

		m_pObjectOne->GetComponent<star::TransformComponent>()->Translate(star::PathFindManager::GetInstance()->GetStep(m_Step));
		vec3 pos = m_pObjectOne->GetComponent<star::TransformComponent>()->GetWorldPosition();
		//tstringstream tstr;
		//tstr << _T("PlayerPos : (") << pos.x << _T(", ") << pos.y << _T(")");
		//LOGGER->Log(LogLevel::Info, tstr.str());
		++m_Step;
	}
	star::PathFindManager::GetInstance()->FindPath(m_pObjectOne->GetComponent<star::TransformComponent>()->GetWorldPosition(), vec3(3,2,0));

	if(pos.y < (star::GraphicsManager::GetInstance()->GetScreenHeight()/2)
		&& pos.y > 0)
	{
		star::SceneManager::GetInstance()->SetActiveScene(_T("TestScene"));
	}


	return STATUS_OK;
}

status TestScene2::Draw()
{
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // Clear the background of our window to red

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)

	m_pTestSprite->Draw();

	return STATUS_OK;
}
