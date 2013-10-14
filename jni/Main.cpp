#include "../StarEngine/jni/Logger.h"
#include "Game.h"

#ifdef _WIN32

#include "../StarEngine/jni/Window.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) 
{
	//notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL,0);

	// Enable run-time memory leak check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		//_CrtSetBreakAlloc(19521);
	#endif

	Game * pGame = new Game();

	star::Window::GetInstance()->Initialize(hInstance, pGame);

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