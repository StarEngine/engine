#include "Math.h"
#include "Rect.h"
#include <random>
#include "../StarEngine.h"
#include <math.h>

namespace star
{
	float32 Cotan(float32 x)
	{
		return 1.0f / tan(x);
	}

	float64 Cotan(float64 x)
	{
		return 1.0 / tan(x);
	}

	float128 Cotan(float128 x)
	{
		return 1.0 / tan(x);
	}

	fvec2 DegreesToRadians(const vec2 & degrees)
	{
		fvec2 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		return vec;
	}

	fvec3 DegreesToRadians(const fvec3 & degrees)
	{
		fvec3 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		vec.z = DegreesToRadians(degrees.z);
		return vec;
	}

	fvec4 DegreesToRadians(const fvec4 & degrees)
	{
		fvec4 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		vec.z = DegreesToRadians(degrees.z);
		vec.w = DegreesToRadians(degrees.w);
		return vec;
	}

	dvec2 DegreesToRadians(const dvec2 & degrees)
	{
		dvec2 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		return vec;
	}

	dvec3 DegreesToRadians(const dvec3 & degrees)
	{
		dvec3 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		vec.z = DegreesToRadians(degrees.z);
		return vec;
	}

	dvec4 DegreesToRadians(const dvec4 & degrees)
	{
		dvec4 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		vec.z = DegreesToRadians(degrees.z);
		vec.w = DegreesToRadians(degrees.w);
		return vec;
	}

	void DegreesToRadians(const vec2 & degIn, vec2 & degOut)
	{
		degOut.x = DegreesToRadians(degIn.x);
		degOut.y = DegreesToRadians(degIn.y);
	}

	void DegreesToRadians(const fvec3 & degIn, fvec3 & degOut)
	{
		degOut.x = DegreesToRadians(degIn.x);
		degOut.y = DegreesToRadians(degIn.y);
		degOut.z = DegreesToRadians(degIn.z);
	}

	void DegreesToRadians(const fvec4 & degIn, fvec4 & degOut)
	{
		degOut.x = DegreesToRadians(degIn.x);
		degOut.y = DegreesToRadians(degIn.y);
		degOut.z = DegreesToRadians(degIn.z);
		degOut.w = DegreesToRadians(degIn.w);
	}

	void DegreesToRadians(const dvec2 & degIn, dvec2 & degOut)
	{
		degOut.x = DegreesToRadians(degIn.x);
		degOut.y = DegreesToRadians(degIn.y);
	}

	void DegreesToRadians(const dvec3 & degIn, dvec3 & degOut)
	{
		degOut.x = DegreesToRadians(degIn.x);
		degOut.y = DegreesToRadians(degIn.y);
		degOut.z = DegreesToRadians(degIn.z);
	}

	void DegreesToRadians(const dvec4 & degIn, dvec4 & degOut)
	{
		degOut.x = DegreesToRadians(degIn.x);
		degOut.y = DegreesToRadians(degIn.y);
		degOut.z = DegreesToRadians(degIn.z);
		degOut.w = DegreesToRadians(degIn.w);
	}

	fvec2 RadiansToDegrees(const fvec2 & radians)
	{
		fvec2 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		return vec;
	}

	fvec3 RadiansToDegrees(const fvec3 & radians)
	{
		fvec3 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		vec.z = RadiansToDegrees(radians.z);
		return vec;
	}

	fvec4 RadiansToDegrees(const fvec4 & radians)
	{
		fvec4 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		vec.z = RadiansToDegrees(radians.z);
		vec.w = RadiansToDegrees(radians.w);
		return vec;
	}

	dvec2 RadiansToDegrees(const dvec2 & radians)
	{
		dvec2 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		return vec;
	}

	dvec3 RadiansToDegrees(const dvec3 & radians)
	{
		dvec3 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		vec.z = RadiansToDegrees(radians.z);
		return vec;
	}

	dvec4 RadiansToDegrees(const dvec4 & radians)
	{
		dvec4 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		vec.z = RadiansToDegrees(radians.z);
		vec.w = RadiansToDegrees(radians.w);
		return vec;
	}

	void RadiansToDegrees(const fvec2 & radIn, fvec2 & radOut)
	{
		radOut.x = RadiansToDegrees(radIn.x);
		radOut.y = RadiansToDegrees(radIn.y);
	}

	void RadiansToDegrees(const fvec3 & radIn, fvec3 & radOut)
	{
		radOut.x = RadiansToDegrees(radIn.x);
		radOut.y = RadiansToDegrees(radIn.y);
		radOut.z = RadiansToDegrees(radIn.z);
	}

	void RadiansToDegrees(const fvec4 & radIn, fvec4 & radOut)
	{
		radOut.x = RadiansToDegrees(radIn.x);
		radOut.y = RadiansToDegrees(radIn.y);
		radOut.z = RadiansToDegrees(radIn.z);
		radOut.w = RadiansToDegrees(radIn.w);
	}

	void RadiansToDegrees(const dvec2 & radIn, dvec2 & radOut)
	{
		radOut.x = RadiansToDegrees(radIn.x);
		radOut.y = RadiansToDegrees(radIn.y);
	}

	void RadiansToDegrees(const dvec3 & radIn, dvec3 & radOut)
	{
		radOut.x = RadiansToDegrees(radIn.x);
		radOut.y = RadiansToDegrees(radIn.y);
		radOut.z = RadiansToDegrees(radIn.z);
	}

	void RadiansToDegrees(const dvec4 & radIn, dvec4 & radOut)
	{
		radOut.x = RadiansToDegrees(radIn.x);
		radOut.y = RadiansToDegrees(radIn.y);
		radOut.z = RadiansToDegrees(radIn.z);
		radOut.w = RadiansToDegrees(radIn.w);
	}
	
	fvec2 Slerp(const fvec2 & start, const fvec2 & end, float32 percent)
	{
		float32 dot = Dot(start, end);
		dot = Clamp(dot, -1.0f, 1.0f);
		float32 theta = acos(dot) * percent;
		fvec2 relativeVec = end - start * dot;
		relativeVec = Normalize(relativeVec);
		return (start * float32(cos(theta))) +
				(relativeVec * float32(sin(theta)));
	}

	fvec3 Slerp(const fvec3 & start, const fvec3 & end, float32 percent)
	{
		float32 dot = Dot(start, end);
		dot = Clamp(dot, -1.0f, 1.0f);
		float32 theta = acos(dot) * percent;
		fvec3 relativeVec = end - start * dot;
		relativeVec = Normalize(relativeVec);
		return (start * float32(cos(theta))) +
				(relativeVec * float32(sin(theta)));
	}

	fvec4 Slerp(const fvec4 & start, const fvec4 & end, float32 percent)
	{
		float32 dot = Dot(start, end);
		dot = Clamp(dot, -1.0f, 1.0f);
		float32 theta = acos(dot) * percent;
		fvec4 relativeVec = end - start * dot;
		relativeVec = Normalize(relativeVec);
		return (start * float32(cos(theta))) +
				(relativeVec * float32(sin(theta)));
	}
	
	dvec2 Slerp(const dvec2 & start, const dvec2 & end, float64 percent)
	{
		float64 dot = Dot(start, end);
		dot = Clamp(dot, -1.0, 1.0);
		float64 theta = acos(dot) * percent;
		dvec2 relativeVec = end - start * dot;
		relativeVec = Normalize(relativeVec);
		return (start * float64(cos(theta))) +
				(relativeVec * float64(sin(theta)));
	}

	dvec3 Slerp(const dvec3 & start, const dvec3 & end, float64 percent)
	{
		float64 dot = Dot(start, end);
		dot = Clamp(dot, -1.0, 1.0);
		float64 theta = acos(dot) * percent;
		dvec3 relativeVec = end - start * dot;
		relativeVec = glm::normalize(relativeVec);
		return (start * float64(cos(theta))) +
				(relativeVec * float64(sin(theta)));
	}

	dvec4 Slerp(const dvec4 & start, const dvec4 & end, float64 percent)
	{
		float64 dot = Dot(start, end);
		dot = Clamp(dot, -1.0, 1.0);
		float64 theta = acos(dot) * percent;
		dvec4 relativeVec = end - start * dot;
		relativeVec = Normalize(relativeVec);
		return (start * float64(cos(theta))) +
				(relativeVec * float64(sin(theta)));
	}

	fquat Slerp(const fquat & start, const fquat & end, float32 percent)
	{
		fvec4 vec = Slerp(
			fvec4(start.x, start.y, start.z, start.w),
			fvec4(end.x, end.y, end.z, end.w),
			percent
			);
		return fquat(vec.x, vec.y, vec.z, vec.w);
	}

	dquat Slerp(const dquat & start, const dquat & end, float64 percent)
	{
		dvec4 vec = Slerp(
			dvec4(start.x, start.y, start.z, start.w),
			dvec4(end.x, end.y, end.z, end.w),
			percent
			);
		return dquat(vec.x, vec.y, vec.z, vec.w);
	}

	fvec2 Nlerp(const fvec2 & start, const fvec2 & end, float32 percent)
	{
		fvec2 result = Lerp(start, end, percent);
		Normalize(result, result);
		return result;
	}

	fvec3 Nlerp(const fvec3 & start, const fvec3 & end, float32 percent)
	{
		fvec3 result = Lerp(start, end, percent);
		Normalize(result, result);
		return result;
	}

	fvec4 Nlerp(const fvec4 & start, const fvec4 & end, float32 percent)
	{
		fvec4 result = Lerp(start, end, percent);
		Normalize(result, result);
		return result;
	}

	fquat Nlerp(const fquat & start, const fquat & end, float32 percent)
	{
		fvec4 vec = Lerp(
			fvec4(start.x, start.y, start.z, start.w),
			fvec4(end.x, end.y, end.z, end.w),
			percent
			);
		Normalize(vec, vec);
		return fquat(vec.x, vec.y, vec.z, vec.w);
	}

	dvec2 Nlerp(const dvec2 & start, const dvec2 & end, float64 percent)
	{
		dvec2 result = Lerp(start, end, percent);
		Normalize(result, result);
		return result;
	}

	dvec3 Nlerp(const dvec3 & start, const dvec3 & end, float64 percent)
	{
		dvec3 result = Lerp(start, end, percent);
		Normalize(result, result);
		return result;
	}

	dvec4 Nlerp(const dvec4 & start, const dvec4 & end, float64 percent)
	{
		dvec4 result = Lerp(start, end, percent);
		Normalize(result, result);
		return result;
	}

	dquat Nlerp(const dquat & start, const dquat & end, float64 percent)
	{
		dvec4 vec = Lerp(
			dvec4(start.x, start.y, start.z, start.w),
			dvec4(end.x, end.y, end.z, end.w),
			percent
			);
		Normalize(vec, vec);
		return dquat(vec.x, vec.y, vec.z, vec.w);
	}

	fmat2 Transpose(const fmat2& matrix)
	{
		return glm::transpose(matrix);
	}

	fmat3 Transpose(const fmat3& matrix)
	{
		return glm::transpose(matrix);
	}

	fmat4 Transpose(const fmat4& matrix)
	{
		return glm::transpose(matrix);
	}

	void Transpose(const fmat2& matIn, fmat2& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	void Transpose(const fmat3& matIn, fmat3& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	void Transpose(const fmat4& matIn, fmat4& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	dmat2 Transpose(const dmat2& matIn)
	{
		return glm::transpose(matIn);
	}

	dmat3 Transpose(const dmat3& matIn)
	{
		return glm::transpose(matIn);
	}

	dmat4 Transpose(const dmat4& matIn)
	{
		return glm::transpose(matIn);
	}

	void Transpose(const dmat2& matIn, dmat2& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	void Transpose(const dmat3& matIn, dmat3& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	void Transpose(const dmat4& matIn, dmat4& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	fmat2 Inverse(const fmat2 & mat)
	{
		return glm::inverse<float32>(mat);
	}

	fmat3 Inverse(const fmat3 & mat)
	{
		return glm::inverse<float32>(mat);
	}

	fmat4 Inverse(const fmat4 & mat)
	{
		return glm::inverse<float32>(mat);
	}

	fquat Inverse(const fquat & quat)
	{
		return glm::inverse<float32>(quat);
	}

	void Inverse(const fmat2 & mat, fmat2 & out)
	{
		out = glm::inverse<float32>(mat);
	}

	void Inverse(const fmat3 & mat, fmat3 & out)
	{
		out = glm::inverse<float32>(mat);
	}

	void Inverse(const fmat4 & mat, fmat4 & out)
	{
		out = glm::inverse<float32>(mat);
	}

	void Inverse(const fquat & quat, fquat & out)
	{
		out = glm::inverse<float32>(quat);
	}

	dmat2 Inverse(const dmat2 & mat)
	{
		return glm::inverse<float64>(mat);
	}

	dmat3 Inverse(const dmat3 & mat)
	{
		return glm::inverse<float64>(mat);
	}

	dmat4 Inverse(const dmat4 & mat)
	{
		return glm::inverse<float64>(mat);
	}

	dquat Inverse(const dquat & quat)
	{
		return glm::inverse<float64>(quat);
	}

	void Inverse(const dmat2 & mat, dmat2 & out)
	{
		out = glm::inverse<float64>(mat);
	}

	void Inverse(const dmat3 & mat, dmat3 & out)
	{
		out = glm::inverse<float64>(mat);
	}

	void Inverse(const dmat4 & mat, dmat4 & out)
	{
		out = glm::inverse<float64>(mat);
	}

	void Inverse(const dquat & quat, dquat & out)
	{
		out = glm::inverse<float64>(quat);
	}

	fmat4 LookAt(const fvec3 & eye, const fvec3 & center, const fvec3 & up)
	{
		return glm::lookAt<float32>(eye, center, up);
	}

	dmat4 LookAt(const dvec3 & eye, const dvec3 & center, const dvec3 & up)
	{
		return glm::lookAt<float64>(eye, center, up);
	}

	void LookAt(const fvec3 & eye, const fvec3 & center, const fvec3 & up, fmat4 & out)
	{
		out = glm::lookAt<float32>(eye, center, up);
	}

	void LookAt(const dvec3 & eye, const dvec3 & center, const dvec3 & up, fmat4 & out)
	{
		out = glm::lookAt<float64>(eye, center, up);
	}

	fvec2 Log(const fvec2 & vec)
	{
		return glm::log<float32>(vec);
	}

	fvec3 Log(const fvec3 & vec)
	{
		return glm::log<float32>(vec);
	}

	fvec4 Log(const fvec4 & vec)
	{
		return glm::log<float32>(vec);
	}

	fquat Log(const fquat & quat)
	{
		return glm::log<float32>(quat);
	}

	void Log(const fvec2 & vecIn, fvec2 & vecOut)
	{
		vecOut = glm::log<float32>(vecIn);
	}

	void Log(const fvec3 & vecIn, fvec3 & vecOut)
	{
		vecOut = glm::log<float32>(vecIn);
	}

	void Log(const fvec4 & vecIn, fvec4 & vecOut)
	{
		vecOut = glm::log<float32>(vecIn);
	}

	void Log(const fquat & quatIn, fquat & quatOut)
	{
		quatOut = glm::log<float32>(quatIn);
	}

	dvec2 Log(const dvec2 & vec)
	{
		return glm::log<float64>(vec);
	}

	dvec3 Log(const dvec3 & vec)
	{
		return glm::log<float64>(vec);
	}

	dvec4 Log(const dvec4 & vec)
	{
		return glm::log<float64>(vec);
	}

	dquat Log(const dquat & quat)
	{
		return glm::log<float64>(quat);
	}

	void Log(const dvec2 & vecIn, dvec2 & vecOut)
	{
		vecOut = glm::log<float64>(vecIn);
	}

	void Log(const dvec3 & vecIn, dvec3 & vecOut)
	{
		vecOut = glm::log<float64>(vecIn);
	}

	void Log(const dvec4 & vecIn, dvec4 & vecOut)
	{
		vecOut = glm::log<float64>(vecIn);
	}

	void Log(const dquat & quatIn, dquat & quatOut)
	{
		quatOut = glm::log<float64>(quatIn);
	}

	fvec2 Log2(const fvec2 & vec)
	{
		return glm::log2<float32>(vec);
	}

	fvec3 Log2(const fvec3 & vec)
	{
		return glm::log2<float32>(vec);
	}

	fvec4 Log2(const fvec4 & vec)
	{
		return glm::log2<float32>(vec);
	}

	void Log2(const fvec2 & vecIn, fvec2 & vecOut)
	{
		vecOut = glm::log2<float32>(vecIn);
	}

	void Log2(const fvec3 & vecIn, fvec3 & vecOut)
	{
		vecOut = glm::log2<float32>(vecIn);
	}

	void Log2(const fvec4 & vecIn, fvec4 & vecOut)
	{
		vecOut = glm::log2<float32>(vecIn);
	}

	dvec2 Log2(const dvec2 & vec)
	{
		return glm::log2<float64>(vec);
	}

	dvec3 Log2(const dvec3 & vec)
	{
		return glm::log2<float64>(vec);
	}

	dvec4 Log2(const dvec4 & vec)
	{
		return glm::log2<float64>(vec);
	}

	void Log2(const dvec2 & vecIn, dvec2 & vecOut)
	{
		vecOut = glm::log2<float64>(vecIn);
	}

	void Log2(const dvec3 & vecIn, dvec3 & vecOut)
	{
		vecOut = glm::log2<float64>(vecIn);
	}

	void Log2(const dvec4 & vecIn, dvec4 & vecOut)
	{
		vecOut = glm::log2<float64>(vecIn);
	}

	float32 GetPitch(const fquat & quaternion)
	{
		return float32(atan2f(2 * (
			quaternion.y * quaternion.z +
			quaternion.w * quaternion.x),
			quaternion.w * quaternion.w -
			quaternion.x * quaternion.x -
			quaternion.y * quaternion.y +
			quaternion.z * quaternion.z
			));
	}

	float32 GetYaw(const fquat & quaternion)
	{
		return float32(asinf(-2 * (
			quaternion.x * quaternion.z -
			quaternion.w * quaternion.y
			)));
	}

	float32 GetRoll(const fquat & quaternion)
	{
		return float32(atan2f(2 * (
			quaternion.x * quaternion.y +
			quaternion.w * quaternion.z),
			quaternion.w * quaternion.w +
			quaternion.x * quaternion.x -
			quaternion.y * quaternion.y -
			quaternion.z * quaternion.z
			));
	}

	float64 GetPitch(const dquat & quaternion)
	{
		return float64(atan2(2 * (
			quaternion.y * quaternion.z +
			quaternion.w * quaternion.x),
			quaternion.w * quaternion.w -
			quaternion.x * quaternion.x -
			quaternion.y * quaternion.y +
			quaternion.z * quaternion.z
			));
	}

	float64 GetYaw(const dquat & quaternion)
	{
		return float64(asin(-2 * (
			quaternion.x * quaternion.z -
			quaternion.w * quaternion.y
			)));
	}

	float64 GetRoll(const dquat & quaternion)
	{
		return float64(atan2(2 * (
			quaternion.x * quaternion.y +
			quaternion.w * quaternion.z),
			quaternion.w * quaternion.w +
			quaternion.x * quaternion.x -
			quaternion.y * quaternion.y -
			quaternion.z * quaternion.z
			));
	}

	void GetTranslation(const mat4& matrix, pos & translation)
	{
		translation.x = matrix[3][0];
		translation.y = matrix[3][1];
		translation.l = lay(matrix[3][2] / LAYER_HEIGHT);
	}

	void GetScaling(const mat4& matrix, vec2 & scaling)
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

	void GetRotation(const mat4& matrix, float32 & rotation)
	{
		vec2 scaling;
		GetRotationAndScaling(matrix, rotation, scaling);
	}
	
	void GetRotationAndScaling(const mat4& matrix,
		float32 & rotation, vec2 & scaling)
	{
		GetScaling(matrix, scaling);

		mat4 rot;

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

		quat rotQuat(rot);

		rotation = GetRoll(rotQuat);
	}

	void DecomposeMatrix(const mat4& matrix, pos & position,
		vec2 & scaling, float32 & rotation)
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

	float32 GenerateRandomNumber(float32 min, float32 max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_real_distribution<float32> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	float64 GenerateRandomNumber(float64 min, float64 max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_real_distribution<float64> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	float128 GenerateRandomNumber(float128 min, float128 max)
	{
		if(min == max)
		{
			return min;
		}
		std::uniform_real_distribution<float128> dist(min, max);
		return dist(StarEngine::GetInstance()->GetMt19937Engine());
	}

	float32 Mag(const fvec2 & vec)
	{
		return glm::length<float32>(vec);
	}

	float32 Mag(const fvec3 & vec)
	{
		return glm::length<float32>(vec);
	}

	float32 Mag(const fvec4 & vec)
	{
		return glm::length<float32>(vec);
	}
	
	float64 Mag(const dvec2 & vec)
	{
		return glm::length<float64>(vec);
	}

	float64 Mag(const dvec3 & vec)
	{
		return glm::length<float64>(vec);
	}

	float64 Mag(const dvec4 & vec)
	{
		return glm::length<float64>(vec);
	}
	
	float32 Dot(const fvec2 & vecA, const fvec2 & vecB)
	{
		return glm::dot<float32>(vecA, vecB);
	}

	float32 Dot(const fvec3 & vecA, const fvec3 & vecB)
	{
		return glm::dot<float32>(vecA, vecB);
	}

	float32 Dot(const fvec4 & vecA, const fvec4 & vecB)
	{
		return glm::dot<float32>(vecA, vecB);
	}

	float64 Dot(const dvec2 & vecA, const dvec2 & vecB)
	{
		return glm::dot<float64>(vecA, vecB);
	}

	float64 Dot(const dvec3 & vecA, const dvec3 & vecB)
	{
		return glm::dot<float64>(vecA, vecB);
	}

	float64 Dot(const dvec4 & vecA, const dvec4 & vecB)
	{
		return glm::dot<float64>(vecA, vecB);
	}

	fvec3 Cross(const fvec3 & vecA, const fvec3 & vecB)
	{	
		return glm::cross<float32>(vecA, vecB);
	}

	dvec3 Cross(const dvec3 & vecA, const dvec3 & vecB)
	{
		return glm::cross<float64>(vecA, vecB);
	}

	void Cross(const fvec3 & vecA, const fvec3 & vecB, fvec3 & vecOut)
	{
		vecOut = glm::cross<float32>(vecA, vecB);
	}

	void Cross(const dvec3 & vecA, const dvec3 & vecB, dvec3 & vecOut)
	{
		vecOut = glm::cross<float64>(vecA, vecB);
	}

	fvec2 Mul(const fvec2 & vec, const fmat2 & mat)
	{
		return glm::mul<float32>(vec, mat);
	}

	fvec3 Mul(const fvec3 & vec, const fmat3 & mat)
	{
		return glm::mul<float32>(vec, mat);
	}

	fvec4 Mul(const fvec4 & vec, const fmat4 & mat)
	{
		return glm::mul<float32>(vec, mat);
	}

	dvec2 Mul(const dvec2 & vec, const dmat2 & mat)
	{
		return glm::mul<float64>(vec, mat);
	}

	dvec3 Mul(const dvec3 & vec, const dmat3 & mat)
	{
		return glm::mul<float64>(vec, mat);
	}

	dvec4 Mul(const dvec4 & vec, const dmat4 & mat)
	{
		return glm::mul<float64>(vec, mat);
	}

	void Mul(const fvec2 & vecIn, const fmat2 & mat, fvec2 & vecOut)
	{
		vecOut = glm::mul<float32>(vecIn, mat);
	}

	void Mul(const fvec3 & vecIn, const fmat3 & mat, fvec3 & vecOut)
	{
		vecOut = glm::mul<float32>(vecIn, mat);
	}

	void Mul(const fvec4 & vecIn, const fmat4 & mat, fvec4 & vecOut)
	{
		vecOut = glm::mul<float32>(vecIn, mat);
	}

	void Mul(const dvec2 & vecIn, const dmat2 & mat, dvec2 & vecOut)
	{
		vecOut = glm::mul<float64>(vecIn, mat);
	}

	void Mul(const dvec3 & vecIn, const dmat3 & mat, dvec3 & vecOut)
	{
		vecOut = glm::mul<float64>(vecIn, mat);
	}

	void Mul(const dvec4 & vecIn, const dmat4 & mat, dvec4 & vecOut)
	{
		vecOut = glm::mul<float64>(vecIn, mat);
	}

	fvec2 Normalize(const fvec2 & vec)
	{
		return glm::normalize<float32>(vec);
	}

	fvec3 Normalize(const fvec3 & vec)
	{
		return glm::normalize<float32>(vec);
	}

	fvec4 Normalize(const fvec4 & vec)
	{
		return glm::normalize<float32>(vec);
	}

	void Normalize(const fvec2 & vecIn, fvec2 & vecOut)
	{
		vecOut = glm::normalize<float32>(vecIn);
	}

	void Normalize(const fvec3 & vecIn, fvec3 & vecOut)
	{
		vecOut = glm::normalize<float32>(vecIn);
	}

	void Normalize(const fvec4 & vecIn, fvec4 & vecOut)
	{
		vecOut = glm::normalize<float32>(vecIn);
	}

	dvec2 Normalize(const dvec2 & vec)
	{
		return glm::normalize<float64>(vec);
	}

	dvec3 Normalize(const dvec3 & vec)
	{
		return glm::normalize<float64>(vec);
	}

	dvec4 Normalize(const dvec4 & vec)
	{
		return glm::normalize<float64>(vec);
	}

	void Normalize(const dvec2 & vecIn, dvec2 & vecOut)
	{
		vecOut = glm::normalize<float64>(vecIn);
	}

	void Normalize(const dvec3 & vecIn, dvec3 & vecOut)
	{
		vecOut = glm::normalize<float64>(vecIn);
	}

	void Normalize(const dvec4 & vecIn, dvec4 & vecOut)
	{
		vecOut = glm::normalize<float64>(vecIn);
	}

	float32 Distance(const fvec2 & vecA, const fvec2 & vecB)
	{
		return glm::distance<float32>(vecA, vecB);
	}

	float32 Distance(const fvec3 & vecA, const fvec3 & vecB)
	{
		return glm::distance<float32>(vecA, vecB);
	}

	float32 Distance(const fvec4 & vecA, const fvec4 & vecB)
	{
		return glm::distance<float32>(vecA, vecB);
	}

	float64 Distance(const dvec2 & vecA, const dvec2 & vecB)
	{
		return glm::distance<float64>(vecA, vecB);
	}

	float64 Distance(const dvec3 & vecA, const dvec3 & vecB)
	{
		return glm::distance<float64>(vecA, vecB);
	}

	float64 Distance(const dvec4 & vecA, const dvec4 & vecB)
	{
		return glm::distance<float64>(vecA, vecB);
	}

	fmat3 ToMat3(const fquat & quaternion)
	{
		return glm::toMat3<float32>(quaternion);
	}

	dmat3 ToMat3(const dquat & quaternion)
	{
		return glm::toMat3<float64>(quaternion);
	}

	void ToMat3(const fquat & quaternion, fmat3 & out)
	{
		out = glm::toMat3<float32>(quaternion);
	}

	void ToMat3(const dquat & quaternion, dmat3 & out)
	{
		out = glm::toMat3<float64>(quaternion);
	}

	fmat4 ToMat4(const fquat & quaternion)
	{
		return glm::toMat4<float32>(quaternion);
	}

	dmat4 ToMat4(const dquat & quaternion)
	{
		return glm::toMat4<float64>(quaternion);
	}

	void ToMat4(const fquat & quaternion, fmat4 & out)
	{
		out = glm::toMat4<float32>(quaternion);
	}

	void ToMat4(const dquat & quaternion, dmat4 & out)
	{
		out = glm::toMat4<float64>(quaternion);
	}

	fmat4 Translate(const fmat4 & mat, const fvec3 & vec)
	{
		return glm::translate<float32>(mat, vec);
	}

	fmat4 Translate(const fmat4 & mat, float32 x, float32 y, float32 z)
	{
		return glm::translate<float32>(mat, x, y, z);
	}

	fmat4 Translate(const fvec3 & vec)
	{
		return glm::translate<float32>(vec);
	}

	fmat4 Translate(float32 x, float32 y, float32 z)
	{
		return glm::translate<float32>(x, y, z);
	}

	void Translate(const fmat4 & mat, const fvec3 & vec, fmat4 & out)
	{
		out = glm::translate<float32>(mat, vec);
	}

	void Translate(const fmat4 & mat, float32 x, float32 y, float32 z, fmat4 & out)
	{
		out = glm::translate<float32>(mat, x, y, z);
	}

	void Translate(const fvec3 & vec, fmat4 & out)
	{
		out = glm::translate<float32>(vec);
	}

	void Translate(float32 x, float32 y, float32 z, fmat4 & out)
	{
		out = glm::translate<float32>(x, y, z);
	}

	dmat4 Translate(const dmat4 & mat, const dvec3 & vec)
	{
		return glm::translate<float64>(mat, vec);
	}

	dmat4 Translate(const dmat4 & mat, float64 x, float64 y, float64 z)
	{
		return glm::translate<float64>(mat, x, y, z);
	}

	dmat4 Translate(const dvec3 & vec)
	{
		return glm::translate<float64>(vec);
	}

	dmat4 Translate(float64 x, float64 y, float64 z)
	{
		return glm::translate<float64>(x, y, z);
	}

	void Translate(const dmat4 & mat, const dvec3 & vec, dmat4 & out)
	{
		out = glm::translate<float64>(mat, vec);
	}

	void Translate(const dmat4 & mat, float64 x, float64 y, float64 z, dmat4 & out)
	{
		out = glm::translate<float64>(mat, x, y, z);
	}

	void Translate(const dvec3 & vec, dmat4 & out)
	{
		out = glm::translate<float64>(vec);
	}

	void Translate(float64 x, float64 y, float64 z, dmat4 & out)
	{
		out = glm::translate<float64>(x, y, z);
	}

	fmat4 Scale(const fmat4 & mat, const fvec3 & vec)
	{
		return glm::scale<float32>(mat, vec);
	}

	fmat4 Scale(const fmat4 & mat, float32 x, float32 y, float32 z)
	{
		return glm::scale<float32>(mat, x, y, z);
	}

	fmat4 Scale(const fvec3 & vec)
	{
		return glm::scale<float32>(vec);
	}

	fmat4 Scale(float32 x, float32 y, float32 z)
	{
		return glm::scale<float32>(x, y, z);
	}

	void Scale(const fmat4 & mat, const fvec3 & vec, fmat4 & out)
	{
		out = glm::scale<float32>(mat, vec);
	}

	void Scale(const fmat4 & mat, float32 x, float32 y, float32 z, fmat4 & out)
	{
		out = glm::scale<float32>(mat, x, y, z);
	}

	void Scale(const fvec3 & vec, fmat4 & out)
	{
		out = glm::scale<float32>(vec);
	}

	void Scale(float32 x, float32 y, float32 z, fmat4 & out)
	{
		out = glm::scale<float32>(x, y, z);
	}

	dmat4 Scale(const dmat4 & mat, const dvec3 & vec)
	{
		return glm::scale<float64>(mat, vec);
	}

	dmat4 Scale(const dmat4 & mat, float64 x, float64 y, float64 z)
	{
		return glm::scale<float64>(mat, x, y, z);
	}

	dmat4 Scale(const dvec3 & vec)
	{
		return glm::scale<float64>(vec);
	}

	dmat4 Scale(float64 x, float64 y, float64 z)
	{
		return glm::scale<float64>(x, y, z);
	}

	void Scale(const dmat4 & mat, const dvec3 & vec, dmat4 & out)
	{
		out = glm::scale<float64>(mat, vec);
	}

	void Scale(const dmat4 & mat, float64 x, float64 y, float64 z, dmat4 & out)
	{
		out = glm::scale<float64>(mat, x, y, z);
	}

	void Scale(const dvec3 & vec, dmat4 & out)
	{
		out = glm::scale<float64>(vec);
	}

	void Scale(float64 x, float64 y, float64 z, dmat4 & out)
	{
		out = glm::scale<float64>(x, y, z);
	}

	fvec2 Rotate(const fvec2 & vec, float32 angle)
	{
		return glm::rotate(vec, angle);
	}

	fvec3 Rotate(const fvec3 & vec, float32 angle, const fvec3 & normal)
	{
		return glm::rotate(vec, angle, normal);
	}

	fvec4 Rotate(const fvec4 & vec, float32 angle, const fvec3 & normal)
	{
		return glm::rotate(vec, angle, normal);
	}

	fmat4 Rotate(const fmat4 & mat, float32 angle, float32 x, float32 y, float32 z)
	{
		return glm::rotate(mat, angle, x, y, z);
	}

	fmat4 Rotate(const fvec3 & vec, float32 angle)
	{
		return glm::rotate(angle, vec);
	}

	fmat4 Rotate(float32 angle, float32 x, float32 y, float32 z)
	{
		return glm::rotate(angle, x, y, z);
	}

	fvec3 Rotate(const fquat & quat, const fvec3 & vec)
	{
		return glm::rotate(quat, vec);
	}

	fvec4 Rotate(const fquat & quat, const fvec4 & vec)
	{
		return glm::rotate(quat, vec);
	}

	void Rotate(const fvec2 & vec, float32 angle, fvec2 & out)
	{
		out = glm::rotate(vec, angle);
	}

	void Rotate(const fvec3 & vec, float32 angle, const fvec3 & normal, fvec3 & out)
	{
		out = glm::rotate(vec, angle, normal);
	}

	void Rotate(const fvec4 & vec, float32 angle, const fvec3 & normal, fvec4 & out)
	{
		out = glm::rotate(vec, angle, normal);
	}

	void Rotate(const fmat4 & mat, float32 angle, float32 x, float32 y, float32 z, fmat4 & out)
	{
		out = glm::rotate(mat, angle, x, y, z);
	}

	void Rotate(const fvec3 & vec, float32 angle, fmat4 & out)
	{
		out = glm::rotate(angle, vec);
	}

	void Rotate(float32 angle, float32 x, float32 y, float32 z, fmat4 & out)
	{
		out = glm::rotate(angle, x, y, z);
	}

	void Rotate(const fquat & quat, const fvec3 & vec, fvec3 & out)
	{
		out = glm::rotate(quat, vec);
	}

	void Rotate(const fquat & quat, const fvec4 & vec, fvec4 & out)
	{
		out = glm::rotate(quat, vec);
	}

	dvec2 Rotate(const dvec2 & vec, float64 angle)
	{
		return glm::rotate(vec, angle);
	}

	dvec3 Rotate(const dvec3 & vec, float64 angle, const dvec3 & normal)
	{
		return glm::rotate(vec, angle, normal);
	}

	dvec4 Rotate(const dvec4 & vec, float64 angle, const dvec3 & normal)
	{
		return glm::rotate(vec, angle, normal);
	}

	dmat4 Rotate(const dmat4 & mat, float64 angle, float64 x, float64 y, float64 z)
	{
		return glm::rotate(mat, angle, x, y, z);
	}

	dmat4 Rotate(const dvec3 & vec, float64 angle)
	{
		return glm::rotate(angle, vec);
	}

	dmat4 Rotate(float64 angle, float64 x, float64 y, float64 z)
	{
		return glm::rotate(angle, x, y, z);
	}

	dvec3 Rotate(const dquat & quat, const dvec3 & vec)
	{
		return glm::rotate(quat, vec);
	}

	dvec4 Rotate(const dquat & quat, const dvec4 & vec)
	{
		return glm::rotate(quat, vec);
	}

	void Rotate(const dvec2 & vec, float64 angle, dvec2 & out)
	{
		out = glm::rotate(vec, angle);
	}

	void Rotate(const dvec3 & vec, float64 angle, const dvec3 & normal, dvec3 & out)
	{
		out = glm::rotate(vec, angle, normal);
	}

	void Rotate(const dvec4 & vec, float64 angle, const dvec3 & normal, dvec4 & out)
	{
		out = glm::rotate(vec, angle, normal);
	}

	void Rotate(const dmat4 & mat, float64 angle, float64 x, float64 y, float64 z, dmat4 & out)
	{
		out = glm::rotate(mat, angle, x, y, z);
	}

	void Rotate(const dvec3 & vec, float64 angle, dmat4 & out)
	{
		out = glm::rotate(angle, vec);
	}

	void Rotate(float64 angle, float64 x, float64 y, float64 z, dmat4 & out)
	{
		out = glm::rotate(angle, x, y, z);
	}

	void Rotate(const dquat & quat, const dvec3 & vec, dvec3 & out)
	{
		out = glm::rotate(quat, vec);
	}

	void Rotate(const dquat & quat, const dvec4 & vec, dvec4 & out)
	{
		out = glm::rotate(quat, vec);
	}

	fvec2 Step(const fvec2 & edge, const fvec2 & x)
	{
		return glm::step<float32>(edge, x);
	}

	fvec3 Step(const fvec3 & edge, const fvec3 & x)
	{
		return glm::step<float32>(edge, x);
	}

	fvec4 Step(const fvec4 & edge, const fvec4 & x)
	{
		return glm::step<float32>(edge, x);
	}

	fvec2 Step(const fvec2 & edge, float32 x)
	{
		fvec2 vec(x, x);
		return glm::step<float32>(edge, vec);
	}

	fvec3 Step(const fvec3 & edge, float32 x)
	{
		fvec3 vec(x, x, x);
		return glm::step<float32>(edge, vec);
	}

	fvec4 Step(const fvec4 & edge, float32 x)
	{
		fvec4 vec(x, x, x, x);
		return glm::step<float32>(edge, vec);
	}

	void Step(const fvec2 & edge, const fvec2 & x, fvec2 & out)
	{
		out = glm::step<float32>(edge, x);
	}

	void Step(const fvec3 & edge, const fvec3 & x, fvec3 & out)
	{
		out = glm::step<float32>(edge, x);
	}

	void Step(const fvec4 & edge, const fvec4 & x, fvec4 & out)
	{
		out = glm::step<float32>(edge, x);
	}

	void Step(const fvec2 & edge, float32 x, fvec2 & out)
	{
		fvec2 vec(x, x);
		out = glm::step<float32>(edge, vec);
	}

	void Step(const fvec3 & edge, float32 x, fvec3 & out)
	{
		fvec3 vec(x, x, x);
		out = glm::step<float32>(edge, vec);
	}

	void Step(const fvec4 & edge, float32 x, fvec4 & out)
	{
		fvec4 vec(x, x, x, x);
		out = glm::step<float32>(edge, vec);
	}

	dvec2 Step(const dvec2 & edge, const dvec2 & x)
	{
		return glm::step<float64>(edge, x);
	}

	dvec3 Step(const dvec3 & edge, const dvec3 & x)
	{
		return glm::step<float64>(edge, x);
	}

	dvec4 Step(const dvec4 & edge, const dvec4 & x)
	{
		return glm::step<float64>(edge, x);
	}

	dvec2 Step(const dvec2 & edge, float64 x)
	{
		dvec2 vec(x, x);
		return glm::step<float64>(edge, vec);
	}

	dvec3 Step(const dvec3 & edge, float64 x)
	{
		dvec3 vec(x, x, x);
		return glm::step<float64>(edge, vec);
	}

	dvec4 Step(const dvec4 & edge, float64 x)
	{
		dvec4 vec(x, x, x, x);
		return glm::step<float64>(edge, vec);
	}

	void Step(const dvec2 & edge, const dvec2 & x, dvec2 & out)
	{
		out = glm::step<float64>(edge, x);
	}

	void Step(const dvec3 & edge, const dvec3 & x, dvec3 & out)
	{
		out = glm::step<float64>(edge, x);
	}

	void Step(const dvec4 & edge, const dvec4 & x, dvec4 & out)
	{
		out = glm::step<float64>(edge, x);
	}

	void Step(const dvec2 & edge, float64 x, dvec2 & out)
	{
		dvec2 vec(x, x);
		out = glm::step<float64>(edge, vec);
	}

	void Step(const dvec3 & edge, float64 x, dvec3 & out)
	{
		dvec3 vec(x, x, x);
		out = glm::step<float64>(edge, vec);
	}

	void Step(const dvec4 & edge, float64 x, dvec4 & out)
	{
		dvec4 vec(x, x, x, x);
		out = glm::step<float64>(edge, vec);
	}

	fvec2 Saturate(const fvec2 & vec)
	{
		return glm::saturate<float32>(vec);
	}

	fvec3 Saturate(const fvec3 & vec)
	{
		return glm::saturate<float32>(vec);
	}

	fvec4 Saturate(const fvec4 & vec)
	{
		return glm::saturate<float32>(vec);
	}

	dvec2 Saturate(const dvec2 & vec)
	{
		return glm::saturate<float64>(vec);
	}

	dvec3 Saturate(const dvec3 & vec)
	{
		return glm::saturate<float64>(vec);
	}

	dvec4 Saturate(const dvec4 & vec)
	{
		return glm::saturate<float64>(vec);
	}

	void Saturate(const fvec2 & vecIn, fvec2 & vecOut)
	{
		vecOut = glm::saturate<float32>(vecIn);
	}

	void Saturate(const fvec3 & vecIn, fvec3 & vecOut)
	{
		vecOut = glm::saturate<float32>(vecIn);
	}

	void Saturate(const fvec4 & vecIn, fvec4 & vecOut)
	{
		vecOut = glm::saturate<float32>(vecIn);
	}

	void Saturate(const dvec2 & vecIn, dvec2 & vecOut)
	{
		vecOut = glm::saturate<float64>(vecIn);
	}

	void Saturate(const dvec3 & vecIn, dvec3 & vecOut)
	{
		vecOut = glm::saturate<float64>(vecIn);
	}

	void Saturate(const dvec4 & vecIn, dvec4 & vecOut)
	{
		vecOut = glm::saturate<float64>(vecIn);
	}

	fvec2 Refract(const fvec2 & I, const fvec2 & N, float32 eta)
	{
		return glm::refract(I, N, eta);
	}

	fvec3 Refract(const fvec3 & I, const fvec3 & N, float32 eta)
	{
		return glm::refract(I, N, eta);
	}

	fvec4 Refract(const fvec4 & I, const fvec4 & N, float32 eta)
	{
		return glm::refract(I, N, eta);
	}

	void Refract(const fvec2 & I, const fvec2 & N, float32 eta, fvec2 & out)
	{
		out = glm::refract(I, N, eta);
	}

	void Refract(const fvec3 & I, const fvec3 & N, float32 eta, fvec3 & out)
	{
		out = glm::refract(I, N, eta);
	}

	void Refract(const fvec4 & I, const fvec4 & N, float32 eta, fvec4 & out)
	{
		out = glm::refract(I, N, eta);
	}

	dvec2 Refract(const dvec2 & I, const dvec2 & N, float32 eta)
	{
		return glm::refract(I, N, eta);
	}

	dvec3 Refract(const dvec3 & I, const dvec3 & N, float32 eta)
	{
		return glm::refract(I, N, eta);
	}

	dvec4 Refract(const dvec4 & I, const dvec4 & N, float32 eta)
	{
		return glm::refract(I, N, eta);
	}

	void Refract(const dvec2 & I, const dvec2 & N, float32 eta, dvec2 & out)
	{
		out = glm::refract(I, N, eta);
	}

	void Refract(const dvec3 & I, const dvec3 & N, float32 eta, dvec3 & out)
	{
		out = glm::refract(I, N, eta);
	}

	void Refract(const dvec4 & I, const dvec4 & N, float32 eta, dvec4 & out)
	{
		out = glm::refract(I, N, eta);
	}

	uint32 Mod(uint32 x, uint32 y)
	{
		return x % y;
	}

	int32 Mod(int32 x, int32 y)
	{
		return x % y;
	}

	float32 Mod(float32 x, float32 y)
	{
		return glm::modf<float32>(x, y);
	}

	float64 Mod(float64 x, float64 y)
	{
		return glm::modf<float64>(x, y);
	}

	fvec2 Mod(const fvec2 & x, const fvec2 & y)
	{
		return glm::mod<float32>(x, y);
	}

	fvec3 Mod(const fvec3 & x, const fvec3 & y)
	{
		return glm::mod<float32>(x, y);
	}

	fvec4 Mod(const fvec4 & x, const fvec4 & y)
	{
		return glm::mod<float32>(x, y);
	}

	dvec2 Mod(const dvec2 & x, const dvec2 & y)
	{
		return glm::mod<float64>(x, y);
	}

	dvec3 Mod(const dvec3 & x, const dvec3 & y)
	{
		return glm::mod<float64>(x, y);
	}

	dvec4 Mod(const dvec4 & x, const dvec4 & y)
	{
		return glm::mod<float64>(x, y);
	}

	void Mod(const fvec2 & x, const fvec2 & y, fvec2 & out)
	{
		out = glm::mod<float32>(x, y);
	}

	void Mod(const fvec3 & x, const fvec3 & y, fvec3 & out)
	{
		out = glm::mod<float32>(x, y);
	}

	void Mod(const fvec4 & x, const fvec4 & y, fvec4 & out)
	{
		out = glm::mod<float32>(x, y);
	}

	void Mod(const dvec2 & x, const dvec2 & y, dvec2 & out)
	{
		out = glm::mod<float64>(x, y);
	}

	void Mod(const dvec3 & x, const dvec3 & y, dvec3 & out)
	{
		out = glm::mod<float64>(x, y);
	}

	void Mod(const dvec4 & x, const dvec4 & y, dvec4 & out)
	{
		out = glm::mod<float64>(x, y);
	}

	fvec2 Mod(const fvec2 & x, float32 y)
	{
		return glm::mod<float32>(x, fvec2(y, y));
	}

	fvec3 Mod(const fvec3 & x, float32 y)
	{
		return glm::mod<float32>(x, fvec3(y, y, y));
	}

	fvec4 Mod(const fvec4 & x, float32 y)
	{
		return glm::mod<float32>(x, fvec4(y, y, y, y));
	}

	dvec2 Mod(const dvec2 & x, float64 y)
	{
		return glm::mod<float64>(x, dvec2(y, y));
	}

	dvec3 Mod(const dvec3 & x, float64 y)
	{
		return glm::mod<float64>(x, dvec3(y, y, y));
	}

	dvec4 Mod(const dvec4 & x, float64 y)
	{
		return glm::mod<float64>(x, dvec4(y, y, y, y));
	}

	void Mod(const fvec2 & x, float32 y, fvec2 & out)
	{
		out = glm::mod<float32>(x, fvec2(y, y));
	}

	void Mod(const fvec3 & x, float32 y, fvec3 & out)
	{
		out = glm::mod<float32>(x, fvec3(y, y, y));
	}

	void Mod(const fvec4 & x, float32 y, fvec4 & out)
	{
		out = glm::mod<float32>(x, fvec4(y, y, y, y));
	}

	void Mod(const dvec2 & x, float64 y, dvec2 & out)
	{
		out = glm::mod<float64>(x, dvec2(y, y));
	}

	void Mod(const dvec3 & x, float64 y, dvec3 & out)
	{
		out = glm::mod<float64>(x, dvec3(y, y, y));
	}

	void Mod(const dvec4 & x, float64 y, dvec4 & out)
	{
		out = glm::mod<float64>(x, dvec4(y, y, y, y));
	}

#ifdef STAR2D

	fmat3 Reflect(const fmat3 & mat, const fvec3 & normal)
	{
		return glm::reflect2D<float32>(mat, normal);
	}

	dmat3 Reflect(const dmat3 & mat, const dvec3 & normal)
	{
		return glm::reflect2D<float64>(mat, normal);
	}

	void Reflect(const fmat3 & matIn, const fvec3 & normal, fmat3 & matOut)
	{
		matOut = glm::reflect2D<float32>(matIn, normal);
	}

	void Reflect(const dmat3 & matIn, const dvec3 & normal, dmat3 & matOut)
	{
		matOut = glm::reflect2D<float64>(matIn, normal);
	}
	
	fmat3 Project(const fmat3 & mat, const fvec3 & normal)
	{
		return glm::proj2D<float32>(mat, normal);
	}

	dmat3 Project(const dmat3 & mat, const dvec3 & normal)
	{
		return glm::proj2D<float64>(mat, normal);
	}

	void Project(const fmat3 & matIn, const fvec3 & normal, fmat3 & matOut)
	{
		matOut = glm::proj2D<float32>(matIn, normal);
	}

	void Project(const dmat3 & matIn, const dvec3 & normal, dmat3 & matOut)
	{
		matOut = glm::proj2D<float64>(matIn, normal);
	}

#else

	fmat4 Reflect(const fmat4 & mat, const fvec4 & normal)
	{
		return glm::reflect3D<float32>(mat, normal);
	}

	dmat4 Reflect(const dmat4 & mat, const dvec4 & normal)
	{
		return glm::reflect3D<float64>(mat, normal);
	}

	void Reflect(const fmat4 & matIn, const fvec4 & normal, fmat4 & matOut)
	{
		matOut = glm::reflect3D<float32>(matIn, normal);
	}

	void Reflect(const dmat4 & matIn, const dvec4 & normal, dmat4 & matOut)
	{
		matOut = glm::reflect3D<float64>(matIn, normal);
	}

	fmat4 Project(const fmat4 & mat, const fvec4 & normal)
	{
		return glm::proj3D<float32>(mat, normal);
	}

	dmat4 Project(const dmat4 & mat, const dvec4 & normal)
	{
		return glm::proj3D<float64>(mat, normal);
	}

	void Project(const fmat4 & matIn, const fvec4 & normal, fmat4 & matOut)
	{
		matOut = glm::proj3D<float32>(matIn, normal);
	}

	void Project(const dmat4 & matIn, const dvec4 & normal, dmat4 & matOut)
	{
		matOut = glm::proj3D<float64>(matIn, normal);
	}

#endif

	const float32 * ToPointerValue(const fmat2 & mat)
	{
		return glm::value_ptr<float32>(mat);
	}

	const float32 * ToPointerValue(const fmat3 & mat)
	{
		return glm::value_ptr<float32>(mat);
	}

	const float32 * ToPointerValue(const fmat4 & mat)
	{
		return glm::value_ptr<float32>(mat);
	}

	const float32 * ToPointerValue(const fvec2 & vec)
	{
		return glm::value_ptr<float32>(vec);
	}

	const float32 * ToPointerValue(const fvec3 & vec)
	{
		return glm::value_ptr<float32>(vec);
	}

	const float32 * ToPointerValue(const fvec4 & vec)
	{
		return glm::value_ptr<float32>(vec);
	}

	const float32 * ToPointerValue(const fquat & quat)
	{
		return glm::value_ptr<float32>(quat);
	}

	const float64 * ToPointerValue(const dmat2 & mat)
	{
		return glm::value_ptr<float64>(mat);
	}

	const float64 * ToPointerValue(const dmat3 & mat)
	{
		return glm::value_ptr<float64>(mat);
	}

	const float64 * ToPointerValue(const dmat4 & mat)
	{
		return glm::value_ptr<float64>(mat);
	}

	const float64 * ToPointerValue(const dvec2 & vec)
	{
		return glm::value_ptr<float64>(vec);
	}

	const float64 * ToPointerValue(const dvec3 & vec)
	{
		return glm::value_ptr<float64>(vec);
	}

	const float64 * ToPointerValue(const dvec4 & vec)
	{
		return glm::value_ptr<float64>(vec);
	}

	const float64 * ToPointerValue(const dquat & quat)
	{
		return glm::value_ptr<float64>(quat);
	}

#ifdef STAR2D
	pos Lerp(const pos & start, const pos & end, float32 percent)
	{
		return pos(
			Lerp(start.pos2D(), end.pos2D(), percent),
			start.l
			);
	}

	pos Slerp(const pos & start, const pos & end, float32 percent)
	{
		return pos(
			Slerp(start.pos2D(), end.pos2D(), percent),
			start.l
			);
	}

	pos Nlerp(const pos & start, const pos & end, float32 percent)
	{
		return pos(
			Nlerp(start.pos2D(), end.pos2D(), percent),
			start.l
			);
	}

	float32 Mag(const pos & pos)
	{
		return Mag(pos.pos2D());
	}

	float32 Dot(const pos & posA, const pos & posB)
	{
		return Dot(posA.pos2D(), posB.pos2D());
	}

	pos Mul(const pos & position, const fmat2 & mat)
	{
		return 
			pos(
				Mul(position.pos2D(), mat),
				position.l
				);
	}

	void Mul(const pos & posIn, const fmat2 & mat, pos & posOut)
	{
		posOut = pos(
				Mul(posIn.pos2D(), mat),
				posIn.l
				);
	}

	pos Normalize(const pos & position)
	{
		return pos(
			Normalize(position.pos2D()),
			position.l
			);
	}

	void Normalize(const pos & posIn, pos & posOut)
	{
		posOut = pos(
			Normalize(posIn.pos2D()),
			posIn.l
			);
	}

	float32 Distance(const pos & posA, const pos & posB)
	{
		return Distance(posA.pos2D(), posB.pos2D());
	}

	fmat4 Translate(const pos & pos)
	{
		return Translate(pos.pos3D());
	}

	fmat4 Translate(const fmat4 & mat, const pos & pos)
	{
		fvec3 pos3D(pos.pos3D());
		return Translate(mat, pos3D);
	}

	void Translate(const pos & pos, fmat4 & out)
	{
		out = Translate(pos.pos3D());
	}

	void Translate(const fmat4 & mat, const pos & pos, fmat4 & out)
	{
		fvec3 pos3D(pos.pos3D());
		out = Translate(mat, pos3D);
	}

	fmat4 Scale(const pos & pos)
	{
		return Scale(pos.pos3D());
	}

	fmat4 Scale(const fmat4 & mat, const pos & pos)
	{
		fvec3 pos3D(pos.pos3D());
		return Scale(mat, pos3D);
	}

	void Scale(const pos & pos, fmat4 & out)
	{
		out = Scale(pos.pos3D());
	}

	void Scale(const fmat4 & mat, const pos & pos, fmat4 & out)
	{
		fvec3 pos3D(pos.pos3D());
		out = Scale(mat, pos3D);
	}

	fmat4 LookAt(const pos & eye, const pos & center)
	{
		return LookAt(eye.pos3D(), center.pos3D(), fvec3(0,0,1.0f));
	}

	void LookAt(const pos & eye, const pos & center, fmat4 & out)
	{
		out = LookAt(eye.pos3D(), center.pos3D(), fvec3(0,0,1.0f));
	}

	pos Log(const pos & pos)
	{
		return star::pos(Log(pos.pos2D()), pos.l);
	}

	void Log(const pos & posIn, pos & posOut)
	{
		posOut = star::pos(Log(posIn.pos2D()), posIn.l);
	}

	pos Log2(const pos & pos)
	{
		return star::pos(Log2(pos.pos2D()), pos.l);
	}

	void Log2(const pos & posIn, pos & posOut)
	{
		posOut = star::pos(Log2(posIn.pos2D()), posIn.l);
	}

	pos Step(const pos & pos, const fvec2 & x)
	{
		fvec2 pos2D = pos.pos2D();
		return star::pos(Step(pos2D, x), pos.l);
	}

	pos Step(const pos & pos, float32 x)
	{
		fvec2 pos2D = pos.pos2D();
		return star::pos(Step(pos2D, x), pos.l);
	}

	void Step(const pos & posIn, const fvec2 & x, pos & posOut)
	{
		fvec2 pos2D = posIn.pos2D();
		posOut = star::pos(Step(pos2D, x), posIn.l);
	}

	void Step(const pos & posIn, float32 x, pos & posOut)
	{
		fvec2 pos2D = posIn.pos2D();
		posOut = star::pos(Step(pos2D, x), posIn.l);
	}
	
	pos Mod(const pos & pos, const fvec2 & mod)
	{
		fvec2 pos2D = pos.pos2D();
		return star::pos(
			Mod(pos2D, mod),
			pos.l
			);
	}

	pos Mod(const pos & pos, float32 mod)
	{
		fvec2 pos2D = pos.pos2D();
		return star::pos(
			Mod(pos2D, mod),
			pos.l
			);
	}

	void Mod(const pos & posIn, const fvec2 & mod, pos & posOut)
	{
		fvec2 pos2D = posIn.pos2D();
		posOut = star::pos(
			Mod(pos2D, mod),
			posIn.l
			);
	}

	void Mod(const pos & posIn, float32 mod, pos & posOut)
	{
		fvec2 pos2D = posIn.pos2D();
		posOut = star::pos(
			Mod(pos2D, mod),
			posIn.l
			);
	}
#endif
}
