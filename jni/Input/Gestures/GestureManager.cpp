#include "GestureManager.h"
#include <algorithm>
#include "BaseGesture.h"
#include "../InputManager.h"

namespace star
{
	GestureManager::GestureManager() : m_GestureVec()
	{

	}

	GestureManager::~GestureManager()
	{

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

	bool GestureManager::RemoveGesture(BaseGesture* gesture)
	{
		if(std::find(m_GestureVec.begin(), m_GestureVec.end(), gesture) == m_GestureVec.end())
		{
			return false;
		}
		else
		{
			m_GestureVec.erase(std::find(m_GestureVec.begin(), m_GestureVec.end(), gesture));
			delete gesture;
			return true;
		}
	}

	void GestureManager::Update(const Context& context)
	{
		for(auto gesture : m_GestureVec)
		{
			gesture->Update(context);
		}
	}
}
