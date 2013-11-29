#include "BaseScene.h"
#include "../Context.h"
#include "../Input/InputManager.h"
#include "../StarComponents.h"
#include "../Objects/BaseCamera.h"
#include "../Graphics/GraphicsManager.h"
#include "../Graphics/ScaleSystem.h"
#include "../Helpers/Debug/DebugDraw.h"
#include "../Physics/Collision/CollisionManager.h"
#include "../Input/Gestures/GestureManager.h"
#include "../Graphics/UI/UICursor.h"
#include "../Graphics/UI/UIBaseCursor.h"
#include "SceneManager.h"

namespace star 
{
	bool BaseScene::CULLING_IS_ENABLED = true;

	BaseScene::BaseScene(const tstring & name)
		: Entity(name)
		, m_GestureManagerPtr(nullptr)
		, m_CollisionManagerPtr(nullptr)
		, m_Objects()
		, m_Garbage()
		, m_pDefaultCamera(nullptr)
		, m_pCursor(nullptr)
		, m_CullingOffsetX(0)
		, m_CullingOffsetY(0)
		, m_Initialized(false)
		, m_CursorIsHidden(false)
		, m_SystemCursorIsHidden(false)
	{
		m_pStopwatch = std::make_shared<Stopwatch>();
		m_GestureManagerPtr = std::make_shared<GestureManager>();
		m_CollisionManagerPtr = std::make_shared<CollisionManager>();
	}
	
	BaseScene::~BaseScene()
	{
		for(auto object : m_Objects)
		{
			SafeDelete(object);
		}
		m_Objects.clear();
		m_GestureManagerPtr = nullptr;
		m_CollisionManagerPtr = nullptr;
		SafeDelete(m_pCursor);
	}

	void BaseScene::Destroy()
	{
		SceneManager::GetInstance()->RemoveScene(GetName());
	}

	void BaseScene::BaseInitialize()
	{
		if(!m_Initialized)
		{
			CreateObjects();

			if(m_pDefaultCamera == nullptr)
			{
				m_pDefaultCamera = new BaseCamera();
				AddObject(m_pDefaultCamera);
			}

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
		SetActiveCamera(m_pDefaultCamera);
		AfterInitializedObjects();
	}

	void BaseScene::BaseOnActivate()
	{
		InputManager::GetInstance()->SetGestureManager(m_GestureManagerPtr);
		SetOSCursorHidden(m_CursorIsHidden || m_SystemCursorIsHidden);
		SetActiveCursorLocked(false);
		return OnActivate();
	}

	void BaseScene::BaseOnDeactivate()
	{
		SetStateActiveCursor(_T("idle"));
		for(auto object : m_Objects)
		{
			object->Reset();
		}
		OnDeactivate();
	}

	void BaseScene::BaseUpdate(const Context& context)
	{	
		CollectGarbage();

		m_pStopwatch->Update(context);
		
#ifdef DESKTOP
		if(m_SystemCursorIsHidden && !m_CursorIsHidden)
		{
			if(m_pCursor)
			{
				m_pCursor->BaseUpdate(context);
			}
			else
			{
				SceneManager::GetInstance()->UpdateDefaultCursor(context);
			}
		}
#endif
		
		Update(context);

		for(auto object : m_Objects)
		{
			object->BaseUpdate(context);
		}

		//[COMMENT] Updating the collisionManager before the objects or here?
		//			If i do it before the objects, there is the problem that
		//			the objects won't be translated correctly...
		//			So i think here is best, unless somebody proves me wrong
		m_CollisionManagerPtr->Update(context);
	}

	void BaseScene::BaseDraw()
	{
		if(!CULLING_IS_ENABLED)
		{
			for(auto object : m_Objects)
			{
				object->BaseDraw();
			}
		}
		else
		{
			pos camPos = m_pDefaultCamera->GetTransform()->GetWorldPosition();

			float32 xPos = camPos.pos2D().x *
				((star::ScaleSystem::GetInstance()->GetWorkingResolution().x) / 2.0f);
			float32 yPos = camPos.pos2D().y *
				((star::ScaleSystem::GetInstance()->GetWorkingResolution().y) / 2.0f); 

			int32 screenWidth = GraphicsManager::GetInstance()->GetScreenWidth();
			int32 screenHeight = GraphicsManager::GetInstance()->GetScreenHeight();

			float32 left = xPos - m_CullingOffsetX;
			float32 right = xPos + screenWidth + m_CullingOffsetX;
			float32 top = yPos + screenHeight + m_CullingOffsetY;
			float32 bottom = yPos - m_CullingOffsetY;

			for(auto object : m_Objects)
			{
				object->BaseDrawWithCulling(left, right, top, bottom);
			}
		}
	
		Draw(); 

#ifdef DESKTOP
		if(m_SystemCursorIsHidden && !m_CursorIsHidden)
		{
			if(m_pCursor)
			{
				m_pCursor->BaseDraw();
			}
			else
			{
				SceneManager::GetInstance()->DrawDefaultCursor();
			}
		}
#endif
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
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::AddObject: \
				   Trying to add a duplicate object."));
		}
	}

	void BaseScene::AddObject(Object * object, const tstring & name)
	{
		auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
		if(it == m_Objects.end())
		{
			object->SetName(name);
			m_Objects.push_back(object);
			object->SetScene(this);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::AddObject: \
				   Trying to add a duplicate object '")
				   + name + _T("'."));
		}
	}

	void BaseScene::RemoveObject(Object * object)
	{
		auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
		if(it != m_Objects.end())
		{
			m_Garbage.push_back(object);
			object->UnsetScene();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::RemoveObject: \
				   Trying to remove an unknown object."));
		}
	}
	
	void BaseScene::RemoveObject(const tstring & name)
	{
		for(auto object : m_Objects)
		{
			if(object->CompareName(name))
			{
				RemoveObject(object);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::RemoveObject: \
				   Trying to remove an unknown object '")
				   + name + _T("'."));
	}

	void BaseScene::SetObjectFrozen(const tstring & name, bool freeze)
	{
		for(auto object : m_Objects)
		{
			if(object->CompareName(name))
			{
				object->Freeze(freeze);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::SetObjectFrozen: \
				   Trying to (un)freeze an unknown object '")
				   + name + _T("'."));
	}

	void BaseScene::SetObjectDisabled(const tstring & name, bool disabled)
	{
		for(auto object : m_Objects)
		{
			if(object->CompareName(name))
			{
				object->SetDisabled(disabled);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::SetObjectDisabled: \
				   Trying to enable/disable an unknown object '")
				   + name + _T("'."));
	}

	void BaseScene::SetObjectVisible(const tstring & name, bool visible)
	{
		for(auto object : m_Objects)
		{
			if(object->CompareName(name))
			{
				object->SetVisible(visible);
				return;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::SetObjectVisible: \
				   Trying to (un)hide an unknown object '")
				   + name + _T("'."));
	}

	void BaseScene::SetGroupFrozen(const tstring & tag, bool visible)
	{
		for(auto object : m_Objects)
		{
			if(object->CompareGroupTag(tag))
			{
				object->Freeze(visible);
			}
		}
	}

	void BaseScene::SetGroupDisabled(const tstring & tag, bool visible)
	{
		for(auto object : m_Objects)
		{
			if(object->CompareGroupTag(tag))
			{
				object->SetDisabled(visible);
			}
		}
	}

	void BaseScene::SetGroupVisible(const tstring & tag, bool visible)
	{
		for(auto object : m_Objects)
		{
			if(object->CompareGroupTag(tag))
			{
				object->SetVisible(visible);
			}
		}
	}

	void BaseScene::GetGroup(const tstring & tag, std::vector<Object*> & group)
	{
		group.clear();
		for(auto object : m_Objects)
		{
			if(object->CompareGroupTag(tag))
			{
				group.push_back(object);
			}
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

	void BaseScene::SetCullingIsEnabled(bool enabled)
	{
		CULLING_IS_ENABLED = enabled;
	}

	bool BaseScene::IsCullingEnabled()
	{
		return CULLING_IS_ENABLED;
	}

	void BaseScene::SetCursorHidden(bool hidden)
	{
		m_CursorIsHidden = hidden;
		if(hidden)
		{
			SetOSCursorHidden(true);
		}
	}
	
	void BaseScene::SetSystemCursorHidden(bool hidden)
	{
		m_SystemCursorIsHidden = hidden;
		SetOSCursorHidden(hidden);
	}

	void BaseScene::SetOSCursorHidden(bool hidden)
	{
#ifdef _WIN32
		ShowCursor(BOOL(!hidden));
#endif
	}

	void BaseScene::SetCursor(UIBaseCursor * cursor)
	{
		SafeDelete(m_pCursor);
		m_pCursor = cursor;
		m_pCursor->BaseInitialize();
		SetSystemCursorHidden(true);
#ifdef MOBILE
		Logger::GetInstance()->Log(LogLevel::Warning,
			tstring(_T("BaseScene::SetCursor: Cursor isn't supported on mobile device."))
			+ _T(" For optimialisation reasons it's better to disable the code related to\
the custom cursor code in your game project."));
#endif
	}

	void BaseScene::UnsetCursor(bool showSystemCursor)
	{
		SafeDelete(m_pCursor);
		if(SceneManager::GetInstance()->IsDefaultCursorDefined())
		{
			SetSystemCursorHidden(!showSystemCursor);
		}
#ifdef MOBILE
		Logger::GetInstance()->Log(LogLevel::Warning,
			tstring(_T("BaseScene::UnsetCursor: Cursor isn't supported on mobile device."))
			+ _T(" For optimialisation reasons it's better to disable the code related to\
the custom cursor code in your game project."));
#endif
	}

	void BaseScene::SetStateActiveCursor(const tstring & state)
	{
		if(m_pCursor)
		{
			m_pCursor->SetState(state);
#ifdef MOBILE
		Logger::GetInstance()->Log(LogLevel::Warning,
			tstring(_T("BaseScene::SetStateActiveCursor: Cursor isn't supported on mobile device."))
			+ _T(" For optimialisation reasons it's better to disable the code related to\
the custom cursor code in your game project."));
#endif
			return;
		}
		else
		{
			SceneManager::GetInstance()->SetDefaultCursorState(state);
			return;
		}
	}
	
	void BaseScene::SetActiveCursorLocked(bool locked)
	{
		if(m_pCursor)
		{
			m_pCursor->SetLocked(locked);
#ifdef MOBILE
		Logger::GetInstance()->Log(LogLevel::Warning,
			tstring(_T("BaseScene::SetActiveCursorLocked: Cursor isn't supported on mobile device."))
			+ _T(" For optimialisation reasons it's better to disable the code related to\
the custom cursor code in your game project."));
#endif
			return;
		}
		else
		{
			SceneManager::GetInstance()->SetDefaultCursorLocked(locked);
			return;
		}
	}
	
	bool BaseScene::IsActiveCursorLocked() const
	{
		if(m_pCursor)
		{
			return m_pCursor->IsLocked();
		}
		else
		{
			return SceneManager::GetInstance()->IsDefaultCursorLocked();
		}
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

	void BaseScene::CollectGarbage()
	{
		for(auto elem : m_Garbage)
		{
			auto it = std::find(m_Objects.begin(), m_Objects.end(), elem);
			Logger::GetInstance()->Log(it != m_Objects.end(),
				_T("BaseScene::CollectGarbage: Trying to delete unknown object"));
			m_Objects.erase(it);
			delete elem;
		}
		m_Garbage.clear();
		
	}
}
