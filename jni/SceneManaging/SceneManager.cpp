#include "SceneManager.h"
#include "../Logger.h"

SceneManager* SceneManager::m_pSceneManager=NULL;


SceneManager::SceneManager( void )
{
	m_ActiveScene=NULL;
	m_NewActiveScene=NULL;
	m_bSwitchingScene=false;
	m_bInitialized=false;
	CurrentSceneName=_T("");

}

SceneManager::~SceneManager( void ){}


SceneManager* SceneManager::GetInstance()
{
	if(m_pSceneManager==NULL)
	{
		m_pSceneManager = new SceneManager();
	}
	return m_pSceneManager;
}

BaseScene* SceneManager::GetScene(tstring name)
{
	if(m_SceneList.find(name)!=m_SceneList.end())
	{
		return m_SceneList[name];
	}
	return NULL;
}

bool SceneManager::SetActiveScene( tstring name )
{
	if(CurrentSceneName==name)return true;

	if(m_SceneList.find(name)!=m_SceneList.end())
	{
		m_NewActiveScene = m_SceneList[name];
		m_bSwitchingScene = true;
		m_bInitialized=m_NewActiveScene->IsInitialized();
		CurrentSceneName=name;
		return true;
	}else
	{
		m_bSwitchingScene=false;
		return false;
	}

	return true;
}

bool SceneManager::AddScene( tstring name,BaseScene* scene )
{
	if ( m_SceneList.find(name) == m_SceneList.end() )
	{
		m_SceneList[name] = scene;
	}
	else
	{
		return false;
		//Logger::Log(LogLevel::Info,"Exiting event loop");
	}

	return true;
}
/*
bool SceneManager::RemoveScene( tstring name )
{
	if(m_ScenesList.find(name)!=m_ScenesList.end())
	{
		m_ScenesList.erase(name);
		return true;
	}
#ifdef DEBUG
	else
	{
		cout<< "Scene :"<< name << " already exists"<<endl;
	}
#endif
	return false;
}

bool SceneManager::InitializeCurScene()
{
	if(m_bInitialized)return true;
	if(m_NewActiveScene==nullptr)return false;
	m_NewActiveScene->Initialize();
	m_bInitialized=m_NewActiveScene->IsInitialized();
	return m_bInitialized;

}
*/
status SceneManager::Update(float deltaTime)
{
	/*if(m_bSwitchingScene)
	{
		//if(!m_bInitialized)InitializeCurScene();


		m_ActiveScene = m_NewActiveScene;
		m_NewActiveScene=NULL;
		m_bSwitchingScene=false;
		return STATUS_OK;
	}

	if(m_ActiveScene!=NULL){


		return m_ActiveScene->onStep();

	}*/
	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Going trough Update"));
	return STATUS_OK;
}


status SceneManager::Draw()
{
	/*if(m_ActiveScene!=NULL)

*/
	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Going trough Draw"));
	return STATUS_OK;

}
