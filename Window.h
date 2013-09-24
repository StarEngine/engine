#ifndef _STAR_WINDOW_H
#define _STAR_WINDOW_H

#include <Windows.h>
#include <jni/Logger.h>
#include <jni/MainGame.h>
#include <jni/TimeManager.h>
#include <jni/Context.h>

class Window
{
public:
	Window(HINSTANCE instance,const char* windowName,int width,int height);
	~Window(void);
	static HWND handle;
	
	static HGLRC OGLcontext;
	static HDC hdc;
	static LRESULT CALLBACK wEventsProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	star::Logger* mLoggerPtr;
	star::MainGame* mMainGamePtr;
	star::TimeManager* mTimeManager;
	star::TextureManager* mTextureManager;
	star::Context mContext;
};

#endif