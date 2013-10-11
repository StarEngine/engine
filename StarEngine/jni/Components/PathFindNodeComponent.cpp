#include "PathFindNodeComponent.h"
#include "..\Logger.h"

namespace star
{
	PathFindNodeComponent::PathFindNodeComponent():
		BaseComponent()
	{

	}

	PathFindNodeComponent::~PathFindNodeComponent(void)
	{
	}

	void PathFindNodeComponent::InitializeComponent()
	{
		m_bInitialized = true;
	}

	void PathFindNodeComponent::Update(const Context& context)
	{
		if(!m_bInitialized)
		{
			return;
		}
	}

	void PathFindNodeComponent::Draw()
	{
	}
}
