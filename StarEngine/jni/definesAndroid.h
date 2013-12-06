#pragma once

#ifdef ANDROID

#include <stdint.h>

typedef uint8_t		BYTE, byte;
typedef uint8_t *        PBYTE;

/// <summary>
/// A point data structure that contains 2 integer values
/// representing the x and y values of a position.
/// </summary>
typedef struct myPoint
{
	int32_t  x;
	int32_t  y;
} POINT;

#include <android/log.h>

//#define _T(x) x

#ifndef NDEBUG
#define ASSERT \
	if ( false ) {} \
	else \
	struct LocalAssert { \
		int32 mLine; \
		LocalAssert(int32 line=__LINE__) : mLine(line) {} \
		LocalAssert(bool isOK, const tchar* message=_T("")) { \
		if ( !isOK ) { \
		tstringstream buffer; \
		buffer << _T("ERROR!! Assert failed on line ") << LocalAssert().mLine << _T(" in file '") << __FILE__ << std::endl << _T("Message: \"") << message << _T("\"\n"); \
		__android_log_assert(_T("ASSERT"), STARENGINE_LOG_TAG, "%s", buffer.str().c_str()); \
		} \
	} \
	} myAsserter = LocalAssert
	#define ASSERTC \
		if ( false ) {} \
	else \
	struct LocalAssert { \
		int32 mLine; \
		LocalAssert(int32 line=__LINE__) : mLine(line) {} \
		LocalAssert(bool isOK, const schar* message="") { \
		if ( !isOK ) { \
		sstringstream buffer; \
		buffer << "ERROR!! Assert failed on line " << LocalAssert().mLine << " in file '" << __FILE__ << std::endl << "Message: \"" << message << "\"\n"; \
		__android_log_assert("ASSERT", STARENGINE_LOG_TAG, "%s", buffer.str().c_str()); \
		} \
	} \
	} myAsserter = LocalAssert
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

#endif
