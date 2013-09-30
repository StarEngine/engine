#pragma once

#include <Windows.h>
#include <jni/Logger.h>
#include <jni/MainGame.h>
#include <jni/TimeManager.h>
#include <jni/Context.h>

// [TODO] change public datamembers into private ones!

class Window final
{
public:
	Window(HINSTANCE instance);
	~Window(void);
	static HWND handle;
	
	static HGLRC OGLcontext;
	static HDC hdc;
	static LRESULT CALLBACK wEventsProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

	static RECT CLIP_RECT;
	static tstring ASSETS_ROOT;

	static void WindowInactiveUpdate(bool inactive);

private:
	star::Logger* mLoggerPtr;
	star::MainGame* mMainGamePtr;
	star::TimeManager* mTimeManager;
	star::TextureManager* mTextureManager;
	star::Context mContext;

	static const uint32 CLASS_STYLES_COUNT = 5;
	static const uint32 WINDOW_STYLES_COUNT = 28;

	typedef std::pair<tstring, uint32> psip;
	static const psip CLASS_STYLES[];
	static const psip WINDOW_STYLES[];

	int CastStringToClassStyle(const tstring & style);
	int CastStringToWinStyle(const tstring & style);

	Window & operator=(const Window&);
	Window(const Window&);
	Window(Window&&);
};
