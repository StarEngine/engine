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

	ScreenPercentY::ScreenPercentY(const ScreenPercentY & yRef)
		:ScreenPercentAbstract(yRef)
	{

	}

	ScreenPercentY::ScreenPercentY(const ScreenPercentX & screenPercentX)
		:ScreenPercentAbstract(screenPercentX)
	{
		//m_ScreenPercentage = screenPercentX.
	}

	ScreenPercentY::~ScreenPercentY()
	{

	}

	void ScreenPercentY::ConvertPercentToScreenPos()
	{

	}

	const ScreenPercentY ScreenPercentY::operator+(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentY temp = *this;
		temp += yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator+(const int &yRef) const
	{
		ScreenPercentY temp = *this;
		temp += yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator+(const float &yRef) const
	{
		ScreenPercentY temp = *this;
		temp += yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator+(const double &yRef) const
	{
		ScreenPercentY temp = *this;
		temp += yRef;
		return temp;
	}
						
	const ScreenPercentY ScreenPercentY::operator-(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentY temp = *this;
		temp -= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator-(const int &yRef) const
	{
		ScreenPercentY temp = *this;
		temp -= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator-(const float &yRef) const
	{
		ScreenPercentY temp = *this;
		temp -= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator-(const double &yRef) const
	{
		ScreenPercentY temp = *this;
		temp -= yRef;
		return temp;
	}
						
	const ScreenPercentY ScreenPercentY::operator*(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentY temp = *this;
		temp *= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator*(const int &yRef) const
	{
		ScreenPercentY temp = *this;
		temp *= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator*(const float &yRef) const
	{
		ScreenPercentY temp = *this;
		temp *= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator*(const double &yRef) const
	{
		ScreenPercentY temp = *this;
		temp *= yRef;
		return temp;
	}
						
	const ScreenPercentY ScreenPercentY::operator/(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentY temp = *this;
		temp /= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator/(const int &yRef) const
	{
		ScreenPercentY temp = *this;
		temp /= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator/(const float &yRef) const
	{
		ScreenPercentY temp = *this;
		temp /= yRef;
		return temp;
	}

	const ScreenPercentY ScreenPercentY::operator/(const double &yRef) const
	{
		ScreenPercentY temp = *this;
		temp /= yRef;
		return temp;
	}
}