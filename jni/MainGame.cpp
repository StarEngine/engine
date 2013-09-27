#include "MainGame.h"
#include "Context.h"
#include "GraphicsManager.h"
#include "SceneManaging/SceneManager.h"
#include "SceneManaging/BaseScene.h"
#include "TestScene.h"
#include "Logger.h"

namespace star
{

//[COMMENT] -- INITIALIZE VARIABLES!! (test scene
	MainGame::MainGame() :
			mTestScene(nullptr)
	{
	}

	status MainGame::Run(const Context& context)
	{
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

		return STATUS_OK;
	}

	status MainGame::Initialize()
	{
		Logger::GetSingleton()->Log(LogLevel::Info,_T("MainGame Initialize"));
		mSceneManager = SceneManager::GetInstance();

		mTestScene = new TestScene(_T("TestScene"));
		mSceneManager->AddScene(mTestScene->GetName(),mTestScene);
		mSceneManager->SetActiveScene(_T("TestScene"));

		Logger::GetSingleton()->Log(LogLevel::Info,_T("Scenes Set and Done"));

		star::GraphicsManager::GetInstance()->Setup();

		return STATUS_OK;
	}

	status MainGame::End()
	{
		return STATUS_OK;
	}

}
