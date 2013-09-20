#ifndef _STAR_WINDOW_H
#define _STAR_WINDOW_H

#include <Windows.h>
#include <jni/Logger.h>
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
};

#endif