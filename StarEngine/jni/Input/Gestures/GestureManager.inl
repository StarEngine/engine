#include "GestureManager.h"
#include "../../Logger.h"

namespace star
{
	template <typename T>
	T * GestureManager::GetGesture(const tstring & name) const
	{
		auto it = m_GestureMap.find(name);
		
		ASSERT_LOG(it != m_GestureMap.end(),
			_T("GestureManager::GetGesture(const tstring& tag): Gesture \"") + 
			name +
			tstring(_T("\" not found!")),
			STARENGINE_LOG_TAG
			);

		auto returnObject = dynamic_cast<T*>((*it).second);
		if(returnObject == nullptr)
		{
			LOG(LogLevel::Error,
				_T("BaseScene::GetGestureByName: couldn't convert object '")
				+ name + _T("' to the requested type. Returning nullptr..."),
				STARENGINE_LOG_TAG);
		}
		return returnObject;
	}
}