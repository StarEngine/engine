#include "PathFindNodeComponent.h"
#include "..\Logger.h"

namespace star
{
	// [COMMENT] call basecomponent constructor
	PathFindNodeComponent::PathFindNodeComponent()
	{
		Logger::GetSingleton()->Log(LogLevel::Info, _T("PathFindNodeComponent initialized"));
	}

	PathFindNodeComponent::~PathFindNodeComponent(void)
	{
	}

	void PathFindNodeComponent::Initialize()
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
