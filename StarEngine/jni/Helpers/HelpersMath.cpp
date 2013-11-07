#include "HelpersMath.h"
#include "Rect.h"

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
		float x1, y1, z1, w1,
			  x2, y2, z2, w2,
			  x3, y3, z3, w3,
			  x4, y4, z4, w4;

		x1 = matrix[0][0];
		x2 = matrix[1][0];
		x3 = matrix[2][0];
		x4 = matrix[3][0];

		y1 = matrix[0][1];
		y2 = matrix[1][1];
		y3 = matrix[2][1];
		y4 = matrix[3][1];

		z1 = matrix[0][2];
		z2 = matrix[1][2];
		z3 = matrix[2][2];
		z4 = matrix[3][2];

		w1 = matrix[0][3];
		w2 = matrix[1][3];
		w3 = matrix[2][3];
		w4 = matrix[3][3];

		mat4x4 TransposeMatrix
		(
		x1, y1, z1, x4,
		x2, y2, z2, y4,
		x3, y3, z3, z4,
		w1, w2, w3, w4
		);

		return TransposeMatrix;
	}

int GenerateRandomNumber(int min, int max)
{
	if (min >= 0 && max > min)
	{
		return (rand() % (max-min + 1)) + min;
	}
	else if (min == max)
	{
		return min;
	}
	else if (min < 0 && max > min)
	{
		return (rand() % (abs(min)+max + 1)) + min;
	}

	else if (min > max)
	{
		if (max >= 0)
		{
			return (rand() % (min - max + 1) + max);
		}
		else
		{
			return (rand() % (abs(max) + min + 1)) + min;
		}
	}
	ASSERT(false, _T("Unknown case of random number generation."));
	return 0;
}

uint32 GenerateRandomNumber(uint32 min, uint32 max)
{
	if(max > min)
	{
		return (rand() % (max-min + 1)) + min;
	}
	else if(max == min)
	{
		return min;
	}
	else if(min > max)
	{
		return (rand() % (min - max + 1) + max);
	}
	ASSERT(false, _T("Unknown case of random number generation."));
	return 0;
}

int32 GenerateRandomNumber(int32 min, uint32 max)
{
	if (min >= 0 && max > uint32(min))
	{
		return (rand() % (max-min + 1)) + min;
	}
	else if (min == max)
	{
		return min;
	}
	else if (min < 0)
	{
		return (rand() % (abs(min)+max + 1)) + min;
	}

	else if (min > int32(max))
	{

		return (rand() % (min - max + 1) + max);


	}
	ASSERT(false, _T("Unknown case of random number generation."));
	return 0;
	}
}

int32 GenerateRandomNumber(uint32 min, int32 max)
{
	if (max > int(min))
	{
		return (rand() % (max-min + 1)) + min;
	}
	else if (min == max)
	{
		return min;
	}
	else if (int(min) > max)
	{
		if (max >= 0)
		{
			return (rand() % (min - max + 1) + max);
		}
		else
		{
			return (rand() % (abs(max) + min + 1)) + min;
		}
	}
	ASSERT(false, _T("Unknown case of random number generation."));
	return 0;
}

float GenerateRandomNumber(float min, float max)
{
	if (min == max)
	{
		return min;
	}
	else
	{
		return (min + (float)rand() / ((float)RAND_MAX / (max - min)));
	}
}

double GenerateRandomNumber(double min, double max)
{
	if (min == max)
	{
		return min;
	}
	else
	{
		return (min + (double)rand() / ((double)RAND_MAX / (max - min)));
	}
}
