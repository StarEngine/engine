#include "MainGame.h"
#include "Context.h"
#include "GraphicsManager.h"
#include "SceneManaging/SceneManager.h"
#include "SceneManaging/BaseScene.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "Logger.h"
#include "Input/InputManager.h"
#include "Sound/SoundService.h"

namespace star
{

	MainGame::MainGame() :
			mTestScene(nullptr),
			mWindowWidth(0),
			mWindowHeight(0)
	{
	}

	status MainGame::Run(const Context& context)
	{
		InputManager::GetInstance()->Update();
		if(mSceneManager->Update(context) != STATUS_OK)
		{
			return STATUS_KO;
		}
		star::GraphicsManager::GetInstance()->StartDraw();
		if(mSceneManager->Draw() != STATUS_OK)
		{
			return STATUS_KO;
		}
		star::GraphicsManager::GetInstance()->StopDraw();

		InputManager::GetInstance()->EndUpdate();
		return STATUS_OK;
	}

	status MainGame::Initialize(int32 windowWidth, int32 windowHeight)
	{
		mWindowWidth = windowWidth;
		mWindowHeight = windowHeight;

		//Only for windows we need to pas the window paramaters
		//for android these will be fetched when setting up the OpenGL context
		//within the Graphics Manager
#ifdef _WIN32
		star::GraphicsManager::GetInstance()->Initialize(windowWidth,  windowHeight);
#endif
		Logger::GetInstance()->Log(LogLevel::Info,_T("MainGame Initialize"));
		mSceneManager = SceneManager::GetInstance();

		mTestScene = new TestScene(_T("TestScene"));
		mSceneManager->AddScene(mTestScene->GetName(),mTestScene);
		mSceneManager->SetActiveScene(_T("TestScene"));

		mTestScene2 = new TestScene2(_T("TestScene2"));
		mSceneManager->AddScene(mTestScene2->GetName(),mTestScene2);

		Logger::GetInstance()->Log(LogLevel::Info,_T("Scenes Set and Done"));

		star::GraphicsManager::GetInstance()->Setup();

		star::SoundService::GetInstance()->Start();

		return STATUS_OK;
	}

	status MainGame::End()
	{
		return STATUS_OK;
	}

}
