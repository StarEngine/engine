#pragma once

#include <Windows.h>
#include <Context.h>
#include <defines.h>

#include "jni/Game.h"

namespace star
{
	class TimeManager;
	class TextureManager;
}

class Window final
{
public:
	static Window * GetInstance();

	~Window(void);

	void Initialize(HINSTANCE instance);

	void WindowInactiveUpdate(bool inactive);
	const tstring & GetAssetRoot() const;
	const HDC & GetHDC() const;
	const HWND & GetHandle() const;

private:
	Window();
	static Window *m_pInstance;

	bool m_IsInitialized;

	Game* mMainGamePtr;
	star::TimeManager* mTimeManager;
	star::Context mContext;

	HWND mHandle;
	HGLRC mOGLContext;
	HDC mHDC;
	RECT mClipRect;
	tstring mAssetsRoot;

	static LRESULT CALLBACK wEventsProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

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
