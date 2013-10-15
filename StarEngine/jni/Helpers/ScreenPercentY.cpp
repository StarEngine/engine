#include "ScreenPercentY.h"
#include "ScreenPercentX.h"
#include "../Graphics/GraphicsManager.h"

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

	ScreenPercentY::ScreenPercentY(const ScreenPercentAbstract & yRef)
		:ScreenPercentAbstract(yRef)
	{

	}

	ScreenPercentY::~ScreenPercentY()
	{

	}

	void ScreenPercentY::ConvertPercentToScreenPos()
	{
		int32 height = GraphicsManager::GetInstance()->GetWindowHeight();
		m_ScreenValue = height/100.0f;
		m_ScreenValue *= m_ScreenPercentage;
	}
}