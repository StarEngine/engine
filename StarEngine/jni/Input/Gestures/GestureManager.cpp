#include "GestureManager.h"
#include <algorithm>
#include "BaseGesture.h"
#include "../InputManager.h"

namespace star
{
	GestureManager::GestureManager() : 
		m_GestureVec()
	{

	}

	GestureManager::~GestureManager()
	{
		//[COMMENT] somehow there is a memory leak here?
		for(auto gesture : m_GestureVec)
		{
			delete gesture;
			gesture = nullptr;
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
		// Check if the gesture is not already in the vector
		if(std::find(m_GestureVec.begin(), m_GestureVec.end(), gesture) == m_GestureVec.end())
		{
			m_GestureVec.push_back(gesture);
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
