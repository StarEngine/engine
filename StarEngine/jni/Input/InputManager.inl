#include "InputManager.h"

namespace star
{
	template <typename T>
	T * InputManager::GetGlobalGesture(const tstring & name) const
	{
		return m_IndependantGestureManager->GetGesture<T>(name);
	}
}
