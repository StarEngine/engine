#pragma once
#include "ScreenPercentAbstract.h"
namespace star
{
	class ScreenPercentX;

	class ScreenPercentY : public ScreenPercentAbstract
	{
	public:
		ScreenPercentY();
		ScreenPercentY(int value);
		ScreenPercentY(float value);
		ScreenPercentY(double value);
		// [COMMENT] why not one constructor with a 
		// a reference to ScreenPercentAbstract ?? (INSTEAD OF 2!)
		// 1) This class shouldn't even know the excistance of his brother ScreenPercentX
		// 2) It will work for both this class and all other classes that ever inherent from ScreenPercentAbstract
		// 3) These classes don't have their own unique variables 
		//    ans so it doesn't make sense to make a seperation!
		ScreenPercentY(const ScreenPercentY & yRef);
		ScreenPercentY(const ScreenPercentX & screenPercentX);
		// [COMMENT] put this final keyword on line 7, not here...
		~ScreenPercentY() final;

		//Can't put these operators in ScreenPercentageAbstract class, because it has pure virtual members

		const ScreenPercentY operator+(const ScreenPercentAbstract &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator+(const int &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator+(const float &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator+(const double &yRef) const;

		const ScreenPercentY operator-(const ScreenPercentAbstract &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator-(const int &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator-(const float &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator-(const double &yRef) const;

		const ScreenPercentY operator*(const ScreenPercentAbstract &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator*(const int &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator*(const float &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator*(const double &yRef) const;
						   
		const ScreenPercentY operator/(const ScreenPercentAbstract &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator/(const int &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator/(const float &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentY operator/(const double &yRef) const;

	private: 
		// [COMMENT] Why not make the entire class final?
		void ConvertPercentToScreenPos() final;
	};
}