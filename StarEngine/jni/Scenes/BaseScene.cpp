#include "BaseScene.h"
#include "../Context.h"
#include "../Input/InputManager.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"
#include "../Objects/BaseCamera.h"
#include "../Graphics/GraphicsManager.h"
#include "../Helpers/Debug/DebugDraw.h"

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
		for(auto object : m_Objects)
		{
			delete object;
		}
		m_Objects.clear();
		m_GestureManagerPtr = nullptr;
	}

	void BaseScene::BaseInitialize()
	{
		if(!m_Initialized)
		{
			CreateObjects();

			m_pDefaultCamera = new BaseCamera();

			m_Initialized = true;
			for(auto object : m_Objects)
			{
				object->BaseInitialize();
			}
			BaseAfterInitializedObjects();
		}
	}

	void BaseScene::BaseAfterInitializedObjects()
	{
		AfterInitializedObjects();
	}

	void BaseScene::BaseOnActivate()
	{
		InputManager::GetInstance()->SetGestureManager(m_GestureManagerPtr);
		return OnActivate();
	}

	void BaseScene::BaseOnDeactivate()
	{
		OnDeactivate();
	}

	void BaseScene::BaseUpdate(const Context& context)
	{	
		m_pStopwatch->Update(context);

		for(auto object : m_Objects)
		{
			if(CheckCulling(object))
			{
				object->BaseUpdate(context);
			}
		}

		Update(context);
	}

	void BaseScene::BaseDraw()
	{
		for(auto object : m_Objects)
		{
			if(CheckCulling(object))
			{
				object->BaseDraw();
			}
		}
		Draw(); 
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

	std::shared_ptr<GestureManager> BaseScene::GetGestureManager() const
	{
		return m_GestureManagerPtr;
	}

	void BaseScene::CreateObjects()
	{
	}

	void BaseScene::AfterInitializedObjects()
	{
	}

	void BaseScene::OnActivate()
	{
	}

	void BaseScene::OnDeactivate()
	{
	}

	void BaseScene::Update(const Context& context)
	{
	}

	void BaseScene::Draw()
	{
	}

	bool BaseScene::CheckCulling(Object* object)
	{
		pos objectPos = object->GetTransform()->GetWorldPosition();
		pos camPos = m_pDefaultCamera->GetTransform()->GetWorldPosition();
		float xPos = (camPos.pos2D().x) ;//* ((star::ScaleSystem::GetInstance()->GetWorkingResolution().x)/2.0f);
		float yPos = (camPos.pos2D().y) ;//* ((star::ScaleSystem::GetInstance()->GetWorkingResolution().y)/2.0f); 
		int screenWidth = GraphicsManager::GetInstance()->GetWindowWidth();//GetTargetWindowWidth();
		int screenHeight = GraphicsManager::GetInstance()->GetWindowHeight();//->GetTargetWindowHeight();

		SpriteComponent* sprite = object->GetComponent<SpriteComponent>();
		SpritesheetComponent* spritesheet = object->GetComponent<SpritesheetComponent>();
		if(sprite == nullptr && spritesheet == nullptr)
		{
			return false;
		}

		int spriteWidth;
		int spriteHeight;

		if(sprite != nullptr)
		{
			spriteWidth = sprite->GetWidth() * object->GetTransform()->GetWorldScale().x;
			spriteHeight = sprite->GetHeight() * object->GetTransform()->GetWorldScale().y;
		}
		if(spritesheet != nullptr)
		{
			spriteWidth = spritesheet->GetWidth() * object->GetTransform()->GetWorldScale().x;
			spriteHeight = spritesheet->GetHeight() * object->GetTransform()->GetWorldScale().y;
		}

		//[TODO] allow used to set the offset you want around the culling area.
		if(objectPos.x > xPos + screenWidth + 64 ||
			objectPos.x + spriteWidth < xPos - 64 ||
			objectPos.y > yPos + screenHeight + 64 ||
			objectPos.y + spriteHeight < yPos - 64)
		{
			return false;
		}
		return true;
	}
}
