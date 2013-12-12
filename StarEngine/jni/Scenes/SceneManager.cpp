#include "SceneManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "BaseScene.h"
#include "../Objects/Object.h"
#include "../Graphics/GraphicsManager.h"
#include "../Assets/TextureManager.h"
#include "../Sound/AudioManager.h"
#include "../Graphics/SpriteBatch.h"
#include "../Input/InputManager.h"
#include "../Graphics/UI/UICursor.h"
#include "../Graphics/UI/UIBaseCursor.h"

#define INPUT_MANAGER (InputManager::GetInstance())

namespace star 
{
	SceneManager * SceneManager::m_pSceneManager = nullptr;

	SceneManager::SceneManager()
		: m_ActiveScene(nullptr)
		, m_NewActiveScene(nullptr)
		, m_Stopwatch(nullptr)
		, m_GarbageList()
		, m_bSwitchingScene(false)
		, m_bInitialized(false)
		, m_bDestroyRequested(false)
		, m_bCursorHiddenByDefault(false)
		, m_bCustomCursorDefined(false)
		, m_CurrentSceneName(EMPTY_STRING)
		, m_pDefaultCursor(nullptr)
#ifdef ANDROID
		, mApplicationPtr(nullptr)
#endif
	{
		m_Stopwatch = std::make_shared<Stopwatch>();
		CreateDefaultCursor();
	}

	void SceneManager::CreateDefaultCursor()
	{
		m_pDefaultCursor = new UIBaseCursor(_T("DefaultCursor"));
		m_pDefaultCursor->BaseInitialize();
		m_bCustomCursorDefined = false;
	}

	SceneManager::~SceneManager()
	{
		for(auto scene : m_GarbageList)
		{
			SafeDelete(scene);
		}
		m_GarbageList.clear();
		for(auto scene : m_SceneList)
		{
			SafeDelete(scene.second);
		}
		m_SceneList.clear();
		SafeDelete(m_pDefaultCursor);
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
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SceneManager::SetActiveScene: Scene is already active!"),
				STARENGINE_LOG_TAG);
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
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("Scene ") + name + _T(" is now Active"),
				STARENGINE_LOG_TAG);
			return true;
		}
		else
		{
			m_bSwitchingScene = false;
			return false;
		}
		return true;
	}

	bool SceneManager::AddScene(BaseScene* scene)
	{
		if(!scene)
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SceneManager::AddScene: Trying to add a nullptr as a scene."));
			return false;
		}
		if (m_SceneList.find(scene->GetName()) == m_SceneList.end())
		{
			m_SceneList[scene->GetName()] = scene;
			scene->BaseInitialize();
			scene->SetSystemCursorHidden(m_bCursorHiddenByDefault);
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("Adding scene"), STARENGINE_LOG_TAG);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("Scene Already Exists"), STARENGINE_LOG_TAG);
			return false;
		}
		return true;
	}
	
	bool SceneManager::AddScene(const tstring & name, BaseScene* scene)
	{
		if(!scene)
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SceneManager::AddScene: Trying to add a nullptr as a scene."));
			return false;
		}
		scene->SetName(name);
		return AddScene(scene);
	}

	bool SceneManager::RemoveScene(const tstring & name)
	{
		auto it = m_SceneList.find(name);
		if(it != m_SceneList.end())
		{
			m_GarbageList.push_back(it->second);
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
		Logger::GetInstance()->Log(LogLevel::Info,
			_T("Initializing Scene :") + m_CurrentSceneName, STARENGINE_LOG_TAG);
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

		for(auto & scene : m_GarbageList)
		{
			auto it = m_SceneList.find(scene->GetName());
			m_SceneList.erase(it);
			if(m_ActiveScene == scene)
			{
				m_ActiveScene = nullptr;
			}
			SafeDelete(scene);
		}
		m_GarbageList.clear();

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

	void SceneManager::DrawDefaultCursor()
	{
		m_pDefaultCursor->BaseDraw();
	}

	void SceneManager::UpdateDefaultCursor(const Context & context)
	{
		m_pDefaultCursor->BaseUpdate(context);
	}

	void SceneManager::SetDefaultCursor(UIBaseCursor * cursor)
	{
		SafeDelete(m_pDefaultCursor);
		SetSystemCursorHiddenByDefault(true);
		m_pDefaultCursor = cursor;
		m_pDefaultCursor->BaseInitialize();
		m_bCustomCursorDefined = true;
#ifdef MOBILE
		Logger::GetInstance()->Log(LogLevel::Warning,
			tstring(_T("SceneManager::SetDefaultCursor: Cursor isn't supported on mobile device."))
			+ _T(" For optimialisation reasons it's better to disable the code related to\
the custom cursor code in your game project."), STARENGINE_LOG_TAG);
#endif
	}

	void SceneManager::UnsetDefaultCursor()
	{
		SafeDelete(m_pDefaultCursor);
		SetSystemCursorHiddenByDefault(false);
#ifdef MOBILE
		Logger::GetInstance()->Log(LogLevel::Warning,
			tstring(_T("SceneManager::UnsetDefaultCursor: Cursor isn't supported on mobile device."))
			+ _T(" For optimialisation reasons it's better to disable the code related to\
the custom cursor code in your game project."), STARENGINE_LOG_TAG);
#endif
		CreateDefaultCursor();
	}

	void SceneManager::SetDefaultCursorState(const tstring & state)
	{
		m_pDefaultCursor->SetState(state);
	}
	
	void SceneManager::SetDefaultCursorLocked(bool locked)
	{
		m_pDefaultCursor->SetLocked(locked);
	}
	
	bool SceneManager::IsDefaultCursorLocked() const
	{
		return m_pDefaultCursor->IsLocked();
	}

	bool SceneManager::IsDefaultCursorDefined() const
	{
		return m_bCustomCursorDefined;
	}

	void SceneManager::SetSystemCursorHiddenByDefault(bool hidden)
	{
		m_bCursorHiddenByDefault = hidden;
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
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("SceneManager : APP_CMD_STOP"), STARENGINE_LOG_TAG);
			break;

		case APP_CMD_GAINED_FOCUS:
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("SceneManager : APP_CMD_GAINED_FOCUS"), STARENGINE_LOG_TAG);
			break;


		case APP_CMD_SAVE_STATE:
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("SceneManager : APP_CMD_SAVE_STATE"), STARENGINE_LOG_TAG);
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
