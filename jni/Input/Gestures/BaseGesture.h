#pragma once
#include <android/input.h>
#include <android_native_app_glue.h>
#include "../../defines.h"

namespace star
{
	class BaseGesture
	{
	public:
		BaseGesture();
		virtual ~BaseGesture();
		virtual void OnTouchEvent(AInputEvent* pEvent);
		bool CompletedGesture() {return (m_bCompletedGesture);}
	protected:

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
