#pragma once
#include "ScreenPercentX.h"
#include "ScreenPercentY.h"

namespace star
{
	struct ScreenPercent
	{
		ScreenPercent()
			:x(0)
			,y(0)
		{};
		ScreenPercent(ScreenPercentX widthPercent, ScreenPercentY heightPercent)
			:x(widthPercent)
			,y(heightPercent)
		{};
		~ScreenPercent(void);

		ScreenPercentX x;
		ScreenPercentY y;
	};
}


