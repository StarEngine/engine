#include "FPS.h"
#include "../Context.h"
#include "Time.h"

namespace star
{
	FPS::FPS()
		: CurrentFPS(0)
		, PreviousFPS(0)
		, m_Timer(0)
		, m_Counter(0)
	{
	}

	void FPS::Update(const Context & context)
	{
		++m_Counter;
		m_Timer += context.time->DeltaTime().GetSeconds();
		if(m_Timer > 1.0)
		{
			m_Timer -= 1.0;
			PreviousFPS = CurrentFPS;
			CurrentFPS = m_Counter;
			m_Counter = 0;
		}
	}
}