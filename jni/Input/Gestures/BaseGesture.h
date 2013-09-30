#pragma once
#include <android/input.h>


namespace star
{
	class BaseGesture
	{
	public:
		BaseGesture();
		virtual ~BaseGesture();

		bool CompletedGesture() {return m_bCompletedGesture;}
		static void OnTouchEventAbstract(AInputEvent* pEvent);
	protected:
		virtual void OnTouchEvent(AInputEvent* pEvent);
		bool m_bCompletedGesture;

	private:
		// -------------------------
		// Disabling default copy constructor and default
		// assignment operator.
		// -------------------------
		BaseGesture(const BaseGesture& t);
		BaseGesture(BaseGesture&& t);
		BaseGesture& operator=(const BaseGesture& t);
	};
}
