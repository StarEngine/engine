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
		, m_DirectoryMode(DEFAULT_DIRECTORY_MODE)
	{

	}

	FilePath::FilePath(const tstring & full_path, DirectoryMode mode)
		: m_Path(EMPTY_STRING)
		, m_File(EMPTY_STRING)
		, m_DirectoryMode(mode)
	{
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
		ConvertPathToCorrectPlatformStyle(m_Path);
		CheckIfPathIsCapitalCorrect(GetRoot() + m_Path + m_File);
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

	const tstring & FilePath::GetRoot() const
	{
#ifdef DESKTOP
		switch(m_DirectoryMode)
		{
		case DirectoryMode::assets:
			return m_AssetsRoot;
		case DirectoryMode::internal:
			return m_InternalRoot;
		case DirectoryMode::external:
			return m_ExternalRoot;
		default:
			return EMPTY_STRING;
		}
#endif
#ifdef ANDROID
		auto app = StarEngine::GetInstance()->GetAndroidApp();
		switch(m_DirectoryMode)
		{
		case DirectoryMode::assets:
			return EMPTY_STRING;
		case DirectoryMode::internal:
			return string_cast<tstring>(app->activity->internalDataPath) + tstring(_T("/"));
		case DirectoryMode::external:
			return string_cast<tstring>(app->activity->externalDataPath) + tstring(_T("/"));
		default:
			return EMPTY_STRING;
		}
#endif
	}
	
	tstring FilePath::GetLocalPath() const
	{
		return m_Path + m_File;
	}
	
	void FilePath::GetCorrectPath(tstring & correct_path) const
	{
		correct_path = GetRoot() + GetLocalPath();
	}

	tstring FilePath::GetCorrectPath() const
	{
		return GetRoot() + GetLocalPath();
	}

	DirectoryMode FilePath::GetDirectoryMode() const
	{
		return m_DirectoryMode;
	}

#ifdef DESKTOP
	void FilePath::SetAssetsRoot(const tstring & root)
	{
		m_AssetsRoot = root;
		ConvertPathToCorrectPlatformStyle(m_AssetsRoot);
	}
	
	void FilePath::SetInternalRoot(const tstring & root)
	{
		m_InternalRoot = root;
		ConvertPathToCorrectPlatformStyle(m_InternalRoot);
	}
	
	void FilePath::SetExternalRoot(const tstring & root)
	{
		m_ExternalRoot = root;
		ConvertPathToCorrectPlatformStyle(m_ExternalRoot);
	}
#endif


	bool FilePath::GetActualPathName(const tstring & pathIn, tstring & pathOut)
	{
#ifdef _WIN32
		const tchar kSeparator = _T('\\');

		tstring buffer(pathIn);

		size_t i = 0;
		pathOut = EMPTY_STRING;

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
				pathOut += kSeparator;
			}

			// if we found path separator, get real filename of this
			// last path name component
			bool foundSeparator = (i < buffer.size());
			buffer[i] = 0;
			TSHFILEINFO info;

			// nuke the path separator so that we get real name of current path component
			info.szDisplayName[0] = 0;
			if(SHGetFileInfo(buffer.c_str(), 0, &info, sizeof(info), SHGFI_DISPLAYNAME))
			{
				pathOut += info.szDisplayName;
			}
			else
			{
				tstringstream message;
				message << _T("FilePath::GetActualPathName: ")
					<< _T("The path \"") 
					<< pathIn 
					<< _T("\" points to an unexisting file! ")
					<< _T("The file might be created or this can \
be unexpected behaviour. Please verify!");
				LOG(LogLevel::Info,
					message.str(), STARENGINE_LOG_TAG);
				return false;
			}

			// restore path separator that we might have nuked before
			if(foundSeparator)
			{
				buffer[i] = kSeparator;
			}

			++i;
			addSeparator = true;
		}
		return true;
#endif
	}
	void FilePath::ConvertPathToCorrectPlatformStyle(tstring & path)
	{
#ifdef _WIN32
		std::replace(path.begin(), path.end(), '/', '\\');
#else
		std::replace(path.begin(), path.end(), '\\', '/');
#endif
	}

	void FilePath::CheckIfPathIsCapitalCorrect(const tstring & full_path)
	{
#if defined (_WIN32) & defined (_DEBUG)
		tstring shellPath;
		if(GetActualPathName(full_path, shellPath))
		{
			auto seperatorIndex(shellPath.find_last_of(_T("\\")));
			if(seperatorIndex != tstring::npos)
			{
				shellPath = shellPath.substr(seperatorIndex + 1, shellPath.size() - (seperatorIndex + 1));
			}
			auto extensionIndex = m_File.find_last_of(_T("."));
			auto fileWithoutExtension(m_File);
			if(extensionIndex != tstring::npos)
			{
				fileWithoutExtension = m_File.substr(0, extensionIndex);
			}
			auto shellExtensionIndex = shellPath.find_last_of(_T("."));
			auto shellNameWithoutExtension(shellPath);
			if(shellExtensionIndex != tstring::npos)
			{
				shellNameWithoutExtension = shellPath.substr(0, shellExtensionIndex);
			}
			if(fileWithoutExtension != shellNameWithoutExtension)
			{
				tstringstream buffer; 
				buffer << 
					_T("The path \" ") << 
					full_path << 
					_T(" \" is not capital correct. Please change the name in code to \" ") << 
					shellPath << 
					_T(" \" or your game will crash on Android and Linux");
				DEBUG_LOG(LogLevel::Error, buffer.str(), STARENGINE_LOG_TAG);
			}
		}
#endif
	}

}
