#pragma once

#include "..\defines.h"

namespace star
{
	struct Context;

	class State
	{
	public:
		virtual ~State() {}

		virtual void Initialize(void) = 0;
		virtual void Update(const Context& context) = 0;
		virtual void Draw() = 0;

		virtual void Activate() { m_Active = true; }
		virtual void Deactivate() { m_Active = false; }

		bool IsActive() const { return m_Active; }

	protected:
		State() : m_Active(false) {}
		bool m_Active;

	private:
		State(const State& yRef);
		State& operator=(const State& yRef);
	};
}
