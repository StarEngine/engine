#include "MainGame.h"


MainGame::MainGame()
{
	mSceneManager = SceneManager::GetInstance();
}

status MainGame::Run()
{
	if(mSceneManager->Update(0.1f)!= STATUS_OK)
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
	if(!mSceneManager->AddScene(mTestScene->getName(),mTestScene))return STATUS_KO;
	if(!mSceneManager->SetActiveScene(mTestScene->getName()))return STATUS_KO;
	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Scenes Set and Done"));
	return STATUS_OK;
}

status MainGame::End()
{
	return STATUS_OK;
}


