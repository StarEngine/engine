#include "../defines.h"
#include "../Objects/Object.h"

namespace star
{
	template <typename T>
	T * BaseScene::GetObjectByName(const tstring & name)
	{
		for(auto object : m_Objects)
		{
			if(object->CompareName(name))
			{
				auto returnObject = dynamic_cast<T*>(object);
				if(returnObject == nullptr)
				{
					Logger::GetInstance()->Log(LogLevel::Error,
						_T("BaseScene::GetObjectByName: couldn't convert object '")
						+ name + _T("' to the requested type. Returning nullptr..."),
						STARENGINE_LOG_TAG);
				}
				return returnObject;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("BaseScene::GetObjectByName: Trying to get an unknown object '")
				+ name + _T("'."), STARENGINE_LOG_TAG);
		return nullptr;
	}
}
