#include  "../defines.h"

namespace star
{
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
