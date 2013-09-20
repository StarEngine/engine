#include "Logger.h"

#ifdef _WIN32
#include <stdio.h>

#include "Console.h"
#else
#include <android/log.h>
#endif
namespace star {

	Logger::Logger()
	{
		#ifdef _WIN32
		m_ConsoleHandle = nullptr;
		#endif
	}
	void Logger::Initialize()
	{
		#ifdef _WIN32
		WindowsConsole::RedirectIOToConsole();
		m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		#endif
	}

	void Logger::Log(LogLevel level, const tstring& pMessage, const tstring& tag) const
	{
		#ifdef _WIN32

		tstring levelName;
		switch(level)
		{
		case LogLevel::Info :
			levelName = _T("INFO");
			break;
		case LogLevel::Warning:
			levelName = _T("WARNING");
			break;
		case LogLevel::Error:
			levelName = _T("ERROR");
			break;
		case LogLevel::Debug:
			levelName = _T("DEBUG");
			break;
		}

		tstringstream messageBuffer;
		messageBuffer << _T("[") << tag << _T("] ") << _T("[") << levelName <<  _T("] ") << pMessage << std::endl;
		tstring combinedMessage = messageBuffer.str();

			switch(level)
			{
			case LogLevel::Info :
				SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				tprintf(combinedMessage.c_str());
				break;
			case LogLevel::Warning :
				SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
				tprintf(combinedMessage.c_str());
				break;
			case LogLevel::Error :
				SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY|FOREGROUND_RED);
				tprintf(combinedMessage.c_str());
				//[TODO] Add assert + messagebox!
				break;
			case LogLevel::Debug :
				#ifdef DEBUG
				SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY|FOREGROUND_GREEN);
				tprintf(combinedMessage.c_str());
				#endif
				break;
			//[TODO] Add default with cross platform assert!
			}
		#else
			switch(level)
			{
			case LogLevel::Info :
				__android_log_print(ANDROID_LOG_INFO, tag.c_str(), pMessage.c_str());
				break;
			case LogLevel::Warning :
				__android_log_print(ANDROID_LOG_WARN, tag.c_str(), pMessage.c_str());
				break;
			case LogLevel::Error:
				__android_log_print(ANDROID_LOG_ERROR, tag.c_str(), pMessage.c_str());
				break;
			case LogLevel::Debug:
				#ifdef DEBUG
				__android_log_print(ANDROID_LOG_DEBUG, tag.c_str(), pMessage.c_str());
				#endif
				break;
			//[TODO] Add default with cross platform assert!
			}
		#endif
	}
}
