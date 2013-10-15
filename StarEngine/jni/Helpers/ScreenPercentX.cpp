#include "ScreenPercentX.h"

namespace star
{
	ScreenPercentX::ScreenPercentX()
		:ScreenPercentAbstract()
	{

	}

	ScreenPercentX::ScreenPercentX(int value)
		:ScreenPercentAbstract(value)
	{

	}
	ScreenPercentX::ScreenPercentX(float value)
		:ScreenPercentAbstract(value)
	{

	}
	ScreenPercentX::ScreenPercentX(double value)
		:ScreenPercentAbstract(value)
	{

	}

	ScreenPercentX::ScreenPercentX(const ScreenPercentAbstract & yRef)
		:ScreenPercentAbstract(yRef)
	{

	}

	ScreenPercentX::~ScreenPercentX()
	{

	}

	void ScreenPercentX::ConvertPercentToScreenPos()
	{
		// [TODO] Implement
		//Prolly something like GraphicsManager get DPI, get Width, calc according to that :D
	}
}