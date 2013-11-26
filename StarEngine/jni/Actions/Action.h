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

		virtual ~Action();

		void Destroy();

		virtual void Restart();
		virtual void Pause();
		virtual void Resume();

		void BaseUpdate(const Context & context);
		void BaseInitialize();

		void SetParent(Object * parent);
		Object * GetParent() const;

	protected:
		virtual void Initialize() = 0;
		virtual void Update(const Context & context) = 0;

		Object *m_pParent;
		bool m_IsPaused;
		bool m_IsInitialized;

	private:
		Action & operator=(const Action&);
		Action & operator=(Action&&);
		Action(const Action&);
		Action(Action&&);
	};
}
