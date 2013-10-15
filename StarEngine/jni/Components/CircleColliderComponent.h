#pragma once

#include "BaseComponent.h"
#include "..\defines.h"

namespace star
{
	struct Context;

	class CircleColliderComponent final : public BaseComponent
	{
	public:
		CircleColliderComponent(float radius);
		~CircleColliderComponent(void);

		void Update(const Context& context);
		void Draw();

		void SetAsTrigger(bool isTrigger);
		bool IsTrigger() const;
		float GetRadius() const;

	protected:
		void InitializeComponent();

		float m_Radius;
		bool m_bIsTrigger;

	private:
		CircleColliderComponent(CircleColliderComponent&& t);
		CircleColliderComponent(const CircleColliderComponent& t);
		CircleColliderComponent& operator=(const CircleColliderComponent& t);
	};
}
