#pragma once

#include "definesTypes.h"

using std::min;
using std::max;

//OpenGL Math Library
#include "Helpers\glm\glm.h"
#include "Helpers\glm\ext.hpp"

typedef glm::ivec2 ivec2;
typedef glm::ivec3 ivec3;
typedef glm::ivec4 ivec4;

typedef glm::uvec2 uvec2;
typedef glm::uvec3 uvec3;
typedef glm::uvec4 uvec4;

typedef glm::fvec2 fvec2;
typedef glm::fvec3 fvec3;
typedef glm::fvec4 fvec4;

typedef glm::dvec2 dvec2;
typedef glm::dvec3 dvec3;
typedef glm::dvec4 dvec4;

typedef glm::fquat fquat;
typedef glm::dquat dquat;

typedef glm::fmat2 fmat2;
typedef glm::fmat3 fmat3;
typedef glm::fmat4 fmat4;

typedef glm::dmat2 dmat2;
typedef glm::dmat3 dmat3;
typedef glm::dmat4 dmat4;

typedef fvec2 vec2;
typedef fvec3 vec3;
typedef fvec4 vec4;

typedef fquat quat;

typedef fmat2 mat2;
typedef fmat3 mat3;
typedef fmat4 mat4;

/// <summary>
/// A constant value that represents the mathematical number 'Pi'.
/// </summary>
const float64 PI = 3.14159265358979323846264338327950288;
/// <summary>
/// The epsilon value used in this engine.
/// </summary>
const float32 EPSILON = 0.0000001f;