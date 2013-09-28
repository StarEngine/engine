#pragma once

#include "..\defines.h"
#include <algorithm>

namespace star
{
	const uint32 GenerateHash(const tstring & str);

	template < typename TReturnValue, typename TValue>
	TReturnValue string_cast(const TValue & value)
	{
		tstringstream strstr;
		strstr << value;
		return strstr.str();
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
	
	template <>
	tstring string_cast<tstring, glm::vec2>
		(const glm::vec2 & value);

	template <>
	tstring string_cast<tstring, glm::vec3>
		(const glm::vec3 & value);

	template <>
	tstring string_cast<tstring, glm::vec4>
		(const glm::vec4 & value);

	template <>
	tstring string_cast<tstring, glm::quat>
		(const glm::quat & value);

	template <>
	bool string_cast<bool, tstring>
		(const tstring & value);

	template <>
	int string_cast<int, tstring>
		(const tstring & value);

	template <>
	float string_cast<float, tstring>
		(const tstring & value);

	template <>
	double string_cast<double, tstring>
		(const tstring & value);

	template <>
	glm::vec2 string_cast<glm::vec2, tstring>
		(const tstring & value);

	template <>
	glm::vec3 string_cast<glm::vec3, tstring>
		(const tstring & value);

	template <>
	glm::vec4 string_cast<glm::vec4, tstring>
		(const tstring & value);

	template <>
	glm::quat string_cast<glm::quat, tstring>
		(const tstring & value);
}
