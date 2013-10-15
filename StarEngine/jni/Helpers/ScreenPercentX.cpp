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

	// [COMMENT] const on a copy is useless and it prevents from doing things like A + B + C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator+(const ScreenPercentAbstract &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp += yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A + B + C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator+(const int &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp += yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A + B + C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator+(const float &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp += yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A + B + C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator+(const double &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp += yRef;
		return temp;
	}

	// [COMMENT] const on a copy is useless and it prevents from doing things like A - B - C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator-(const ScreenPercentAbstract &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp -= yRef;
		return temp;
	}

	// [COMMENT] const on a copy is useless and it prevents from doing things like A - B - C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator-(const int &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp -= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A - B - C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator-(const float &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp -= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A - B - C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator-(const double &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp -= yRef;
		return temp;
	}

	// [COMMENT] const on a copy is useless and it prevents from doing things like A * B * C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator*(const ScreenPercentAbstract &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp *= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A * B * C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator*(const int &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp *= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A * B * C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator*(const float &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp *= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A * B * C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator*(const double &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp *= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A / B / C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator/(const ScreenPercentAbstract &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp /= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A / B / C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator/(const int &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp /= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A / B / C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator/(const float &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp /= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A / B / C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentX ScreenPercentX::operator/(const double &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentX temp = *this;
		temp /= yRef;
		return temp;
	}
}