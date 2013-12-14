#include <vector>
#include <typeinfo>
#include "../Entity.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Components/TransformComponent.h"
#include "../Helpers/HashTag.h"

namespace star
{
	template <typename T>
	T * Object::GetChildByName(const tstring & name)
	{
		for(auto child : m_pChildren)
		{
			if(child->CompareName(name))
			{
				auto returnobject = dynamic_cast<T*>(child);
				if(returnobject == nullptr)
				{
					Logger::GetInstance()->Log(LogLevel::Error,
						_T("Object::GetChildByName: couldn't convert object '")
						+ name + _T("' to the requested type. Returning nullptr..."),
						STARENGINE_LOG_TAG);
				}
				return returnobject;
			}
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Object::GetChildByName: \
Trying to get unknown child '")
				+ name + _T("'."), STARENGINE_LOG_TAG);
		return nullptr;
	}

	template <typename T>
	void Object::RemoveComponent()
	{
		const std::type_info& ti = typeid(T);
		for(auto component : m_pComponents)
		{
			if(component && typeid(*component) == ti)
			{
				m_pGarbageContainer.push_back(
					GarbageInfo(
						component,
						GarbageType::ComponentType
						)
					);
			}
		}	
	}

	template <typename T>
	T* Object::GetComponent(bool searchChildren) const
	{
		const std::type_info& ti = typeid(T);
		for(auto component : m_pComponents)
		{
			if(component && typeid(*component) == ti)
			{
				return dynamic_cast<T*>(component);
			}
		}

		if(searchChildren)
		{
			for(auto child : m_pChildren)
			{
				return (child->GetComponent<T>(searchChildren));
			}
		}
		return nullptr;
	}

	template <typename T>
	T* Object::GetChild() const
	{
		const std::type_info& ti = typeid(T);
		for(auto child : m_pChildren)
		{
			if(child && typeid(*child) == ti)
			{
				return (dynamic_cast<T*>(child));
			}
		}
		return nullptr;
	}

	template <typename T>
	T* Object::GetChild(const tstring & name) const
	{
		const std::type_info& ti = typeid(T);
		for(auto child : m_pChildren)
		{
			if(child && typeid(*child) == ti
				&& child->GetName() == name)
			{
				return dynamic_cast<T*>(child);
			}
		}
		return nullptr;
	}

	
	template <typename T>
	bool Object::HasComponent(BaseComponent * component) const
	{
		const std::type_info& ti = typeid(T);
		for(auto comp : m_pComponents)
		{
			if(comp != component &&
				typeid(*comp) == ti)
			{
				return true;
			}
		}
		return false;
	}
}
