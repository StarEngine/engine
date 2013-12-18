#include "Logger.h"

#ifdef _WIN32
#include <stdio.h>
#include "Console.h"
#elif defined(ANDROID)
#include <android/log.h>
#endif
#ifdef DESKTOP
#include <glew.h>
#else
#include <GLES2/gl2.h>
#endif

#include "Scenes/SceneManager.h"
#include "Helpers/Helpers.h"

#include "Context.h"
#include "TimeManager.h"
#include "StarEngine.h"

namespace star
{
	Logger* Logger::m_LoggerPtr = nullptr;

	Logger::Logger()
#ifdef _WIN32
		:m_ConsoleHandle(nullptr)
		,m_UseConsole(false)
		,m_LogStream()
#else
		:m_LogStream()
#endif
		,m_TimeStamp(_T("00:00:00"))
	{

	}
	
	Logger::~Logger()
	{
		SaveLogFile();
#ifdef _WIN32
		CloseHandle(m_ConsoleHandle);
#endif
	}

	Logger * Logger::GetInstance()
	{
		if(m_LoggerPtr == nullptr)
		{
			m_LoggerPtr = new Logger();
		}
		return m_LoggerPtr;
	}

#ifdef _WIN32
	void Logger::Initialize(bool useConsole)
	{
		m_UseConsole = useConsole;
		if(useConsole)
		{
			star_w::RedirectIOToConsole();
			m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
#ifndef NO_LOG_FILE
		InitializeLogStream();
#endif
	}
#else
	void Logger::Initialize()
	{
#ifndef NO_LOG_FILE
		InitializeLogStream();
#endif
	}
#endif
	
	void Logger::Update(const Context & context)
	{
		m_TimeStamp = context.mTimeManager->GetTimeStamp();
	}

	void Logger::Log(bool assert, const tstring& pMessage, const tstring& tag)
	{
		if(!assert)
		{
			Log(LogLevel::Error, pMessage, tag);
		}
		ASSERT(assert, pMessage.c_str());
	}

	void Logger::Log(LogLevel level, const tstring& pMessage, const tstring& tag)
	{
#if LOGGER_MIN_LEVEL > 0
		
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

	#ifdef DESKTOP
		tstringstream messageBuffer;
		messageBuffer << _T("[") << tag << _T("] ") << _T("[") << levelName <<  _T("] ") << pMessage << std::endl;
		tstring combinedMessage = messageBuffer.str();
		
		if(m_UseConsole)
		{
			switch(level)
			{
			case LogLevel::Info :
				#if LOGGER_MIN_LEVEL < 2
				SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				#endif
				break;
			case LogLevel::Warning :
				#if LOGGER_MIN_LEVEL < 3
				SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				#endif
				break;
			case LogLevel::Error :
				#if LOGGER_MIN_LEVEL < 4
				SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				#endif
				break;
			case LogLevel::Debug :
				#if LOGGER_MIN_LEVEL < 5
				#ifdef DEBUG
				SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				#endif
				#endif
				break;
			}
			tprintf(combinedMessage.c_str());
		}
		else
		{
			OutputDebugString(combinedMessage.c_str());
		}
		#ifndef NO_LOG_FILE
		LogMessage(combinedMessage);
		#endif
	#else
		switch(level)
		{
		case LogLevel::Info:
			#if LOGGER_MIN_LEVEL < 2
			__android_log_print(ANDROID_LOG_INFO, tag.c_str(), "%s", pMessage.c_str());
			#endif
			break;
		case LogLevel::Warning:
			#if LOGGER_MIN_LEVEL < 3
			__android_log_print(ANDROID_LOG_WARN, tag.c_str(), "%s", pMessage.c_str());
			#endif
			break;
		case LogLevel::Error:
			#if LOGGER_MIN_LEVEL < 4
			__android_log_print(ANDROID_LOG_ERROR, tag.c_str(), "%s", pMessage.c_str());
			#endif
			break;
		case LogLevel::Debug:
			#if LOGGER_MIN_LEVEL < 5
			#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, tag.c_str(), pMessage.c_str());
			#endif
			#endif
			break;
		}
		#ifndef NO_LOG_FILE
		tstringstream messageBuffer;
		messageBuffer << _T("[") << tag << _T("] ") << _T("[") << levelName <<  _T("] ") << pMessage << std::endl;
		LogMessage(messageBuffer.str());
		#endif
	#endif
#endif
	}

	void Logger::_CheckGlError(const schar* file, int32 line) 
	{
#if LOGGER_MIN_LEVEL > 0
		GLenum err (glGetError());
		while(err!= GL_NO_ERROR) 
		{
			tstring error;
			switch(err) 
			{
				case GL_INVALID_OPERATION:      
					error = _T("INVALID_OPERATION");     
					break;
				case GL_INVALID_ENUM:
					error = _T("INVALID_ENUM");
					break;
				case GL_INVALID_VALUE:
					error = _T("INVALID_VALUE");
					break;
				case GL_OUT_OF_MEMORY:  
					error = _T("OUT_OF_MEMORY"); 
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					error = _T("INVALID_FRAMEBUFFER_OPERATION");
					break;
				default:
					error =_T("UNKNOWN_ERROR");
					break;
			}
			tstringstream buffer;
			buffer << "GL_" << error << " - " << file << ":" << line << std::endl;
#ifndef NO_LOG_FILE
			LogMessage(buffer.str());
#endif
			Logger::GetInstance()->Log(LogLevel::Error, buffer.str(),_T("OPENGL"));
			err = glGetError();
		}
#endif
	}

	void Logger::SetLogSaveDelayTime(float32 seconds)
	{
#ifndef NO_LOG_FILE
		SceneManager::GetInstance()->GetStopwatch()->SetTargetTimeTimer(
			_T("STAR_LogSaveFileTimer"), seconds, true, false);
		SaveLogFile();
#endif
	}

	void Logger::InitializeLogStream()
	{
		SceneManager::GetInstance()->GetStopwatch()->CreateTimer(_T("STAR_LogSaveFileTimer"), 60.0f,
			false, true, [&] () { SaveLogFile(); }, false);

		m_LogStream << _T("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		m_LogStream << _T("	Star Engine version ") << STARENGINE_VERSION << std::endl << std::endl;
		m_LogStream << _T("	Game is built in");

	#ifdef _DEBUG
		m_LogStream << _T(" debug mode.\n");
	#else
		m_LogStream << _T(" release mode.\n");
#endif
	#if LOGGER_MIN_LEVEL < 2
		m_LogStream << _T("	All Star::Logging levels are enabled.\n");
	#elif LOGGER_MIN_LEVEL < 3
		m_LogStream << _T("	Star::Logging level info is disabled.\n");
	#elif LOGGER_MIN_LEVEL < 4
		m_LogStream << _T("	Star::Logging levels info and warning is disabled.\n");
	#elif LOGGER_MIN_LEVEL < 5
		m_LogStream << _T("	Star::Logging levels info, warning and error is disabled.\n");
	#elif LOGGER_MIN_LEVEL < 6
		m_LogStream << _T("	All Star::Logging levels are disabled.\n");
	#endif
		m_LogStream << std::endl;
		m_LogStream << _T("	The Star Engine is licensed under the MIT License. \n");
		m_LogStream << _T("	For more information you can go to http://www.starengine.eu/ \n\n");
		m_LogStream << _T("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	}
	
	void Logger::LogMessage(const tstring & message)
	{
		m_LogStream << _T("[") << m_TimeStamp << _T("] ") << message;
	}

	void Logger::SaveLogFile()
	{
		WriteTextFile(_T("StarLog.txt"), m_LogStream.str(), DirectoryMode::internal);
	}
}
