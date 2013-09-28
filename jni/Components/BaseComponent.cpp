#include "BaseComponent.h"
#include "..\SceneGraph\Object.h"
#include "..\Context.h"
#include "..\Logger.h"

namespace star
{
	// [COMMENT] create a second constructor that uses a parentobject as parameter
	BaseComponent::BaseComponent():
		m_pParentObject(nullptr),
		m_bInitialized(false)
	{
	}


	BaseComponent::~BaseComponent(void)
	{
	}

	void BaseComponent::Initialize()
	{
		if(m_bInitialized)
		{
			return;
		}

		InitializeComponent();
		m_bInitialized = true;
	}
}
