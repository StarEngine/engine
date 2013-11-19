#pragma once

#include "../defines.h"

namespace star
{
	struct Context;

	struct FPS
	{
		int32 CurrentFPS, PreviousFPS;

		FPS();

		void Update(const Context & context);

	private:
		float64 m_Timer;
		int32 m_Counter;
	};
}