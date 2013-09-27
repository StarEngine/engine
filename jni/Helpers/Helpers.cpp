#include "Helpers.h"

namespace star
{
	const uint32 GenerateHash(const tstring & str) 
	{
		uint32 hash(0);
		for(size_t i = 0; i < str.size(); ++i) 
			hash = 65599 * hash + str[i];
		return hash ^ (hash >> 16);
	}

	tchar* CharToTChar(const char* text)
	{
		if(std::is_same<char, tchar>::value)
		{
			return (tchar*)text;
		}
		else
		{
			std::string str_t(text);
			std::wstring str(str_t.begin(), str_t.end());
			return (tchar*)str.c_str();
		}
	}

	tchar* WCharToTChar(const wchar_t* text)
	{
		if(std::is_same<wchar_t, tchar>::value)
		{
			return (tchar*)text;
		}
		else
		{
			std::wstring str_t(text);
			std::string str(str_t.begin(), str_t.end());
			return (tchar*)str.c_str();
		}
	}
}