#pragma once



namespace star
{
	class TapGesture : public BaseGesture
	{
	public:
		TapGesture();
		virtual ~TapGesture();
	protected:
		virtual void OnTouchEvent(AInputEvent* pEvent);
	};
}
