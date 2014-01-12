#pragma once

#include "../defines.h"

namespace star
{
	template<typename ClassType>
	class Singleton
	{
	public:
		static ClassType * GetInstance();

	protected:
		Singleton();
		virtual ~Singleton();

	private:
		static ClassType * m_pSingletonObject;
	};
}

#include "Singleton.inl"
