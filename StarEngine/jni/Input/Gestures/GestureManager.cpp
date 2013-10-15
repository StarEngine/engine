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
		//[NOTE] If you think this, check if the gestures all get deleted,
		// if yes check if everything within the gesture get's deleted, etc...
		for(auto gesture : m_GestureVec)
		{
			delete gesture;
			// [ COMMENT] assigning to nullptr is useless,
			// you only do such a thing if you gonna use the pointer variable
			// again, which is not the case in this situation.
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
		// [COMMENT] you might log this information as a warning,
		// this can help programmers to find code that shouldnt be in their game.
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
