#pragma once
#include "../defines.h"

namespace star
{
	class ScreenPercentAbstract
	{
	public:
		ScreenPercentAbstract();
		ScreenPercentAbstract(int value);
		ScreenPercentAbstract(float value);
		ScreenPercentAbstract(double value);
		ScreenPercentAbstract(const ScreenPercentAbstract & yRef);
		ScreenPercentAbstract(ScreenPercentAbstract&& t);
		virtual ~ScreenPercentAbstract();

		//[TODO] Try to see if i have to do this only on changes, 
		//		 make sure the operators pass the converted float correctly!
		float GetScreenValue() const;

		//Implement all operator overloading functions here, 
		// because the structure of ScreenPercentX and ScreenPercentY is the same
		ScreenPercentAbstract& operator=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator=(const int &yRef);
		ScreenPercentAbstract& operator=(const float &yRef);
		ScreenPercentAbstract& operator=(const double &yRef);

		ScreenPercentAbstract& operator+=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator+=(const int &yRef);
		ScreenPercentAbstract& operator+=(const float &yRef);
		ScreenPercentAbstract& operator+=(const double &yRef);

		ScreenPercentAbstract& operator-=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator-=(const int &yRef);
		ScreenPercentAbstract& operator-=(const float &yRef);
		ScreenPercentAbstract& operator-=(const double &yRef);

		ScreenPercentAbstract& operator*=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator*=(const int &yRef);
		ScreenPercentAbstract& operator*=(const float &yRef);
		ScreenPercentAbstract& operator*=(const double &yRef);

		ScreenPercentAbstract& operator/=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator/=(const int &yRef);
		ScreenPercentAbstract& operator/=(const float &yRef);
		ScreenPercentAbstract& operator/=(const double &yRef);

		bool operator==(const ScreenPercentAbstract& yRef) const;
		bool operator==(const int& yRef) const;
		bool operator==(const float& yRef) const;
		bool operator==(const double& yRef) const;

		bool operator!=(const ScreenPercentAbstract& yRef) const;
		bool operator!=(const int& yRef) const;
		bool operator!=(const float& yRef) const;
		bool operator!=(const double& yRef) const;
		

	protected:
		float m_ScreenPercentage;
		float m_ScreenValue;

	private:						   
		virtual void ConvertPercentToScreenPos() = 0;
		
		

		
	};
}
