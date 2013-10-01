#include "BaseScene.h"
#include "../Context.h"

namespace star 
{
	BaseScene::BaseScene(const tstring & name)
		: m_Name(name)
		, m_Initialized(false)
	{

	}
	status BaseScene::BaseInitialize(const Context & context)
	{
		m_Initialized=true;
		return Initialize(context);
		return STATUS_OK;
	}
}
