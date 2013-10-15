#include "ScreenPercentX.h"
#include "../Graphics/GraphicsManager.h"
namespace star
{
	ScreenPercentX::ScreenPercentX()
		:ScreenPercentAbstract()
	{

	}

	ScreenPercentX::ScreenPercentX(int value)
		:ScreenPercentAbstract(value)
	{

	}
	ScreenPercentX::ScreenPercentX(float value)
		:ScreenPercentAbstract(value)
	{

	}
	ScreenPercentX::ScreenPercentX(double value)
		:ScreenPercentAbstract(value)
	{

	}

	ScreenPercentX::ScreenPercentX(const ScreenPercentAbstract & yRef)
		:ScreenPercentAbstract(yRef)
	{

	}

	ScreenPercentX::~ScreenPercentX()
	{

	}

	void ScreenPercentX::ConvertPercentToScreenPos()
	{
		//We will need "ScaleTo" functions for sprites, and percent - scale values in the init already
		int32 width = GraphicsManager::GetInstance()->GetWindowWidth();
		m_ScreenValue = width/100.0f;
		m_ScreenValue *= m_ScreenPercentage;
	}
}