#pragma once

#include "TimedAction.h"
#include "../Graphics/Color.h"

namespace star
{
	class SpriteComponent;

	class TimedFadeAction : public TimedAction
	{
	public:
		TimedFadeAction(
			float32 seconds,
			const Color & begin,
			const Color & end,
			const std::function<void()> & callback = nullptr
			);

		TimedFadeAction(
			const tstring & name,
			float32 seconds,
			const Color & begin,
			const Color & end,
			const std::function<void()> & callback = nullptr
			);

		virtual ~TimedFadeAction();

		virtual void Restart();

	protected:
		virtual void Initialize();
		virtual void Update(const Context & context);

		Color m_StartColor, m_EndColor;
		float32 m_CurrentSeconds;
		SpriteComponent * m_pSpriteComponent;

	private:
		TimedFadeAction & operator=(const TimedFadeAction&);
		TimedFadeAction & operator=(TimedFadeAction&&);
		TimedFadeAction(const TimedFadeAction&);
		TimedFadeAction(TimedFadeAction&&);
	};
}
