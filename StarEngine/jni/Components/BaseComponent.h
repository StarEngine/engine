#pragma once

#include "..\defines.h"

namespace star
{
	struct Context;
	class BaseScene;
	class TransformComponent;
	class Object;

	class BaseComponent
	{
	public:
		BaseComponent(void);
		BaseComponent(Object* parent);
		virtual ~BaseComponent(void);

		void Initialize();
		virtual void Update(const Context& context) = 0;
		virtual void Draw() = 0;

		bool IsInitialized() const {return m_bInitialized;}

		Object* GetParent() const {return m_pParentObject;}
		void SetParent(Object* parent) {m_pParentObject = parent;}

		BaseScene* GetGameScene() const;

		TransformComponent* GetTransform() const;

	protected:
		virtual void InitializeComponent() = 0;

		Object* m_pParentObject;
		bool m_bInitialized;

	private:
		BaseComponent(const BaseComponent& t);
		BaseComponent(BaseComponent&& t);
		BaseComponent& operator=(const BaseComponent& t);
	};
}
