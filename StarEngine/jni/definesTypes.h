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

typedef float		float32;
typedef double		float64;
typedef long double float128;

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#include <stdlib.h>
#include <minmax.h>
#include <tchar.h>
#endif

// unicode (widebyte) defines ( can be 2 or 4 bytes )
#define swstring std::wstring
#define swstringstream std::wstringstream
#define swofstream std::wofstream
#define swifstream std::wifstream
#define swfstream std::wfstream
#define swchar wchar_t
#define uswchar unsigned wchar_t
#define swcin std::wcin
#define swcout std::wcout
#define swprintf std::wprintf
#define swtof _wtof
#define swtoi _wtoi
#define swcslen wcslen
#ifdef _WIN32
	#define swfopen _wfopen_s
	#define SWSHFILEINFO SHFILEINFOW
#endif

// 2 byte defines 
#define sstring_16 std::basic_string<char16_t>
#define sstringstream_16 std::basic_stringstream<char16_t>
#define sofstream_16 std::basic_ofstream<char16_t>
#define sifstream_16 std::basic_ifstream<char16_t>
#define sfstream_16 std::basic_fstream<char16_t>
#define schar_16 char16_t
#define uschar_16 unsigned char16_t

// singlebyte defines ( 1 byte )
#define sstring std::string
#define scin std::cin
#define scout std::cout
#define sstringstream std::stringstream
#define sofstream std::ofstream
#define sifstream std::ifstream
#define sfstream std::fstream
#define schar char
#define suchar unsigned schar
#define sprintf std::printf
#define satof atof
#define satoi atoi
#define sstrlen strlen
#ifdef _WIN32
	#define sfopen fopen_s
	#define SSHFILEINFO SHFILEINFOA
#endif

#ifdef _T
	#undef _T
#endif

#ifdef _TEXT
	#undef _TEXT
#endif

#ifdef _UNICODE
	#define tstring swstring
	#define tcin swcin
	#define tcout swcout
	#define tstringstream swstringstream
	#define tofstream swofstream
	#define tifstream swifstream
	#define tfstream swfstream
	#define tchar swchar
	#define tuchar uswchar
	#define tprintf swprintf
	#define ttof swtof
	#define ttoi swtoi
	#define tstrlen swcslen
	#define _T(x) L ## x
	#define _TEXT(x) L ## x
	#ifdef _WIN32
		#define tfopen swfopen
		#define TSHFILEINFO SWSHFILEINFO
	#endif
#else
	#define tstring sstring
	#define tcin scin
	#define tcout scout
	#define tstringstream sstringstream
	#define tofstream sofstream
	#define tifstream sifstream
	#define tfstream sfstream
	#define tchar schar
	#define tuchar suchar
	#define tprintf sprintf
	#define ttof satof
	#define ttoi satoi
	#define tstrlen sstrlen
	#define _T(x) x
	#define _TEXT(x) x
	#ifdef _WIN32
		#define tfopen sfopen
		#define TSHFILEINFO SSHFILEINFO
	#endif
#endif

/// <summary>
/// A small struct that can be used to represent an array of objects
/// and a number that represents the amount of elements in the array.
/// </summary>
template <typename T, typename U = uint8>
struct PointerArray
{
	  U amount;
	  T * elements;
};
