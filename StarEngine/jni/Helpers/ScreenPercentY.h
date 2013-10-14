#pragma once
#include "ScreenPercentAbstract.h"
namespace star
{
	class ScreenPercentX;

	class ScreenPercentY : public ScreenPercentAbstract
	{
		ScreenPercentY();
		ScreenPercentY(int value);
		ScreenPercentY(float value);
		ScreenPercentY(double value);
		ScreenPercentY(const ScreenPercentY & yRef);
		ScreenPercentY(const ScreenPercentX & screenPercentX);
		~ScreenPercentY() final;

		//Can't put these operators in ScreenPercentageAbstract class, because it has pure virtual members

		const ScreenPercentY operator+(const ScreenPercentAbstract &yRef) const;
		const ScreenPercentY operator+(const int &yRef) const;
		const ScreenPercentY operator+(const float &yRef) const;
		const ScreenPercentY operator+(const double &yRef) const;

		const ScreenPercentY operator-(const ScreenPercentAbstract &yRef) const;
		const ScreenPercentY operator-(const int &yRef) const;
		const ScreenPercentY operator-(const float &yRef) const;
		const ScreenPercentY operator-(const double &yRef) const;

		const ScreenPercentY operator*(const ScreenPercentAbstract &yRef) const;
		const ScreenPercentY operator*(const int &yRef) const;
		const ScreenPercentY operator*(const float &yRef) const;
		const ScreenPercentY operator*(const double &yRef) const;
						   
		const ScreenPercentY operator/(const ScreenPercentAbstract &yRef) const;
		const ScreenPercentY operator/(const int &yRef) const;
		const ScreenPercentY operator/(const float &yRef) const;
		const ScreenPercentY operator/(const double &yRef) const;

	private: 
		void ConvertPercentToScreenPos() final;
	};
}