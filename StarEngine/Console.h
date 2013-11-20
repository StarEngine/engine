#pragma once

#include <process.h> //MT
#include <cstdlib> //rand()
#include <sys/stat.h> //file info
#include <atlbase.h> //CComPtr
#include <iostream>
#include <iosfwd>
#include <io.h>
#include <fcntl.h>

namespace WindowsConsole
{
	void RedirectIOToConsole();
}
 