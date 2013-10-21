#include "BaseScene.h"
#include "../Context.h"
#include "../Input/InputManager.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"
#include "../Objects/FreeCamera.h"

namespace star 
{
	BaseScene::BaseScene(const tstring & name)
		: m_GestureManagerPtr(nullptr)
		, m_Objects()
		, m_pDefaultCamera(nullptr)
		, m_Initialized(false) 
		, m_Name(name)
	{
		m_pStopwatch = std::make_shared<Stopwatch>();
		//m_GestureManagerPtr = new GestureManager();
	}
	
	BaseScene::~BaseScene()
	{
		for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
		{
			delete m_Objects[i];
		}
		m_Objects.clear();
		delete m_GestureManagerPtr;
	}

	status BaseScene::BaseInitialize(const Context & context)
	{
		status isInitialized(CreateObjects());
		if(isInitialized == STATUS_OK)
		{
			m_pDefaultCamera = new FreeCamera();
			AddObject(m_pDefaultCamera);

			m_Initialized = true;
			for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
			{
				m_Objects[i]->Initialize();
			}
			return AfterInitializedObjects(context);
		}
		return STATUS_KO;
	}

	status BaseScene::BaseOnActivate()
	{/*
		if(m_GestureManagerPtr)
		{
			InputManager::GetInstance()->SetGestureManager(m_GestureManagerPtr);
		}*/
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
		
		m_pStopwatch->Update(context);

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

	void BaseScene::OnStart()
	{

	}

	void BaseScene::OnResume()
	{

	}

	void BaseScene::OnPause()
	{

	}

	void BaseScene::OnStop()
	{

	}

	void BaseScene::OnDestroy()
	{

	}

	void BaseScene::OnSaveState(void** pData, size_t* pSize)
	{

	}

	void BaseScene::OnConfigurationChanged()
	{

	}

	void BaseScene::OnLowMemory()
	{

	}

	void BaseScene::OnCreateWindow()
	{

	}

	void BaseScene::OnDestroyWindow()
	{

	}

	void BaseScene::OnGainFocus()
	{

	}

	void BaseScene::OnLostFocus()
	{

	}

	const tstring & BaseScene::GetName() const
	{
		return m_Name;
	}

	bool BaseScene::IsInitialized() const
	{
		return m_Initialized;
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
		auto camComp = m_pDefaultCamera->GetComponent<CameraComponent>();
		if(camComp != nullptr)
		{
			camComp->Deactivate();
		}

		camComp = pCameraComponent;
		camComp->Activate();
	}
	
	FreeCamera* BaseScene::GetActiveCamera() const
	{
		return m_pDefaultCamera;
	}
	
	std::shared_ptr<Stopwatch> BaseScene::GetStopwatch() const
	{
		return m_pStopwatch;
	}

	status BaseScene::CreateObjects()
	{
		return STATUS_OK;
	}

	status BaseScene::AfterInitializedObjects(const Context& context)
	{
		return STATUS_OK;
	}

	status BaseScene::OnActivate()
	{
		return STATUS_OK;
	}

	void BaseScene::OnDeactivate()
	{
	}

	status BaseScene::Update(const Context& context)
	{
		return STATUS_OK;
	}

	status BaseScene::Draw()
	{
		return STATUS_OK;
	}
}
