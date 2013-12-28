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
		, m_pGestureManager(nullptr)
		, m_pCollisionManager(nullptr)
		, m_pObjects()
		, m_pGarbage()
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
		m_pGestureManager = std::make_shared<GestureManager>();
		m_pCollisionManager = std::make_shared<CollisionManager>();
	}
	
	BaseScene::~BaseScene()
	{
		for(auto & object : m_pObjects)
		{
			SafeDelete(object);
		}
		m_pObjects.clear();
		m_pGestureManager = nullptr;
		m_pCollisionManager = nullptr;
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
			for(auto object : m_pObjects)
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
		InputManager::GetInstance()->SetGestureManager(m_pGestureManager);
		SetOSCursorHidden(m_CursorIsHidden || m_SystemCursorIsHidden);
		SetActiveCursorLocked(false);
		return OnActivate();
	}

	void BaseScene::BaseOnDeactivate()
	{
		SetStateActiveCursor(_T("idle"));
		for(auto object : m_pObjects)
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

		for(auto pObject : m_pObjects)
		{
			pObject->BaseUpdate(context);
		}

		//[COMMENT] Updating the collisionManager before the objects or here?
		//			If i do it before the objects, there is the problem that
		//			the objects won't be translated correctly...
		//			So i think here is best, unless somebody proves me wrong
		m_pCollisionManager->Update(context);
	}

	void BaseScene::BaseDraw()
	{
		if(!CULLING_IS_ENABLED)
		{
			for(auto pObject : m_pObjects)
			{
				pObject->BaseDraw();
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

			for(auto pObject : m_pObjects)
			{
				pObject->BaseDrawWithCulling(left, right, top, bottom);
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

	void BaseScene::AddObject(Object * pObject)
	{
		if(!pObject)
		{
			LOG(LogLevel::Error,
				_T("BaseScene::AddObject: You can't add a nullptr object.\
 Adding failed!"));
			return;
		}
		auto it = std::find(m_pObjects.begin(), m_pObjects.end(), pObject);
		if(it == m_pObjects.end())
		{
			if(m_Initialized)
			{
				pObject->BaseInitialize();
			}
			if(IsObjectNameAlreadyInUse(pObject->GetName()))
			{
				DEBUG_LOG(LogLevel::Warning,
				_T("BaseScene::AddObject: an object with the name '")
				+ pObject->GetName() + _T("' already exists. \
Object gets added but beware, duplicate names can become the cause of problems."),
				STARENGINE_LOG_TAG);
			}
			m_pObjects.push_back(pObject);
			pObject->SetScene(this);
		}
		else
		{
			LOG(LogLevel::Warning,
				_T("BaseScene::AddObject: \
				   Trying to add a duplicate object."), STARENGINE_LOG_TAG);
		}
	}

	void BaseScene::AddObject(Object * pObject, const tstring & name)
	{
		if(!pObject)
		{
			LOG(LogLevel::Error,
				_T("BaseScene::AddObject: Trying to add a nullptr object."));
			return;
		}
		pObject->SetName(name);
		AddObject(pObject);
	}

	void BaseScene::RemoveObject(Object * pObject)
	{
		auto it = std::find(m_pObjects.begin(), m_pObjects.end(), pObject);
		if(it != m_pObjects.end())
		{
			m_pGarbage.push_back(pObject);
		}
		else
		{
			LOG(LogLevel::Warning,
				_T("BaseScene::RemoveObject: \
				   Trying to remove an unknown object."), STARENGINE_LOG_TAG);
		}
	}
	
	void BaseScene::RemoveObject(const tstring & name)
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareName(name))
			{
				RemoveObject(pObject);
				return;
			}
		}
		LOG(LogLevel::Warning,
				_T("BaseScene::RemoveObject: \
				   Trying to remove an unknown object '")
				   + name + _T("'."), STARENGINE_LOG_TAG);
	}

	void BaseScene::AddGesture(BaseGesture* pGesture)
	{
		LOG(LogLevel::Warning, 
_T("Please use the method AddGesture(BaseGesture* gesture, \
const tstring & name) to add gestures. \
using BaseScene::AddGesture(BaseGesture* gesture) is much slower, use with care!"),
			STARENGINE_LOG_TAG);

		m_pGestureManager->AddGesture(pGesture, _T("Gesture_") + string_cast<tstring>(m_GestureID));
		++m_GestureID;
	}

	void BaseScene::AddGesture(BaseGesture* pGesture, const tstring & name)
	{
		m_pGestureManager->AddGesture(pGesture, name);
	}

	void BaseScene::RemoveGesture(BaseGesture* pGesture)
	{
		m_pGestureManager->RemoveGesture(pGesture);
	}

	void BaseScene::RemoveGesture(const tstring & name)
	{
		m_pGestureManager->RemoveGesture(name);
	}

	void BaseScene::SetObjectFrozen(const tstring & name, bool freeze)
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareName(name))
			{
				pObject->Freeze(freeze);
				return;
			}
		}
		LOG(LogLevel::Warning,
				_T("BaseScene::SetObjectFrozen: \
				   Trying to (un)freeze an unknown object '")
				   + name + _T("'."), STARENGINE_LOG_TAG);
	}

	void BaseScene::SetObjectDisabled(const tstring & name, bool disabled)
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareName(name))
			{
				pObject->SetDisabled(disabled);
				return;
			}
		}
		LOG(LogLevel::Warning,
				_T("BaseScene::SetObjectDisabled: \
				   Trying to enable/disable an unknown object '")
				   + name + _T("'."), STARENGINE_LOG_TAG);
	}

	void BaseScene::SetObjectVisible(const tstring & name, bool visible)
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareName(name))
			{
				pObject->SetVisible(visible);
				return;
			}
		}
		LOG(LogLevel::Warning,
				_T("BaseScene::SetObjectVisible: \
				   Trying to (un)hide an unknown object '")
				   + name + _T("'."), STARENGINE_LOG_TAG);
	}

	void BaseScene::SetGroupFrozen(const tstring & tag, bool visible)
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareGroupTag(tag))
			{
				pObject->Freeze(visible);
			}
		}
	}

	void BaseScene::SetGroupDisabled(const tstring & tag, bool visible)
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareGroupTag(tag))
			{
				pObject->SetDisabled(visible);
			}
		}
	}

	void BaseScene::SetGroupVisible(const tstring & tag, bool visible)
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareGroupTag(tag))
			{
				pObject->SetVisible(visible);
			}
		}
	}

	void BaseScene::GetGroup(const tstring & tag, std::vector<Object*> & group)
	{
		for(auto pObject : m_pObjects)
		{
			if(pObject->CompareGroupTag(tag))
			{
				group.push_back(pObject);
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
	
	bool BaseScene::IsObjectNameAlreadyInUse(const tstring & name) const
	{
		for(auto object : m_pObjects)
		{
			if(object->CompareName(name))
			{
				return true;
			}
		}
		return false;
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

	void BaseScene::SetCursor(UIBaseCursor * pCursor)
	{
		SafeDelete(m_pCursor);
		m_pCursor = pCursor;
		m_pCursor->BaseInitialize();
		SetSystemCursorHidden(true);
#ifdef MOBILE
		LOG(LogLevel::Warning,
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
		LOG(LogLevel::Warning,
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
		LOG(LogLevel::Warning,
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
		LOG(LogLevel::Warning,
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
		return m_pGestureManager;
	}

	std::shared_ptr<CollisionManager> BaseScene::GetCollisionManager() const
	{
		return m_pCollisionManager;
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
		for(auto pElement : m_pGarbage)
		{
			auto it = std::find(m_pObjects.begin(), m_pObjects.end(), pElement);
			ASSERT_LOG(it != m_pObjects.end(),
				_T("BaseScene::CollectGarbage: Trying to delete unknown object"),
				STARENGINE_LOG_TAG);
			(*it)->UnsetScene();
			m_pObjects.erase(it);
			delete pElement;
		}
		m_pGarbage.clear();
		
	}
}
