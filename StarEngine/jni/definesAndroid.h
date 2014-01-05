#pragma once

#ifdef ANDROID

#include <stdint.h>

typedef uint8_t BYTE, byte;
typedef uint8_t PBYTE;

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
#include "definesCrossPlatform.h"

#ifdef _DEBUG
	#define ASSERT \
		if ( false ) {} \
		else \
		struct localAssert \
		{ \
			localAssert(bool isOk, const tstring & message) \
			{ \
				if(isOk) \
				{ \
					BreakInformation info = BREAK_INFO(); \
					tstringstream buffer; \
					buffer	<< _T("ERROR!! Assert failed on line ") \
							<< info.line << _T(" in file '") \
							<< info.file << _T("', message: \"") \
							<< message << _T("\"\n"); \
					__android_log_assert( \
						_T("ASSERT"), \
						STARENGINE_LOG_TAG.c_str(), \
						"%s", \
						buffer.str().c_str() \
						); \
				} \
			} \
		} myAssert = localAssert
#else
	#define ASSERT(...) (void(0))
#endif
#endif
