#include "..\defines.h"

namespace star
{
	template <typename T>
	T DegreesToRadians(T degrees)
	{
		return T(float64(degrees) * PI / 180);
	}

	template <typename T>
	T RadiansToDegrees(T radians)
	{
		return T(float64(radians) * 180 / PI);
	}

	template <typename T>
	T Clamp(T x, T min, T max)
	{
		return x < min ? min : (x > max ? max : x);
	}

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

	template <typename T>
	T Saturate(T x)
	{
		return glm::saturate<T>(x);
	}
}
