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

	float GetPitch(const glm::quat & quaternion);
	float GetYaw(const glm::quat & quaternion);
	float GetRoll(const glm::quat & quaternion);

	void GetTranslation(const mat4x4& matrix, pos & translation);
	void GetScaling(const mat4x4& matrix, vec2 & scaling);
	void GetRotation(const mat4x4& matrix, float & rotation);
	void GetRotationAndScaling(const mat4x4& matrix, float & rotation, vec2 & scaling);
	void DecomposeMatrix(const mat4x4& matrix, pos & position,
		vec2 & scaling, float & rotation);

	int32 GenerateRandomNumber(int32 min, int32 max);
	uint32 GenerateRandomNumber(uint32 min, uint32 max);
	int32 GenerateRandomNumber(int32 min, uint32 max);
	int32 GenerateRandomNumber(uint32 min, int32 max);
	float GenerateRandomNumber(float min, float max);
	double GenerateRandomNumber(double min, double max);
}
