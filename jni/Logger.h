#pragma once

#include "defines.h"

#ifdef _WIN32
#include <windows.h>
#endif
//[TODO] : make singleton

namespace star {
	enum LogLevel {
			Info, 
			Warning, 
			Error, 
			Debug
		};

    class Logger {
    public:

		
		~Logger();

		// Static methods
		static Logger*  GetSingleton();
		static void ResetSingleton();

		void Initialize();
		void Log(LogLevel level, const tstring& pMessage, const tstring& tag = _T("STAR_ENGINE")) const;
		
	
	private:
		//SINGLETON IMPLEMENTATION
		//----------------------------------
		Logger(void);
		static Logger* mLoggerPtr;
		//----------------------------------

		#ifdef _WIN32
		HANDLE m_ConsoleHandle;
		#endif

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		Logger(const Logger& t);
		Logger& operator=(const Logger& t);
    };


}

