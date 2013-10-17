#pragma once

#include "ScreenPercentX.h"
#include "ScreenPercentY.h"

namespace star
{
	struct ScreenPercent
	{
		ScreenPercent();
		ScreenPercent(const ScreenPercentX & widthPercent,
					const ScreenPercentY & heightPercent);
		~ScreenPercent(void);
		vec2 GetScreenValue()
		{
			return vec2(x.GetScreenValue(),	y.GetScreenValue());
		}

		ScreenPercentX x;
		ScreenPercentY y;
	};
}
