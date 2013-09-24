#include "MainGame.h"
#include "Context.h"
#include "SceneManaging/SceneManager.h"
#include "SceneManaging/BaseScene.h"
#include "TestScene.h"
#include "Logger.h"

namespace star
{

	MainGame::MainGame()
	{
		mSceneManager = SceneManager::GetInstance();

	}

	status MainGame::Run(const Context& context)
	{
		if(mSceneManager->Update(context) != STATUS_OK)
		{
			return STATUS_KO;
		}

		if(mSceneManager->Draw() != STATUS_OK)
		{
			return STATUS_KO;
		}

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
