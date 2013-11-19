#include "HelpersMath.h"
#include "Rect.h"
#include <random>
#include "../StarEngine.h"
#include <math.h>

namespace star
{
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

	fmat2 TransposeMatrix(const fmat2& matrix)
	{
		return glm::transpose(matrix);
	}

	fmat3 TransposeMatrix(const fmat3& matrix)
	{
		return glm::transpose(matrix);
	}

	fmat4 TransposeMatrix(const fmat4& matrix)
	{
		return glm::transpose(matrix);
	}

	void TransposeMatrix(const fmat2& matIn, fmat2& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	void TransposeMatrix(const fmat3& matIn, fmat3& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	void TransposeMatrix(const fmat4& matIn, fmat4& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	dmat2 TransposeMatrix(const dmat2& matIn)
	{
		return glm::transpose(matIn);
	}

	dmat3 TransposeMatrix(const dmat3& matIn)
	{
		return glm::transpose(matIn);
	}

	dmat4 TransposeMatrix(const dmat4& matIn)
	{
		return glm::transpose(matIn);
	}

	void TransposeMatrix(const dmat2& matIn, dmat2& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	void TransposeMatrix(const dmat3& matIn, dmat3& matOut)
	{
		matOut = glm::transpose(matIn);
	}

	void TransposeMatrix(const dmat4& matIn, dmat4& matOut)
	{
		matOut = glm::transpose(matIn);
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

#ifdef STAR2D
	pos Lerp(const pos & start, const pos & end, float percent)
	{
		return pos(
			Lerp(start.pos2D(), end.pos2D(), percent),
			start.l
			);
	}

	pos Slerp(const pos & start, const pos & end, float percent)
	{
		return pos(
			Slerp(start.pos2D(), end.pos2D(), percent),
			start.l
			);
	}

	pos Nlerp(const pos & start, const pos & end, float percent)
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
#endif
}
