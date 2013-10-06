#include "BaseScene.h"
#include "../Context.h"
#include "../Input/InputManager.h"

namespace star 
{
	BaseScene::BaseScene(const tstring & name)
		: m_Name(name)
		, m_Initialized(false)
		// [COMMENT] Manager has to be initialized first
		// respect the order of your header file!
		, m_GestureManagerPtr(nullptr)
	{
		m_GestureManagerPtr = new GestureManager();
	}
	status BaseScene::BaseInitialize(const Context & context)
	{
		status isInitialized(Initialize(context));
		if(isInitialized == STATUS_OK)
		{
			m_Initialized = true;
			return STATUS_OK;
		}
		return STATUS_KO;
	}

	status BaseScene::BaseOnActivate()
	{
		if(m_GestureManagerPtr)
		{
			InputManager::GetInstance()->SetGestureManager(m_GestureManagerPtr);
		}
		return OnActivate();
	}

	void BaseScene::BaseOnDeactivate()
	{
		OnDeactivate();
	}

	status BaseScene::BaseUpdate(const Context& context)
	{
		// [COMMENT] don't ever use long lines please... SHORTEN THEM!!!
		if((m_GestureManagerPtr && InputManager::GetInstance()->GetGestureManager() == nullptr) || m_GestureManagerPtr != InputManager::GetInstance()->GetGestureManager())
		{
			InputManager::GetInstance()->SetGestureManager(m_GestureManagerPtr);
		}
		// [COMMENT] don't ever use long lines please... SHORTEN THEM!!!
		if(m_GestureManagerPtr && m_GestureManagerPtr == InputManager::GetInstance()->GetGestureManager())
		{
			m_GestureManagerPtr->Update(context);
		}
		return Update(context);
	}
}
