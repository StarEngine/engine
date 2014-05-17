#pragma once

#include "../defines.h"

namespace star
{
	template<typename ClassType>
	class Singleton
	{
	public:
		static ClassType * GetInstance();
		static void DeleteSingleton();

	protected:
		Singleton();
		virtual ~Singleton();

	private:
		static ClassType * m_pSingletonObject;
	};
}

#include "Singleton.inl"
