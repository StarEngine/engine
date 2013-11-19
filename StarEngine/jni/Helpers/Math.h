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
	
	fmat2 Transpose(const fmat2& matIn);
	fmat3 Transpose(const fmat3& matIn);
	fmat4 Transpose(const fmat4& matIn);

	void Transpose(const fmat2& matIn, fmat2& matOut);
	void Transpose(const fmat3& matIn, fmat3& matOut);
	void Transpose(const fmat4& matIn, fmat4& matOut);

	dmat2 Transpose(const dmat2& matIn);
	dmat3 Transpose(const dmat3& matIn);
	dmat4 Transpose(const dmat4& matIn);

	void Transpose(const dmat3& matIn, dmat3& matOut);
	void Transpose(const dmat3& matIn, dmat3& matOut);
	void Transpose(const dmat3& matIn, dmat3& matOut);

	fmat2 Inverse(const fmat2 & mat);
	fmat3 Inverse(const fmat3 & mat);
	fmat4 Inverse(const fmat4 & mat);
	fquat Inverse(const fquat & quat);

	void Inverse(const fmat2 & mat, fmat2 & out);
	void Inverse(const fmat3 & mat, fmat3 & out);
	void Inverse(const fmat4 & mat, fmat4 & out);
	void Inverse(const fquat & quat, fquat & out);

	dmat2 Inverse(const dmat2 & mat);
	dmat3 Inverse(const dmat3 & mat);
	dmat4 Inverse(const dmat4 & mat);
	dquat Inverse(const dquat & quat);

	void Inverse(const dmat2 & mat, dmat2 & out);
	void Inverse(const dmat3 & mat, dmat3 & out);
	void Inverse(const dmat4 & mat, dmat4 & out);
	void Inverse(const dquat & quat, dquat & out);

	fmat4 LookAt(const fvec3 & eye, const fvec3 & center, const fvec3 & up);
	dmat4 LookAt(const dvec3 & eye, const dvec3 & center, const dvec3 & up);

	void LookAt(const fvec3 & eye, const fvec3 & center, const fvec3 & up, fmat4 & out);
	void LookAt(const dvec3 & eye, const dvec3 & center, const dvec3 & up, fmat4 & out);

	fvec2 Log(const fvec2 & vec);
	fvec3 Log(const fvec3 & vec);
	fvec4 Log(const fvec4 & vec);
	fquat Log(const fquat & quat);

	void Log(const fvec2 & vecIn, fvec2 & vecOut);
	void Log(const fvec3 & vecIn, fvec3 & vecOut);
	void Log(const fvec4 & vecIn, fvec4 & vecOut);
	void Log(const fquat & quatIn, fquat & quatOut);

	dvec2 Log(const dvec2 & vec);
	dvec3 Log(const dvec3 & vec);
	dvec4 Log(const dvec4 & vec);
	dquat Log(const dquat & quat);

	void Log(const dvec2 & vecIn, dvec2 & vecOut);
	void Log(const dvec3 & vecIn, dvec3 & vecOut);
	void Log(const dvec4 & vecIn, dvec4 & vecOut);
	void Log(const dquat & quatIn, dquat & quatOut);

	fvec2 Log2(const fvec2 & vec);
	fvec3 Log2(const fvec3 & vec);
	fvec4 Log2(const fvec4 & vec);

	void Log2(const fvec2 & vecIn, fvec2 & vecOut);
	void Log2(const fvec3 & vecIn, fvec3 & vecOut);
	void Log2(const fvec4 & vecIn, fvec4 & vecOut);

	dvec2 Log2(const dvec2 & vec);
	dvec3 Log2(const dvec3 & vec);
	dvec4 Log2(const dvec4 & vec);

	void Log2(const dvec2 & vecIn, dvec2 & vecOut);
	void Log2(const dvec3 & vecIn, dvec3 & vecOut);
	void Log2(const dvec4 & vecIn, dvec4 & vecOut);

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

	fmat4 Translate(const fmat4 & mat, const fvec3 & vec);
	fmat4 Translate(const fmat4 & mat, float32 x, float32 y, float32 z);
	fmat4 Translate(const fvec3 & vec);
	fmat4 Translate(float32 x, float32 y, float32 z);

	void Translate(const fmat4 & mat, const fvec3 & vec, fmat4 & out);
	void Translate(const fmat4 & mat, float32 x, float32 y, float32 z, fmat4 & out);
	void Translate(const fvec3 & vec, fmat4 & out);
	void Translate(float32 x, float32 y, float32 z, fmat4 & out);

	dmat4 Translate(const dmat4 & mat, const dvec3 & vec);
	dmat4 Translate(const dmat4 & mat, float64 x, float64 y, float64 z);
	dmat4 Translate(const dvec3 & vec);
	dmat4 Translate(float64 x, float64 y, float64 z);

	void Translate(const dmat4 & mat, const dvec3 & vec, dmat4 & out);
	void Translate(const dmat4 & mat, float64 x, float64 y, float64 z, dmat4 & out);
	void Translate(const dvec3 & vec, dmat4 & out);
	void Translate(float64 x, float64 y, float64 z, dmat4 & out);

	fmat4 Scale(const fmat4 & mat, const fvec3 & vec);
	fmat4 Scale(const fmat4 & mat, float32 x, float32 y, float32 z);
	fmat4 Scale(const fvec3 & vec);
	fmat4 Scale(float32 x, float32 y, float32 z);

	void Scale(const fmat4 & mat, const fvec3 & vec, fmat4 & out);
	void Scale(const fmat4 & mat, float32 x, float32 y, float32 z, fmat4 & out);
	void Scale(const fvec3 & vec, fmat4 & out);
	void Scale(float32 x, float32 y, float32 z, fmat4 & out);

	dmat4 Scale(const dmat4 & mat, const dvec3 & vec);
	dmat4 Scale(const dmat4 & mat, float64 x, float64 y, float64 z);
	dmat4 Scale(const dvec3 & vec);
	dmat4 Scale(float64 x, float64 y, float64 z);

	void Scale(const dmat4 & mat, const dvec3 & vec, dmat4 & out);
	void Scale(const dmat4 & mat, float64 x, float64 y, float64 z, dmat4 & out);
	void Scale(const dvec3 & vec, dmat4 & out);
	void Scale(float64 x, float64 y, float64 z, dmat4 & out);

	fvec2 Rotate(const fvec2 & vec, float32 angle);
	fvec3 Rotate(const fvec3 & vec, float32 angle, const fvec3 & normal);
	fvec4 Rotate(const fvec4 & vec, float32 angle, const fvec3 & normal);
	fmat4 Rotate(const fmat4 & mat, float32 angle, float32 x, float32 y, float32 z);
	fmat4 Rotate(const fvec3 & vec, float32 angle);
	fmat4 Rotate(float32 angle, float32 x, float32 y, float32 z);
	fvec3 Rotate(const fquat & quat, const fvec3 & vec);
	fvec4 Rotate(const fquat & quat, const fvec4 & vec);

	void Rotate(const fvec2 & vec, float32 angle, fvec2 & out);
	void Rotate(const fvec3 & vec, float32 angle, const fvec3 & normal, fvec3 & out);
	void Rotate(const fvec4 & vec, float32 angle, const fvec3 & normal, fvec4 & out);
	void Rotate(const fmat4 & mat, float32 angle, float32 x, float32 y, float32 z, fmat4 & out);
	void Rotate(const fvec3 & vec, float32 angle, fmat4 & out);
	void Rotate(float32 angle, float32 x, float32 y, float32 z, fmat4 & out);
	void Rotate(const fquat & quat, const fvec3 & vec, fvec3 & out);
	void Rotate(const fquat & quat, const fvec4 & vec, fvec4 & out);

	dvec2 Rotate(const dvec2 & vec, float64 angle);
	dvec3 Rotate(const dvec3 & vec, float64 angle, const dvec3 & normal);
	dvec4 Rotate(const dvec4 & vec, float64 angle, const dvec3 & normal);
	dmat4 Rotate(const dmat4 & mat, float64 angle, float64 x, float64 y, float64 z);
	dmat4 Rotate(const dvec3 & vec, float64 angle);
	dmat4 Rotate(float64 angle, float64 x, float64 y, float64 z);
	dvec3 Rotate(const dquat & quat, const dvec3 & vec);
	dvec4 Rotate(const dquat & quat, const dvec4 & vec);

	void Rotate(const dvec2 & vec, float64 angle, dvec2 & out);
	void Rotate(const dvec3 & vec, float64 angle, const dvec3 & normal, dvec3 & out);
	void Rotate(const dvec4 & vec, float64 angle, const dvec3 & normal, dvec4 & out);
	void Rotate(const dmat4 & mat, float64 angle, float64 x, float64 y, float64 z, dmat4 & out);
	void Rotate(const dvec3 & vec, float64 angle, dmat4 & out);
	void Rotate(float64 angle, float64 x, float64 y, float64 z, dmat4 & out);
	void Rotate(const dquat & quat, const dvec3 & vec, dvec3 & out);
	void Rotate(const dquat & quat, const dvec4 & vec, dvec4 & out);

	fvec2 Step(const fvec2 & edge, const fvec2 & x);
	fvec3 Step(const fvec3 & edge, const fvec3 & x);
	fvec4 Step(const fvec4 & edge, const fvec4 & x);

	fvec2 Step(const fvec2 & edge, float32 x);
	fvec3 Step(const fvec3 & edge, float32 x);
	fvec4 Step(const fvec4 & edge, float32 x);

	void Step(const fvec2 & edge, const fvec2 & x, fvec2 & out);
	void Step(const fvec3 & edge, const fvec3 & x, fvec2 & out);
	void Step(const fvec4 & edge, const fvec4 & x, fvec2 & out);

	void Step(const fvec2 & edge, float32 x, fvec2 & out);
	void Step(const fvec3 & edge, float32 x, fvec2 & out);
	void Step(const fvec4 & edge, float32 x, fvec2 & out);

	dvec2 Step(const dvec2 & edge, const dvec2 & x);
	dvec3 Step(const dvec3 & edge, const dvec3 & x);
	dvec4 Step(const dvec4 & edge, const dvec4 & x);

	dvec2 Step(const dvec2 & edge, float64 x);
	dvec3 Step(const dvec3 & edge, float64 x);
	dvec4 Step(const dvec4 & edge, float64 x);

	void Step(const dvec2 & edge, const dvec2 & x, dvec2 & out);
	void Step(const dvec3 & edge, const dvec3 & x, dvec2 & out);
	void Step(const dvec4 & edge, const dvec4 & x, dvec2 & out);

	void Step(const dvec2 & edge, float64 x, dvec2 & out);
	void Step(const dvec3 & edge, float64 x, dvec2 & out);
	void Step(const dvec4 & edge, float64 x, dvec2 & out);

	template <typename T>
	T Saturate(T x)
	{
		return glm::saturate<T>(x);
	}

	fvec2 Saturate(const fvec2 & vec);
	fvec3 Saturate(const fvec3 & vec);
	fvec4 Saturate(const fvec4 & vec);

	dvec2 Saturate(const dvec2 & vec);
	dvec3 Saturate(const dvec3 & vec);
	dvec4 Saturate(const dvec4 & vec);

	void Saturate(const fvec2 & vecIn, fvec2 & vecOut);
	void Saturate(const fvec3 & vecIn, fvec3 & vecOut);
	void Saturate(const fvec4 & vecIn, fvec4 & vecOut);

	void Saturate(const dvec2 & vecIn, dvec2 & vecOut);
	void Saturate(const dvec3 & vecIn, dvec3 & vecOut);
	void Saturate(const dvec4 & vecIn, dvec4 & vecOut);

	fvec2 Refract(const fvec2 & I, const fvec2 & N, float32 eta);
	fvec3 Refract(const fvec3 & I, const fvec3 & N, float32 eta);
	fvec4 Refract(const fvec4 & I, const fvec4 & N, float32 eta);

	void Refract(const fvec2 & I, const fvec2 & N, float32 eta, fvec2 & out);
	void Refract(const fvec3 & I, const fvec3 & N, float32 eta, fvec3 & out);
	void Refract(const fvec4 & I, const fvec4 & N, float32 eta, fvec4 & out);

	dvec2 Refract(const dvec2 & I, const dvec2 & N, float32 eta);
	dvec3 Refract(const dvec3 & I, const dvec3 & N, float32 eta);
	dvec4 Refract(const dvec4 & I, const dvec4 & N, float32 eta);

	void Refract(const dvec2 & I, const dvec2 & N, float32 eta, dvec2 & out);
	void Refract(const dvec3 & I, const dvec3 & N, float32 eta, dvec3 & out);
	void Refract(const dvec4 & I, const dvec4 & N, float32 eta, dvec4 & out);

	uint32 Mod(uint32 x, uint32 y);
	int32 Mod(int32 x, int32 y);
	float32 Mod(float32 x, float32 y);
	float64 Mod(float64 x, float64 y);

	fvec2 Mod(const fvec2 & x, const fvec2 & y);
	fvec3 Mod(const fvec3 & x, const fvec3 & y);
	fvec4 Mod(const fvec4 & x, const fvec4 & y);

	dvec2 Mod(const dvec2 & x, const dvec2 & y);
	dvec3 Mod(const dvec3 & x, const dvec3 & y);
	dvec4 Mod(const dvec4 & x, const dvec4 & y);

	void Mod(const fvec2 & x, const fvec2 & y, fvec2 & out);
	void Mod(const fvec3 & x, const fvec3 & y, fvec3 & out);
	void Mod(const fvec4 & x, const fvec4 & y, fvec4 & out);

	void Mod(const dvec2 & x, const dvec2 & y, dvec2 & out);
	void Mod(const dvec3 & x, const dvec3 & y, dvec3 & out);
	void Mod(const dvec4 & x, const dvec4 & y, dvec4 & out);

	fvec2 Mod(const fvec2 & x, float32 y);
	fvec3 Mod(const fvec3 & x, float32 y);
	fvec4 Mod(const fvec4 & x, float32 y);

	dvec2 Mod(const dvec2 & x, float64 y);
	dvec3 Mod(const dvec3 & x, float64 y);
	dvec4 Mod(const dvec4 & x, float64 y);

	void Mod(const fvec2 & x, float32 y, fvec2 & out);
	void Mod(const fvec3 & x, float32 y, fvec3 & out);
	void Mod(const fvec4 & x, float32 y, fvec4 & out);

	void Mod(const dvec2 & x, float64 y, dvec2 & out);
	void Mod(const dvec3 & x, float64 y, dvec3 & out);
	void Mod(const dvec4 & x, float64 y, dvec4 & out);

#ifdef STAR2D
	fmat3 Reflect(const fmat3 & mat, const fvec3 & normal);
	dmat3 Reflect(const dmat3 & mat, const dvec3 & normal);
	void Reflect(const fmat3 & matIn, const fvec3 & normal, fmat3 & matOut);
	void Reflect(const dmat3 & matIn, const dvec3 & normal, dmat3 & matOut);

	fmat3 Project(const fmat3 & mat, const fvec3 & normal);
	dmat3 Project(const dmat3 & mat, const dvec3 & normal);
	void Project(const fmat3 & matIn, const fvec3 & normal, fmat3 & matOut);
	void Project(const dmat3 & matIn, const dvec3 & normal, dmat3 & matOut);
#else
	fmat4 Reflect(const fmat4 & mat, const fvec4 & normal);
	dmat4 Reflect(const dmat4 & mat, const dvec4 & normal);
	void Reflect(const fmat4 & matIn, const fvec4 & normal, fmat4 & matOut);
	void Reflect(const dmat4 & matIn, const dvec4 & normal, dmat4 & matOut);

	fmat4 Project(const fmat4 & mat, const fvec4 & normal);
	dmat4 Project(const dmat4 & mat, const dvec4 & normal);
	void Project(const fmat4 & matIn, const fvec4 & normal, fmat4 & matOut);
	void Project(const dmat4 & matIn, const dvec4 & normal, dmat4 & matOut);
#endif

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
	fmat4 Translate(const pos & pos);
	fmat4 Translate(const fmat4 & mat, const pos & pos);
	void Translate(const pos & pos, fmat4 & out);
	void Translate(const fmat4 & mat, const pos & pos, fmat4 & out);
	fmat4 Scale(const pos & pos);
	fmat4 Scale(const fmat4 & mat, const pos & pos);
	void Scale(const pos & pos, fmat4 & out);
	void Scale(const fmat4 & mat, const pos & pos, fmat4 & out);
	fmat4 LookAt(const pos & eye, const pos & center);
	void LookAt(const pos & eye, const pos & center, fmat4 & out);
	pos Log(const pos & pos);
	void Log(const pos & posIn, pos & posOut);
	pos Log2(const pos & pos);
	void Log2(const pos & posIn, pos & posOut);
	pos Step(const pos & pos, const fvec2 & x);
	pos Step(const pos & pos, float32 x);
	void Step(const pos & posIn, const fvec2 & x, pos & posOut);
	void Step(const pos & posIn, float32 x, pos & posOut);
	pos Mod(const pos & pos, const fvec2 & mod);
	pos Mod(const pos & pos, float32 mod);
	void Mod(const pos & posIn, const fvec2 & mod, pos & posOut);
	void Mod(const pos & posIn, float32 mod, pos & posOut);
#endif
}
