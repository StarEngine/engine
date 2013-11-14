#pragma once

#include "../defines.h"
#include <map>

namespace star
{
	struct Context;
	class State;

	class StateManager final 
	{
	public:
		StateManager();
		~StateManager();

		void Initialize();
		void Update(const Context& context);
		void Draw();

		void AddState(const tstring & name, State * pState);
		bool RemoveState(const tstring & name);
		void Clear();

		void SetState(const tstring & name);
		void SetPreviousState();

		const tstring & GetCurrentStateName() const;
		State * GetCurrentState() const;

	private:
		void DeactiveCurrentState();

		std::map<uint32, State*> m_States;
		State * m_pCurrentState;
		tstring m_CurrentStateName,
				m_PreviousStateName;

		StateManager(const StateManager &);
		StateManager(StateManager&&);
		StateManager & operator=(const StateManager&);
		StateManager & operator=(StateManager&&);
	};
}
