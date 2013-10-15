#pragma once

namespace star
{
	class ScreenPercentAbstract
	{
	public:

		virtual ~ScreenPercentAbstract();

		//[TODO] Try to see if i have to do this only on changes, 
		//		 make sure the operators pass the converted float correctly!
		float GetScreenValue();

		//Implement all operator overloading functions here, 
		// because the structure of ScreenPercentX and ScreenPercentY is the same
		ScreenPercentAbstract& operator=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator=(int yRef);
		ScreenPercentAbstract& operator=(float yRef);
		ScreenPercentAbstract& operator=(double yRef);

		ScreenPercentAbstract& operator+=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator+=(int yRef);
		ScreenPercentAbstract& operator+=(float yRef);
		ScreenPercentAbstract& operator+=(double yRef);

		ScreenPercentAbstract& operator-=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator-=(int yRef);
		ScreenPercentAbstract& operator-=(float yRef);
		ScreenPercentAbstract& operator-=(double yRef);

		ScreenPercentAbstract& operator*=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator*=(int yRef);
		ScreenPercentAbstract& operator*=(float yRef);
		ScreenPercentAbstract& operator*=(double yRef);

		ScreenPercentAbstract& operator/=(const ScreenPercentAbstract &yRef);
		ScreenPercentAbstract& operator/=(int yRef);
		ScreenPercentAbstract& operator/=(float yRef);
		ScreenPercentAbstract& operator/=(double yRef);

		bool operator==(const ScreenPercentAbstract& yRef) const;
		bool operator==(int yRef) const;
		bool operator==(float yRef) const;
		bool operator==(double yRef) const;

		bool operator!=(const ScreenPercentAbstract& yRef) const;
		bool operator!=(int yRef) const;
		bool operator!=(float yRef) const;
		bool operator!=(double yRef) const;

		ScreenPercentAbstract operator+(const ScreenPercentAbstract &yRef) const;
		ScreenPercentAbstract operator+(int yRef) const;
		ScreenPercentAbstract operator+(float yRef) const;
		ScreenPercentAbstract operator+(double yRef) const;

		ScreenPercentAbstract operator-(const ScreenPercentAbstract &yRef) const;
		ScreenPercentAbstract operator-(int yRef) const;
		ScreenPercentAbstract operator-(float yRef) const;
		ScreenPercentAbstract operator-(double yRef) const;

		ScreenPercentAbstract operator*(const ScreenPercentAbstract &yRef) const;
		ScreenPercentAbstract operator*(int yRef) const;
		ScreenPercentAbstract operator*(float yRef) const;
		ScreenPercentAbstract operator*(double yRef) const;

		ScreenPercentAbstract operator/(const ScreenPercentAbstract &yRef) const;
		ScreenPercentAbstract operator/(int yRef) const;
		ScreenPercentAbstract operator/(float yRef) const;
		ScreenPercentAbstract operator/(double yRef) const;

	protected:

		ScreenPercentAbstract();
		ScreenPercentAbstract(int value);
		ScreenPercentAbstract(float value);
		ScreenPercentAbstract(double value);
		ScreenPercentAbstract(const ScreenPercentAbstract & yRef);
		ScreenPercentAbstract(ScreenPercentAbstract&& t);

		float m_ScreenPercentage;
		float m_ScreenValue;

	private:
		virtual void ConvertPercentToScreenPos() {};
	};
}
