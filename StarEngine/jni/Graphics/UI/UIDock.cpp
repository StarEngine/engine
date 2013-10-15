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

	void UIDock::Update(const Context& context)
	{
		Object::Update(context);
	}

	void UIDock::Draw()
	{
		Object::Draw();
	}
}
