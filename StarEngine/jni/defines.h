#pragma once

#if defined(_WIN32)
	#define DESKTOP
#elif defined(ANDROID)
	#define MOBILE
#endif

#include "Helpers\SerializedData.h"
#include "definesTypes.h"

#define STARENGINE_VERSION _T("0.0.3")

#include <algorithm>

#include "definesMath.h"

#define EMPTY_STRING _T("")
#define ANDROID_LOG_TAG _T("STAR_ENGINE")
#define NO_WRAPPING -1

#ifdef STAR2D
#include "defines2D.h" 
#endif

#ifdef ANDROID
#include "definesAndroid.h"
#endif

#ifdef _WIN32
#include "definesWindows.h"
#endif

enum class DirectoryMode : byte
{
	assets = 0,
	internal,
	external,
	custom
};

#define UI_STATE_IDLE _T("idle")
#define UI_STATE_HOVER _T("hover")
#define UI_STATE_CLICK _T("click")
#define UI_STATE_DISABLE _T("disable")

namespace star
{
	template <typename T>
	inline void SafeDelete(T * pointer)
	{
		if(pointer != nullptr)
		{
			delete pointer;
			pointer = nullptr;
		}
	}
}
