#pragma once

#include "definesCrossPlatform.h"

#ifdef _DEBUG
	#define ASSERT(a, m) \
		{ \
			bool isOk(a); \
			auto info = BREAK_INFO(); \
			if(!isOk) \
			{ \
				tstringstream buffer; \
				buffer	<< _T("ERROR!! Assert failed on line ") \
						<< info.line << _T(" in file '") \
						<< info.file << _T("', message: \"") \
						<< m << _T("\"\n"); \
				tprintf(buffer.str().c_str()); \
				__asm { int 3 } \
			} \
		}
#else
	#define ASSERT(...) (void(0))
#endif
