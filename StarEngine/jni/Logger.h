#pragma once

#include "defines.h"
#include <memory>

namespace star 
{
	enum LogLevel : byte
	{
		Info, 
		Warning, 
		Error, 
		Debug
	};

    class Logger {
    public:
		~Logger();
		// Static methods
		static std::shared_ptr<Logger> GetInstance();
		static void ResetSingleton();

		void Initialize();
		void Log(LogLevel level, const tstring& pMessage, const tstring& tag = ANDROID_LOG_TAG) const;
		void _CheckGlError(const char* file, int line);
		#define CheckGlError() _CheckGlError(__FILE__,__LINE__);
	private:
		Logger(void);
		static std::shared_ptr<Logger> m_LoggerPtr;

		#ifdef _WIN32
		HANDLE m_ConsoleHandle;
		#endif

		Logger(const Logger& t);
		Logger(Logger&& t);
		Logger& operator=(const Logger& t);
    };
}
