#pragma once
#include "../defines.h"

namespace star
{
	class ScreenPercentAbstract
	{
	public:
		// [COMMENT] you can just define the other operators here to
		// you ask me how? Well as follows:
		// 1) Remove the pure virtual from that one function, 
		//    just make it an empty body function
		// 2) Put the constructor protected, this way you can't allocate
		//    this class either by accident.

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
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator=(const int &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator=(const float &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator=(const double &yRef);

		ScreenPercentAbstract& operator+=(const ScreenPercentAbstract &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator+=(const int &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator+=(const float &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator+=(const double &yRef);

		ScreenPercentAbstract& operator-=(const ScreenPercentAbstract &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator-=(const int &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator-=(const float &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator-=(const double &yRef);

		ScreenPercentAbstract& operator*=(const ScreenPercentAbstract &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator*=(const int &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator*=(const float &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator*=(const double &yRef);

		ScreenPercentAbstract& operator/=(const ScreenPercentAbstract &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator/=(const int &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator/=(const float &yRef);
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		ScreenPercentAbstract& operator/=(const double &yRef);

		bool operator==(const ScreenPercentAbstract& yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		bool operator==(const int& yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		bool operator==(const float& yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		bool operator==(const double& yRef) const;

		bool operator!=(const ScreenPercentAbstract& yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		bool operator!=(const int& yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		bool operator!=(const float& yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		bool operator!=(const double& yRef) const;
		

	protected:
		float m_ScreenPercentage;
		float m_ScreenValue;

	private:						   
		virtual void ConvertPercentToScreenPos() = 0;
		
		

		
	};
}
