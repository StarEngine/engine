#include "StarEngine.h"
#include "GraphicsManager.h"
#include "SceneManaging/SceneManager.h"
#include "Input/InputManager.h"
#include "Context.h"
#include "Logger.h"
#include "Sound/SoundService.h"

namespace star
{
	StarEngine * StarEngine::m_pEngine = nullptr;

	StarEngine::~StarEngine()
	{

	}

	StarEngine * StarEngine::GetInstance()
	{
		if(m_pEngine == nullptr)
		{
			m_pEngine = new StarEngine();
		}
		return m_pEngine;
	}

	status StarEngine::Initialize(int32 window_width, int32 window_height)
	{
		//Only for windows we need to pas the window paramaters
		//for android these will be fetched when setting up the OpenGL context
		//within the Graphics Manager
#ifdef _WIN32
		GraphicsManager::GetInstance()->Initialize(window_width, window_height);
		Logger::GetInstance()->Log(LogLevel::Info,_T("GraphicsManager Initialized"));
#endif
		SoundService::GetInstance()->Start();
		Logger::GetInstance()->Log(LogLevel::Info,_T("SoundService Initialized"));

		Logger::GetInstance()->Log(LogLevel::Info,_T("StarEngine Initialized"));

		return STATUS_OK;
	}

	status StarEngine::Update(const Context & context)
	{
		InputManager::GetInstance()->Update();

		if(SceneManager::GetInstance()->Update(context) != STATUS_OK)
		{
			return STATUS_KO;
		}
		
		InputManager::GetInstance()->EndUpdate();

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

	StarEngine::StarEngine()
	{
	}
}