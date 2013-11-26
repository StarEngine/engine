#pragma once

#include "Action.h"
#include <functional>

namespace star
{
	class Object;

	class DelayedAction : public Action
	{
	public:
		DelayedAction(float32 seconds);
		DelayedAction(
			const tstring & name,
			float32 seconds
			);

		virtual ~DelayedAction();

		virtual void Initialize();

		virtual void Restart();
		virtual void Pause();
		virtual void Resume();

	protected:
		std::function<void()> m_Callback;

	private:
		void CreateTimer();

		static uint64 ID_COUNTER;
		tstring m_UniqueID;
		float32 m_Seconds;
		bool m_HasStarted;

		DelayedAction & operator=(const DelayedAction&);
		DelayedAction & operator=(DelayedAction&&);
		DelayedAction(const DelayedAction&);
		DelayedAction(DelayedAction&&);
	};
}
