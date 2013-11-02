#pragma once

#include "../defines.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"

namespace star
{
	float DegreesToRadians(float degrees);
	vec2 DegreesToRadians(const vec2 & degrees);
	vec3 DegreesToRadians(const vec3 & degrees);
	vec4 DegreesToRadians(const vec4 & degrees);

	float RadiansToDegrees(float degrees);
	vec2 RadiansToDegrees(const vec2 & degrees);
	vec3 RadiansToDegrees(const vec3 & degrees);
	vec4 RadiansToDegrees(const vec4 & degrees);

	mat4x4 TransposeMatrix(const mat4x4& matrix);
}
