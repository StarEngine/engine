#include "SceneManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "BaseScene.h"
#include "../GraphicsManager.h"

namespace star 
{
	SceneManager* SceneManager::m_pSceneManager = nullptr;

	//[COMMENT] PLEASE initialize all members in the constructor!!!! (if platform dependant, put in constructors body
	SceneManager::SceneManager( void )
		: m_ActiveScene(nullptr)
		, m_NewActiveScene(nullptr)
		, m_bSwitchingScene(false)
		, m_bInitialized(false)
		, m_CurrentSceneName(_T(""))

	{
#ifndef _WIN32
		mApplicationPtr = nullptr;
#endif
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
			Logger::GetSingleton()->Log(LogLevel::Info,_T("Scene ")+ name + _T(" is now Active"));
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
			Logger::GetSingleton()->Log(LogLevel::Info,_T("Adding scene"));
		}
		else
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("Scene Already Exists"));
			return false;
		}

		return true;
	}

	bool SceneManager::RemoveScene(const tstring & name)
	{
		if(m_SceneList.find(name)!=m_SceneList.end())
		{
			m_SceneList.erase(name);
			return true;
		}
		return false;
	}

	bool SceneManager::InitializeCurScene(const Context& context)
	{
		if(m_bInitialized)
		{
			return true;
		}
		if(m_NewActiveScene == nullptr)
		{
			return false;
		}
		Logger::GetSingleton()->Log(LogLevel::Info,_T("Initializing Scene :")+m_CurrentSceneName);
		m_NewActiveScene->Initialize(context);
		m_bInitialized=m_NewActiveScene->IsInitialized();
		return m_bInitialized;

	}

	status SceneManager::Update(const Context& context)
	{
		if(m_bSwitchingScene)
		{
			if(!m_bInitialized)
			{
				InitializeCurScene(context);
			}
			m_ActiveScene = m_NewActiveScene;
			m_NewActiveScene = nullptr;
			m_bSwitchingScene = false;
			return STATUS_OK;
		}
		if(m_ActiveScene != nullptr)
		{
			return m_ActiveScene->Update(context);
		}
		return STATUS_OK;
	}


	status SceneManager::Draw()
	{
		if(m_ActiveScene != nullptr)
		{
			m_ActiveScene->Draw();
		}
		return STATUS_OK;
	}

#ifndef _WIN32

	void SceneManager::processActivityEvent(int32 pCommand, android_app* pApplication)
	{
		if(m_ActiveScene==nullptr)return;
		mApplicationPtr = pApplication;
		switch(pCommand)
		{
		case APP_CMD_CONFIG_CHANGED:
			m_ActiveScene->OnConfigurationChanged();
			break;
		case APP_CMD_INIT_WINDOW:
			m_ActiveScene->OnCreateWindow();
			break;
		case APP_CMD_DESTROY:
			m_ActiveScene->OnDestroy();
			break;
		case APP_CMD_GAINED_FOCUS:
			Activate();
			m_ActiveScene->OnGainFocus();
			break;
		case APP_CMD_LOST_FOCUS:
			m_ActiveScene->OnLostFocus();
			DeActivate();
			break;
		case APP_CMD_LOW_MEMORY:
			m_ActiveScene->OnLowMemory();
			break;
		case APP_CMD_PAUSE:
			m_ActiveScene->OnPause();
			DeActivate();
			break;
		case APP_CMD_RESUME:
			m_ActiveScene->OnResume();
			break;
		case APP_CMD_SAVE_STATE:
			m_ActiveScene->OnSaveState(&mApplicationPtr->savedState,&mApplicationPtr->savedStateSize);
			break;
		case APP_CMD_START:
			m_ActiveScene->OnStart();
			break;
		case APP_CMD_STOP:
			m_ActiveScene->OnStop();
			break;
		case APP_CMD_TERM_WINDOW:
			m_ActiveScene->OnDestroyWindow();
			DeActivate();
			break;
		default:
			break;
		}
	}

	void SceneManager::Activate()
	{
		star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Going trough activate"));
		if(mApplicationPtr->window != nullptr)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("native window not null"));
			star::GraphicsManager::GetInstance()->Initialize(mApplicationPtr);
			if(m_ActiveScene->OnActivate() != STATUS_OK)
			{
				ANativeActivity_finish(mApplicationPtr->activity);
			}
		}
	}

	void SceneManager::DeActivate()
	{
		star::GraphicsManager::GetInstance()->Destroy();
		m_ActiveScene->OnDeactivate();
	}

#endif // _WIN32
}
