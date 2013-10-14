#pragma once
#include "ScreenPercentAbstract.h"

namespace star
{
	class ScreenPercentY;

	class ScreenPercentX : public ScreenPercentAbstract
	{
		ScreenPercentX();
		ScreenPercentX(int value);
		ScreenPercentX(float value);
		ScreenPercentX(double value);
		ScreenPercentX(const ScreenPercentX & yRef);
		ScreenPercentX(const ScreenPercentY & screenPercentY);
		~ScreenPercentX() final;

		//Can't put these operators in ScreenPercentageAbstract class, because it has pure virtual members

		const ScreenPercentX operator+(const ScreenPercentAbstract &yRef) const;
		const ScreenPercentX operator+(const int &yRef) const;
		const ScreenPercentX operator+(const float &yRef) const;
		const ScreenPercentX operator+(const double &yRef) const;

		const ScreenPercentX operator-(const ScreenPercentAbstract &yRef) const;
		const ScreenPercentX operator-(const int &yRef) const;
		const ScreenPercentX operator-(const float &yRef) const;
		const ScreenPercentX operator-(const double &yRef) const;

		const ScreenPercentX operator*(const ScreenPercentAbstract &yRef) const;
		const ScreenPercentX operator*(const int &yRef) const;
		const ScreenPercentX operator*(const float &yRef) const;
		const ScreenPercentX operator*(const double &yRef) const;

		const ScreenPercentX operator/(const ScreenPercentAbstract &yRef) const;
		const ScreenPercentX operator/(const int &yRef) const;
		const ScreenPercentX operator/(const float &yRef) const;
		const ScreenPercentX operator/(const double &yRef) const;

	private: 
		void ConvertPercentToScreenPos() final;
		ScreenPercentX(ScreenPercentX&& t);
	};
}
