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

	template <>
	tstring string_cast<tstring, glm::vec2>
		(const glm::vec2 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, glm::vec3>
		(const glm::vec3 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, glm::vec4>
		(const glm::vec4 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z << _T(";");
		strstr << value.w;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, glm::quat>
		(const glm::quat & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z << _T(";");
		strstr << value.w;
		return strstr.str();
	}

	template <>
	bool string_cast<bool, tstring>
		(const tstring & value)
	{
		tstring val(value);
		transform(val.begin(), val.end(), val.begin(), ::tolower);
		return val[0] == _T('t');
	}

	template <>
	int string_cast<int, tstring>
		(const tstring & value)
	{
		return ttoi(value.c_str());
	}

	template <>
	float string_cast<float, tstring>
		(const tstring & value)
	{
		return static_cast<float>(ttof(value.c_str()));
	}

	template <>
	double string_cast<double, tstring>
		(const tstring & value)
	{
		return ttof(value.c_str());
	}

	template <>
	glm::vec2 string_cast<glm::vec2, tstring>
		(const tstring & value)
	{
		glm::vec2 vec;
		int index = value.find(';',0);
		vec.x = string_cast<float>(value.substr(0, index));
		vec.y = string_cast<float>(value.substr(++index,value.size()-index));
		return vec;
	}

	template <>
	glm::vec3 string_cast<glm::vec3, tstring>
		(const tstring & value)
	{
		glm::vec3 vec;
		int index = value.find(';', 0);
		vec.x = string_cast<float>(value.substr(0, index));
		int index2 = value.find(';', ++index);
		vec.y = string_cast<float>(value.substr(index, index2 - index));
		vec.z = string_cast<float>(value.substr(++index2, value.size() - index2));
		return vec;
	}

	template <>
	glm::vec4 string_cast<glm::vec4, tstring>
		(const tstring & value)
	{
		glm::vec4 vec;
		int index = value.find(';', 0);
		vec.x = string_cast<float>(value.substr(0, index));
		int index2 = value.find(';', ++index);
		vec.y = string_cast<float>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		vec.z = string_cast<float>(value.substr(index2, index - index2));
		vec.w = string_cast<float>(value.substr(++index, value.size() - index));
		return vec;
	}

	template <>
	glm::quat string_cast<glm::quat, tstring>
		(const tstring & value)
	{
		glm::quat quat;
		int index = value.find(';', 0);
		quat.x = string_cast<float>(value.substr(0, index));
		int index2 = value.find(';', ++index);
		quat.y = string_cast<float>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		quat.z = string_cast<float>(value.substr(index2, index - index2));
		quat.w = string_cast<float>(value.substr(++index, value.size() - index));
		return quat;
	}
}