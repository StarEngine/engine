#include "../StarEngine/jni/Logger.h"
#include "Game.h"

#ifdef _WIN32

#include "../StarEngine/jni/Window.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) 
{
	Game * pGame = new Game();

	star::Window::GetInstance()->Initialize(hInstance, pGame);

	delete pGame;

	return 0;
}

#else
#include "../StarEngine/jni/EventLoop.h"

void android_main(android_app* pApplication) 
{
	app_dummy();

	Game * pGame = new Game();

	star::EventLoop::GetInstance()->Initialize(pApplication, pGame);
	star::EventLoop::GetInstance()->Run();

	delete pGame;
}
#endif