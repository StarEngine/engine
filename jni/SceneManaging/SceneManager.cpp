#include "SceneManager.h"
#include "../Logger.h"

namespace star 
{
	SceneManager* SceneManager::m_pSceneManager = nullptr;

	SceneManager::SceneManager( void )
		: m_ActiveScene(nullptr)
		, m_NewActiveScene(nullptr)
		, m_bSwitchingScene(false)
		, m_bInitialized(false)
		, m_CurrentSceneName(_T(""))
	{

	}

	SceneManager::~SceneManager(void)
	{

	}


	SceneManager* SceneManager::GetInstance()
	{
		if(m_pSceneManager == nullptr)
		{
			m_pSceneManager = new SceneManager();
		}
		return m_pSceneManager;
	}

	BaseScene* SceneManager::GetScene(const tstring & name)
	{
		if(m_SceneList.find(name) != m_SceneList.end())
		{
			return m_SceneList[name];
		}
		return nullptr;
	}

	bool SceneManager::SetActiveScene(const tstring & name)
	{
		if(m_CurrentSceneName == name)
		{
			return true;
		}
		if(m_SceneList.find(name) != m_SceneList.end())
		{
			m_NewActiveScene = m_SceneList[name];
			m_bSwitchingScene = true;
			m_bInitialized = m_NewActiveScene->IsInitialized();
			m_CurrentSceneName = name;
			return true;
		}
		else
		{
			m_bSwitchingScene = false;
			return false;
		}
		return true;
	}

	bool SceneManager::AddScene(const tstring & name,BaseScene* scene)
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
	bool SceneManager::RemoveScene(const tstring & name)
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
		if(m_bInitialized)
		{
			return true;
		}
		if(m_NewActiveScene == nullptr)
		{
			return false;
		}
		m_NewActiveScene->Initialize();
		m_bInitialized=m_NewActiveScene->IsInitialized();
		return m_bInitialized;

	}
	*/
	status SceneManager::Update(float deltaTime)
	{
		/*
		if(m_bSwitchingScene)
		{
			//if(!m_bInitialized)InitializeCurScene();
			m_ActiveScene = m_NewActiveScene;
			m_NewActiveScene=NULL;
			m_bSwitchingScene=false;
			return STATUS_OK;
		}
		if(m_ActiveScene!=NULL)
		{
			return m_ActiveScene->onStep();
		}
		*/
		return STATUS_OK;
	}


	status SceneManager::Draw()
	{
		//if(m_ActiveScene!=NULL)
		return STATUS_OK;
	}
}