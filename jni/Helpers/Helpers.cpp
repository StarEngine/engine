#include "Helpers.h"
#include "..\Logger.h"

namespace star
{
	const uint32 GenerateHash(const tstring & str) 
	{
		uint32 hash(0);
		for(size_t i = 0; i < str.size(); ++i) 
		{
			hash = 65599 * hash + str[i];
		}
		return hash ^ (hash >> 16);
	}

	template <>
	std::wstring string_cast<std::wstring, std::wstring>
		(const std::wstring & value) { return value; }

	template <>
	std::string string_cast<std::string, std::string>
		(const std::string & value) { return value; }

	template <>
	std::string string_cast<std::string, std::wstring>
		(const std::wstring & value)
	{
		std::string ss;
		ss.assign(value.begin(), value.end());
		return ss;
	}

	template <>
	std::wstring string_cast<std::wstring, std::string>
		(const std::string & value)
	{
		std::wstring ss;
		ss.assign(value.begin(), value.end());
		return ss;
	}

	template <>
	std::wstring string_cast<std::wstring, wchar_t>
		(const wchar_t * value)
	{
		return string_cast<std::wstring, std::wstring>(value);
	}

	template <>
	std::string string_cast<std::string, char>
		(const char * value)
	{
		return string_cast<std::string, std::string>(value);
	}

	template <>
	std::string string_cast<std::string, wchar_t>
		(const wchar_t * value)
	{
		return string_cast<std::string, std::wstring>(value);
	}

	template <>
	std::wstring string_cast<std::wstring, char>
		(const char * value)
	{
		return string_cast<std::wstring, std::string>(value);
	}
}