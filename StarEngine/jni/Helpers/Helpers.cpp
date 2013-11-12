#include "Helpers.h"
#include "..\Logger.h"
#include "Filepath.h"
#include <iostream>
#include <fstream>
#include <string>

#ifdef ANDROID
#include "HelpersAndroid.h"
#include "../StarEngine.h"
#endif

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
	char* string_cast<char*, std::wstring>
		(const std::wstring & value)
	{
		char * result = 
			const_cast<char*>(
				string_cast<std::string, std::wstring>(value).c_str()
				);
		return result;
	}

	template <>
	char* string_cast<char*, std::string>
		(const std::string & value)
	{
		char * result = 
			const_cast<char*>(value.c_str());
		return result;
	}

	template <>
	wchar_t* string_cast<wchar_t*, std::wstring>
		(const std::wstring & value)
	{
		wchar_t * result = 
			const_cast<wchar_t*>(value.c_str());
		return result;
	}

	template <>
	wchar_t* string_cast<wchar_t*, std::string>
		(const std::string & value)
	{
		wchar_t * result = 
			const_cast<wchar_t*>(
				string_cast<std::wstring, std::string>(value).c_str()
				);
		return result;
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
	tstring string_cast<tstring, pos>
		(const pos & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.l;
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
	uint32 string_cast<uint32, tstring>
		(const tstring & value)
	{
		return uint32(string_cast<int>(value));
	}

	template <>
	long string_cast<long, tstring>
		(const tstring & value)
	{
		return static_cast<long>(ttoi(value.c_str()));
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
	pos string_cast<pos, tstring>
		(const tstring & value)
	{
		pos pos;
		int index = value.find(';', 0);
		pos.x = string_cast<float>(value.substr(0, index));
		int index2 = value.find(';', ++index);
		pos.y = string_cast<float>(value.substr(index, index2 - index));
		pos.l = lay(string_cast<int32>(value.substr(++index2, value.size() - index2)));
		return pos;
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

	void ReadTextFile(const tstring & file, tstring & text,
			DirectoryMode directory)
	{
#ifdef ANDROID
		if(directory == DirectoryMode::assets)
		{
			SerializedData data;
			star_a::ReadFileAsset(file, data);
			text = string_cast<tstring>(data.data);
			delete [] data.data;
		}
		else
		{
			text = _T("");
			auto app = StarEngine::GetInstance()->GetAndroidApp();
			std::stringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<std::string>(file);

			std::ifstream myfile;
			myfile.open(strstr.str(), std::ios::in);
			bool succes = myfile.is_open();
			ASSERT(succes, (_T("Couldn't open the text file '") +
					strstr.str() + _T("'.")).c_str());
			if(succes)
			{
				std::string str;
				while (std::getline(myfile,str))
				{
					text += str;
				}
				myfile.close();
			}
		}
#else
		tifstream myfile;
		tstring file_path(EMPTY_STRING);
		Filepath::GetCorrectPath(file, file_path, directory);
		myfile.open(file_path, std::ios::in);
		bool succes = myfile.is_open();
		ASSERT(succes, (_T("Couldn't open the text file '") + file_path + _T("'.")).c_str());
		if(succes)
		{
			tstring str;
			while (std::getline(myfile,str))
			{
				text += str;
			}
			myfile.close();
		}
#endif
	}

	tstring ReadTextFile(const tstring & file, DirectoryMode directory)
	{
		tstring text;
		ReadTextFile(file, text, directory);
		return text;
	}

	void WriteTextFile(const tstring & file, const tstring & text,
			DirectoryMode directory)
	{
#ifdef ANDROID
		bool succesfull = directory != DirectoryMode::assets;
		ASSERT(succesfull, _T("Android doesn't support writing to a text file in the assets directory."));
		if(succesfull)
		{
			auto app = StarEngine::GetInstance()->GetAndroidApp();
			std::stringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<std::string>(file);
			std::ofstream myfile(strstr.str(), std::ios::out);
			succesfull = myfile.is_open();
			ASSERT(succesfull, (_T("Couldn't open the text file '") + strstr.str() + _T("'.")).c_str());
			if(succesfull)
			{
				myfile << text;
				myfile.close();
			}
		}
#else
		tstring file_path(EMPTY_STRING);
		Filepath::GetCorrectPath(file, file_path, directory);
		tofstream myfile(file_path, std::ios::out);
		bool succes = myfile.is_open();
		ASSERT(succes, (_T("Couldn't open the text file '") + file_path + _T("'.")).c_str());
		if(succes)
		{
			myfile << text;
			myfile.close();
		}
#endif
	}

	void AppendTextFile(const tstring & file, const tstring & text,
			DirectoryMode directory)
	{
#ifdef ANDROID
		bool succesfull = directory != DirectoryMode::assets;
		ASSERT(succesfull, _T("Android doesn't support writing to a text file in the assets directory."));
		if(succesfull)
		{
			auto app = StarEngine::GetInstance()->GetAndroidApp();
			std::stringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<std::string>(file);
			std::ofstream myfile(strstr.str(), std::ios::out | std::ios::app);
			succesfull = myfile.is_open();
			ASSERT(succesfull, (_T("Couldn't open the text file '") + strstr.str() + _T("'.")).c_str());
			if(succesfull)
			{
				myfile << text;
				myfile.close();
			}
		}
#else
		tstring file_path(EMPTY_STRING);
		Filepath::GetCorrectPath(file, file_path, directory);
		tofstream myfile(file_path, std::ios::out | std::ios::app);
		bool succes = myfile.is_open();
		ASSERT(succes, (_T("Couldn't open the text file '") + file_path + _T("'.")).c_str());
		if(succes)
		{
			myfile << text;
			myfile.close();
		}
#endif
	}

	char * ReadBinaryFile(const tstring & file, uint32 & size,
			DirectoryMode directory)
	{
#ifdef ANDROID
		if(directory == DirectoryMode::assets)
		{
			SerializedData data;
			star_a::ReadFileAsset(file, data);
			size = data.size;
			return data.data;
		}
		else
		{
			auto app = StarEngine::GetInstance()->GetAndroidApp();
			std::stringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<std::string>(file);

			std::ifstream binary_file;
			binary_file.open(strstr.str().c_str(),
					std::ios::in | std::ios::binary | std::ios::ate);
			bool succes = binary_file.is_open();
			char * buffer(nullptr);
			ASSERT(succes, (_T("Couldn't open the binary file '") +
					strstr.str() + _T("'.")).c_str());
			if (succes)
			{
				size = uint32(binary_file.tellg());
				buffer = new char[size];
				binary_file.seekg(0, std::ios::beg);
				binary_file.read(buffer, sizeof(char) * size);
				binary_file.close();
			}
			return buffer;
		}
#else
		tstring file_path(EMPTY_STRING);
		Filepath::GetCorrectPath(file, file_path, directory);
		std::ifstream binary_file;
		binary_file.open(file_path,
				std::ios::in | std::ios::binary | std::ios::ate);
		bool succes = binary_file.is_open();
		char * buffer(nullptr);
		ASSERT(succes, (_T("Couldn't open the binary file '") +
				file_path + _T("'.")).c_str());
		if (succes)
		{
			size = uint32(binary_file.tellg());
			buffer = new char[size];
			binary_file.seekg(0, std::ios::beg);
			binary_file.read(buffer, sizeof(char) * size);
			binary_file.close();
		}
		return buffer;
#endif
	}

	void WriteBinaryFile(const tstring & file, char * buffer, uint32 size,
			DirectoryMode directory)
	{
#ifdef ANDROID
		bool succesfull = directory != DirectoryMode::assets;
		ASSERT(succesfull, _T("Android doesn't support writing to a binary file in the assets directory."));
		if(succesfull)
		{
			auto app = StarEngine::GetInstance()->GetAndroidApp();
			std::stringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<std::string>(file);
			std::ofstream binary_file;
			binary_file.open(strstr.str(), std::ios::binary
					| std::ios::trunc);
			succesfull = binary_file.is_open();
			ASSERT(succesfull, (_T("Couldn't open the binary file '") +
					strstr.str() + _T("'.")).c_str());
			if (succesfull)
			{
				for(uint32 i = 0 ; i < size ; ++i)
				{
					binary_file << buffer[i];
				}
				binary_file.close();
			}
		}
#else
		tstring file_path(EMPTY_STRING);
		Filepath::GetCorrectPath(file, file_path, directory);
		std::ofstream binary_file;
		binary_file.open(file_path, std::ios::binary | std::ios::trunc);
		bool succes = binary_file.is_open();
		ASSERT(succes, (_T("Couldn't open the binary file '") + file_path + _T("'.")).c_str());
		if (succes)
		{
			for(uint32 i = 0 ; i < size ; ++i)
			{
				binary_file << buffer[i];
			}
			binary_file.close();
		}
#endif
	}

	void AppendBinaryFile(const tstring & file, char * buffer, uint32 size,
			DirectoryMode directory)
	{
#ifdef ANDROID
		bool succesfull = directory != DirectoryMode::assets;
		ASSERT(succesfull, _T("Android doesn't support writing to a binary file in the assets directory."));
		if(succesfull)
		{
			auto app = StarEngine::GetInstance()->GetAndroidApp();
			std::stringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<std::string>(file);
			std::ofstream binary_file(strstr.str(),
					std::ios::out | std::ios::binary | std::ios::app);
			succesfull = binary_file.is_open();
			ASSERT(succesfull, (_T("Couldn't open the binary file '") +
					strstr.str() + _T("'.")).c_str());
			if (succesfull)
			{
				for(uint32 i = 0 ; i < size ; ++i)
				{
					binary_file << buffer[i];
				}
				binary_file.close();
			}
		}
#else
		tstring file_path(EMPTY_STRING);
		Filepath::GetCorrectPath(file, file_path, directory);
		std::ofstream binary_file(file_path,
				std::ios::out | std::ios::binary | std::ios::app);
		bool succes = binary_file.is_open();
		ASSERT(succes, (_T("Couldn't open the binary file '") +
				file_path + _T("'.")).c_str());
		if (succes)
		{
			for(uint32 i = 0 ; i < size ; ++i)
			{
				binary_file << buffer[i];
			}
			binary_file.close();
		}
#endif
	}
}
