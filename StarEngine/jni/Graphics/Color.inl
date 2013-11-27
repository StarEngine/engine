#include  "../defines.h"

namespace star
{
	template <typename T>
	Color & Color::operator*=(T x)
	{
		r *= x;
		g *= x;
		b *= x;
		a *= x;
		return *this;
	}

	template <typename T>
	Color & Color::operator/=(T x)
	{
		r /= x;
		g /= x;
		b /= x;
		a /= x;
		return *this;
	}

	template <typename T>
	Color Color::operator*(T x)
	{
		Color color(*this);
		color.r *= x;
		color.g *= x;
		color.b *= x;
		color.a *= x;
		return color;
	}

	template <typename T>
	Color Color::operator/(T x)
	{
		Color color(*this);
		color.r /= x;
		color.g /= x;
		color.b /= x;
		color.a /= x;
		return color;
	}

	template <typename T>
	Color operator*(T x, const Color & op2)
	{
		Color color(op2);
		color.r *= x;
		color.g *= x;
		color.b *= x;
		color.a *= x;
		return color;
	}

	template <typename T>
	Color operator/(T x, const Color & op2)
	{
		Color color(op2);
		color.r /= x;
		color.g /= x;
		color.b /= x;
		color.a /= x;
		return color;
	}

	template <typename T, typename U>
	T Color::FloatToInteger(U yRef) const
	{
		return T( 255 * yRef );
	}

	template <typename T, typename U>
	T Color::IntegerToFloat(U yRef) const
	{
		return T(yRef) / T(255);
	}
}
