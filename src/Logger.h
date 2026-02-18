#pragma once

#include "defines.h"
#include "Helpers/Singleton.h"

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

	class Logger final : public Singleton<Logger>
	{
	public:
		friend Singleton<Logger>;

#ifdef _WIN32
		void Initialize(bool useConsole);
#else
		void Initialize();
#endif
		void Update(const Context & context);

		void Log(
			LogLevel level,
			const tstring& message,
			const tstring& tag,
			const BreakInformation& breakInfo = BreakInformation()
			);
		void Log(
			LogLevel level,
			const tstring& message,
			const BreakInformation& breakInfo = BreakInformation()
			);

		void DebugLog(
			LogLevel level,
			const tstring& message,
			const tstring& tag,
			const BreakInformation& breakInfo = BreakInformation()
			);
		void DebugLog(
			LogLevel level,
			const tstring& message,
			const BreakInformation& breakInfo = BreakInformation()
			);

		void DebugLog(
			const tstring& message,
			const tstring& tag,
			const BreakInformation& breakInfo = BreakInformation()
			);
		void DebugLog(
			const tstring& message,
			const BreakInformation& breakInfo = BreakInformation()
			);

		void OpenGLLog(
			const BreakInformation& breakInfo
			);

		void SetLogSaveDelayTime(float32 seconds);

	private:
		Logger();
		~Logger();

		void PrivateLog(
			LogLevel level,
			const tstring& message,
			const tstring& tag,
			const tstring& levelName,
			const BreakInformation& breakInfo
			);

		void InitializeLogStream();
		void LogMessage(const tstring& message);
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

#define LOG(...) \
	star::Logger::GetInstance()->Log( \
		__VA_ARGS__, \
		BREAK_INFO() \
		) 

#ifdef _DEBUG
	#define X_ASSERT_LOG_BREAK __asm { int 3 }
#else
	#define X_ASSERT_LOG_BREAK
#endif

#define ASSERT_LOG \
	if ( false ) {} \
	else \
	struct LocalAssertLog { \
			int32 mLine; \
			LocalAssertLog(int32 line=__LINE__) : mLine(line) {} \
			LocalAssertLog(bool isOK, const tstring& message, \
				const tstring& tag = GAME_LOG_TAG) : mLine(0) { \
				if ( !isOK ) { \
					LocalAssertLog info; \
					star::Logger::GetInstance()->Log( \
						star::LogLevel::Error, message, tag, \
						BreakInformation(info.mLine, __FILE__)); \
					X_ASSERT_LOG_BREAK \
				} \
		} \
	} myAssertLogger = LocalAssertLog

#ifdef _DEBUG
	#define DEBUG_LOG(...) \
		star::Logger::GetInstance()->DebugLog( \
			##__VA_ARGS__, \
			BREAK_INFO() \
			) 
#else
	#define DEBUG_LOG(...) ((void)0)
#endif
	#define OPENGL_LOG() \
		star::Logger::GetInstance()->OpenGLLog(BREAK_INFO());
