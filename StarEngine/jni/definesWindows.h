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
		int32 mLine; \
		LocalAssert(int32 line=__LINE__) : mLine(line) {} \
		LocalAssert(bool isOK, const schar* message="") { \
		if ( !isOK ) { \
		sstringstream buffer; \
		buffer << "ERROR!! Assert failed on line " << LocalAssert().mLine << " in file '" << __FILE__ << "'\\Message: \"" << message << "\"\n"; \
		sprintf(buffer.str().c_str()); \
		__asm int 3 \
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
