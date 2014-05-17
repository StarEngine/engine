#include "../defines.h"

namespace star
{
	template<typename ClassType>
	ClassType * Singleton<ClassType>::m_pSingletonObject = nullptr;

	template<typename ClassType>
	ClassType * Singleton<ClassType>::GetInstance()
	{
		if(m_pSingletonObject == nullptr)
		{
			m_pSingletonObject = new ClassType();
		}
		return m_pSingletonObject;
	}
	
	template<typename ClassType>
	void Singleton<ClassType>::DeleteSingleton()
	{
		delete m_pSingletonObject;
		m_pSingletonObject = nullptr;
	}

	template<typename ClassType>
	Singleton<ClassType>::Singleton() {}

	template<typename ClassType>
	Singleton<ClassType>::~Singleton() {}
}