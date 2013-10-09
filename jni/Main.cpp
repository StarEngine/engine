//#include "../StarEngine/jni/Logger.h"
#ifdef _WIN32
#include "..\Window.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) 
{
	Window::GetInstance()->Initialize(hInstance);
	return 0;
}

#else
//#include "EventLoop.h"
#include <android/log.h>
#include <android_native_app_glue.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "NativeActivitySimpleExample", __VA_ARGS__))

void android_main(android_app* pApplication) 
{
	app_dummy();

	while(1)
   {
	  LOGI("Tick!");
   }
    //EventLoop lEventLoop(pApplication);
    //lEventLoop.run();
}
#endif
