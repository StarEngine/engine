#include "ScreenPercentAbstract.h"

namespace star
{
	ScreenPercentAbstract::ScreenPercentAbstract()
		:m_ScreenPercentage(0)
		,m_ScreenValue(0)
	{
	}

	ScreenPercentAbstract::ScreenPercentAbstract(int value)
		:m_ScreenPercentage((float)value)
		,m_ScreenValue(0)
	{

	}

	ScreenPercentAbstract::ScreenPercentAbstract(float value)
		:m_ScreenPercentage(value)
		,m_ScreenValue(0)
	{

	}

	ScreenPercentAbstract::ScreenPercentAbstract(double value)
		:m_ScreenPercentage((float)value)
		,m_ScreenValue(0)
	{

	}

	ScreenPercentAbstract::ScreenPercentAbstract(const ScreenPercentAbstract & yRef)
		:m_ScreenPercentage(0)
		,m_ScreenValue(0)
	{
		//Check for self assignment, could fuck things up!
		if(this != &yRef)
		{
			m_ScreenPercentage = yRef.m_ScreenPercentage;
			//[TODO] make sure this value will get updated in the very beginning of the update loop! before anything else!
			m_ScreenValue = 0;
		}
	}

	ScreenPercentAbstract::ScreenPercentAbstract(ScreenPercentAbstract&& t)
		:m_ScreenPercentage(0)
		,m_ScreenValue(0)
	{
		//Check for self assignment, could fuck things up!
		if(this != &t)
		{
			m_ScreenPercentage = t.m_ScreenPercentage;
			//[TODO] make sure this value will get updated in the very beginning of the update loop! before anything else!
			m_ScreenValue = 0;

			t.m_ScreenPercentage = 0;
			t.m_ScreenValue = 0;
		}
	}

	ScreenPercentAbstract::~ScreenPercentAbstract()
	{
	}

	float ScreenPercentAbstract::GetScreenValue()
	{
		ConvertPercentToScreenPos();
		return m_ScreenValue;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator=(const ScreenPercentAbstract &yRef)
	{
		//Check for self assignment, could fuck things up!
		if(this != &yRef)
		{
			m_ScreenPercentage = yRef.m_ScreenPercentage;
			m_ScreenValue = 0;
		}

		//Do the assignment
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator=(int yRef)
	{
		m_ScreenPercentage = (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator=(float yRef)
	{
		m_ScreenPercentage = yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator=(double yRef)
	{
		m_ScreenPercentage = (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator+=(const ScreenPercentAbstract &yRef)
	{
		m_ScreenPercentage += yRef.m_ScreenPercentage;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator+=(int yRef)
	{
		m_ScreenPercentage += (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator+=(float yRef)
	{
		m_ScreenPercentage += yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator+=(double yRef)
	{
		m_ScreenPercentage += (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}
	
	ScreenPercentAbstract& ScreenPercentAbstract::operator-=(const ScreenPercentAbstract &yRef)
	{
		m_ScreenPercentage -= yRef.m_ScreenPercentage;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator-=(int yRef)
	{
		m_ScreenPercentage -= (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator-=(float yRef)
	{
		m_ScreenPercentage -= yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator-=(double yRef)
	{
		m_ScreenPercentage -= (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}
	
	ScreenPercentAbstract& ScreenPercentAbstract::operator*=(const ScreenPercentAbstract &yRef)
	{
		m_ScreenPercentage *= yRef.m_ScreenPercentage;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator*=(int yRef)
	{
		m_ScreenPercentage *= (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator*=(float yRef)
	{
		m_ScreenPercentage *= yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator*=(double yRef)
	{
		m_ScreenPercentage *= (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}
	
	ScreenPercentAbstract& ScreenPercentAbstract::operator/=(const ScreenPercentAbstract &yRef)
	{
		m_ScreenPercentage /= yRef.m_ScreenPercentage;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator/=(int yRef)
	{
		m_ScreenPercentage /= (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator/=(float yRef)
	{
		m_ScreenPercentage /= (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}

	ScreenPercentAbstract& ScreenPercentAbstract::operator/=(double yRef)
	{
		m_ScreenPercentage /= (float)yRef;
		m_ScreenValue = 0;
		return *this;
	}

	bool ScreenPercentAbstract::operator==(const ScreenPercentAbstract& yRef) const
	{
		if(m_ScreenPercentage == yRef.m_ScreenPercentage)
		{
			return true;
		}
		return false;
	}

	bool ScreenPercentAbstract::operator==(int yRef) const
	{
		if(m_ScreenPercentage == (float)yRef)
		{
			return true;
		}
		return false;
	}

	bool ScreenPercentAbstract::operator==(float yRef) const
	{
		if(m_ScreenPercentage == yRef)
		{
			return true;
		}
		return false;
	}

	bool ScreenPercentAbstract::operator==(double yRef) const
	{
		if(m_ScreenPercentage == (float)yRef)
		{
			return true;
		}
		return false;
	}

	bool ScreenPercentAbstract::operator!=(const ScreenPercentAbstract& yRef) const
	{
		return !(*this == yRef);
	}

	bool ScreenPercentAbstract::operator!=(int yRef) const
	{
		return !(*this == yRef);
	}

	bool ScreenPercentAbstract::operator!=(float yRef) const
	{
		return !(*this == yRef);
	}

	bool ScreenPercentAbstract::operator!=(double yRef) const
	{
		return !(*this == yRef);
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator+(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp += yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator+(int yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp += yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator+(float yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp += yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator+(double yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp += yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator-(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp -= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator-(int yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp -= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator-(float yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp -= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator-(double yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp -= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator*(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp *= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator*(int yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp *= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator*(float yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp *= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator*(double yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp *= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator/(const ScreenPercentAbstract &yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp /= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator/(int yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp /= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator/(float yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp /= yRef;
		return temp;
	}

	ScreenPercentAbstract ScreenPercentAbstract::operator/(double yRef) const
	{
		ScreenPercentAbstract temp(*this);
		temp /= yRef;
		return temp;
	}
}
