#include "BaseScene.h"
#include "../Context.h"
#include "../Input/InputManager.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"
#include "../Objects/BaseCamera.h"
#include "../Graphics/ScaleSystem.h"
#include "../Graphics/GraphicsManager.h"

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
		m_GestureManagerPtr = std::make_shared<GestureManager>();
	}
	
	BaseScene::~BaseScene()
	{
		for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
		{
			delete m_Objects[i];
		}
		m_Objects.clear();
		m_GestureManagerPtr = nullptr;
	}

	status BaseScene::BaseInitialize()
	{
		status isInitialized(CreateObjects());
		if(isInitialized == STATUS_OK)
		{
			m_pDefaultCamera = new BaseCamera();

			m_Initialized = true;
			for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
			{
				m_Objects[i]->BaseInitialize();
			}
			return AfterInitializedObjects();
		}
		return STATUS_KO;
	}

	status BaseScene::BaseOnActivate()
	{
		InputManager::GetInstance()->SetGestureManager(m_GestureManagerPtr);
		return OnActivate();
	}

	void BaseScene::BaseOnDeactivate()
	{
		OnDeactivate();
	}

	status BaseScene::BaseUpdate(const Context& context)
	{	
		m_pStopwatch->Update(context);

		for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
		{
			m_Objects[i]->BaseUpdate(context);
		}

		return Update(context);
	}

	status BaseScene::BaseDraw()
	{
		glClearColor(0.0f,0.0f,0.0f,1.0f);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
		for(uint32 i = 0 ; i < m_Objects.size() ; ++i)
		{
			m_Objects[i]->BaseDraw();
		}
		return Draw(); 
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

	void BaseScene::SetActiveCamera(BaseCamera* pCamera)
	{
		if(m_pDefaultCamera == pCamera)
		{
			return;
		}

		if(m_pDefaultCamera != nullptr)
		{
			delete m_pDefaultCamera;
			m_pDefaultCamera = nullptr;
		}

		m_pDefaultCamera = pCamera;
		m_pDefaultCamera->GetComponent<CameraComponent>()->Activate();
	}
	
	BaseCamera* BaseScene::GetActiveCamera() const
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

	status BaseScene::AfterInitializedObjects()
	{
		return STATUS_OK;
	}

	status BaseScene::OnActivate()
	{
		return STATUS_OK;
	}

	status BaseScene::OnDeactivate()
	{
		return STATUS_OK;
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
