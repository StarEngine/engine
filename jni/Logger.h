#ifndef _STAR_LOGGER_HPP_
#define _STAR_LOGGER_HPP_

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

		Logger();
		void Initialize();
		void Log(LogLevel level, const tstring& pMessage, const tstring& tag = _T("STAR_ENGINE")) const;
		
	#ifdef _WIN32
	private:
	
		HANDLE m_ConsoleHandle;
	#endif
    };


}

#endif
