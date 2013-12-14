#pragma once

#if defined(_WIN32)
	#define DESKTOP
#elif defined(ANDROID)
	#define MOBILE
#endif

#include "Helpers\SerializedData.h"
#include "definesTypes.h"

#define STARENGINE_VERSION _T("0.1.0")

#include <algorithm>

#include "definesMath.h"

#define EMPTY_STRING _T("")
#define NO_WRAPPING -1
#define STARENGINE_LOG_TAG _T("STARENGINE")
#define GAME_LOG_TAG _T("GAME")

#ifdef STAR2D
#include "defines2D.h" 
#endif

#ifdef ANDROID
#include "definesAndroid.h"
#endif

#ifdef _WIN32
#include "definesWindows.h"
#endif

/// <summary>
/// Enumeration that describes where the root of the path of a file can be found.
/// </summary>
enum class DirectoryMode : byte
{
	/// <summary>
	/// This is the default Assets folder on Android.
	/// On windows this directory is defined in the Win32Manifest.xml
	/// </summary>
	assets = 0,
	/// <summary>
	/// This is the default APK internal folder on Android.
	/// On windows this directory is defined in the Win32Manifest.xml
	/// </summary>
	internal,
	/// <summary>
	/// On android the root directory is '<SD-CARD>/<GAME-NAME>/'.
	/// On windows the root directory is '???/documents/<GAME-NAME>/'.
	/// </summary>
	external,
	/// <summary>
	/// Using this mode gives you the freedom to define a dynamic or static path yourself.
	/// We advice that you never use a static path in this mode, as it isn't portable
	/// to another device and/or platform.
	/// </summary>
	custom
};

/// <summary>
/// The default directory mode used by all functions related to I/O.
/// </summary>
static const DirectoryMode DEFAULT_DIRECTORY_MODE = DirectoryMode::assets;

#define UI_STATE_IDLE _T("idle")
#define UI_STATE_HOVER _T("hover")
#define UI_STATE_CLICK _T("click")
#define UI_STATE_DISABLE _T("disable")

#define TAB _T("    ")

/// <summary>
/// Value that can be used to create a stopwatch with the duration of +/- 1 frame
/// </summary>
static const float32 STOPWATCH_ONE_FRAME_DELAY = 0.016667f;

namespace star
{
	/// <summary>
	/// Delete a non-null pointer,
	/// and assign the nullptr value to the pointer when deleting succesfully.
	/// </summary>
	/// <param name="pointer">the pointer to the object to be deleted</param>
	template <typename T>
	inline void SafeDelete(T * &pointer)
	{
		if(pointer != nullptr)
		{
			delete pointer;
			pointer = nullptr;
		}
	}
}
