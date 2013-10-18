#include "UIDock.h"

namespace star
{
	UIDock::UIDock(void)
		: Object()
		, m_ScreenScale(1.0f, 1.0f)
	{

	}

	UIDock::~UIDock(void)
	{

	}

	void UIDock::Initialize()
	{
		Object::Initialize();
	}

	void UIDock::BaseUpdate(const Context& context)
	{
		Object::BaseUpdate(context);
	}

	void UIDock::BaseDraw()
	{
		Object::BaseDraw();
	}
}
