#include "../defines.h"
#include <algorithm>
#include <string>
#include <functional>
#include "../Logger.h"

namespace star
{
	template < typename T>
	T CalculateSmallestElem(
		const T * vec, 
		uint8 size
		)
	{
		Logger::GetInstance()->Log(size != 0,
			_T("You can't calculate the minimum of 0 elements!"),
			STARENGINE_LOG_TAG);
		float32 minimum = vec[0];
		for(int32 i = 1; i < size; ++i)
		{
			if(vec[i] < minimum)
			{
				minimum = vec[i];
			}
		}
		return minimum;
	}

	template < typename T>
	T CalculateLargestElem(
		const T * vec, 
		uint8 size
		)
	{
		Logger::GetInstance()->Log(size != 0, 
			_T("You can't calculate the maximum of 0 elements!"),
			STARENGINE_LOG_TAG);
		float32 maximum = vec[0];
		for(int32 i = 1; i < size; ++i)
		{
			if(vec[i] > maximum)
			{
				maximum = vec[i];
			}
		}
		return maximum;
	}

	template < typename TReturnValue, typename TValue>
	TReturnValue string_cast(const TValue & value)
	{
		tstringstream strstr;
		strstr << value;
		return strstr.str();
	}

	template < typename TReturnValue, typename TValue>
	TReturnValue string_cast(const TValue * value)
	{
		Logger::GetInstance()->Log(false,
			_T("Invalid String cast: No implementation found that match these parameters!"),
			STARENGINE_LOG_TAG);
		return TReturnValue();
	}

	template<class To, class From>
	To cast(From v)
	{
		return static_cast<To>(static_cast<void*>(v));
	}

	template <typename T>
	void WriteData(const tstring & file, T * buffer,
			DirectoryMode directory)
	{
		auto dataSize = sizeof(T);
		schar * dataBuffer = new schar[dataSize];
		memcpy(dataBuffer, buffer, dataSize);
		WriteBinaryFile(file, dataBuffer, dataSize, directory);
		delete [] dataBuffer;
	}

	template <typename T>
	void ReadData(const tstring & file, T * buffer,
			DirectoryMode directory)
	{
		uint32 dataSize = sizeof(T);
		schar * dataBuffer = ReadBinaryFile(file, dataSize, directory);
		memcpy(buffer, dataBuffer, dataSize);
		delete [] dataBuffer;
	}

	template <typename T>
	void WriteDataArray(const tstring & file, T * buffer, uint32 size,
			DirectoryMode directory)
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
			DirectoryMode directory)
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
		DirectoryMode directory)
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
		DirectoryMode directory)
	{
		uint32 dataSize = sizeof(T);
		schar * dataBuffer = DecryptBinaryFile(file, dataSize, decrypter, directory);
		memcpy(buffer, dataBuffer, dataSize);
		delete [] dataBuffer;
	}

	template <typename T>
	void EncryptDataArray(const tstring & file, T * buffer, uint32 size,
		const std::function<schar*(const schar*, uint32&)> & encrypter,
		DirectoryMode directory)
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
		DirectoryMode directory)
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
