#include "ScreenPercentX.h"
#include "ScreenPercentY.h"

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

	ScreenPercentX::ScreenPercentX(const ScreenPercentX & yRef)
		:ScreenPercentAbstract(yRef)
	{

	}

	ScreenPercentX::ScreenPercentX(const ScreenPercentY & screenPercentY)
		:ScreenPercentAbstract(screenPercentY)
	{

	}

	ScreenPercentX::~ScreenPercentX()
	{

	}

	void ScreenPercentX::ConvertPercentToScreenPos()
	{
		//Here the magic happens!
		//Prolly something like GraphicsManager get DPI, get Width, calc according to that :D
	}

	const ScreenPercentX ScreenPercentX::operator+(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentX temp = *this;
		temp += yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator+(const int &yRef) const
	{
		ScreenPercentX temp = *this;
		temp += yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator+(const float &yRef) const
	{
		ScreenPercentX temp = *this;
		temp += yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator+(const double &yRef) const
	{
		ScreenPercentX temp = *this;
		temp += yRef;
		return temp;
	}
						
	const ScreenPercentX ScreenPercentX::operator-(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentX temp = *this;
		temp -= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator-(const int &yRef) const
	{
		ScreenPercentX temp = *this;
		temp -= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator-(const float &yRef) const
	{
		ScreenPercentX temp = *this;
		temp -= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator-(const double &yRef) const
	{
		ScreenPercentX temp = *this;
		temp -= yRef;
		return temp;
	}
						
	const ScreenPercentX ScreenPercentX::operator*(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentX temp = *this;
		temp *= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator*(const int &yRef) const
	{
		ScreenPercentX temp = *this;
		temp *= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator*(const float &yRef) const
	{
		ScreenPercentX temp = *this;
		temp *= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator*(const double &yRef) const
	{
		ScreenPercentX temp = *this;
		temp *= yRef;
		return temp;
	}
						
	const ScreenPercentX ScreenPercentX::operator/(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentX temp = *this;
		temp /= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator/(const int &yRef) const
	{
		ScreenPercentX temp = *this;
		temp /= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator/(const float &yRef) const
	{
		ScreenPercentX temp = *this;
		temp /= yRef;
		return temp;
	}

	const ScreenPercentX ScreenPercentX::operator/(const double &yRef) const
	{
		ScreenPercentX temp = *this;
		temp /= yRef;
		return temp;
	}
}