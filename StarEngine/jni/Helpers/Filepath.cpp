#include "Filepath.h"
#ifdef _WIN32
#include <shellapi.h>
#include "../StarEngine.h"
#include "../Logger.h"
#endif
//[TODO]
//Add case sensitivity on windows. 
// Probably using the SHGetFileInfo - SHGetFileInfoW functions. 
// Where should i check this though...? 
// http://stackoverflow.com/questions/74451/getting-actual-file-name-with-proper-casing-on-windows
namespace star
{
#ifdef DESKTOP
tstring Filepath::m_AssetsRoot = EMPTY_STRING;
#endif

	Filepath::Filepath()
		: m_Path(EMPTY_STRING) 
		, m_File(EMPTY_STRING)
	{

	}

	Filepath::Filepath(const tstring & full_path)
		: m_Path(EMPTY_STRING)
		, m_File(EMPTY_STRING)
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
	}

	Filepath::Filepath(const tstring & path, const tstring & file)
		: m_Path(path)
		, m_File(file)
	{

	}

	Filepath::Filepath(const Filepath & yRef)
		: m_Path(yRef.m_Path)
		, m_File(yRef.m_File)
	{
		
	}

	Filepath::~Filepath()
	{

	}

	const Filepath & Filepath::operator=(const Filepath & yRef)
	{
		m_Path = yRef.m_Path;
		m_File = yRef.m_File;
		return *this;
	}

	bool Filepath::operator==(const Filepath & yRef)
	{
		return m_Path == yRef.m_Path && m_File == yRef.m_File;
	}

	const tstring & Filepath::GetPath() const
	{
		return m_Path;
	}

	const tstring & Filepath::GetFile() const
	{
		return m_File;
	}

	tstring Filepath::GetName() const
	{
		tstring name(m_File);
		auto index(name.find_last_of(_T(".")));
		return name.substr(0, index);
	}

	tstring Filepath::GetExtension() const
	{
		tstring extension(m_File);
		auto index(extension.find_last_of(_T(".")));
		return extension.substr(index, extension.size() - index);
	}

	tstring Filepath::GetFullPath()
	{
		tstring full_path(EMPTY_STRING);
#ifdef DESKTOP
		full_path = m_AssetsRoot;
#endif
		full_path += m_Path + m_File;

#if defined(_WIN32) && defined (_DEBUG)

			tstring shellFullPath;
			for(uint32 i = 0; i < full_path.size(); ++i)
			{
				tstring temp;
				temp = full_path[i];
				if(temp == _T("/"))
				{
					temp = _T("\\");
				}
				shellFullPath += temp;
			}
			shellFullPath = GetActualPathName(shellFullPath.c_str());
			auto index(shellFullPath.find_last_of(_T("\\")));
			if(index != tstring::npos)
			{
				shellFullPath = shellFullPath.substr(index + 1,shellFullPath.size() - (index+1));
			}
			
			if(m_File != shellFullPath)
			{
				tstringstream buffer; 
				buffer << _T("The file name \" ") << m_File << 
					_T(" \" is invalid. Please change it to \" ") << shellFullPath << 
					_T(" \" or your game will not run on Android and Linux");
				Logger::GetInstance()->Log(LogLevel::Error, buffer.str());
			}
#endif
		return full_path;
	}

#ifdef DESKTOP
	void Filepath::SetAssetsRoot(const tstring & root)
	{
		m_AssetsRoot = root;
	}
#endif

	tstring Filepath::GetActualPathName(const TCHAR* path )
	{
		// This is quite involved, but the meat is SHGetFileInfo

		const TCHAR kSeparator = _T('\\');

		// copy input string because we'll be temporary modifying it in place
		size_t length = tstrlen(path);
		TCHAR buffer[MAX_PATH];
		memcpy(buffer, path, (length + 1) * sizeof(path[0]));

		size_t i = 0;

		tstring result;
		bool addSeparator = false;

		while(i < length)
		{
			// skip until path separator
			while(i < length && buffer[i] != kSeparator)
			{
				++i;
			}

			if(addSeparator)
			{
				result += kSeparator;
			}

			// if we found path separator, get real filename of this
			// last path name component
			bool foundSeparator = (i < length);
			buffer[i] = 0;
			SHFILEINFOW info;

			// nuke the path separator so that we get real name of current path component
			info.szDisplayName[0] = 0;
			if(SHGetFileInfoW( buffer, 0, &info, sizeof(info), SHGFI_DISPLAYNAME ))
			{
				result += info.szDisplayName;
			}
			else
			{
				tstringstream message;
				message << _T("The path \" ") << path << _T(" \" Is Invalid!");
				Logger::GetInstance()->Log(LogLevel::Error,message.str());
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
}