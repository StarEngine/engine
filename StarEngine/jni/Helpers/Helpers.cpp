#include "Helpers.h"
#include "..\Logger.h"
#include "Filepath.h"
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <clocale>
#include <vector>

#include "HelpersCrossplatform.h"

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
	sstring_16 string_cast<sstring_16, sstring_16>
		(const sstring_16 & value)
	{
		return value;
	}

	template <>
	sstring_16 string_cast<sstring_16, swstring>
		(const swstring & value)
	{
		sstring_16 str(value.begin(), value.end());
		return str;
	}

	template <>
	sstring_16 string_cast<sstring_16, sstring>
		(const sstring & value)
	{
		sstring_16 str(value.begin(), value.end());
		return str;
	}

	template <>
	swstring string_cast<swstring, sstring_16>
		(const sstring_16 & value)
	{
		swstring str(value.begin(), value.end());
		return str;
	}

	template <>
	sstring string_cast<sstring, sstring_16>
		(const sstring_16 & value)
	{
		sstring str(value.begin(), value.end());
		return str;
	}

	template <>
	swstring string_cast<swstring, swstring>
		(const swstring & value) { return value; }

	template <>
	sstring string_cast<sstring, sstring>
		(const sstring & value) { return value; }

	template <>
	sstring string_cast<sstring, swstring>
		(const swstring & value)
	{
		sstring str(value.begin(), value.end());
		return str;
	}

	template <>
	swstring string_cast<swstring, sstring>
		(const sstring & value)
	{
		swstring str(value.begin(), value.end());
		return str;
	}

	template <>
	sstring_16 string_cast<sstring_16, schar_16>
		(const schar_16 * value)
	{
		return sstring_16(value);
	}

	template <>
	sstring_16 string_cast<sstring_16, swchar>
		(const swchar * value)
	{
		return string_cast<sstring_16, swstring>(value);
	}

	template <>
	sstring_16 string_cast<sstring_16, schar>
		(const schar * value)
	{
		return string_cast<sstring_16, sstring>(value);
	}

	template <>
	schar_16 * string_cast<schar_16*, sstring_16>
		(const sstring_16 & value)
	{
		schar_16 * cstr =
			const_cast<schar_16*>(
				value.c_str()
			);
		return cstr;
	}

	template <>
	swchar * string_cast<swchar*, sstring_16>
		(const sstring_16 & value)
	{
		swchar * cstr =
			const_cast<swchar*>(
				string_cast<swstring, sstring_16>(
					value
					).c_str()
			);
		return cstr;
	}

	template <>
	schar * string_cast<schar*, sstring_16>
		(const sstring_16 & value)
	{
		schar * cstr =
			const_cast<schar*>(
				string_cast<sstring, sstring_16>(
					value
					).c_str()
			);
		return cstr;
	}

	template <>
	sstring string_cast<sstring, schar_16>
		(const schar_16 * value)
	{
		return string_cast<sstring, sstring_16>(value);
	}

	template <>
	swstring string_cast<swstring, schar_16>
		(const schar_16 * value)
	{
		return string_cast<swstring, sstring_16>(value);
	}

	template <>
	schar_16* string_cast<schar_16*, sstring>
		(const sstring & value)
	{
		schar_16 * cstr =
			const_cast<schar_16*>(
				string_cast<sstring_16, sstring>(value).c_str()
				);
		return cstr;
	}

	template <>
	schar_16* string_cast<schar_16*, swstring>
		(const swstring & value)
	{
		schar_16 * cstr =
			const_cast<schar_16*>(
				string_cast<sstring_16, swstring>(value).c_str()
				);
		return cstr;
	}

	template <>
	swstring string_cast<swstring, swchar>
		(const swchar * value)
	{
		return string_cast<swstring, swstring>(value);
	}

	template <>
	sstring string_cast<sstring, schar>
		(const schar * value)
	{
		return string_cast<sstring, sstring>(value);
	}

	template <>
	sstring string_cast<sstring, swchar>
		(const swchar * value)
	{
		return string_cast<sstring, swstring>(value);
	}

	template <>
	swstring string_cast<swstring, schar>
		(const schar * value)
	{
		return string_cast<swstring, sstring>(value);
	}

	template <>
	schar* string_cast<schar*, swstring>
		(const swstring & value)
	{
		schar * result = 
			const_cast<schar*>(
				string_cast<sstring, swstring>(value).c_str()
				);
		return result;
	}

	template <>
	schar* string_cast<schar*, sstring>
		(const sstring & value)
	{
		schar * result = 
			const_cast<schar*>(value.c_str());
		return result;
	}

	template <>
	swchar* string_cast<swchar*, swstring>
		(const swstring & value)
	{
		swchar * result = 
			const_cast<swchar*>(value.c_str());
		return result;
	}

	template <>
	swchar* string_cast<swchar*, sstring>
		(const sstring & value)
	{
		swchar * result = 
			const_cast<swchar*>(
				string_cast<swstring, sstring>(value).c_str()
				);
		return result;
	}

	template <>
	swchar* string_cast<swchar*, schar>
		(const schar * value)
	{
		return string_cast<swchar*>(
			sstring(value)
			);
	}

	template <>
	swchar* string_cast<swchar*, swchar>
		(const swchar * value)
	{
		return const_cast<swchar*>(value);
	}

	template <>
	schar* string_cast<schar*, swchar>
		(const swchar * value)
	{
		return string_cast<schar*>(
			swstring(value)
			);
	}

	template <>
	schar* string_cast<schar*, schar>
		(const schar * value)
	{
		return const_cast<schar*>(value);
	}

	template <>
	schar_16* string_cast<schar_16*, schar>
		(const schar * value)
	{
		return string_cast<schar_16*, sstring>(value);
	}

	template <>
	schar_16* string_cast<schar_16*, swchar>
		(const swchar * value)
	{
		return string_cast<schar_16*, swstring>(value);
	}

	template <>
	schar* string_cast<schar*, schar_16>
		(const schar_16 * value)
	{
		return string_cast<schar*, sstring_16>(value);
	}

	template <>
	swchar* string_cast<swchar*, schar_16>
		(const schar_16 * value)
	{
		return string_cast<swchar*, sstring_16>(value);
	}

	template <>
	tstring string_cast<tstring, fvec2>
		(const fvec2 & value)
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
	tstring string_cast<tstring, fvec3>
		(const fvec3 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, fvec4>
		(const fvec4 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z << _T(";");
		strstr << value.w;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, fquat>
		(const fquat & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z << _T(";");
		strstr << value.w;
		return strstr.str();
	}
	
	template <>
	tstring string_cast<tstring, dvec2>
		(const dvec2 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, dvec3>
		(const dvec3 & value)
	{
		
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, dvec4>
		(const dvec4 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z << _T(";");
		strstr << value.w;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, dquat>
		(const dquat & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z << _T(";");
		strstr << value.w;
		return strstr.str();
	}
	
	template <>
	tstring string_cast<tstring, ivec2>
		(const ivec2 & value)
	{	
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, ivec3>
		(const ivec3 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, ivec4>
		(const ivec4 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z << _T(";");
		strstr << value.w;
		return strstr.str();
	}
	
	template <>
	tstring string_cast<tstring, uvec2>
		(const uvec2 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, uvec3>
		(const uvec3 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";");
		strstr << value.y << _T(";");
		strstr << value.z;
		return strstr.str();
	}

	template <>
	tstring string_cast<tstring, uvec4>
		(const uvec4 & value)
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
	int32 string_cast<int32, tstring>
		(const tstring & value)
	{
		return ttoi(value.c_str());
	}

	template <>
	uint32 string_cast<uint32, tstring>
		(const tstring & value)
	{
		return uint32(string_cast<int32>(value));
	}

	template <>
	long string_cast<long, tstring>
		(const tstring & value)
	{
		return static_cast<long>(ttoi(value.c_str()));
	}

	template <>
	float32 string_cast<float32, tstring>
		(const tstring & value)
	{
		return static_cast<float32>(ttof(value.c_str()));
	}

	template <>
	float64 string_cast<float64, tstring>
		(const tstring & value)
	{
		return ttof(value.c_str());
	}

	template <>
	fvec2 string_cast<fvec2, tstring>
		(const tstring & value)
	{
		fvec2 vec;
		int32 index = value.find(';',0);
		vec.x = string_cast<float32>(value.substr(0, index));
		vec.y = string_cast<float32>(value.substr(++index,value.size()-index));
		return vec;
	}

	template <>
	pos string_cast<pos, tstring>
		(const tstring & value)
	{
		pos pos;
		int32 index = value.find(';', 0);
		pos.x = string_cast<float32>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		pos.y = string_cast<float32>(value.substr(index, index2 - index));
		pos.l = lay(string_cast<int32>(value.substr(++index2, value.size() - index2)));
		return pos;
	}

	template <>
	fvec3 string_cast<fvec3, tstring>
		(const tstring & value)
	{
		fvec3 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<float32>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		vec.y = string_cast<float32>(value.substr(index, index2 - index));
		vec.z = string_cast<float32>(value.substr(++index2, value.size() - index2));
		return vec;
	}

	template <>
	fvec4 string_cast<fvec4, tstring>
		(const tstring & value)
	{
		fvec4 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<float32>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		vec.y = string_cast<float32>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		vec.z = string_cast<float32>(value.substr(index2, index - index2));
		vec.w = string_cast<float32>(value.substr(++index, value.size() - index));
		return vec;
	}

	template <>
	fquat string_cast<fquat, tstring>
		(const tstring & value)
	{
		fquat quat;
		int32 index = value.find(';', 0);
		quat.x = string_cast<float32>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		quat.y = string_cast<float32>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		quat.z = string_cast<float32>(value.substr(index2, index - index2));
		quat.w = string_cast<float32>(value.substr(++index, value.size() - index));
		return quat;
	}

	template <>
	dvec2 string_cast<dvec2, tstring>
		(const tstring & value)
	{
		dvec2 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<float64>(value.substr(0, index));
		vec.y = string_cast<float64>(value.substr(++index, value.size() - index));
		return vec;
	}

	template <>
	dvec3 string_cast<dvec3, tstring>
		(const tstring & value)
	{
		dvec3 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<float64>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		vec.y = string_cast<float64>(value.substr(index, index2 - index));
		vec.z = string_cast<float64>(value.substr(++index2, value.size() - index2));
		return vec;
	}

	template <>
	dvec4 string_cast<dvec4, tstring>
		(const tstring & value)
	{
		dvec4 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<float64>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		vec.y = string_cast<float64>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		vec.z = string_cast<float64>(value.substr(index2, index - index2));
		vec.w = string_cast<float64>(value.substr(++index, value.size() - index));
		return vec;
	}

	template <>
	dquat string_cast<dquat, tstring>
		(const tstring & value)
	{
		dquat quat;
		int32 index = value.find(';', 0);
		quat.x = string_cast<float64>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		quat.y = string_cast<float64>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		quat.z = string_cast<float64>(value.substr(index2, index - index2));
		quat.w = string_cast<float64>(value.substr(++index, value.size() - index));
		return quat;
	}

	template <>
	ivec2 string_cast<ivec2, tstring>
		(const tstring & value)
	{
		ivec2 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<int32>(value.substr(0, index));
		vec.y = string_cast<int32>(value.substr(++index ,value.size() - index));
		return vec;
	}

	template <>
	ivec3 string_cast<ivec3, tstring>
		(const tstring & value)
	{
		ivec3 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<int32>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		vec.y = string_cast<int32>(value.substr(index, index2 - index));
		vec.z = string_cast<int32>(value.substr(++index2, value.size() - index2));
		return vec;
	}

	template <>
	ivec4 string_cast<ivec4, tstring>
		(const tstring & value)
	{
		ivec4 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<int32>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		vec.y = string_cast<int32>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		vec.z = string_cast<int32>(value.substr(index2, index - index2));
		vec.w = string_cast<int32>(value.substr(++index, value.size() - index));
		return vec;
	}

	template <>
	uvec2 string_cast<uvec2, tstring>
		(const tstring & value)
	{
		uvec2 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<uint32>(value.substr(0, index));
		vec.y = string_cast<uint32>(value.substr(++index, value.size() - index));
		return vec;
	}

	template <>
	uvec3 string_cast<uvec3, tstring>
		(const tstring & value)
	{
		uvec3 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<uint32>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		vec.y = string_cast<uint32>(value.substr(index, index2 - index));
		vec.z = string_cast<uint32>(value.substr(++index2, value.size() - index2));
		return vec;
	}

	template <>
	uvec4 string_cast<uvec4, tstring>
		(const tstring & value)
	{
		uvec4 vec;
		int32 index = value.find(';', 0);
		vec.x = string_cast<uint32>(value.substr(0, index));
		int32 index2 = value.find(';', ++index);
		vec.y = string_cast<uint32>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		vec.z = string_cast<uint32>(value.substr(index2, index - index2));
		vec.w = string_cast<uint32>(value.substr(++index, value.size() - index));
		return vec;
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
			sstringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<sstring>(file);

			sifstream myfile;
			myfile.open(strstr.str(), std::ios::in);
			bool succes = myfile.is_open();
			ASSERT(succes, (_T("Couldn't open the text file '") +
					strstr.str() + _T("'.")).c_str());
			if(succes)
			{
				sstring str;
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
			sstringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<sstring>(file);
			sofstream myfile(strstr.str(), std::ios::out);
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
			sstringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<sstring>(file);
			sofstream myfile(strstr.str(), std::ios::out | std::ios::app);
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

	schar * ReadBinaryFile(const tstring & file, uint32 & size,
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
			sstringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<sstring>(file);

			sifstream binary_file;
			binary_file.open(strstr.str().c_str(),
					std::ios::in | std::ios::binary | std::ios::ate);
			bool succes = binary_file.is_open();
			schar * buffer(nullptr);
			ASSERT(succes, (_T("Couldn't open the binary file '") +
					strstr.str() + _T("'.")).c_str());
			if (succes)
			{
				size = uint32(binary_file.tellg());
				buffer = new schar[size];
				binary_file.seekg(0, std::ios::beg);
				binary_file.read(buffer, sizeof(schar) * size);
				binary_file.close();
			}
			return buffer;
		}
#else
		tstring file_path(EMPTY_STRING);
		Filepath::GetCorrectPath(file, file_path, directory);
		sifstream binary_file;
		binary_file.open(file_path,
				std::ios::in | std::ios::binary | std::ios::ate);
		bool succes = binary_file.is_open();
		schar * buffer(nullptr);
		ASSERT(succes, (_T("Couldn't open the binary file '") +
				file_path + _T("'.")).c_str());
		if (succes)
		{
			size = uint32(binary_file.tellg());
			buffer = new schar[size];
			binary_file.seekg(0, std::ios::beg);
			binary_file.read(buffer, sizeof(schar) * size);
			binary_file.close();
		}
		return buffer;
#endif
	}

	void WriteBinaryFile(const tstring & file, schar * buffer, uint32 size,
			DirectoryMode directory)
	{
#ifdef ANDROID
		bool succesfull = directory != DirectoryMode::assets;
		ASSERT(succesfull, _T("Android doesn't support writing to a binary file in the assets directory."));
		if(succesfull)
		{
			auto app = StarEngine::GetInstance()->GetAndroidApp();
			sstringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<sstring>(file);
			sofstream binary_file;
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
		sofstream binary_file;
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

	void AppendBinaryFile(const tstring & file, schar * buffer, uint32 size,
			DirectoryMode directory)
	{
#ifdef ANDROID
		bool succesfull = directory != DirectoryMode::assets;
		ASSERT(succesfull, _T("Android doesn't support writing to a binary file in the assets directory."));
		if(succesfull)
		{
			auto app = StarEngine::GetInstance()->GetAndroidApp();
			sstringstream strstr;
			if(directory == DirectoryMode::internal)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			else if(directory == DirectoryMode::external)
			{
				strstr << app->activity->internalDataPath << "/";
			}
			strstr << string_cast<sstring>(file);
			sofstream binary_file(strstr.str(),
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
		sofstream binary_file(file_path,
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

	schar * DecryptBinaryFile(const tstring & file, uint32 & size,
		const std::function<schar*(const schar*, uint32&)> & decrypter, 
		DirectoryMode directory)
	{
		schar * buffer = ReadBinaryFile(file, size, directory);
		schar * decryptedBuffer = decrypter(buffer, size);
		delete [] buffer;
		return decryptedBuffer;
	}

	void EncryptBinaryFile(const tstring & file, schar * buffer, uint32 size,
		const std::function<schar*(const schar*, uint32&)> & encrypter, 
		DirectoryMode directory)
	{
		schar * encryptedBuffer = encrypter(buffer, size);
		WriteBinaryFile(file, encryptedBuffer, size, directory);
		delete [] encryptedBuffer;
	}
}
