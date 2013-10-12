#pragma once

#include "../defines.h"

namespace star
{
	struct Context;

	struct FPS
	{
		int CurrentFPS, PreviousFPS;

		FPS();

		void Update(const Context & context);

	private:
		double m_Timer;
		int m_Counter;
	};
}