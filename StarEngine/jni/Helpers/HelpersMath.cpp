#include "HelpersMath.h"
#include "Rect.h"
#include <random>
#include "../StarEngine.h"

namespace star
{
	float DegreesToRadians(float degrees)
	{
		return degrees * 180.0f / (float)PI;
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
		return radians * (float)PI / 180.0f;
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

	

	mat4x4 TransposeMatrix(const mat4x4& matrix)
	{
		return glm::transpose(matrix);
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
		std::normal_distribution<float> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	double GenerateRandomNumber(double min, double max)
	{
		if(min == max)
		{
			return min;
		}
		std::normal_distribution<double> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}
}
