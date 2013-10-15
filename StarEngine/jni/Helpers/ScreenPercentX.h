#pragma once
#include "ScreenPercentAbstract.h"

namespace star
{
	class ScreenPercentY;

	class ScreenPercentX : public ScreenPercentAbstract
	{
	public:
		ScreenPercentX();
		ScreenPercentX(int value);
		ScreenPercentX(float value);
		ScreenPercentX(double value);
		// [COMMENT] why not one constructor with a 
		// a reference to ScreenPercentAbstract ?? (INSTEAD OF 2!)
		// 1) This class shouldn't even know the excistance of his brother ScreenPercentY
		// 2) It will work for both this class and all other classes that ever inherent from ScreenPercentAbstract
		// 3) These classes don't have their own unique variables 
		//    ans so it doesn't make sense to make a seperation!
		ScreenPercentX(const ScreenPercentX & yRef);
		ScreenPercentX(const ScreenPercentY & screenPercentY);
		// [COMMENT] put this final keyword on line 8, not here...
		~ScreenPercentX() final;

		//Can't put these operators in ScreenPercentageAbstract class, because it has pure virtual members

		const ScreenPercentX operator+(const ScreenPercentAbstract &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator+(const int &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator+(const float &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator+(const double &yRef) const;

		const ScreenPercentX operator-(const ScreenPercentAbstract &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator-(const int &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator-(const float &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator-(const double &yRef) const;

		const ScreenPercentX operator*(const ScreenPercentAbstract &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator*(const int &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator*(const float &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator*(const double &yRef) const;

		const ScreenPercentX operator/(const ScreenPercentAbstract &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator/(const int &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator/(const float &yRef) const;
		// [COMMENT] for native (build-in C++) never use references...
		// just pass them by value 'T name' (much faster)
		const ScreenPercentX operator/(const double &yRef) const;

	private: 
		// [COMMENT] Why not make the entire class final?
		void ConvertPercentToScreenPos() final;
		// [COMMENT] don't do this! Just remove it...
		ScreenPercentX(ScreenPercentX&& t);
	};
}
