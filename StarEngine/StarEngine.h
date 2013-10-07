#pragma once

#include "defines.h"

namespace star
{
	struct Context;

	class StarEngine final
	{
	public:
		~StarEngine();

		static StarEngine * GetInstance();

		status Initialize(int32 window_width, int32 window_height);

		status Update(const Context & context);
		status Draw();

		status End();

	private:
		static StarEngine * m_pEngine;

		StarEngine();

		StarEngine(const StarEngine &);
		StarEngine(StarEngine &&);
		StarEngine & operator=(const StarEngine &);
	};
}
