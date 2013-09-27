#pragma once

#include "..\defines.h"

namespace star
{
	const uint32 GenerateHash(const tstring & str);
	tchar* CharToTChar(const char* text);
	tchar* WCharToTChar(const wchar_t* text);
}