#pragma once

#include "definesCrossPlatform.h"

#ifdef _DEBUG
	#define ASSERT \
		if ( false ) {} \
		else \
		struct LocalAssert { \
				int32 mLine; \
				LocalAssert(int32 line=__LINE__) : mLine(line) {} \
				LocalAssert(bool isOK, const tstring & message = _T("")) { \
				if ( !isOK ) { \
				tstringstream buffer; \
				buffer  << _T("ERROR!! Assert failed on line ") \
						<< LocalAssert().mLine << _T(" in file \""); \
				buffer  << __FILE__ << _T("\", message: \"") \
						<< message << _T("\"\n"); \
				tprintf(buffer.str().c_str()); \
				__asm { int 3 } \
				} \
			} \
		} myAsserter = LocalAssert
#else
	#define ASSERT \
		if ( true ) {} else \
		struct NoAssert { \
				NoAssert(bool isOK, const tstring & message = _T("")) {} \
		} myAsserter = NoAssert
#endif
