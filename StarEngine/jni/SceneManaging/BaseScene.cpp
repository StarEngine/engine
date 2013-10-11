#include "BaseScene.h"
#include "../Context.h"
#include "../Input/InputManager.h"
#include "../SceneGraph/Object.h"
#include "../StarComponents.h"

namespace star 
{
	BaseScene::BaseScene(const tstring & name)
		: m_GestureManagerPtr(nullptr)
		, m_Name(name)
		, m_Initialized(false) 
		, m_Objects()
		, m_pActiveCamera(nullptr)
	{
		m_GestureManagerPtr = new GestureManager();
	}
	status BaseScene::BaseInitialize(const Context & context)
	{
		status isInitialized(Initialize(context));
		if(isInitialized == STATUS_OK)
		{
			m_Initialized = true;
			for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
			{
				m_Objects[i]->Initialize();
			}
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
		if((m_GestureManagerPtr && 
			InputManager::GetInstance()->GetGestureManager() == nullptr) || 
			m_GestureManagerPtr != InputManager::GetInstance()->GetGestureManager())
		{
			InputManager::GetInstance()->SetGestureManager(m_GestureManagerPtr);
		}
		if(m_GestureManagerPtr && m_GestureManagerPtr == 
			InputManager::GetInstance()->GetGestureManager())
		{
			m_GestureManagerPtr->Update(context);
		}
		for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
		{
			m_Objects[i]->Update(context);
		}
		return Update(context);
	}

	
	status BaseScene::BaseDraw()
	{
		glClearColor(1.0f,0.0f,0.0f, 1.0f); // Clear the background of our window to red

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
		for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
		{
			m_Objects[i]->Draw();
		}
		return Draw(); 
	}

	void BaseScene::AddObject(Object * object)
	{
		auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
		if(it == m_Objects.end())
		{
			m_Objects.push_back(object);
			object->SetScene(this);
		}
	}

	void BaseScene::RemoveObject(Object * object)
	{
		auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
		if(it != m_Objects.end())
		{
			m_Objects.erase(it);
			object->UnsetScene();
		}
	}

	void BaseScene::SetActiveCamera(CameraComponent* pCameraComponent)
	{
		if(m_pActiveCamera != nullptr)
		{
			m_pActiveCamera->Deactivate();
		}

		m_pActiveCamera = pCameraComponent;
		m_pActiveCamera->Activate();
	}
}
