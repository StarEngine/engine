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
#include "../Input/Gestures/BaseGesture.h"

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
		, m_pActiveCamera(nullptr)
		, m_pCursor(nullptr)
		, m_CullingOffsetX(0)
		, m_CullingOffsetY(0)
		, m_Initialized(false)
		, m_CursorIsHidden(false)
		, m_SystemCursorIsHidden(false)
		, m_GestureID(0)
	{
		m_pStopwatch = std::make_shared<Stopwatch>();
		m_GestureManagerPtr = std::make_shared<GestureManager>();
		m_CollisionManagerPtr = std::make_shared<CollisionManager>();
	}
	
	BaseScene::~BaseScene()
	{
		for(auto & object : m_Objects)
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

			int32 screenWidth = GraphicsManager::GetInstance()->GetScreenWidth();
			int32 screenHeight = GraphicsManager::GetInstance()->GetScreenHeight();

			float32 left = camPos.pos2D().x - m_CullingOffsetX;
			float32 right = camPos.pos2D().x + screenWidth + m_CullingOffsetX;
			float32 top = camPos.pos2D().y + screenHeight + m_CullingOffsetY;
			float32 bottom = camPos.pos2D().y - m_CullingOffsetY;

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
		if(!object)
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("BaseScene::AddObjec: Trying to add a nullptr object."));
			return;
		}
		auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
		if(it == m_Objects.end())
		{
			if(m_Initialized)
			{
				object->BaseInitialize();
			}
			m_Objects.push_back(object);
			object->SetScene(this);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::AddObject: \
				   Trying to add a duplicate object."), STARENGINE_LOG_TAG);
		}
	}

	void BaseScene::AddObject(Object * object, const tstring & name)
	{
		if(!object)
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("BaseScene::AddObjec: Trying to add a nullptr object."));
			return;
		}
		object->SetName(name);
		AddObject(object);
	}

	void BaseScene::RemoveObject(Object * object)
	{
		auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
		if(it != m_Objects.end())
		{
			m_Garbage.push_back(object);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::RemoveObject: \
				   Trying to remove an unknown object."), STARENGINE_LOG_TAG);
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
				   + name + _T("'."), STARENGINE_LOG_TAG);
	}

	void BaseScene::AddGesture(BaseGesture* gesture)
	{
		Logger::GetInstance()->Log(LogLevel::Warning, 
_T("Please use the method AddGesture(BaseGesture* gesture, \
const tstring & name) to add gestures. \
using BaseScene::AddGesture(BaseGesture* gesture) is much slower, use with care!"),
			STARENGINE_LOG_TAG);

		m_GestureManagerPtr->AddGesture(gesture, _T("Gesture_") + string_cast<tstring>(m_GestureID));
		++m_GestureID;
	}

	void BaseScene::AddGesture(BaseGesture* gesture, const tstring & name)
	{
		m_GestureManagerPtr->AddGesture(gesture, name);
	}

	void BaseScene::RemoveGesture(BaseGesture* gesture)
	{
		m_GestureManagerPtr->RemoveGesture(gesture);
	}

	void BaseScene::RemoveGesture(const tstring & name)
	{
		m_GestureManagerPtr->RemoveGesture(name);
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
				   + name + _T("'."), STARENGINE_LOG_TAG);
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
				   + name + _T("'."), STARENGINE_LOG_TAG);
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
				   + name + _T("'."), STARENGINE_LOG_TAG);
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
		if(!pCamera ||
			m_pActiveCamera == pCamera)
		{
			return;
		}

		if(m_pActiveCamera != nullptr)
		{
			m_pActiveCamera->GetComponent<CameraComponent>()->Deactivate();
		}

		m_pActiveCamera = pCamera;
		m_pActiveCamera->GetComponent<CameraComponent>()->Activate();
	}
	
	BaseCamera* BaseScene::GetActiveCamera() const
	{
		return m_pActiveCamera;
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
the custom cursor code in your game project."), STARENGINE_LOG_TAG);
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
the custom cursor code in your game project."), STARENGINE_LOG_TAG);
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
the custom cursor code in your game project."), STARENGINE_LOG_TAG);
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
the custom cursor code in your game project."), STARENGINE_LOG_TAG);
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
				_T("BaseScene::CollectGarbage: Trying to delete unknown object"),
				STARENGINE_LOG_TAG);
			(*it)->UnsetScene();
			m_Objects.erase(it);
			delete elem;
		}
		m_Garbage.clear();
		
	}
}
