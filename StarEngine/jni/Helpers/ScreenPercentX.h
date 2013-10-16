#pragma once
#include "ScreenPercentAbstract.h"

namespace star
{
	class ScreenPercentX final: public ScreenPercentAbstract
	{
	public:
		ScreenPercentX();
		ScreenPercentX(int value);
		ScreenPercentX(float value);
		ScreenPercentX(double value);
		ScreenPercentX(const ScreenPercentAbstract & yRef);
		~ScreenPercentX();

	private: 
		void ConvertPercentToScreenPos();
	};
}
