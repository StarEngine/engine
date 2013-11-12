#pragma once

#include "../defines.h"
#include <algorithm>
#include <string>

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
	char* string_cast<char*, std::wstring>
		(const std::wstring & value);
	template <>
	char* string_cast<char*, std::string>
		(const std::string & value);
	template <>
	wchar_t* string_cast<wchar_t*, std::wstring>
		(const std::wstring & value);
	template <>
	wchar_t* string_cast<wchar_t*, std::string>
		(const std::string & value);
	
	template <>
	tstring string_cast<tstring, glm::vec2>
		(const glm::vec2 & value);

	template <>
	tstring string_cast<tstring, pos>
		(const pos & value);

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
	uint32 string_cast<uint32, tstring>
		(const tstring & value);

	template <>
	long string_cast<long, tstring>
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
	pos string_cast<pos, tstring>
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

	void ReadTextFile(const tstring & file, tstring & text,
			DirectoryMode directory = DirectoryMode::assets);
	tstring ReadTextFile(const tstring & file,
			DirectoryMode directory = DirectoryMode::assets);

	void WriteTextFile(const tstring & file, const tstring & text,
			DirectoryMode directory = DirectoryMode::assets);
	void AppendTextFile(const tstring & file, const tstring & text,
			DirectoryMode directory = DirectoryMode::assets);

	char * ReadBinaryFile(const tstring & file, uint32 & size,
			DirectoryMode directory = DirectoryMode::assets);
	void WriteBinaryFile(const tstring & file, char * buffer, uint32 size,
			DirectoryMode directory = DirectoryMode::assets);
	void AppendBinaryFile(const tstring & file, char * buffer, uint32 size,
			DirectoryMode directory = DirectoryMode::assets);

	template<class To, class From>
	To cast(From v)
	{
		return static_cast<To>(static_cast<void*>(v));
	}

	template <typename T>
	void WriteData(const tstring & file, T * buffer,
			DirectoryMode directory = DirectoryMode::assets)
	{
		auto dataSize = sizeof(T);
		char * dataBuffer = new char[dataSize];
		memcpy(dataBuffer, buffer, dataSize);
		WriteBinaryFile(file, dataBuffer, dataSize, directory);
		delete [] dataBuffer;
	}

	template <typename T>
	void ReadData(const tstring & file, T * buffer,
			DirectoryMode directory = DirectoryMode::assets)
	{
		uint32 dataSize = sizeof(T);
		char * dataBuffer = ReadBinaryFile(file, dataSize, directory);
		memcpy(buffer, dataBuffer, dataSize);
		delete [] dataBuffer;
	}

	template <typename T>
	void WriteDataArray(const tstring & file, T * buffer, uint32 size,
			DirectoryMode directory = DirectoryMode::assets)
	{
		auto dataSize = sizeof(T);
		char * dataBuffer = new char[size * dataSize];
		for(uint32 i = 0 ; i < size ; ++i)
		{
			char * data = new char[dataSize];
			memcpy(data, buffer[i], dataSize);
			for(uint32 u = 0 ; u < dataSize ; ++u)
			{
				dataBuffer[(i * dataSize) + u] = data[u];
			}
			delete [] data;
		}
		uint32 totalSize = sizeof(T) * size;
		WriteBinaryFile(file, dataBuffer, totalSize, directory);
		delete [] dataBuffer;
	}

	template <typename T>
	T * ReadDataArray(const tstring & file, uint32 size,
			DirectoryMode directory = DirectoryMode::assets)
	{
		uint32 dataSize = sizeof(T);
		uint32 totalSize = dataSize * size;
		char * dataBuffer = ReadBinaryFile(file, totalSize, directory);
		T * buffer = new T[size];
		for(uint32 i = 0 ; i < size ; ++i)
		{
			char * data = new char[dataSize];
			for(uint32 u = 0 ; u < dataSize ; ++u)
			{
				data[u] = dataBuffer[(i * dataSize) + u];
			}
			T temp;
			memcpy(&temp, data, dataSize);
			buffer[i] = temp;
			delete [] data;
		}
		delete [] dataBuffer;
		return buffer;
	}
}
