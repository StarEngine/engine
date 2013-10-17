#pragma once

#include "ScreenPercentX.h"
#include "ScreenPercentY.h"
#include "glm\glm.h"

namespace star
{
	struct ScreenPercent
	{
		ScreenPercent();
		ScreenPercent(const ScreenPercentX & widthPercent,
					const ScreenPercentY & heightPercent);
		~ScreenPercent(void);
		glm::vec2 GetScreenValue();

		ScreenPercentX x;
		ScreenPercentY y;
	};
}
