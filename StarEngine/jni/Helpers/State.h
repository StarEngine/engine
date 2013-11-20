#pragma once

#include "..\defines.h"

namespace star
{
	struct Context;

	class State
	{
	public:
		virtual ~State();

		virtual void Initialize(void) = 0;
		virtual void Update(const Context& context) = 0;
		virtual void Draw();

		virtual void Activate();
		virtual void Deactivate();

		bool IsActive() const;

	protected:
		State();

		bool m_Active;

	private:
		State(const State& yRef);
		State(State&& yRef);
		State& operator=(const State& yRef);
		State& operator=(State&& yRef);
	};
}
