#include "BaseScene.h"
#include "../Context.h"
#include "../Input/InputManager.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"
#include "../Objects/BaseCamera.h"
#include "../Graphics/GraphicsManager.h"
#include "../Graphics/ScaleSystem.h"
#include "../Helpers/Debug/DebugDraw.h"
#include "../Physics/Collision/CollisionManager.h"
#include "../Input/Gestures/GestureManager.h"

namespace star 
{
	BaseScene::BaseScene(const tstring & name)
		: m_GestureManagerPtr(nullptr)
		, m_CollisionManagerPtr(nullptr)
		, m_Objects()
		, m_pDefaultCamera(nullptr)
		, m_CullingOffsetX(0)
		, m_CullingOffsetY(0)
		, m_Initialized(false) 
		, m_Name(name)
	{
		m_pStopwatch = std::make_shared<Stopwatch>();
		m_GestureManagerPtr = std::make_shared<GestureManager>();
		m_CollisionManagerPtr = std::make_shared<CollisionManager>();
	}
	
	BaseScene::~BaseScene()
	{
		for(auto object : m_Objects)
		{
			delete object;
		}
		m_Objects.clear();
		m_GestureManagerPtr = nullptr;
		m_CollisionManagerPtr = nullptr;
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
			//if(CheckCulling(object))
			//{
				object->BaseUpdate(context);
			//}
		}
		Update(context);
		//[COMMENT] Updating the collisionManager before the objects or here?
		//			If i do it before the objects, there is the problem that
		//			the objects won't be translated correctly...
		//			So i think here is best, unless somebody proves me wrong
		m_CollisionManagerPtr->Update(context);
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

	std::shared_ptr<CollisionManager> BaseScene::GetCollisionManager() const
	{
		return m_CollisionManagerPtr;
	}

	bool BaseScene::CheckCulling(Object* object)
	{
		pos objectPos = object->GetTransform()->GetWorldPosition();
		pos camPos = m_pDefaultCamera->GetTransform()->GetWorldPosition();
		float32 xPos = (camPos.pos2D().x) * ((star::ScaleSystem::GetInstance()->GetWorkingResolution().x) / 2.0f);
		float32 yPos = (camPos.pos2D().y) * ((star::ScaleSystem::GetInstance()->GetWorkingResolution().y) / 2.0f); 
		int32 screenWidth = GraphicsManager::GetInstance()->GetScreenWidth();
		int32 screenHeight = GraphicsManager::GetInstance()->GetScreenHeight();
		SpriteComponent* sprite = object->GetComponent<SpriteComponent>();
		SpritesheetComponent* spritesheet = object->GetComponent<SpritesheetComponent>();
		if(sprite == nullptr && spritesheet == nullptr)
		{
			return false;
		}

		int32 spriteWidth;
		int32 spriteHeight;

		if(sprite != nullptr)
		{
			spriteWidth = int32(float32(sprite->GetWidth()) * object->GetTransform()->GetWorldScale().x);
			spriteHeight = int32(float32(sprite->GetHeight()) * object->GetTransform()->GetWorldScale().y);
		}
		if(spritesheet != nullptr)
		{
			spriteWidth = int32(float32(spritesheet->GetWidth()) * object->GetTransform()->GetWorldScale().x);
			spriteHeight = int32(float32(spritesheet->GetHeight()) * object->GetTransform()->GetWorldScale().y);
		}

		//[TODO] allow used to set the offset you want around the culling area.
		if(	objectPos.x > xPos + screenWidth + m_CullingOffsetX ||
			objectPos.x + spriteWidth < xPos - m_CullingOffsetX ||
			objectPos.y > yPos + screenHeight + m_CullingOffsetY ||
			objectPos.y + spriteHeight < yPos - m_CullingOffsetY)
		{
			return false;
		}
		return true;
	}

	void BaseScene::SetCullingOffset(int32 offset)
	{
		m_CullingOffsetX = offset;
		m_CullingOffsetY = offset;
	}

	void BaseScene::SetCullingOffset(int32 offsetX, int32 offsetY)
	{
		m_CullingOffsetX = offsetX;
		m_CullingOffsetY = offsetY;
	}
}
