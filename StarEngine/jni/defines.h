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

using std::min;
using std::max;

//OpenGL Math Library
#include "Helpers\glm\glm.h"
#include "Helpers\glm\ext.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::quat;
using glm::mat4x4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;

const double PI = 3.14159265358979323846264338327950288;

#define EMPTY_STRING _T("")
#define ANDROID_LOG_TAG _T("STAR_ENGINE")
#define NO_WRAPPING -1
const float EPSILON = 0.0000001f;

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
