#include "ScreenPercentY.h"
#include "ScreenPercentX.h"

namespace star
{
	ScreenPercentY::ScreenPercentY()
		:ScreenPercentAbstract()
	{

	}

	ScreenPercentY::ScreenPercentY(int value)
		:ScreenPercentAbstract(value)
	{

	}
	ScreenPercentY::ScreenPercentY(float value)
		:ScreenPercentAbstract(value)
	{

	}
	ScreenPercentY::ScreenPercentY(double value)
		:ScreenPercentAbstract(value)
	{

	}

	ScreenPercentY::ScreenPercentY(const ScreenPercentAbstract & yRef)
		:ScreenPercentAbstract(yRef)
	{

	}

	ScreenPercentY::~ScreenPercentY()
	{

	}

	void ScreenPercentY::ConvertPercentToScreenPos()
	{
		// [TODO] Implement
	}
}