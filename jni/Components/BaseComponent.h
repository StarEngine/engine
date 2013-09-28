#pragma once

#include "..\defines.h"

namespace star
{
	struct Context;
	class Object;

	class BaseComponent
	{
	public:
		BaseComponent(void);
		virtual ~BaseComponent(void);

		virtual void Initialize();
		virtual void Update(const Context& context) = 0;
		virtual void Draw() = 0;

		bool IsInitialized() const {return m_bInitialized;}

		Object* GetParent() const {return m_pParentObject;}
		void SetParent(Object* parent) {m_pParentObject = parent;}

	protected:
		virtual void InitializeComponent() = 0;

		Object* m_pParentObject;
		bool m_bInitialized;

	private:
		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		BaseComponent(const BaseComponent& t);
		BaseComponent(BaseComponent&& t);
		BaseComponent& operator=(const BaseComponent& t);
	};
}
