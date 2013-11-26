#pragma once

#include "../Entity.h"

namespace star
{
	class Object;

	class Action : public Entity
	{
	public:
		Action();
		Action(const tstring & name);

		~Action();

		void Destroy();

		virtual void Restart();
		virtual void Pause();
		virtual void Resume();

		void BaseUpdate(const Context & context);

		void SetParent(Object * parent);
		Object * GetParent() const;

	protected:
		virtual void Update(const Context & context) = 0;

		Object *m_pParent;
		bool m_IsPaused;

	private:
		Action & operator=(const Action&);
		Action & operator=(Action&&);
		Action(const Action&);
		Action(Action&&);
	};
}
