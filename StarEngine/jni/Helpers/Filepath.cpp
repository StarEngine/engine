#include "FilePath.h"
#ifdef _WIN32
	#include <shellapi.h>
	#include "../StarEngine.h"
#endif
#include "../Logger.h"
#ifdef ANDROID
	#include <android_native_app_glue.h>
	#include "../StarEngine.h"
#endif
#include "../Helpers/Helpers.h"

namespace star
{
#ifdef DESKTOP
tstring FilePath::m_AssetsRoot = EMPTY_STRING;
tstring FilePath::m_InternalRoot = EMPTY_STRING;
tstring FilePath::m_ExternalRoot = EMPTY_STRING;
#endif

	FilePath::FilePath()
		: m_Path(EMPTY_STRING) 
		, m_File(EMPTY_STRING)
	{

	}

	FilePath::FilePath(const tstring & full_path)
		: m_Path(EMPTY_STRING)
		, m_File(EMPTY_STRING)
	{
		int32 dotCounter(0);
		for(uint32 i = 0; i < full_path.size(); ++i)
		{
			if(full_path[i] == _T('.'))
			{
				++dotCounter;
			}
		}
		if(dotCounter > 1)
		{
			Logger::GetInstance()->Log(LogLevel::Error, 
				_T("Please don't use . in your filename (except for the file extension)"),
				STARENGINE_LOG_TAG);
		}

		auto index = full_path.find_last_of('/');
		if(index == tstring::npos)
		{
			index = full_path.find_last_of('\\');
		}
		if(index != tstring::npos)
		{
			index += 1;
			m_Path = full_path.substr(0,index);
			m_File = full_path.substr(index, full_path.length() - index);
		}
		else
		{
			m_File = full_path;
		}
	}

	FilePath::FilePath(const tstring & path, const tstring & file)
		: m_Path(path)
		, m_File(file)
	{

	}

	FilePath::FilePath(const FilePath & yRef)
		: m_Path(yRef.m_Path)
		, m_File(yRef.m_File)
	{
		
	}

	FilePath::~FilePath()
	{

	}

	FilePath & FilePath::operator=(const FilePath & yRef)
	{
		m_Path = yRef.m_Path;
		m_File = yRef.m_File;
		return *this;
	}

	bool FilePath::operator==(const FilePath & yRef)
	{
		return m_Path == yRef.m_Path && m_File == yRef.m_File;
	}

	const tstring & FilePath::GetPath() const
	{
		return m_Path;
	}

	const tstring & FilePath::GetFile() const
	{
		return m_File;
	}

	tstring FilePath::GetName() const
	{
		tstring name(m_File);
		auto index(name.find_last_of(_T(".")));
		return name.substr(0, index);
	}

	tstring FilePath::GetExtension() const
	{
		tstring extension(m_File);
		auto index(extension.find_last_of(_T(".")));
		return extension.substr(index, extension.size() - index);
	}
	
	tstring FilePath::GetLocalPath() const
	{
		return m_Path + m_File;
	}

	tstring FilePath::GetAssetsPath() const
	{
		tstring assets_path(EMPTY_STRING);
	#ifdef DESKTOP
		assets_path = m_AssetsRoot;
	#endif
		assets_path += m_Path + m_File;
		return assets_path;
	}

	tstring FilePath::GetInternalPath() const
	{
		tstring internal_path(EMPTY_STRING);
	#ifdef DESKTOP
		internal_path = m_InternalRoot;
	#else
		auto app = StarEngine::GetInstance()->GetAndroidApp();
		internal_path = string_cast<tstring>(app->activity->internalDataPath);
		internal_path += _T("/");
	#endif
		internal_path += m_Path + m_File;
		return internal_path;
	}

	tstring FilePath::GetExternalPath() const
	{
		tstring external_path(EMPTY_STRING);
	#ifdef DESKTOP
		external_path = m_ExternalRoot;
	#else
		auto app = StarEngine::GetInstance()->GetAndroidApp();
		external_path = string_cast<tstring>(app->activity->externalDataPath);
		external_path += _T("/");
	#endif
		external_path += m_Path + m_File;
		return external_path;
	}
	
	void FilePath::GetCorrectPath(const tstring & path,
		tstring & correct_path, DirectoryMode mode)
	{
		switch(mode)
		{
		case DirectoryMode::assets:
			correct_path = FilePath(path).GetAssetsPath();
			break;
		case DirectoryMode::internal:
			correct_path = FilePath(path).GetInternalPath();
			break;
		case DirectoryMode::external:
			correct_path = FilePath(path).GetExternalPath();
			break;
		default:
			correct_path = path;
			break;
		}
	}

#ifdef DESKTOP
	void FilePath::SetAssetsRoot(const tstring & root)
	{
		m_AssetsRoot = root;
	}
	
	void FilePath::SetInternalRoot(const tstring & root)
	{
		m_InternalRoot = root;
	}
	
	void FilePath::SetExternalRoot(const tstring & root)
	{
		m_ExternalRoot = root;
	}
#endif

#ifdef _WIN32
	tstring FilePath::GetActualPathName(const tstring& path ) const
	{
		// This is quite involved, but the meat is SHGetFileInfo

		const tchar kSeparator = _T('\\');

		tstring buffer(path);

		size_t i = 0;

		tstring result;
		bool addSeparator = false;

		while(i < buffer.size())
		{
			// skip until path separator
			while(i < buffer.size() && buffer[i] != kSeparator)
			{
				++i;
			}

			if(addSeparator)
			{
				result += kSeparator;
			}

			// if we found path separator, get real filename of this
			// last path name component
			bool foundSeparator = (i < buffer.size());
			buffer[i] = 0;
			TSHFILEINFO info;

			// nuke the path separator so that we get real name of current path component
			info.szDisplayName[0] = 0;
			if(SHGetFileInfo(buffer.c_str(), 0, &info, sizeof(info), SHGFI_DISPLAYNAME ))
			{
				result += info.szDisplayName;
			}
			else
			{
				tstringstream message;
				message << _T("The path \" ") << path << _T(" \" Is Invalid!");
				Logger::GetInstance()->Log(LogLevel::Error,
					message.str(), STARENGINE_LOG_TAG);
				break;
			}

			// restore path separator that we might have nuked before
			if(foundSeparator)
			{
				buffer[i] = kSeparator;
			}

			++i;
			addSeparator = true;
		}
		return result;
	}
#endif
}
