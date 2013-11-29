#pragma once

#include "Action.h"
#include <functional>

namespace star
{
	class TimedAction : public Action
	{
	public:
		TimedAction(
			float32 seconds,
			const std::function<void()> & callback = nullptr
			);
		TimedAction(
			const tstring & name,
			float32 seconds,
			 const std::function<void()> & callback = nullptr
			);

		virtual ~TimedAction();

		virtual void Initialize();

		virtual void Restart();
		virtual void Pause();
		virtual void Resume();
		
		void SetCallback(const std::function<void()> & callback);

	protected:
		std::function<void()> m_Callback;
		float32 m_Seconds;

	private:
		static uint64 ID_COUNTER;
		tstring m_UniqueID;

		TimedAction & operator=(const TimedAction&);
		TimedAction & operator=(TimedAction&&);
		TimedAction(const TimedAction&);
		TimedAction(TimedAction&&);
	};
}
