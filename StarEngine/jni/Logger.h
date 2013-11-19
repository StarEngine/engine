#pragma once

#include "defines.h"

namespace star 
{
	enum LogLevel : byte
	{
		Info, 
		Warning, 
		Error, 
		Debug
	};

	struct Context;

    class Logger final 
	{
    public:
		~Logger();
		static Logger* GetInstance();

#ifdef _WIN32
		void Initialize(bool useConsole);
#else
		void Initialize();
#endif
		void Update(const Context & context);

		void Log(LogLevel level, const tstring& pMessage, const tstring& tag = ANDROID_LOG_TAG);
		void _CheckGlError(const schar* file, int32 line);
		#define CheckGlError() _CheckGlError(__FILE__,__LINE__);

		void SetLogSaveDelayTime(float32 seconds);

	private:
		Logger();
		static Logger* m_LoggerPtr;

		void InitializeLogStream();
		void LogMessage(const tstring & message);
		void SaveLogFile();

		#ifdef _WIN32
		bool m_UseConsole;
		HANDLE m_ConsoleHandle;
		#endif

		tstringstream m_LogStream;
		tstring m_TimeStamp;

		Logger(const Logger& t);
		Logger(Logger&& t);
		Logger& operator=(const Logger& t);
		Logger& operator=(Logger&& t);
    };
}
