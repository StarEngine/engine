#ifdef _WIN32

#include "Window.h"
#include <Shlobj.h>
#include <string>
#include "jni/Scenes/SceneManager.h"
#include "jni/Graphics/TextureManager.h"
#include "jni/Logger.h"
#include "jni/TimeManager.h"
#include "jni/Helpers/Helpers.h"
#include "jni/Helpers/FilePath.h"
#include "jni/Input/XMLContainer.h"
#ifdef _DEBUG
	#include "jni/Input/XMLFileParser.h"
#endif
#include "jni/Graphics/GraphicsManager.h"
#include "jni/StarEngine.h"
#include "jni/Input/InputManager.h"
#include "resource.h"

#pragma comment(lib, "opengl32.lib")

#define KEYDOWN(vkCode) ((GetAsyncKeyState(vkCode) & 0x8000) ? 1 : 0)
#define KEYUP(vkCode) ((GetAsyncKeyState(vkCode) & 0x8000) ? 0 : 1)

namespace star
{
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

	Window * Window::m_pInstance = nullptr;

	Window * Window::GetInstance()
	{
		if(m_pInstance == nullptr)
		{
			m_pInstance = new Window();
		}
		return m_pInstance;
	}

	void Window::Initialize(HINSTANCE instance, BaseGame * pBaseGame, bool useConsole)
	{
		ASSERT_LOG(!m_IsInitialized,
			_T("Engine is already initialized!"), STARENGINE_LOG_TAG);
		if(!m_IsInitialized)
		{
			mGamePtr = pBaseGame;
			Logger::GetInstance()->Initialize(useConsole);

			XMLContainer winManifest;
#ifdef _DEBUG
			XMLFileParser manifestParser(_T("Win32Manifest.xml"), DirectoryMode::custom);
			manifestParser.Read(winManifest);
			winManifest.Serialize(_T("Win32Manifest.star"), DirectoryMode::custom);
#else
			winManifest.Deserialize(_T("Win32Manifest.star"), DirectoryMode::custom);
#endif

			//set console position
			if(useConsole)
			{
				HWND consoleHandle = GetConsoleHWND();
				if(consoleHandle != NULL)
				{
					auto consoleAttributes = winManifest[_T("console")]->GetAttributes();
					int32 x = string_cast<int32>(consoleAttributes[_T("x")]);
					int32 y = string_cast<int32>(consoleAttributes[_T("y")]);
					int32 width = string_cast<int32>(consoleAttributes[_T("width")]);
					int32 height = string_cast<int32>(consoleAttributes[_T("height")]);
					MoveWindow(consoleHandle, x, y, width, height, true);
				}
			}

			mContext.time = TimeManager::GetInstance();

			WNDCLASSEX wndClass;
			wndClass.cbSize = sizeof(WNDCLASSEX);

			//Set the assets root that will be used for DirectoryMode::assets
			auto assets_settings = winManifest[_T("assets")]->GetAttributes();
			FilePath::SetAssetsRoot(assets_settings[_T("root")]);
			
			//Set the internal root that will be used for DirectoryMode::internal
			auto internal_settings = winManifest[_T("internal")]->GetAttributes();
			tstring iPath(internal_settings[_T("root")]);
			FilePath::SetInternalRoot(iPath);
			auto cdReturn = CreateDirectory(iPath.c_str(), NULL);
			if(cdReturn == ERROR_ALREADY_EXISTS)
			{
				LOG(LogLevel::Warning,
					_T("Internal directory '") + iPath + _T("' already exists."),
					STARENGINE_LOG_TAG);
			}
			ASSERT_LOG(cdReturn != ERROR_PATH_NOT_FOUND,
				_T("Couldn't create the internal directory!"), STARENGINE_LOG_TAG);

			//Set the external root that will be used for DirectoryMode::external
			LPWSTR wszPath = NULL;
			auto mdReturn = SHGetKnownFolderPath(
				FOLDERID_Documents,
				NULL,
				NULL,
				&wszPath
			);
			ASSERT_LOG(SUCCEEDED(mdReturn),
				_T("An error has occured, while trying to open 'my documents'!"),
				STARENGINE_LOG_TAG);
			tstring ePath = string_cast<tstring>(wszPath);
			ePath += _T("/");
			ePath += winManifest[_T("title")]->GetValue();
			ePath += _T("/");
			FilePath::SetExternalRoot(ePath);
			
			cdReturn = CreateDirectory(ePath.c_str(), NULL);
			if(cdReturn == ERROR_ALREADY_EXISTS)
			{
				LOG(LogLevel::Warning,
					_T("External directory '") + ePath + _T("' already exists."),
					STARENGINE_LOG_TAG);
			}
			ASSERT_LOG(cdReturn != ERROR_PATH_NOT_FOUND,
				_T("Couldn't create the external directory!"), STARENGINE_LOG_TAG);


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
			wndClass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STARGAMEICON));
			wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wndClass.lpszMenuName = NULL;
			wndClass.lpszClassName = winManifest[_T("class")]->GetValue().c_str();
			wndClass.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STARGAMEICON), IMAGE_ICON, 16, 16, 0);

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

	#pragma warning ( disable : 4800 )
			ASSERT_LOG(RegisterClassEx(&wndClass),
				_T("Couldn't register the Windows Class!"), STARENGINE_LOG_TAG);
	#pragma warning ( default : 4800 )

			m_CanGoFullScreen =
				string_cast<bool>(winManifest[_T("allow_fullscreen")]->GetValue());
			m_ManipulateWindowResolution = 
				string_cast<bool>(winManifest[_T("allow_fullscreen")]->GetAttributes()[_T("manipulate_window_resolution")]);
			m_UpdateGameWhenInactive = 
				string_cast<bool>(winManifest[_T("update_game_when_inactive")]->GetValue());

			auto & resolution = winManifest[_T("resolution")]->GetAttributes();
			auto & position = winManifest[_T("position")]->GetAttributes();

			int32 position_x = string_cast<int32>(position[_T("x")]);
			int32 position_y = string_cast<int32>(position[_T("y")]);
			int32 position_width = string_cast<int32>(resolution[_T("width")]);
			int32 position_height = string_cast<int32>(resolution[_T("height")]);

			if(position_x == -1)
			{
				position_x = int32(GetSystemMetrics(SM_CXSCREEN)) / 2;
				position_x -= position_width / 2;
			}

			if(position_y == -1)
			{
				position_y = int32(GetSystemMetrics(SM_CYSCREEN)) / 2;
				position_y -= position_height / 2;
			}

			tstring windowsTitle = winManifest[_T("title")]->GetValue();
			StarEngine::GetInstance()->SetGameTitle(windowsTitle);

			mHandle = CreateWindowA(string_cast<sstring>(winManifest[_T("class")]->GetValue()).c_str(),
									string_cast<sstring>(windowsTitle).c_str(),
									windowStyles,
									position_x,
									position_y,
									position_width,
									position_height,
									NULL, NULL, instance, NULL);

			ASSERT_LOG(mHandle != NULL,
				_T("Couldn't create the window."), STARENGINE_LOG_TAG);

			SetResolution(position_width, position_height, false);

			ShowWindow(mHandle, SW_SHOWNORMAL);
			UpdateWindow(mHandle);

			InputManager::GetInstance()->SetWindowsHandle(mHandle);

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
			ASSERT_LOG(mHDC != NULL,
				_T("Couldn't create the Display Context!"), STARENGINE_LOG_TAG);

			int32 pixelFormat = ChoosePixelFormat(mHDC, &pixelFormatDesc); // Chooses the pixel format
			ASSERT_LOG(pixelFormat != 0,
				_T("Invalid pixel format!"), STARENGINE_LOG_TAG);

			// Sets the pixel format
			ASSERT_LOG(SetPixelFormat(mHDC, pixelFormat, &pixelFormatDesc) != 0,
				_T("Couldn't set the pixel format!"), STARENGINE_LOG_TAG);

			HGLRC hglrc = wglCreateContext(mHDC); // Creates the rendering context
			ASSERT_LOG(hglrc != NULL,
				_T("Couldn't create the rendering context!"), STARENGINE_LOG_TAG);

			// Attaches the rendering context
			ASSERT_LOG(wglMakeCurrent(mHDC, hglrc) != 0,
				_T("Action couldn't be completed!"), STARENGINE_LOG_TAG);

			auto cursor = winManifest[_T("cursor")];
			auto cursor_settings = cursor->GetAttributes();

			bool hide_cursor = string_cast<bool>(cursor_settings[_T("hidden")]);
			ShowCursor(!hide_cursor);

			auto clip_settings = cursor->at(_T("clip"))->GetAttributes();
			mClipRect.left = string_cast<long>(clip_settings[_T("x")]);
			if(mClipRect.left != -1)
			{
				RECT windowRect;
				GetWindowRect(mHandle, &windowRect);
				GetWindowClipSize(windowRect);

				mClipRect.left += windowRect.left;
				long width = string_cast<long>(clip_settings[_T("width")]);
				if(width == -1)
				{
					mClipRect.right = windowRect.right;
				}
				else
				{
					mClipRect.right = mClipRect.left + width;
				}
				mClipRect.top = string_cast<long>(clip_settings[_T("y")]);
				mClipRect.top += windowRect.top;
				long height = string_cast<long>(clip_settings[_T("height")]);
				if(height == -1)
				{
					mClipRect.bottom = windowRect.bottom;
				}
				else
				{
					mClipRect.bottom = mClipRect.top + height;
				}

				ClipCursor(&mClipRect);
			}
	
			mGamePtr->Initialize(position_width,position_height);

			POINT pt;
			pt.x = position_width / 2;
			pt.y = position_height / 2;
			ClientToScreen(mHandle, &pt);
			SetCursorPos(pt.x,pt.y);
			
			m_IsInitialized = true;

			//AttachThreadInput(m_dKeybThreadID, GetCurrentThreadId(), true);

			// Main message loop:
			RunMainLoop();

			mGamePtr->End();

			delete this;
		}
	}

	void Window::RunMainLoop()
	{
		MSG msg = {};
		while(msg.message != WM_QUIT)
		{
			TimeManager::GetInstance()->StartMonitoring();		

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				if(m_IsActive)
				{
					star::InputManager::GetInstance()->UpdateWin();
					mGamePtr->Update(mContext);
					SetWindowsTitle();
					GraphicsManager::GetInstance()->SetHasWindowChanged(false);

					mGamePtr->Draw();
					SwapBuffers(Window::mHDC); // Swaps display buffers
					TimeManager::GetInstance()->StopMonitoring();
				}
			}
		}
	}

	Window::Window()
		: m_IsInitialized(false)
		, m_IsFullScreen(false)
		, m_CanGoFullScreen(false)
		, m_WindowMoved(false)
		, m_IsActive(true)
		, m_UpdateGameWhenInactive(false)
		, m_ManipulateWindowResolution(false)
		, m_SavedWindowState()
		, mGamePtr(nullptr)
		, mHandle()
		, mOGLContext()
		, mHDC()
		, mClipRect()
		, m_hKeybThread()
		, m_dKeybThreadID()
	{
		//InputManager::GetInstance()->StartKeyboardThread();
		//m_hKeybThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) :: KeybThreadProc, this, NULL, &m_dKeybThreadID);
	}

	void Window::SetClipRect(const RECT & rect)
	{
		mClipRect = rect;
	}

	bool Window::IsInitialized() const
	{
		return m_IsInitialized;
	}
	
	bool Window::IsCursorClipped() const
	{
		return mClipRect.left != -1;
	}
	bool Window::IsFullScreen() const
	{
		return m_IsFullScreen;
	}

	bool Window::CanGoFullScreen() const
	{
		return m_CanGoFullScreen;
	}

	bool Window::IsActive() const
	{
		return m_IsActive;
	}

	bool Window::UpdateGameWhenInactive() const
	{
		return m_UpdateGameWhenInactive;
	}

	bool Window::ChangeResolutionWhenGoingFullScreen() const
	{
		return m_ManipulateWindowResolution;
	}

	void Window::ToggleFullScreen(HWND hWnd)
	{
		SetFullScreen(hWnd, !m_IsFullScreen);
	}

	void Window::SetFullScreen(HWND hWnd, bool fullscreen)
	{
		if(!m_IsFullScreen)
		{
			m_SavedWindowState.maximized = IsZoomed(hWnd);
			if(m_SavedWindowState.maximized)
			{
				// window can't be maximized in fullscreen modus
				SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			}
			m_SavedWindowState.style = GetWindowLong(hWnd, GWL_STYLE);
			m_SavedWindowState.exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
			GetWindowRect(hWnd, &m_SavedWindowState.winRect);
		}

		m_IsFullScreen = fullscreen;
		auto hdc = GetDC(hWnd);

		WindowInactiveUpdate(false);

		if (m_IsFullScreen) 
		{
			DEVMODE fullscreenSettings = DEVMODE();

			int32 screenWidth = GetDeviceCaps(hdc, HORZRES);
			int32 screenHeight = GetDeviceCaps(hdc, VERTRES);

			if(m_ManipulateWindowResolution)
			{
				screenWidth = m_SavedWindowState.winRect.right - m_SavedWindowState.winRect.left;
				screenHeight = m_SavedWindowState.winRect.bottom - m_SavedWindowState.winRect.top;
			}

			EnumDisplaySettings(NULL, 0, &fullscreenSettings);
			fullscreenSettings.dmPelsWidth        = screenWidth;
			fullscreenSettings.dmPelsHeight       = screenHeight;
			fullscreenSettings.dmBitsPerPel       = GetDeviceCaps(hdc, BITSPIXEL);
			fullscreenSettings.dmDisplayFrequency = GetDeviceCaps(hdc, VREFRESH);
			fullscreenSettings.dmFields           = DM_PELSWIDTH |
													DM_PELSHEIGHT |
													DM_BITSPERPEL |
													DM_DISPLAYFREQUENCY;

			SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
			SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
			SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);
			bool isChangeSuccessful = ChangeDisplaySettings(&fullscreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
			ShowWindow(hWnd, SW_MAXIMIZE);
		}
		else
		{
			SetWindowLongPtr(hWnd, GWL_EXSTYLE, m_SavedWindowState.exStyle);
			SetWindowLongPtr(hWnd, GWL_STYLE, m_SavedWindowState.style);
			bool isChangeSuccessful = ChangeDisplaySettings(NULL, CDS_RESET) == DISP_CHANGE_SUCCESSFUL;
			SetWindowPos(hWnd, HWND_NOTOPMOST, 
				m_SavedWindowState.winRect.left,
				m_SavedWindowState.winRect.top,
				m_SavedWindowState.winRect.right - m_SavedWindowState.winRect.left,
				m_SavedWindowState.winRect.bottom - m_SavedWindowState.winRect.top,
				SWP_SHOWWINDOW);
			ShowWindow(hWnd, SW_RESTORE);

			if (m_SavedWindowState.maximized)
			{
				SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			}
		}
	}

	void Window::UpdateClippingIfNeeded()
	{
		if(m_WindowMoved)
		{
			WindowInactiveUpdate(false);
			m_WindowMoved = false;
		}
	}

	void Window::SetWindowMoved()
	{
		m_WindowMoved = true;
	}

	void Window::SetWindowActive(bool active)
	{
		m_IsActive = active;
	}
	
	void Window::SetResolution(int32 width, int32 height, bool reset)
	{
		GraphicsManager::GetInstance()->SetWindowDimensions(
			width, 
			height);

		ClientResize(width, height);

		m_SavedWindowState.maximized = IsZoomed(mHandle);
		m_SavedWindowState.style = GetWindowLong(mHandle, GWL_STYLE);
		m_SavedWindowState.exStyle = GetWindowLong(mHandle, GWL_EXSTYLE);
		GetWindowRect(mHandle, &m_SavedWindowState.winRect);

		WindowInactiveUpdate(false);

		if(reset)
		{
			SetWindowLongPtr(mHandle, GWL_EXSTYLE, m_SavedWindowState.exStyle);
			SetWindowLongPtr(mHandle, GWL_STYLE, m_SavedWindowState.style);
			bool isChangeSuccessful = 
				ChangeDisplaySettings(NULL, CDS_RESET) == DISP_CHANGE_SUCCESSFUL;
		}
		SetWindowPos(mHandle, HWND_NOTOPMOST, 
			m_SavedWindowState.winRect.left,
			m_SavedWindowState.winRect.top,
			width,
			height,
			SWP_SHOWWINDOW);
		ShowWindow(mHandle, SW_RESTORE);
		UpdateWindow(mHandle);
	}

	void Window::ClientResize(int32 & width, int32 & height)
	{
		int32 difX, difY;
		GetWindowDifferenceSize(difX, difY);

		width += difX;
		height += difY;
	}

	void Window::GetWindowDifferenceSize(int32 & difX, int32 & difY)
	{
		RECT rcClient, rcWindow;

		GetClientRect(mHandle, &rcClient);
		GetWindowRect(mHandle, &rcWindow);

		difX = (rcWindow.right - rcWindow.left) - rcClient.right;
		difY = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
	}

	void Window::GetWindowClipSize(RECT & rect)
	{
		int32 difX, difY;
		GetWindowDifferenceSize(difX, difY);

		int32 border = difX / 2;
		int32 top = difY - border;

		rect.top += top;
		rect.left += border;
		rect.right -= border - 1;
		rect.bottom -= border - 1;
	}

	void Window::ForceTimerCalculation()
	{
		TimeManager::GetInstance()->StartMonitoring();
		TimeManager::GetInstance()->StopMonitoring();
	}

	void Window::SetWindowsTitle() const
	{
		if (StarEngine::GetInstance()->HasTitleUpdated())
		{
			SetWindowText(mHandle, 
				(StarEngine::GetInstance()->m_Title + 
				StarEngine::GetInstance()->m_SubTitle).c_str());
			StarEngine::GetInstance()->ResetTitleUpdateMark();
		}
	}

	HWND Window::GetConsoleHWND()
	{
		#define MY_BUFSIZE 1024 // Buffer size for console window titles.
		HWND hwndFound;         // This is what is returned to the caller.
		tchar pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
											// WindowTitle.
		tchar pszOldWindowTitle[MY_BUFSIZE]; // Contains original
											// WindowTitle.
	
		// Fetch current window title.
		GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

		// Format a "unique" NewWindowTitle.
		wsprintf(pszNewWindowTitle,_T("%d/%d"),
					GetTickCount64(),
					GetCurrentProcessId());

		// Change current window title.
		SetConsoleTitle(pszNewWindowTitle);

		// Ensure window title has been updated.
		Sleep(40);

		// Look for NewWindowTitle.
		hwndFound = FindWindow(NULL, pszNewWindowTitle);

		// Restore original window title.
		SetConsoleTitle(pszOldWindowTitle);

		return(hwndFound);
	}

	LRESULT CALLBACK Window::wEventsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 1;
			case WM_ENTERSIZEMOVE:
			case WM_NCRBUTTONDOWN:
				Window::GetInstance()->SetWindowActive(false);
				break;
			case WM_EXITSIZEMOVE:
			case WM_EXITMENULOOP:
				Window::GetInstance()->SetWindowActive(true);
				Window::GetInstance()->ForceTimerCalculation();
				break;
			case WM_KILLFOCUS:
				Window::GetInstance()->WindowInactiveUpdate(true);
				break;
			case WM_SETFOCUS:
				Window::GetInstance()->WindowInactiveUpdate(false);
				break;
			case WM_LBUTTONUP:
				Window::GetInstance()->UpdateClippingIfNeeded();
				break;
			case WM_ACTIVATE:
				{
					bool active = !(LOWORD(wParam) == WA_INACTIVE);
					Window::GetInstance()->WindowInactiveUpdate(!active);
					Window::GetInstance()->SetWindowActive(
						Window::GetInstance()->UpdateGameWhenInactive() || active
						);
					if(!Window::GetInstance()->UpdateGameWhenInactive())
					{
						if(active)
						{
							StarEngine::GetInstance()->SetActive();
						}
						else
						{
							StarEngine::GetInstance()->SetInactive();
						}
					}
				}
				break;
			case WM_MOVE:
				UpdateWindowClipping(hWnd);
				Window::GetInstance()->SetWindowMoved();
				Window::GetInstance()->WindowInactiveUpdate(true);
				break;
			case WM_SYSCOMMAND:
				if (Window::GetInstance()->CanGoFullScreen()
					&& SC_KEYMENU == (wParam & 0xFFF0)
					&& KEYDOWN(VK_RETURN))
				{
					//alt - enter => FullScreen
					Window::GetInstance()->ToggleFullScreen(hWnd);
					return 1;
				}
				break;
			case WM_SIZE:
				{
					GraphicsManager::GetInstance()->SetHasWindowChanged(true);
					RECT clienRect;
					GetClientRect(hWnd, &clienRect);
					GraphicsManager::GetInstance()->SetWindowDimensions(
						clienRect.right - clienRect.left,
						clienRect.bottom - clienRect.top
						);
					UpdateWindowClipping(hWnd);
				}
				break;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	Window::~Window(void)
	{
		InputManager::DeleteSingleton();

		delete (mGamePtr);
		mGamePtr = nullptr;

		delete StarEngine::GetInstance();
	}

	void Window::WindowInactiveUpdate(bool inactive)
	{
		if(m_IsInitialized)
		{
			if(m_IsFullScreen || (inactive && mClipRect.left != -1))
			{
				ClipCursor(NULL);
			}
			else if(mClipRect.left != -1)
			{
				SetActiveWindow(mHandle);
				ClipCursor(NULL);
				ClipCursor(&mClipRect);
			}
		}
	}

	const HDC & Window::GetHDC() const
	{
		return mHDC;
	}

	const HWND & Window::GetHandle() const
	{
		return mHandle;
	}

	int32 Window::CastStringToClassStyle(const tstring & style)
	{
		for ( int32 i = 0 ; i < CLASS_STYLES_COUNT ; ++i )
		{
			if(style == CLASS_STYLES[i].first)
			{
				return CLASS_STYLES[i].second;
			}
		}
		ASSERT_LOG(false,
			_T("Invalid class style found in Win32Manifest.xml"),
			STARENGINE_LOG_TAG);
		return NULL;
	}

	int32 Window::CastStringToWinStyle(const tstring & style)
	{
		for ( int32 i = 0 ; i < WINDOW_STYLES_COUNT ; ++i )
		{
			if(style == WINDOW_STYLES[i].first)
			{
				return WINDOW_STYLES[i].second;
			}
		}
		ASSERT_LOG(false,
			_T("Invalid window style found in Win32Manifest.xml"),
			STARENGINE_LOG_TAG);
		return NULL;
	}

	void UpdateWindowClipping(HWND hWnd)
	{
		RECT winRect;
		GetWindowRect(hWnd, &winRect);
		Window::GetInstance()->GetWindowClipSize(winRect);
		if(Window::GetInstance()->IsCursorClipped()
					&& Window::GetInstance()->IsInitialized())
		{
			Window::GetInstance()->SetClipRect(winRect);
		}
	}
}

/*DWORD WINAPI KeybThreadProc()
{
	return star::InputManager::GetInstance()->UpdateWin();
}*/
#endif
