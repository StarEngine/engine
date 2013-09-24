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
		mSceneManager = SceneManager::GetInstance();
		star::GraphicsManager::GetInstance()->Initialize();
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
		mTestScene = new TestScene(_T("TestScene"));
		if(!mSceneManager->AddScene(mTestScene->GetName(),mTestScene))
		{
			return STATUS_KO;
		}

		if(!mSceneManager->SetActiveScene(mTestScene->GetName()))
		{
			return STATUS_KO;
		}

		Logger::GetSingleton()->Log(LogLevel::Info,_T("Scenes Set and Done"));
		return STATUS_OK;
	}

	status MainGame::End()
	{
		return STATUS_OK;
	}

}
