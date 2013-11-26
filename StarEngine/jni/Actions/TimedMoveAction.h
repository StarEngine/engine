#pragma once

#include "TimedAction.h"

namespace star
{
	class TimedMoveAction : public TimedAction
	{
	public:
		TimedMoveAction(
			float32 seconds,
			const vec2 & target
			);

		TimedMoveAction(
			const tstring & name,
			float32 seconds,
			const vec2 & target
			);

		TimedMoveAction(
			float32 seconds,
			const vec2 & direction,
			float32 speed
			);

		TimedMoveAction(
			const tstring & name,
			float32 seconds,
			const vec2 & direction,
			float32 speed
			);

		virtual ~TimedMoveAction();

		virtual void Initialize();
		virtual void Update(const Context & context);

		void SetStartPosition(const vec2 & pos);

		virtual void Restart();

	protected:
		vec2 m_Direction, m_Target, m_StartPosition;
		float32 m_Speed, m_CurrentSeconds;

	private:
		bool m_StartPosSet;

		TimedMoveAction & operator=(const TimedMoveAction&);
		TimedMoveAction & operator=(TimedMoveAction&&);
		TimedMoveAction(const TimedMoveAction&);
		TimedMoveAction(TimedMoveAction&&);
	};
}
