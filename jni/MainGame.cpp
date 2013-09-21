#include "MainGame.h"

namespace star
{

	MainGame::MainGame()
	{
		mSceneManager = star::SceneManager::GetInstance();
	}

	status MainGame::Run(Context& context)
	{
		if(mSceneManager->Update(context)!= STATUS_OK)
		{
			return STATUS_KO;
		}

		if(mSceneManager->Draw()!= STATUS_OK)
		{
			return STATUS_KO;
		}

		return STATUS_OK;
	}

	status MainGame::Initialize()
	{
		mTestScene = new TestScene(_T("TestScene"));
		if(!mSceneManager->AddScene(mTestScene->GetName(),mTestScene))return STATUS_KO;
		if(!mSceneManager->SetActiveScene(mTestScene->GetName()))return STATUS_KO;
		star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Scenes Set and Done"));
		return STATUS_OK;
	}

	status MainGame::End()
	{
		return STATUS_OK;
	}

}

