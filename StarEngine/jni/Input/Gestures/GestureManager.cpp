#include "GestureManager.h"
#include <algorithm>
#include "BaseGesture.h"
#include "../InputManager.h"
#include "../../Logger.h"

namespace star
{
	GestureManager::GestureManager() : 
		m_GestureVec()
	{

	}

	GestureManager::~GestureManager()
	{
		//[COMMENT] somehow there is a memory leak here?
		//[NOTE] If you think this, check if the gestures all get deleted,
		// if yes check if everything within the gesture get's deleted, etc...
		for(auto gesture : m_GestureVec)
		{
			delete gesture;
		}
		m_GestureVec.clear();
	}

#ifdef _WIN32

	void GestureManager::OnUpdateWinInputState()
	{
		if(!m_GestureVec.empty())
		{
			for(auto gesture : m_GestureVec)
			{
				gesture->OnUpdateWinInputStateBase();
			}
		}
	}
#else
	void GestureManager::OnTouchEvent(AInputEvent* pEvent)
	{
		for(auto gesture : m_GestureVec)
		{
			gesture->OnTouchEventBase(pEvent);
		}
	}
#endif
	
	void GestureManager::AddGesture(BaseGesture* gesture)
	{
		if(std::find(m_GestureVec.begin(), m_GestureVec.end(), gesture) == m_GestureVec.end())
		{
			m_GestureVec.push_back(gesture);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,_T("The gesture manager already contains this gesture!"));
		}
	}

	void GestureManager::RemoveGesture(BaseGesture* gesture)
	{
		auto it = std::find(m_GestureVec.begin(), m_GestureVec.end(), gesture);
		ASSERT(it != m_GestureVec.end(),_T("Gesture not found!"));
		m_GestureVec.erase(it);
		delete gesture;
	}

	void GestureManager::Update(const Context& context)
	{
		for(auto gesture : m_GestureVec)
		{
			gesture->Update(context);
		}
	}
}
