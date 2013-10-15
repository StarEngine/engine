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

		ScreenPercentX x;
		ScreenPercentY y;
	};
}
