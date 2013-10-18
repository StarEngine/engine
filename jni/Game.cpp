#include "Game.h"
#include "Scenes/SceneManager.h"
#include "Context.h"
#include "StarEngine.h"
#include "Helpers/Helpers.h"
#include "Assets/FontManager.h"
#include "scenes/TestScene.h"
#include "scenes/TestScene2.h"
#include "Input/InputManager.h"

Game::Game()
	: star::BaseGame()
{
	star::StarEngine::GetInstance();
}

status Game::Initialize(int32 window_width, int32 window_height)
{
	ASSERT(star::StarEngine::GetInstance()->Initialize(window_width, window_height) == STATUS_OK, _T("StarEngine couldn't be initialized!"));

#ifdef _WIN32
	star::FontManager::GetInstance();
#endif

	auto scene1 = new TestScene(_T("TestScene"));
	star::SceneManager::GetInstance()->AddScene(scene1->GetName(),scene1);
	star::SceneManager::GetInstance()->SetActiveScene(_T("TestScene"));

	auto scene2 = new TestScene2(_T("TestScene2"));
	star::SceneManager::GetInstance()->AddScene(scene2->GetName(),scene2);

	star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Scenes Set and Done"));

	return STATUS_OK;
}

status Game::Update(const star::Context& context)
{
	tstring subTitle(_T("... FPS: "));
	subTitle += star::string_cast<tstring>(star::StarEngine::GetInstance()->GetCurrentFPS());
	//star::StarEngine::GetInstance()->SetGameSubTitle(subTitle);

	return star::StarEngine::GetInstance()->Update(context);
}

status Game::Draw()
{
	return star::StarEngine::GetInstance()->Draw();
}

status Game::End()
{
#ifdef _WIN32
	star::FontManager::GetInstance()->EraseFonts();
#endif
	star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Game ends."));
	return star::StarEngine::GetInstance()->End();
}
