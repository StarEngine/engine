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
		// [TODO] Where is the implementation ?!
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A + B + C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator+(const ScreenPercentAbstract &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp += yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A + B + C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator+(const int &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp += yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A + B + C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator+(const float &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp += yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A + B + C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator+(const double &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp += yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A - B - C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator-(const ScreenPercentAbstract &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp -= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A - B - C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator-(const int &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp -= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A - B - C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator-(const float &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp -= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A - B - C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator-(const double &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp -= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A * B * C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator*(const ScreenPercentAbstract &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp *= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A * B * C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator*(const int &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp *= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A * B * C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator*(const float &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp *= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A * B * C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator*(const double &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp *= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A / B / C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator/(const ScreenPercentAbstract &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp /= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A / B / C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator/(const int &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp /= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A / B / C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator/(const float &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp /= yRef;
		return temp;
	}
	
	// [COMMENT] const on a copy is useless and it prevents from doing things like A / B / C,
	// as the result of A and B whill be const and so you can't change it... 
	const ScreenPercentY ScreenPercentY::operator/(const double &yRef) const
	{
		// [COMMENT] initialisation > assignment
		ScreenPercentY temp = *this;
		temp /= yRef;
		return temp;
	}
}