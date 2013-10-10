#include "../StarEngine/jni/Logger.h"
#ifdef _WIN32
#include "..\Window.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) 
{
	Window::GetInstance()->Initialize(hInstance);
	return 0;
}

#else
#include "EventLoop.h"

void android_main(android_app* pApplication) 
{
	app_dummy();

	EventLoop::GetInstance()->Initialize(pApplication);
	EventLoop::GetInstance()->Run();
}
#endif
