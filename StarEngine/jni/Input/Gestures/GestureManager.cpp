#include "GestureManager.h"
#include <algorithm>
#include "BaseGesture.h"
#include "../InputManager.h"
#include "../../Logger.h"

namespace star
{
	GestureManager::GestureManager()
		: m_GestureMap()
	{

	}

	GestureManager::~GestureManager()
	{
		m_GestureMap.clear();
	}

#ifdef _WIN32

	void GestureManager::OnUpdateWinInputState()
	{
		if(!m_GestureMap.empty())
		{
			for(auto gesture : m_GestureMap)
			{
				gesture.second->OnUpdateWinInputStateBase();
			}
		}
	}
#else
	void GestureManager::OnTouchEvent(AInputEvent* pEvent)
	{
		if(!m_GestureMap.empty())
		{
			for(auto gesture : m_GestureMap)
			{
				gesture.second->OnTouchEventBase(pEvent);
			}
		}
	}
#endif
	
	void GestureManager::AddGesture(BaseGesture* gesture, const tstring& tag)
	{
		if(!gesture)
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("GestureManager::AddGesture: Trying to add a nullptr gesture."));
			return;
		}
		if(m_GestureMap.find(tag) == m_GestureMap.end())
		{
			m_GestureMap.insert(std::make_pair(tag,std::shared_ptr<BaseGesture>(gesture)));
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning, 
				_T("The gesture manager already contains ") + tag,
				STARENGINE_LOG_TAG);
		}
	}


	void GestureManager::RemoveGesture(BaseGesture* gesture)
	{
		Logger::GetInstance()->Log(LogLevel::Warning, 
_T("Please use the method RemoveGesture(const tstring& tag) to remove gestures.\
tusing GestureManager::RemoveGesture(BaseGesture* gesture) is much slower, use with care!"),
			STARENGINE_LOG_TAG);

		auto it = m_GestureMap.begin();
		for (it ; it != m_GestureMap.end(); ++it )
		{
			if (it->second == std::shared_ptr<BaseGesture>(gesture))
			{
				return;
			}
		}
		Logger::GetInstance()->Log(it != m_GestureMap.end(),
			_T("Gesture not found!"), STARENGINE_LOG_TAG);
		m_GestureMap.erase(it);
	}

	void GestureManager::RemoveGesture(const tstring& tag)
	{
		auto it = m_GestureMap.find(tag);
		bool can_delete = it != m_GestureMap.end();
		Logger::GetInstance()->Log(can_delete,
			_T("Gesture not found!"), STARENGINE_LOG_TAG);
		if(can_delete)
		{
			m_GestureMap.erase(it);
		}
	}

	void GestureManager::Update(const Context& context)
	{
		if(!m_GestureMap.empty())
		{
			for(auto gesture : m_GestureMap)
			{
				gesture.second->Update(context);
			}
		}
	}

	void GestureManager::EndUpdate()
	{
		if(!m_GestureMap.empty())
		{
			for(auto gesture : m_GestureMap)
			{
				gesture.second->EndUpdate();
			}
		}
	}
}
