#pragma once

#include "../defines.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"

namespace star
{
	float32 Cotan(float32 x);
	float64 Cotan(float64 x);
	float128 Cotan(float128 x);

	template <typename T>
	T DegreesToRadians(T degrees)
	{
		return T(float64(degrees) * PI / 180);
	}

	template float32 DegreesToRadians<float32>(float32);
	template float64 DegreesToRadians<float64>(float64);
	template float128 DegreesToRadians<float128>(float128);

	fvec2 DegreesToRadians(const fvec2 & degrees);
	fvec3 DegreesToRadians(const fvec3 & degrees);
	fvec4 DegreesToRadians(const fvec4 & degrees);

	dvec2 DegreesToRadians(const dvec2 & degrees);
	dvec3 DegreesToRadians(const dvec3 & degrees);
	dvec4 DegreesToRadians(const dvec4 & degrees);

	void DegreesToRadians(const fvec2 & degIn, fvec2 & degOut);
	void DegreesToRadians(const fvec3 & degIn, fvec3 & degOut);
	void DegreesToRadians(const fvec4 & degIn, fvec4 & degOut);

	void DegreesToRadians(const dvec2 & degIn, dvec2 & degOut);
	void DegreesToRadians(const dvec3 & degIn, dvec3 & degOut);
	void DegreesToRadians(const dvec4 & degIn, dvec4 & degOut);

	template <typename T>
	T RadiansToDegrees(T radians)
	{
		return T(float64(radians) * 180 / PI);
	}

	template float32 RadiansToDegrees<float32>(float32);
	template float64 RadiansToDegrees<float64>(float64);
	template float128 RadiansToDegrees<float128>(float128);

	fvec2 RadiansToDegrees(const fvec2 & radians);
	fvec3 RadiansToDegrees(const fvec3 & radians);
	fvec4 RadiansToDegrees(const fvec4 & radians);

	dvec2 RadiansToDegrees(const dvec2 & radians);
	dvec3 RadiansToDegrees(const dvec3 & radians);
	dvec4 RadiansToDegrees(const dvec4 & radians);

	void RadiansToDegrees(const fvec2 & radIn, fvec3 & radOut);
	void RadiansToDegrees(const fvec3 & radIn, fvec4 & radOut);
	void RadiansToDegrees(const fvec4 & radIn, fvec4 & radOut);

	void RadiansToDegrees(const dvec2 & radIn, dvec2 & radOut);
	void RadiansToDegrees(const dvec3 & radIn, dvec3 & radOut);
	void RadiansToDegrees(const dvec4 & radIn, dvec4 & radOut);

	template <typename T>
	inline T Clamp(T x, T min, T max)
	{
		return x < min ? min : (x > max ? max : x);
	}
	
	template int16 Clamp<int16>(int16, int16, int16);
	template uint16 Clamp<uint16>(uint16, uint16, uint16);
	template uint32 Clamp<uint32>(uint32, uint32, uint32);
	template int32 Clamp<int32>(int32, int32, int32);
	template uint64 Clamp<uint64>(uint64, uint64, uint64);
	template int64 Clamp<int64>(int64, int64, int64);
	template float32 Clamp<float32>(float32, float32, float32);
	template float64 Clamp<float64>(float64, float64, float64);
	template float128 Clamp<float128>(float128, float128, float128);

	template <typename T>
	T Lerp(const T & start, const T & end, float32 percent)
	{
		return start + percent * (end - start);
	}
	
	template <typename T>
	T Lerp(const T & start, const T & end, float64 percent)
	{
		return start + percent * (end - start);
	}
	
	fvec2 Slerp(const fvec2 & start, const fvec2 & end, float32 percent);
	fvec3 Slerp(const fvec3 & start, const fvec3 & end, float32 percent);
	fvec4 Slerp(const fvec4 & start, const fvec4 & end, float32 percent);
	fquat Slerp(const fquat & start, const fquat & end, float32 percent);
	
	dvec2 Slerp(const dvec2 & start, const dvec2 & end, float64 percent);
	dvec3 Slerp(const dvec3 & start, const dvec3 & end, float64 percent);
	dvec4 Slerp(const dvec4 & start, const dvec4 & end, float64 percent);
	dquat Slerp(const dquat & start, const dquat & end, float64 percent);

	fvec2 Nlerp(const fvec2 & start, const dvec2 & end, float32 percent);
	fvec3 Nlerp(const fvec3 & start, const dvec3 & end, float32 percent);
	fvec4 Nlerp(const fvec4 & start, const dvec4 & end, float32 percent);
	fquat Nlerp(const fquat & start, const dquat & end, float32 percent);
	
	dvec2 Nlerp(const dvec2 & start, const dvec2 & end, float64 percent);
	dvec3 Nlerp(const dvec3 & start, const dvec3 & end, float64 percent);
	dvec4 Nlerp(const dvec4 & start, const dvec4 & end, float64 percent);
	dquat Nlerp(const dquat & start, const dquat & end, float64 percent);
	
	fmat2 TransposeMatrix(const fmat2& matIn);
	fmat3 TransposeMatrix(const fmat3& matIn);
	fmat4 TransposeMatrix(const fmat4& matIn);

	void TransposeMatrix(const fmat2& matIn, fmat2& matOut);
	void TransposeMatrix(const fmat3& matIn, fmat3& matOut);
	void TransposeMatrix(const fmat4& matIn, fmat4& matOut);

	dmat2 TransposeMatrix(const dmat2& matIn);
	dmat3 TransposeMatrix(const dmat3& matIn);
	dmat4 TransposeMatrix(const dmat4& matIn);

	void TransposeMatrix(const dmat3& matIn, dmat3& matOut);
	void TransposeMatrix(const dmat3& matIn, dmat3& matOut);
	void TransposeMatrix(const dmat3& matIn, dmat3& matOut);

	float32 GetPitch(const fquat & quaternion);
	float32 GetYaw(const fquat & quaternion);
	float32 GetRoll(const fquat & quaternion);

	float64 GetPitch(const dquat & quaternion);
	float64 GetYaw(const dquat & quaternion);
	float64 GetRoll(const dquat & quaternion);

	void GetTranslation(const mat4& matrix, pos & translation);
	void GetScaling(const mat4& matrix, vec2 & scaling);
	void GetRotation(const mat4& matrix, float32 & rotation);
	void GetRotationAndScaling(const mat4& matrix, float32 & rotation, vec2 & scaling);
	void DecomposeMatrix(const mat4& matrix, pos & position,
		vec2 & scaling, float32 & rotation);

	int32 GenerateRandomNumber(int32 min, int32 max);
	uint32 GenerateRandomNumber(uint32 min, uint32 max);
	float32 GenerateRandomNumber(float32 min, float32 max);
	float64 GenerateRandomNumber(float64 min, float64 max);
	float128 GenerateRandomNumber(float128 min, float128 max);

	float32 Mag(const fvec2 & vec);
	float32 Mag(const fvec3 & vec);
	float32 Mag(const fvec4 & vec);
	
	float64 Mag(const dvec2 & vec);
	float64 Mag(const dvec3 & vec);
	float64 Mag(const dvec4 & vec);

	float32 Dot(const fvec2 & vecA, const fvec2 & vecB);
	float32 Dot(const fvec3 & vecA, const fvec3 & vecB);
	float32 Dot(const fvec4 & vecA, const fvec4 & vecB);

	float64 Dot(const dvec2 & vecA, const dvec2 & vecB);
	float64 Dot(const dvec3 & vecA, const dvec3 & vecB);
	float64 Dot(const dvec4 & vecA, const dvec4 & vecB);

	fvec3 Cross(const fvec3 & vecA, const fvec3 & vecB);
	dvec3 Cross(const dvec3 & vecA, const dvec3 & vecB);

	void Cross(const fvec3 & vecA, const fvec3 & vecB, fvec3 & vecOut);
	void Cross(const dvec3 & vecA, const dvec3 & vecB, dvec3 & vecOut);

	fvec2 Mul(const fvec2 & vec, const fmat2 & mat);
	fvec3 Mul(const fvec3 & vec, const fmat3 & mat);
	fvec4 Mul(const fvec4 & vec, const fmat4 & mat);

	dvec2 Mul(const dvec2 & vec, const dmat2 & mat);
	dvec3 Mul(const dvec3 & vec, const dmat3 & mat);
	dvec4 Mul(const dvec4 & vec, const dmat4 & mat);

	void Mul(const fvec2 & vecIn, const fmat2 & mat, fvec2 & vecOut);
	void Mul(const fvec3 & vecIn, const fmat3 & mat, fvec3 & vecOut);
	void Mul(const fvec4 & vecIn, const fmat4 & mat, fvec4 & vecOut);

	void Mul(const dvec2 & vecIn, const dmat2 & mat, dvec2 & vecOut);
	void Mul(const dvec3 & vecIn, const dmat3 & mat, dvec3 & vecOut);
	void Mul(const dvec4 & vecIn, const dmat4 & mat, dvec4 & vecOut);

	fvec2 Normalize(const fvec2 & vec);
	fvec3 Normalize(const fvec3 & vec);
	fvec4 Normalize(const fvec4 & vec);

	void Normalize(const fvec2 & vecIn, fvec2 & vecOut);
	void Normalize(const fvec3 & vecIn, fvec3 & vecOut);
	void Normalize(const fvec4 & vecIn, fvec4 & vecOut);

	dvec2 Normalize(const dvec2 & vec);
	dvec3 Normalize(const dvec3 & vec);
	dvec4 Normalize(const dvec4 & vec);

	void Normalize(const dvec2 & vecIn, dvec2 & vecOut);
	void Normalize(const dvec3 & vecIn, dvec3 & vecOut);
	void Normalize(const dvec4 & vecIn, dvec4 & vecOut);

	float32 Distance(const fvec2 & vecA, const fvec2 & vecB);
	float32 Distance(const fvec3 & vecA, const fvec3 & vecB);
	float32 Distance(const fvec4 & vecA, const fvec4 & vecB);

	float64 Distance(const dvec2 & vecA, const dvec2 & vecB);
	float64 Distance(const dvec3 & vecA, const dvec3 & vecB);
	float64 Distance(const dvec4 & vecA, const dvec4 & vecB);

	fmat3 ToMat3(const fquat & quaternion);
	dmat3 ToMat3(const dquat & quaternion);

	void ToMat3(const fquat & quaternion, fmat3 & out);
	void ToMat3(const dquat & quaternion, dmat3 & out);

	fmat4 ToMat4(const fquat & quaternion);
	dmat4 ToMat4(const dquat & quaternion);

	void ToMat4(const fquat & quaternion, fmat4 & out);
	void ToMat4(const dquat & quaternion, dmat4 & out);

	fmat4 Translate(const fmat4 & mat, fvec3 & vec);
	fmat4 Translate(const fmat4 & mat, float32 x, float32 y, float32 z);
	fmat4 Translate(const fvec3 & vec);
	fmat4 Translate(float32 x, float32 y, float32 z);

	void Translate(const fmat4 & mat, fvec3 & vec, fmat4 & out);
	void Translate(const fmat4 & mat, float32 x, float32 y, float32 z, fmat4 & out);
	void Translate(const fvec3 & vec, fmat4 & out);
	void Translate(float32 x, float32 y, float32 z, fmat4 & out);

	dmat4 Translate(const dmat4 & mat, dvec3 & vec);
	dmat4 Translate(const dmat4 & mat, float64 x, float64 y, float64 z);
	dmat4 Translate(const dvec3 & vec);
	dmat4 Translate(float64 x, float64 y, float64 z);

	void Translate(const dmat4 & mat, dvec3 & vec, dmat4 & out);
	void Translate(const dmat4 & mat, float64 x, float64 y, float64 z, dmat4 & out);
	void Translate(const dvec3 & vec, dmat4 & out);
	void Translate(float64 x, float64 y, float64 z, dmat4 & out);

	fmat4 Scale(const fmat4 & mat, fvec3 & vec);
	fmat4 Scale(const fmat4 & mat, float32 x, float32 y, float32 z);
	fmat4 Scale(const fvec3 & vec);
	fmat4 Scale(float32 x, float32 y, float32 z);

	void Scale(const fmat4 & mat, fvec3 & vec, fmat4 & out);
	void Scale(const fmat4 & mat, float32 x, float32 y, float32 z, fmat4 & out);
	void Scale(const fvec3 & vec, fmat4 & out);
	void Scale(float32 x, float32 y, float32 z, fmat4 & out);

	dmat4 Scale(const dmat4 & mat, dvec3 & vec);
	dmat4 Scale(const dmat4 & mat, float64 x, float64 y, float64 z);
	dmat4 Scale(const dvec3 & vec);
	dmat4 Scale(float64 x, float64 y, float64 z);

	void Scale(const dmat4 & mat, dvec3 & vec, dmat4 & out);
	void Scale(const dmat4 & mat, float64 x, float64 y, float64 z, dmat4 & out);
	void Scale(const dvec3 & vec, dmat4 & out);
	void Scale(float64 x, float64 y, float64 z, dmat4 & out);

	const float32 * ToPointerValue(const fmat2 & mat);
	const float32 * ToPointerValue(const fmat3 & mat);
	const float32 * ToPointerValue(const fmat4 & mat);

	const float32 * ToPointerValue(const fvec2 & vec);
	const float32 * ToPointerValue(const fvec3 & vec);
	const float32 * ToPointerValue(const fvec4 & vec);
	const float32 * ToPointerValue(const fquat & quat);

	const float64 * ToPointerValue(const dmat2 & mat);
	const float64 * ToPointerValue(const dmat3 & mat);
	const float64 * ToPointerValue(const dmat4 & mat);

	const float64 * ToPointerValue(const dvec2 & vec);
	const float64 * ToPointerValue(const dvec3 & vec);
	const float64 * ToPointerValue(const dvec4 & vec);
	const float64 * ToPointerValue(const dquat & quat);

#ifdef STAR2D
	pos Lerp(const pos & start, const pos & end, float32 percent);
	pos Slerp(const pos & start, const pos & end, float32 percent);
	pos Nlerp(const pos & start, const pos & end, float32 percent);
	float32 Mag(const pos & pos);
	float32 Dot(const pos & posA, const pos & posB);
	pos Mul(const pos & position, const fmat2 & mat);
	void Mul(const pos & posIn, const fmat2 & mat, pos & posOut);
	pos Normalize(const pos & position);
	void Normalize(const pos & posIn, pos & posOut);
	float32 Distance(const pos & posA, const pos & posB);
#endif
}
