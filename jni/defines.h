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

#ifndef _WIN32
typedef uint8_t		BYTE, byte;
typedef uint8_t *        PBYTE;

typedef struct myPoint
{
    int32_t  x;
    int32_t  y;
} POINT;
#endif

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
#else
#include <android/log.h>
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
	#define ttof _wtof
	#define ttoi _wtoi
#else
	#define tstring std::string
	#define tcin std::cin
	#define tcout std::cout
	#define tstringstream std::stringstream
	#define tofstream std::ofstream
	#define tifstream std::ifstream
	#define tfstream std::fstream
	#define to_tstring std::to_string
	#define tchar char
	#define tuchar unsigned char
	#define tprintf std::printf
	#define ttof atof
	#define ttoi atoi
#endif

#ifndef _WIN32
#define _T(x) x
#endif

#include <algorithm>

using std::min;
using std::max;

//OpenGL Math Library
#include "Helpers\glm\glm.h"
#include "Helpers\glm\ext.hpp"

using glm::vec2;
using glm::vec3;
using glm::quat;
using glm::mat4x4;

#define EMPTY_STRING _T("")
#define ANDROID_LOG_TAG _T("STAR_ENGINE")

#ifndef NDEBUG
#ifdef _WIN32
	#define ASSERT \
		if ( false ) {} \
	else \
	struct LocalAssert { \
		int mLine; \
		LocalAssert(int line=__LINE__) : mLine(line) {} \
		LocalAssert(bool isOK, const tchar* message=_T("")) { \
		if ( !isOK ) { \
		tstringstream buffer; \
		buffer << _T("ERROR!! Assert failed on line ") << LocalAssert().mLine << _T(" in file '") << __FILE__ << _T("'\\Message: \"") << message << _T("\"\n"); \
		tprintf(buffer.str().c_str()); \
		__asm { int 3 } \
		} \
	} \
	} myAsserter = LocalAssert
	#define ASSERTC \
		if ( false ) {} \
	else \
	struct LocalAssert { \
		int mLine; \
		LocalAssert(int line=__LINE__) : mLine(line) {} \
		LocalAssert(bool isOK, const char* message="") { \
		if ( !isOK ) { \
		std::stringstream buffer; \
		buffer << "ERROR!! Assert failed on line " << LocalAssert().mLine << " in file '" << __FILE__ << "'\\Message: \"" << message << "\"\n"; \
		std::printf(buffer.str().c_str()); \
		__asm int 3 \
		} \
	} \
	} myAsserter = LocalAssert
#else
#define ASSERT \
	if ( false ) {} \
	else \
	struct LocalAssert { \
		int mLine; \
		LocalAssert(int line=__LINE__) : mLine(line) {} \
		LocalAssert(bool isOK, const tchar* message=_T("")) { \
		if ( !isOK ) { \
		tstringstream buffer; \
		buffer << _T("ERROR!! Assert failed on line ") << LocalAssert().mLine << _T(" in file '") << __FILE__ << std::endl << _T("Message: \"") << message << _T("\"\n"); \
		__android_log_print(ANDROID_LOG_ERROR, ANDROID_LOG_TAG, "%s", buffer.str().c_str()); \
		} \
	} \
	} myAsserter = LocalAssert
	#define ASSERTC \
		if ( false ) {} \
	else \
	struct LocalAssert { \
		int mLine; \
		LocalAssert(int line=__LINE__) : mLine(line) {} \
		LocalAssert(bool isOK, const char* message="") { \
		if ( !isOK ) { \
		std::stringstream buffer; \
		buffer << "ERROR!! Assert failed on line " << LocalAssert().mLine << " in file '" << __FILE__ << std::endl << "Message: \"" << message << "\"\n"; \
		__android_log_print(ANDROID_LOG_ERROR, ANDROID_LOG_TAG, "%s", buffer.str().c_str()); \
		} \
	} \
	} myAsserter = LocalAssert
#endif
#else
#define ASSERT \
	if ( true ) {} else \
struct NoAssert { \
	NoAssert(bool isOK, const tchar* message=_T("")) {} \
} myAsserter = NoAssert
#define ASSERTC \
	if ( true ) {} else \
struct NoAssert { \
	NoAssert(bool isOK, const tchar* message=_T("")) {} \
} myAsserter = NoAssert
#endif
