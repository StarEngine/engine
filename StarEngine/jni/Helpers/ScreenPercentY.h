#pragma once
#include "ScreenPercentAbstract.h"

namespace star
{
	class ScreenPercentY final: public ScreenPercentAbstract
	{
	public:
		ScreenPercentY();
		ScreenPercentY(int value);
		ScreenPercentY(float value);
		ScreenPercentY(double value);
		ScreenPercentY(const ScreenPercentAbstract & yRef);
		~ScreenPercentY();

	protected: 
		virtual void ConvertPercentToScreenPos();
	};
}