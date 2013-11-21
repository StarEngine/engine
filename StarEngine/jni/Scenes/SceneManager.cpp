#include "SceneManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "BaseScene.h"
#include "../Graphics/GraphicsManager.h"
#include "../Assets/TextureManager.h"
#include "../Sound/AudioManager.h"
#include "../Graphics/SpriteBatch.h"
#include "../Input/InputManager.h"

#define INPUT_MANAGER (InputManager::GetInstance())

namespace star 
{
	SceneManager * SceneManager::m_pSceneManager = nullptr;

	SceneManager::SceneManager()
		: m_ActiveScene(nullptr)
		, m_NewActiveScene(nullptr)
		, m_Stopwatch(nullptr)
		, m_bSwitchingScene(false)
		, m_bInitialized(false)
		, m_bDestroyRequested(false)
		, m_CurrentSceneName(EMPTY_STRING)
#ifdef ANDROID
		, mApplicationPtr(nullptr)
#endif
	{
		m_Stopwatch = std::make_shared<Stopwatch>();
	}

	SceneManager::~SceneManager()
	{
		for(auto scene : m_SceneList)
		{
			delete(scene.second);
			scene.second = nullptr;
		}
		m_SceneList.clear();
	}


	SceneManager * SceneManager::GetInstance()
	{
		if(m_pSceneManager == nullptr)
		{
			m_pSceneManager = new SceneManager();
		}
		return (m_pSceneManager);
	}

	BaseScene* SceneManager::GetActiveScene()
	{
		return m_ActiveScene;
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
			Logger::GetInstance()->Log(LogLevel::Warning, _T("SceneManager::SetActiveScene: Scene is already active!"));
			return true;
		}
		if(m_SceneList.find(name) != m_SceneList.end())
		{
			//[COMMENT] Can somebody confirm this does not cause any harm?? Thanks
			if(m_ActiveScene == nullptr)
			{
				m_ActiveScene = m_SceneList[name];
			}
			m_NewActiveScene = m_SceneList[name];
			m_bSwitchingScene = true;
			m_bInitialized = m_NewActiveScene->IsInitialized();
			m_CurrentSceneName = name;
			Logger::GetInstance()->Log(LogLevel::Info, _T("Scene ") + name + _T(" is now Active"));
			return true;
		}
		else
		{
			m_bSwitchingScene = false;
			return false;
		}
		return true;
	}

	bool SceneManager::AddScene(const tstring & name, BaseScene* scene)
	{
		if ( m_SceneList.find(name) == m_SceneList.end() )
		{
			m_SceneList[name] = scene;
			Logger::GetInstance()->Log(LogLevel::Info, _T("Adding scene"));
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Info, _T("Scene Already Exists"));
			return false;
		}
		return true;
	}

	bool SceneManager::RemoveScene(const tstring & name)
	{
		auto it = m_SceneList.find(name);
		if(it != m_SceneList.end())
		{
			m_SceneList.erase(it);
			return true;
		}
		return false;
	}

	void SceneManager::SetCullingEnabled(bool enabled)
	{
		for(auto scene : m_SceneList)
		{
			scene.second->SetCullingIsEnabled(enabled);
		}
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
		Logger::GetInstance()->Log(LogLevel::Info,
			_T("Initializing Scene :") + m_CurrentSceneName);
		m_NewActiveScene->BaseInitialize();
		m_bInitialized = m_NewActiveScene->IsInitialized();
		return m_bInitialized;

	}

	void SceneManager::Update(const Context& context)
	{
		if(m_bDestroyRequested)
		{
			return;
		}

		m_Stopwatch->Update(context);

		if(m_bSwitchingScene)
		{
			if(!m_bInitialized)
			{
				InitializeCurScene(context);
			}
			if(m_ActiveScene != nullptr)
			{
				m_ActiveScene->BaseOnDeactivate();
			}
			m_ActiveScene = m_NewActiveScene;
			m_ActiveScene->BaseOnActivate();
			m_NewActiveScene = nullptr;
			m_bSwitchingScene = false;
			return;
		}

		else if(m_ActiveScene != nullptr)
		{
			INPUT_MANAGER->UpdateGestures(context);
			return m_ActiveScene->BaseUpdate(context);
		}
	}


	void SceneManager::Draw()
	{
		if(m_bDestroyRequested)
		{
			return;
		}
		if(m_ActiveScene != nullptr)
		{
			m_ActiveScene->BaseDraw();
			SpriteBatch::GetInstance()->Flush();
		}
	}

	std::shared_ptr<Stopwatch> SceneManager::GetStopwatch() const
	{
		return m_Stopwatch;
	}

#ifdef ANDROID

	void SceneManager::processActivityEvent(int32 pCommand, android_app* pApplication)
	{
		if(m_ActiveScene == nullptr)
		{
			return;
		}
		mApplicationPtr = pApplication;
		switch(pCommand)
		{

		//First save state - then Stop - then Start - then Resume - then gained focus

		case APP_CMD_STOP:
			Logger::GetInstance()->Log(LogLevel::Info, _T("SceneManager : APP_CMD_STOP"));
			break;

		case APP_CMD_GAINED_FOCUS:
			Logger::GetInstance()->Log(LogLevel::Info, _T("SceneManager : APP_CMD_START"));
			break;


		case APP_CMD_SAVE_STATE:
			Logger::GetInstance()->Log(LogLevel::Info, _T("SceneManager : APP_CMD_SAVE_STATE"));
			m_ActiveScene->OnSaveState(&mApplicationPtr->savedState,&mApplicationPtr->savedStateSize);
			break;

		}
	}

	int32 SceneManager::processInputEvent(AInputEvent* pEvent)
	{
		//[TODO] Cast the input event to motionEvent and pass that type
		int32_t lEventType = AInputEvent_getType(pEvent);
		switch (lEventType)
		{
		case AINPUT_EVENT_TYPE_MOTION:
			switch (AInputEvent_getSource(pEvent))
			{
			case AINPUT_SOURCE_TOUCHSCREEN:
				INPUT_MANAGER->OnTouchEvent(pEvent);
				return (true);
			default:
				return (false);
			}
			break;

		case AINPUT_EVENT_TYPE_KEY:
			return INPUT_MANAGER->OnKeyboardEvent(pEvent);
		default:
			return false;
		}
		return false;
	}
#endif
}
