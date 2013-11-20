#pragma once

#include "../defines.h"
#include <algorithm>
#include <string>
#include <functional>

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
	sstring_16 string_cast<sstring_16, sstring_16>
		(const sstring_16 & value);
	template <>
	sstring_16 string_cast<sstring_16, swstring>
		(const swstring & value);
	template <>
	sstring_16 string_cast<sstring_16, sstring>
		(const sstring & value);
	template <>
	swstring string_cast<swstring, sstring_16>
		(const sstring_16 & value);
	template <>
	sstring string_cast<sstring, sstring_16>
		(const sstring_16 & value);

	template <>
	swstring string_cast<swstring, swstring>
		(const swstring & value);
	template <>
	sstring string_cast<sstring, sstring>
		(const sstring & value);
	template <>
	sstring string_cast<sstring, swstring>
		(const swstring & value);
	template <>
	swstring string_cast<swstring, sstring>
		(const sstring & value);

	template < typename TReturnValue, typename TValue>
	TReturnValue string_cast(const TValue * value)
	{
		ASSERT(false, _T("Invalid String cast: No implementation found that match these parameters!"));
		return TReturnValue();
	}

	template <>
	sstring_16 string_cast<sstring_16, schar_16>
		(const schar_16 * value);
	template <>
	sstring_16 string_cast<sstring_16, swchar>
		(const swchar * value);
	template <>
	sstring_16 string_cast<sstring_16, schar>
		(const schar * value);
	template <>
	schar_16 * string_cast<schar_16*, sstring_16>
		(const sstring_16 & value);
	template <>
	swchar * string_cast<swchar*, sstring_16>
		(const sstring_16 & value);
	template <>
	schar * string_cast<schar*, sstring_16>
		(const sstring_16 & value);

	template <>
	sstring string_cast<sstring, schar_16>
		(const schar_16 * value);
	template <>
	swstring string_cast<swstring, schar_16>
		(const schar_16 * value);
	template <>
	schar_16* string_cast<schar_16*, sstring>
		(const sstring & value);
	template <>
	schar_16* string_cast<schar_16*, swstring>
		(const swstring & value);

	template <>
	swstring string_cast<swstring, swchar>
		(const swchar * value);
	template <>
	sstring string_cast<sstring, schar>
		(const schar * value);
	template <>
	sstring string_cast<sstring, swchar>
		(const swchar * value);
	template <>
	swstring string_cast<swstring, schar>
		(const schar * value);

	template <>
	schar* string_cast<schar*, swstring>
		(const swstring & value);
	template <>
	schar* string_cast<schar*, sstring>
		(const sstring & value);
	template <>
	swchar* string_cast<swchar*, swstring>
		(const swstring & value);
	template <>
	swchar* string_cast<swchar*, sstring>
		(const sstring & value);

	template <>
	swchar* string_cast<swchar*, schar>
		(const schar * value);
	template <>
	swchar* string_cast<swchar*, swchar>
		(const swchar * value);
	template <>
	schar* string_cast<schar*, swchar>
		(const swchar * value);
	template <>
	schar* string_cast<schar*, schar>
		(const schar * value);

	template <>
	schar_16* string_cast<schar_16*, schar>
		(const schar * value);
	template <>
	schar_16* string_cast<schar_16*, swchar>
		(const swchar * value);
	template <>
	schar* string_cast<schar*, schar_16>
		(const schar_16 * value);
	template <>
	swchar* string_cast<swchar*, schar_16>
		(const schar_16 * value);
	
	template <>
	tstring string_cast<tstring, fvec2>
		(const fvec2 & value);

	template <>
	tstring string_cast<tstring, pos>
		(const pos & value);

	template <>
	tstring string_cast<tstring, fvec3>
		(const fvec3 & value);

	template <>
	tstring string_cast<tstring, fvec4>
		(const fvec4 & value);

	template <>
	tstring string_cast<tstring, fquat>
		(const fquat & value);
	
	template <>
	tstring string_cast<tstring, dvec2>
		(const dvec2 & value);

	template <>
	tstring string_cast<tstring, dvec3>
		(const dvec3 & value);

	template <>
	tstring string_cast<tstring, dvec4>
		(const dvec4 & value);

	template <>
	tstring string_cast<tstring, dquat>
		(const dquat & value);
	
	template <>
	tstring string_cast<tstring, ivec2>
		(const ivec2 & value);

	template <>
	tstring string_cast<tstring, ivec3>
		(const ivec3 & value);

	template <>
	tstring string_cast<tstring, ivec4>
		(const ivec4 & value);
	
	template <>
	tstring string_cast<tstring, uvec2>
		(const uvec2 & value);

	template <>
	tstring string_cast<tstring, uvec3>
		(const uvec3 & value);

	template <>
	tstring string_cast<tstring, uvec4>
		(const uvec4 & value);

	template <>
	bool string_cast<bool, tstring>
		(const tstring & value);

	template <>
	int32 string_cast<int32, tstring>
		(const tstring & value);

	template <>
	uint32 string_cast<uint32, tstring>
		(const tstring & value);

	template <>
	long string_cast<long, tstring>
		(const tstring & value);

	template <>
	float32 string_cast<float32, tstring>
		(const tstring & value);

	template <>
	float64 string_cast<float64, tstring>
		(const tstring & value);

	template <>
	fvec2 string_cast<fvec2, tstring>
		(const tstring & value);

	template <>
	pos string_cast<pos, tstring>
		(const tstring & value);

	template <>
	fvec3 string_cast<fvec3, tstring>
		(const tstring & value);

	template <>
	fvec4 string_cast<fvec4, tstring>
		(const tstring & value);

	template <>
	fquat string_cast<fquat, tstring>
		(const tstring & value);

	template <>
	dvec2 string_cast<dvec2, tstring>
		(const tstring & value);

	template <>
	dvec3 string_cast<dvec3, tstring>
		(const tstring & value);

	template <>
	dvec4 string_cast<dvec4, tstring>
		(const tstring & value);

	template <>
	dquat string_cast<dquat, tstring>
		(const tstring & value);

	template <>
	ivec2 string_cast<ivec2, tstring>
		(const tstring & value);

	template <>
	ivec3 string_cast<ivec3, tstring>
		(const tstring & value);

	template <>
	ivec4 string_cast<ivec4, tstring>
		(const tstring & value);

	template <>
	uvec2 string_cast<uvec2, tstring>
		(const tstring & value);

	template <>
	uvec3 string_cast<uvec3, tstring>
		(const tstring & value);

	template <>
	uvec4 string_cast<uvec4, tstring>
		(const tstring & value);

	void ReadTextFile(const tstring & file, tstring & text,
			DirectoryMode directory = DirectoryMode::assets);
	tstring ReadTextFile(const tstring & file,
			DirectoryMode directory = DirectoryMode::assets);

	void WriteTextFile(const tstring & file, const tstring & text,
			DirectoryMode directory = DirectoryMode::assets);
	void AppendTextFile(const tstring & file, const tstring & text,
			DirectoryMode directory = DirectoryMode::assets);

	schar * ReadBinaryFile(const tstring & file, uint32 & size,
			DirectoryMode directory = DirectoryMode::assets);
	void WriteBinaryFile(const tstring & file, schar * buffer, uint32 size,
			DirectoryMode directory = DirectoryMode::assets);
	void AppendBinaryFile(const tstring & file, schar * buffer, uint32 size,
			DirectoryMode directory = DirectoryMode::assets);

	schar * DecryptBinaryFile(const tstring & file, uint32 & size,
		const std::function<schar*(const schar*, uint32&)> & decrypter, 
		DirectoryMode directory = DirectoryMode::assets);
	void EncryptBinaryFile(const tstring & file, schar * buffer, uint32 size,
		const std::function<schar*(const schar*, uint32&)> & encrypter, 
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
		schar * dataBuffer = new schar[dataSize];
		memcpy(dataBuffer, buffer, dataSize);
		WriteBinaryFile(file, dataBuffer, dataSize, directory);
		delete [] dataBuffer;
	}

	template <typename T>
	void ReadData(const tstring & file, T * buffer,
			DirectoryMode directory = DirectoryMode::assets)
	{
		uint32 dataSize = sizeof(T);
		schar * dataBuffer = ReadBinaryFile(file, dataSize, directory);
		memcpy(buffer, dataBuffer, dataSize);
		delete [] dataBuffer;
	}

	template <typename T>
	void WriteDataArray(const tstring & file, T * buffer, uint32 size,
			DirectoryMode directory = DirectoryMode::assets)
	{
		auto dataSize = sizeof(T);
		schar * dataBuffer = new schar[size * dataSize];
		for(uint32 i = 0 ; i < size ; ++i)
		{
			schar * data = new schar[dataSize];
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
		schar * dataBuffer = ReadBinaryFile(file, totalSize, directory);
		T * buffer = new T[size];
		for(uint32 i = 0 ; i < size ; ++i)
		{
			schar * data = new schar[dataSize];
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

	template <typename T>
	void EncryptData(const tstring & file, T * buffer,
		const std::function<schar*(const schar*, uint32&)> & encrypter, 
		DirectoryMode directory = DirectoryMode::assets)
	{
		auto dataSize = sizeof(T);
		schar * dataBuffer = new schar[dataSize];
		memcpy(dataBuffer, buffer, dataSize);
		EncryptBinaryFile(file, dataBuffer, dataSize, encrypter, directory);
		delete [] dataBuffer;
	}

	template <typename T>
	void DecryptData(const tstring & file, T * buffer,
		const std::function<schar*(const schar*, uint32&)> & decrypter, 
		DirectoryMode directory = DirectoryMode::assets)
	{
		uint32 dataSize = sizeof(T);
		schar * dataBuffer = DecryptBinaryFile(file, dataSize, decrypter, directory);
		memcpy(buffer, dataBuffer, dataSize);
		delete [] dataBuffer;
	}

	template <typename T>
	void EncryptDataArray(const tstring & file, T * buffer, uint32 size,
		const std::function<schar*(const schar*, uint32&)> & encrypter,
		DirectoryMode directory = DirectoryMode::assets)
	{
		auto dataSize = sizeof(T);
		schar * dataBuffer = new schar[size * dataSize];
		for(uint32 i = 0 ; i < size ; ++i)
		{
			schar * data = new schar[dataSize];
			memcpy(data, buffer[i], dataSize);
			for(uint32 u = 0 ; u < dataSize ; ++u)
			{
				dataBuffer[(i * dataSize) + u] = data[u];
			}
			delete [] data;
		}
		uint32 totalSize = sizeof(T) * size;
		EncryptBinaryFile(file, dataBuffer, totalSize, encrypter, directory);
		delete [] dataBuffer;
	}

	template <typename T>
	T * DecryptDataArray(const tstring & file, uint32 size,
		const std::function<schar*(const schar*, uint32&)> & decrypter,
		DirectoryMode directory = DirectoryMode::assets)
	{
		uint32 dataSize = sizeof(T);
		uint32 totalSize = dataSize * size;
		schar * dataBuffer = DecryptBinaryFile(file, totalSize, decrypter, directory);
		T * buffer = new T[size];
		for(uint32 i = 0 ; i < size ; ++i)
		{
			schar * data = new schar[dataSize];
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
