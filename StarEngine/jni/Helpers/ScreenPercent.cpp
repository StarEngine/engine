#include "ScreenPercent.h"

namespace star
{
	ScreenPercent::ScreenPercent()
		: x(0)
		, y(0)
	{
	}
	
	ScreenPercent::ScreenPercent(
		const ScreenPercentX & widthPercent,
		const ScreenPercentY & heightPercent)
		: x(widthPercent)
		, y(heightPercent)
	{
	}

	ScreenPercent::~ScreenPercent(void)
	{
	}

	glm::vec2 ScreenPercent::GetScreenValue()
	{
		return glm::vec2(x.GetScreenValue(), y.GetScreenValue());
	}
}
