#pragma once

#if defined(_WIN32)
	#define DESKTOP
#elif defined(ANDROID)
	#define MOBILE
#endif

#include "Helpers\SerializedData.h"
#include "definesTypes.h"

#define STARENGINE_VERSION _T("0.0.1")

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
