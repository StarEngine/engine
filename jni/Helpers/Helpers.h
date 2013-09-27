#pragma once

#include "..\defines.h"

namespace star
{
	const uint32 GenerateHash(const tstring & str);

	template < typename TReturnValue, typename TValue>
	TReturnValue string_cast(const TValue & value)
	{
		ASSERT(false, _T("Invalid String cast: No implementation found that match these parameters!"));
		return TReturnValue();
	}

	template <>
	std::wstring string_cast<std::wstring, std::wstring>
		(const std::wstring & value);
	template <>
	std::string string_cast<std::string, std::string>
		(const std::string & value);
	template <>
	std::string string_cast<std::string, std::wstring>
		(const std::wstring & value);
	template <>
	std::wstring string_cast<std::wstring, std::string>
		(const std::string & value);

	template < typename TReturnValue, typename TValue>
	TReturnValue string_cast(const TValue * value)
	{
		ASSERT(false, _T("Invalid String cast: No implementation found that match these parameters!"));
		return TReturnValue();
	}

	template <>
	std::wstring string_cast<std::wstring, wchar_t>
		(const wchar_t * value);
	template <>
	std::string string_cast<std::string, char>
		(const char * value);
	template <>
	std::string string_cast<std::string, wchar_t>
		(const wchar_t * value);
	template <>
	std::wstring string_cast<std::wstring, char>
		(const char * value);
}