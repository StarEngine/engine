#pragma once

#include <stdint.h>

typedef int64_t 	int64;
typedef int32_t 	int32;
typedef int16_t 	int16;
typedef int8_t 		int8;

typedef uint64_t	uint64;
typedef uint32_t 	uint32;
typedef uint16_t 	uint16;
typedef uint8_t 	uint8;

typedef int8_t status;

const status STATUS_OK 		= 0;
const status STATUS_KO 		= -1;
const status STATUS_EXIT 	= -2;

#include <string.h>		
#include <sstream>
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#include <stdlib.h>
#include <minmax.h>
#include <tchar.h>
#endif

// Extra unicode defines
#ifdef _UNICODE
	#define tstring std::wstring
	#define tcin std::wcin
	#define tcout std::wcout
	#define tstringstream std::wstringstream
	#define tofstream std::wofstream
	#define tifstream std::wifstream
	#define tfstream std::wfstream
	#define to_tstring std::to_wstring
	#define tchar wchar_t
	#define tuchar unsigned std::char
	#define tprintf std::wprintf
#else
	#define tstring std::string
	#define tcin std::cin
	#define tcout std::cout
	#define tstringstream std::stringstream
	#define tofstream std::ofstream
	#define tifstream std::ifstream
	#define tfstream std::fstream
	#define to_tstring std::to_string
	#define tchar std::char
	#define tuchar unsigned std::char
	#define tprintf std::printf
#endif

#ifndef _WIN32
#define _T(x) x
#endif

using std::min;
using std::max;

//OpenGL Math Library
#include "Helpers\glm\glm.h"
#include "Helpers\glm\ext.hpp"

using glm::vec3;
using glm::quat;
using glm::mat4x4;
