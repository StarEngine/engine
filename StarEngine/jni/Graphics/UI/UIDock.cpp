#include "UIDock.h"
#include "UIElement.h"

namespace star
{
	UIDock::UIDock(void)
		: Object()
	{

	}

	UIDock::~UIDock(void)
	{

	}

	void UIDock::Initialize()
	{
		Object::Initialize();
	}
	
	void UIDock::AddElement(UIElement * pElement)
	{
		AddChild(pElement);
	}

	void UIDock::Update(const Context& context)
	{
	}

	void UIDock::Draw()
	{
	}
}
