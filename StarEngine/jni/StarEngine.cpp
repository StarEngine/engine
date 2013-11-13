#include "StarEngine.h"
#include "Graphics/GraphicsManager.h"
#include "Graphics/SpriteAnimationManager.h"
#include "Graphics/SpriteBatch.h"
#include "Scenes/SceneManager.h"
#include "Input/InputManager.h"
#include "Context.h"
#include "Logger.h"
#include "Sound/SoundService.h"
#include "Helpers/Stopwatch.h"
#include "AI/Pathfinding/PathFindManager.h"
#include "Assets/FontManager.h"
#include "Physics/Collision/CollisionManager.h"
#include "Graphics/ScaleSystem.h"
#include "Helpers/Debug/DebugDraw.h"

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

	void StarEngine::Initialize(int32 window_width, int32 window_height)
	{
		std::random_device seeder;
		m_RandomEngine.seed(seeder());

		//Only for windows we need to pas the window paramaters
		//for android these will be fetched when setting up the OpenGL context
		//within the Graphics Manager
#ifdef DESKTOP
		GraphicsManager::GetInstance()->Initialize(window_width,window_height);
#endif

		SoundService::GetInstance()->Start();
		GraphicsManager::GetInstance()->CalculateViewPort();
		//[COMMENT] Quite unsafe to do this now, because nothing is disabled in release so far
#if defined(DEBUG) | defined(_DEBUG)
		DebugDraw::GetInstance()->Initialize();
#endif
	}

	void StarEngine::Update(const Context & context)
	{
		m_FPS.Update(context);

		SceneManager::GetInstance()->Update(context);
		GraphicsManager::GetInstance()->Update();

		InputManager::GetInstance()->EndUpdate();
		Logger::GetInstance()->Update(context);
		Logger::GetInstance()->CheckGlError();
		m_bInitialized = true;
	}

	void StarEngine::Draw()
	{
		GraphicsManager::GetInstance()->StartDraw();
		if(m_bInitialized)
		{
			SceneManager::GetInstance()->Draw();
		}
		else
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); 

		}
		GraphicsManager::GetInstance()->StopDraw();
	}

	void StarEngine::End()
	{
		FontManager::GetInstance()->EraseFonts();
		delete DebugDraw::GetInstance();
		delete ScaleSystem::GetInstance();
		delete FontManager::GetInstance();
		delete SpriteAnimationManager::GetInstance();
		delete TextureManager::GetInstance();
		delete GraphicsManager::GetInstance();
		delete SpriteBatch::GetInstance();
		delete SoundService::GetInstance();
		delete CollisionManager::GetInstance();
		delete PathFindManager::GetInstance();
		delete SceneManager::GetInstance();
		delete Logger::GetInstance();
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
	
	const tstring & StarEngine::GetGameTitle()
	{
		return m_Title;
	}

	bool StarEngine::HasTitleUpdated() const
	{
		return m_TitleHasUpdated;
	}

	void StarEngine::ResetTitleUpdateMark()
	{
		m_TitleHasUpdated = false;
	}

	std::mt19937& StarEngine::GetMt19937Engine()
	{
		return m_RandomEngine;
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
		, m_bInitialized (false)
		, m_RandomEngine()
	{

	}

}
