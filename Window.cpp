#include <Window.h>
#include <string>
#include "jni/SceneManaging/SceneManager.h"
#include "jni/AssetManaging/TextureManager.h"

#pragma comment(lib, "opengl32.lib")

HWND Window::handle;
HGLRC Window::OGLcontext;
HDC Window::hdc;

Window::Window(HINSTANCE instance,const char* windowName,int width,int height)
{
	mLoggerPtr = star::Logger::GetSingleton();
	mMainGamePtr = new star::MainGame();
	mTimeManager = new star::TimeManager();
	mTextureManager = star::TextureManager::GetInstance();

	mContext.mTimeManager = mTimeManager;

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = wEventsProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = instance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"windowClass";
	wndClass.hIconSm = NULL;

	if(!RegisterClassEx(&wndClass))
	{
		
	}

	handle = CreateWindowA("windowClass", windowName, WS_OVERLAPPED, 0, 0, width, height, NULL, NULL, instance, NULL);

	if (handle == NULL)
	{
		//0.o
	}

	ShowWindow(handle, SW_SHOWNORMAL);
	UpdateWindow(handle);

			PIXELFORMATDESCRIPTOR pixelFormatDesc = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		24, 0, 0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	hdc = GetDC(handle); // Gets the display context

	if(hdc == NULL) {

		//0.o
	}

	int pixelFormat = ChoosePixelFormat(hdc, &pixelFormatDesc); // Chooses the pixel format

	if(pixelFormat == 0) {

		//0.o
	}

	// Sets the pixel format
	if(SetPixelFormat(hdc, pixelFormat, &pixelFormatDesc) == 0) {

		//return 0;
	}

	HGLRC hglrc = wglCreateContext(hdc); // Creates the rendering context

	if(hglrc == NULL) {

		//0.o
	}

	// Attaches the rendering context
	if(wglMakeCurrent(hdc, hglrc) == 0) {

		//return 0;
	}

	MSG msg ={};


	mMainGamePtr->Initialize();
	// Main message loop:
	while(msg.message != WM_QUIT)
	{
		//[TODO] move these things to the engine class!!
		mTimeManager->StartMonitoring();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else // We've processed all pending Win32 messages, and can now do a rendering update.
		{
			mMainGamePtr->Run(mContext);
		
		}
		SwapBuffers(Window::hdc); // Swaps display buffers

		mTimeManager->StopMonitoring();
	}

	mMainGamePtr->End();
}


LRESULT CALLBACK Window::wEventsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 1;
}


Window::~Window(void)
{
	delete mMainGamePtr;
}
