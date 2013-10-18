#include "StarEngine.h"
#include "Graphics/GraphicsManager.h"
#include "Scenes/SceneManager.h"
#include "Input/InputManager.h"
#include "Context.h"
#include "Logger.h"
#include "Sound/SoundService.h"
#include "Helpers/Stopwatch.h"

namespace star
{
	std::shared_ptr<StarEngine> StarEngine::m_pEngine = nullptr;

	StarEngine::~StarEngine()
	{
	}

	std::shared_ptr<StarEngine> StarEngine::GetInstance()
	{
		if(m_pEngine == nullptr)
		{
			m_pEngine = std::shared_ptr<StarEngine>(new StarEngine());
		}
		return m_pEngine;
	}

	status StarEngine::Initialize(int32 window_width, int32 window_height)
	{
		Logger::GetInstance()->Initialize();
		Stopwatch::GetInstance();

		//Only for windows we need to pas the window paramaters
		//for android these will be fetched when setting up the OpenGL context
		//within the Graphics Manager
#ifdef DESKTOP
		GraphicsManager::GetInstance()->Initialize(window_width, window_height);
#endif
		SoundService::GetInstance()->Start();

		return STATUS_OK;
	}

	status StarEngine::Update(const Context & context)
	{
		m_FPS.Update(context);

		if(SceneManager::GetInstance()->Update(context) != STATUS_OK)
		{
			return STATUS_KO;
		}

		Stopwatch::GetInstance()->Update(context);
		
		InputManager::GetInstance()->EndUpdate();
		Logger::GetInstance()->CheckGlError();

		return STATUS_OK;
	}

	status StarEngine::Draw()
	{
		GraphicsManager::GetInstance()->StartDraw();

		if(SceneManager::GetInstance()->Draw() != STATUS_OK)
		{
			return STATUS_KO;
		}

		GraphicsManager::GetInstance()->StopDraw();
		
		return STATUS_OK;
	}

	status StarEngine::End()
	{
		return STATUS_OK;
	}
	
	void StarEngine::SetActive()
	{
		SoundService::GetInstance()->ResumeAllSound();
	}

	void StarEngine::SetInactive()
	{
		SoundService::GetInstance()->PauseAllSound();
	}

	int StarEngine::GetCurrentFPS() const
	{
		return m_FPS.CurrentFPS;
	}

	int StarEngine::GetPreviousFPS() const
	{
		return m_FPS.PreviousFPS;
	}

	void StarEngine::SetGameTitle(const tstring & title)
	{
		m_Title = title;
		m_TitleHasUpdated = true;
	}

	void StarEngine::SetGameSubTitle(const tstring & title)
	{
		m_SubTitle = title;
		m_TitleHasUpdated = true;
	}

	bool StarEngine::HasTitleUpdated() const
	{
		return m_TitleHasUpdated;
	}

	void StarEngine::ResetTitleUpdateMark()
	{
		m_TitleHasUpdated = false;
	}

#ifdef ANDROID
	void StarEngine::SetAndroidApp(android_app * app)
	{
		m_pAndroidApp = app;
	}

	android_app * StarEngine::GetAndroidApp() const
	{
		return m_pAndroidApp;
	}
#endif

	StarEngine::StarEngine()
		: m_FPS()
		, m_Title(EMPTY_STRING)
		, m_SubTitle(EMPTY_STRING)
		, m_TitleHasUpdated(false)
	{
	}
}
