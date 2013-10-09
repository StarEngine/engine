#include "Window.h"
#include <string>
#include <SceneManaging/SceneManager.h>
#include <AssetManaging/TextureManager.h>
#include <Logger.h>
#include <TimeManager.h>
#include <Helpers/Helpers.h>
#include <Helpers/Filepath.h>
#include <Input/XMLContainer.h>
#include <Input/XMLFileParser.h>

#pragma comment(lib, "opengl32.lib")

const Window::psip Window::CLASS_STYLES[] = {
		psip(_T("CS_DBLCLKS"), CS_DBLCLKS),
		psip(_T("CS_HREDRAW"), CS_HREDRAW),
		psip(_T("CS_NOCLOSE"), CS_NOCLOSE),
		psip(_T("CS_PARENTDC"), CS_PARENTDC),
		psip(_T("CS_VREDRAW"), CS_VREDRAW)
	};

const Window::psip Window::WINDOW_STYLES[] = {
		psip(_T("WS_BORDER"), WS_BORDER),
		psip(_T("WS_CAPTION"), WS_CAPTION),
		psip(_T("WS_CHILD"), WS_CHILD),
		psip(_T("WS_CHILDWINDOW"), WS_CHILDWINDOW),
		psip(_T("WS_CLIPCHILDREN"), WS_CLIPCHILDREN),
		psip(_T("WS_CLIPSIBLINGS"), WS_CLIPSIBLINGS),
		psip(_T("WS_DISABLED"), WS_DISABLED),
		psip(_T("WS_DLGFRAME"), WS_DLGFRAME),
		psip(_T("WS_GROUP"), WS_GROUP),
		psip(_T("WS_HSCROLL"), WS_HSCROLL),
		psip(_T("WS_ICONIC"), WS_ICONIC),
		psip(_T("WS_MAXIMIZE"), WS_MAXIMIZE),
		psip(_T("WS_MAXIMIZEBOX"), WS_MAXIMIZEBOX),
		psip(_T("WS_MINIMIZE"), WS_MINIMIZE),
		psip(_T("WS_MINIMIZEBOX"), WS_MINIMIZEBOX),
		psip(_T("WS_OVERLAPPED"), WS_OVERLAPPED),
		psip(_T("WS_OVERLAPPEDWINDOW"), WS_OVERLAPPEDWINDOW),
		psip(_T("WS_POPUP"), WS_POPUP),
		psip(_T("WS_POPUPWINDOW"), WS_POPUPWINDOW),
		psip(_T("WS_SIZEBOX"), WS_SIZEBOX),
		psip(_T("WS_SYSMENU"), WS_SYSMENU),
		psip(_T("WS_TABSTOP"), WS_TABSTOP),
		psip(_T("WS_THICKFRAME"), WS_THICKFRAME),
		psip(_T("WS_TILED"), WS_TILED),
		psip(_T("WS_TILEDWINDOW"), WS_TILEDWINDOW),
		psip(_T("WS_VISIBLE"), WS_VISIBLE),
		psip(_T("WS_VSCROLL"), WS_VSCROLL),
		psip(_T("WS_SYSMENU"), WS_SYSMENU)
	};

Window *Window::m_pInstance = nullptr;

Window * Window::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new Window();
	}
	return m_pInstance;
}

void Window::Initialize(HINSTANCE instance)
{
	star::Logger::GetInstance()->Initialize();

	ASSERT(!m_IsInitialized, _T("Engine is already initialized!"));
	if(!m_IsInitialized)
	{
		m_IsInitialized = true;
		star::XMLContainer winManifest;
		star::XMLFileParser manifestParser(EMPTY_STRING, _T("Win32Manifest.xml"));
		manifestParser.Read(winManifest);

		mContext.mTimeManager = mTimeManager;

		WNDCLASSEX wndClass;
		wndClass.cbSize = sizeof(WNDCLASSEX);

		auto assets_settings = winManifest[_T("assets")]->GetAttributes();
		mAssetsRoot = assets_settings[_T("root")];
		star::Filepath::SetAssetsRoot(mAssetsRoot);

		wndClass.style = 0;
		auto class_map = winManifest[_T("class_styles")];
		auto class_style_it = class_map->lower_bound(_T("style"));
		auto class_style_end_it = class_map->upper_bound(_T("style"));
		do
		{
			wndClass.style |= CastStringToClassStyle(class_style_it->second->GetValue());
			++class_style_it;
		}
		while(class_style_it != class_style_end_it);

		wndClass.lpfnWndProc = wEventsProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = instance;
		wndClass.hIcon = NULL;
		wndClass.hCursor = NULL;
		wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = winManifest[_T("class")]->GetValue().c_str();
		wndClass.hIconSm = NULL;

		uint32 windowStyles(0);
		auto window_map = winManifest[_T("window_styles")];
		auto win_style_it = window_map->lower_bound(_T("style"));
		auto win_style_end_it = window_map->upper_bound(_T("style"));
		do
		{
			windowStyles |= CastStringToWinStyle(win_style_it->second->GetValue());
			++win_style_it;
		}
		while(win_style_it != win_style_end_it);

		if(!RegisterClassEx(&wndClass))
		{
		
		}

		auto & resolution = winManifest[_T("resolution")]->GetAttributes();
		auto & position = winManifest[_T("position")]->GetAttributes();

		int position_x = star::string_cast<int>(position[_T("x")]);
		int position_y = star::string_cast<int>(position[_T("y")]);
		int position_width = star::string_cast<int>(resolution[_T("width")]);
		int position_height = star::string_cast<int>(resolution[_T("height")]);

		if(position_x == -1)
		{
			position_x = int(GetSystemMetrics(SM_CXSCREEN)) / 2;
			position_x -= position_width / 2;
		}

		if(position_y == -1)
		{
			position_y = int(GetSystemMetrics(SM_CYSCREEN)) / 2;
			position_y -= position_height / 2;
		}

		mHandle = CreateWindowA(	star::string_cast<std::string>(winManifest[_T("class")]->GetValue()).c_str(),
								star::string_cast<std::string>(winManifest[_T("title")]->GetValue()).c_str(),
								windowStyles,
								position_x,
								position_y,
								position_width,
								position_height,
								NULL, NULL, instance, NULL);

		ASSERT(mHandle != NULL, _T("Couldn't create the window."));

		ShowWindow(mHandle, SW_SHOWNORMAL);
		UpdateWindow(mHandle);

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
	
		mHDC = GetDC(mHandle); // Gets the display context
		ASSERT(mHDC != NULL, _T("Couldn't create the Display Context!"));

		int pixelFormat = ChoosePixelFormat(mHDC, &pixelFormatDesc); // Chooses the pixel format
		ASSERT(pixelFormat != 0, _T("Invalid pixel format!"));

		// Sets the pixel format
		ASSERT(SetPixelFormat(mHDC, pixelFormat, &pixelFormatDesc) != 0, _T("Couldn't set the pixel format!"));

		HGLRC hglrc = wglCreateContext(mHDC); // Creates the rendering context
		ASSERT(hglrc != NULL, _T("Couldn't create the rendering context!"));

		// Attaches the rendering context
		ASSERT(wglMakeCurrent(mHDC, hglrc) != 0, _T("Action couldn't be completed!"));

		MSG msg ={};

		auto cursor = winManifest[_T("cursor")];
		auto cursor_settings = cursor->GetAttributes();

		bool hide_cursor = star::string_cast<bool>(cursor_settings[_T("hidden")]);
		ShowCursor(!hide_cursor);

		auto clip_settings = cursor->at(_T("clip"))->GetAttributes();
		mClipRect.left = star::string_cast<long>(clip_settings[_T("x")]);
		if(mClipRect.left != -1)
		{
			RECT windowRect;
			GetWindowRect(mHandle, &windowRect);

			mClipRect.left += windowRect.left;
			long width = star::string_cast<long>(clip_settings[_T("width")]);
			if(width == -1)
			{
				mClipRect.right = windowRect.right;
			}
			else
			{
				mClipRect.right = mClipRect.left + width;
			}
			mClipRect.top = star::string_cast<long>(clip_settings[_T("y")]);
			mClipRect.top += windowRect.top;
			long height = star::string_cast<long>(clip_settings[_T("height")]);
			if(height == -1)
			{
				mClipRect.bottom = windowRect.bottom;
			}
			else
			{
				mClipRect.bottom = mClipRect.top + height;
			}

			mClipRect.top += 25;
			mClipRect.left += 5;
			mClipRect.right -= 5;
			mClipRect.bottom -= 5;

			ClipCursor(&mClipRect);
		}
	
		mMainGamePtr->Initialize(position_width,position_height);
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
				mMainGamePtr->Draw();
		
			}
			SwapBuffers(Window::mHDC); // Swaps display buffers

			mMainGamePtr->Update(mContext);

			mTimeManager->StopMonitoring();
		}

		mMainGamePtr->End();
	}
}

Window::Window()
	: m_IsInitialized(false)
	, mMainGamePtr(new Game())
	, mTimeManager(new star::TimeManager())
	, mHandle()
	, mOGLContext()
	, mHDC()
	, mClipRect()
	, mAssetsRoot()
{
}

LRESULT CALLBACK Window::wEventsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 1;
		case WM_KILLFOCUS:
			Window::GetInstance()->WindowInactiveUpdate(true);
			break;
		case WM_SETFOCUS:
			Window::GetInstance()->WindowInactiveUpdate(false);
			break;
		case WM_ACTIVATE:
			Window::GetInstance()->WindowInactiveUpdate(wParam == WA_INACTIVE);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


Window::~Window(void)
{
	delete mMainGamePtr;
}

void Window::WindowInactiveUpdate(bool inactive)
{
	if(inactive && mClipRect.left != -1)
	{
		RECT windowRect;
				
		windowRect.left = 0;
		windowRect.top = 0;
		windowRect.right = GetSystemMetrics(SM_CXSCREEN);
		windowRect.bottom = GetSystemMetrics(SM_CYSCREEN);

		ClipCursor(&windowRect);
	}
	else if(mClipRect.left != -1)
	{
		ClipCursor(&mClipRect);
	}
}

const tstring & Window::GetAssetRoot() const
{
	return mAssetsRoot;
}

const HDC & Window::GetHDC() const
{
	return mHDC;
}

const HWND & Window::GetHandle() const
{
	return mHandle;
}

int Window::CastStringToClassStyle(const tstring & style)
{
	for ( int32 i = 0 ; i < CLASS_STYLES_COUNT ; ++i )
	{
		if(style == CLASS_STYLES[i].first)
		{
			return CLASS_STYLES[i].second;
		}
	}
	ASSERT(false, _T("Invalid class style found in Win32Manifest.xml"));
	return NULL;
}

int Window::CastStringToWinStyle(const tstring & style)
{
	for ( int32 i = 0 ; i < WINDOW_STYLES_COUNT ; ++i )
	{
		if(style == WINDOW_STYLES[i].first)
		{
			return WINDOW_STYLES[i].second;
		}
	}
	ASSERT(false, _T("Invalid window style found in Win32Manifest.xml"));
	return NULL;
}
