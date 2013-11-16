#include "HelpersMath.h"
#include "Rect.h"
#include <random>
#include "../StarEngine.h"
#include <math.h>

namespace star
{
	float DegreesToRadians(float degrees)
	{
		return degrees * (float)PI / 180.0f;
	}

	vec2 DegreesToRadians(const vec2 & degrees)
	{
		vec2 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		return vec;
	}

	vec3 DegreesToRadians(const vec3 & degrees)
	{
		vec3 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		vec.z = DegreesToRadians(degrees.z);
		return vec;
	}

	vec4 DegreesToRadians(const vec4 & degrees)
	{
		vec4 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		vec.z = DegreesToRadians(degrees.z);
		vec.w = DegreesToRadians(degrees.w);
		return vec;
	}

	float RadiansToDegrees(float radians)
	{
		return radians * 180.0f / (float)PI;
	}

	vec2 RadiansToDegrees(const vec2 & radians)
	{
		vec2 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		return vec;
	}

	vec3 RadiansToDegrees(const vec3 & radians)
	{
		vec3 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		vec.z = RadiansToDegrees(radians.z);
		return vec;
	}

	vec4 RadiansToDegrees(const vec4 & radians)
	{
		vec4 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		vec.z = RadiansToDegrees(radians.z);
		vec.w = RadiansToDegrees(radians.w);
		return vec;
	}
	
	vec2 Slerp(const vec2 & start, const vec2 & end, float percent)
	{
		float dot = glm::dot(start, end);
		dot = Clamp(dot, -1.0f, 1.0f);
		float theta = acos(dot) * percent;
		vec2 relativeVec = end - start * dot;
		relativeVec = glm::normalize(relativeVec);
		return (start * cos(theta)) + (relativeVec * sin(theta));
	}

	vec3 Slerp(const vec3 & start, const vec3 & end, float percent)
	{
		float dot = glm::dot(start, end);
		dot = Clamp(dot, -1.0f, 1.0f);
		float theta = acos(dot) * percent;
		vec3 relativeVec = end - start * dot;
		relativeVec = glm::normalize(relativeVec);
		return (start * cos(theta)) + (relativeVec * sin(theta));
	}

	vec4 Slerp(const vec4 & start, const vec4 & end, float percent)
	{
		float dot = glm::dot(start, end);
		dot = Clamp(dot, -1.0f, 1.0f);
		float theta = acos(dot) * percent;
		vec4 relativeVec = end - start * dot;
		relativeVec = glm::normalize(relativeVec);
		return (start * cos(theta)) + (relativeVec * sin(theta));
	}

	quat Slerp(const quat & start, const quat & end, float percent)
	{
		vec4 vec = Slerp(
			vec4(start.x, start.y, start.z, start.w),
			vec4(end.x, end.y, end.z, end.w),
			percent
			);
		return quat(vec.x, vec.y, vec.z, vec.w);
	}

	vec2 Nlerp(const vec2 & start, const vec2 & end, float percent)
	{
		return glm::normalize(Lerp(start, end, percent));
	}

	vec3 Nlerp(const vec3 & start, const vec3 & end, float percent)
	{
		return glm::normalize(Lerp(start, end, percent));
	}

	vec4 Nlerp(const vec4 & start, const vec4 & end, float percent)
	{
		return glm::normalize(Lerp(start, end, percent));
	}

	quat Nlerp(const quat & start, const quat & end, float percent)
	{
		vec4 vec = Lerp(
			vec4(start.x, start.y, start.z, start.w),
			vec4(end.x, end.y, end.z, end.w),
			percent
			);
		vec = glm::normalize(vec);
		return quat(vec.x, vec.y, vec.z, vec.w);
	}

	mat4x4 TransposeMatrix(const mat4x4& matrix)
	{
		return glm::transpose(matrix);
	}

	float GetPitch(const glm::quat & quaternion)
    {
		return float(atan2f(2 * (
			quaternion.y * quaternion.z +
			quaternion.w * quaternion.x),
            quaternion.w * quaternion.w -
			quaternion.x * quaternion.x -
			quaternion.y * quaternion.y +
			quaternion.z * quaternion.z
			));
    }

    float GetYaw(const glm::quat & quaternion)
    {
		return float(asinf(-2 * (
			quaternion.x * quaternion.z -
			quaternion.w * quaternion.y
			)));
    }

    float GetRoll(const glm::quat & quaternion)
    {
		return float(atan2f(2 * (
			quaternion.x * quaternion.y +
			quaternion.w * quaternion.z),
            quaternion.w * quaternion.w +
			quaternion.x * quaternion.x -
			quaternion.y * quaternion.y -
			quaternion.z * quaternion.z
			));
    }

	void GetTranslation(const mat4x4& matrix, pos & translation)
	{
		translation.x = matrix[3][0];
		translation.y = matrix[3][1];
		translation.l = lay(matrix[3][2] / LAYER_HEIGHT);
	}

	void GetScaling(const mat4x4& matrix, vec2 & scaling)
	{
		scaling.x = sqrt(
			pow(matrix[0][0], 2) +
			pow(matrix[1][0], 2) +
			pow(matrix[2][0], 2)
			);
		scaling.y = sqrt(
			pow(matrix[0][1], 2) +
			pow(matrix[1][1], 2) +
			pow(matrix[2][1], 2)
			);
	}

	void GetRotation(const mat4x4& matrix, float & rotation)
	{
		vec2 scaling;
		GetRotationAndScaling(matrix, rotation, scaling);
	}
	
	void GetRotationAndScaling(const mat4x4& matrix,
		float & rotation, vec2 & scaling)
	{
		GetScaling(matrix, scaling);

		mat4x4 rot;

		if(scaling.x != 0)
		{
			rot[0][0] = matrix[0][0] / scaling.x;
			rot[0][1] = matrix[0][1] / scaling.x;
			rot[0][2] = matrix[0][2] / scaling.x;
			rot[0][3] = 0;
		}

		if(scaling.y != 0)
		{
			rot[1][0] = matrix[1][0] / scaling.y;
			rot[1][1] = matrix[1][1] / scaling.y;
			rot[1][2] = matrix[1][2] / scaling.y;
			rot[1][3] = 0;
		}

		rot[2][0] = matrix[2][0];
		rot[2][1] = matrix[2][1];
		rot[2][2] = matrix[2][2];
		rot[2][3] = 0;

		rot[3][0] = 0;
		rot[3][1] = 0;
		rot[3][2] = 0;
		rot[3][3] = 1;

		glm::quat rotQuat(rot);

		rotation = GetRoll(rotQuat);
	}

	void DecomposeMatrix(const mat4x4& matrix, pos & position,
		vec2 & scaling, float & rotation)
	{
		GetTranslation(matrix, position);
		GetRotationAndScaling(matrix, rotation, scaling);
	}

	int32 GenerateRandomNumber(int32 min, int32 max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_int_distribution<int32> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	uint32 GenerateRandomNumber(uint32 min, uint32 max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_int_distribution<uint32> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	int32 GenerateRandomNumber(int32 min, uint32 max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_int_distribution<int32> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	int32 GenerateRandomNumber(uint32 min, int32 max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_int_distribution<int32> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	float GenerateRandomNumber(float min, float max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_real_distribution<float> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	double GenerateRandomNumber(double min, double max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_real_distribution<double> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}
}
