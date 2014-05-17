#include "PathFindNodeComponent.h"
#include "../../Logger.h"
#include "../../AI/Pathfinding/PathFindManager.h"

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
		PathFindManager::GetInstance()->AddObject(m_pParentObject);
	}

	void PathFindNodeComponent::Update(const Context& context)
	{

	}

	void PathFindNodeComponent::Draw()
	{
	}
}
