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

		void Log(
			LogLevel level,
			const tstring& pMessage,
			const tstring& tag,
			const BreakInformation& breakInfo = BreakInformation()
			);
		void Log(
			LogLevel level,
			const tstring& pMessage,
			const BreakInformation& breakInfo = BreakInformation()
			);

		void Log(
			bool assert,
			const tstring& pMessage,
			const tstring& tag,
			const BreakInformation& breakInfo = BreakInformation()
			);
		void Log(
			bool assert,
			const tstring& pMessage,
			const BreakInformation& breakInfo = BreakInformation()
			);

		void DebugLog(
			LogLevel level,
			const tstring& pMessage,
			const tstring& tag,
			const BreakInformation& breakInfo = BreakInformation()
			);
		void DebugLog(
			LogLevel level,
			const tstring& pMessage,
			const BreakInformation& breakInfo = BreakInformation()
			);

		void DebugLog(
			const tstring& pMessage,
			const tstring& tag,
			const BreakInformation& breakInfo = BreakInformation()
			);
		void DebugLog(
			const tstring& pMessage,
			const BreakInformation& breakInfo = BreakInformation()
			);

		void OpenGLLog(
			const BreakInformation& breakInfo
			);

		void SetLogSaveDelayTime(float32 seconds);

	private:
		Logger();
		static Logger* m_LoggerPtr;

		void PrivateLog(
			LogLevel level,
			const tstring& pMessage,
			const tstring& tag,
			const tstring& levelName,
			const BreakInformation& breakInfo
			);

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

	#define LOG(...) \
		Logger::GetInstance()->Log( \
			##__VA_ARGS__, \
			BREAK_INFO() \
			) 

#ifdef _DEBUG
	#define DEBUG_LOG(...) \
		Logger::GetInstance()->DebugLog( \
			##__VA_ARGS__, \
			BREAK_INFO() \
			) 
#else
	#define DEBUG_LOG(...) ((void)0)
#endif

	
	#define OPENGL_LOG() \
		star::Logger::GetInstance()->OpenGLLog(BREAK_INFO());
}
