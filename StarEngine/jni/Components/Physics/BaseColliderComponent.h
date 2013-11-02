#pragma once

#include "../BaseComponent.h"
#include "../../defines.h"

namespace star
{
	struct Context;

	class BaseColliderComponent : public BaseComponent
	{
	public:
		BaseColliderComponent();
		BaseColliderComponent(const tstring* layers, uint8 n = 1);
		virtual ~BaseColliderComponent();

		void Update(const Context& context);
		void Draw();

		void SetAsTrigger(bool isTrigger);
		bool IsTrigger() const;

		void SetAsStatic(bool isStatic);
		bool IsStatic() const;

		virtual bool CollidesWithPoint(const pos& point) const = 0;
		virtual bool CollidesWithLine(const pos& point1, const pos& point2) const = 0;
		virtual void CollidesWith(const BaseColliderComponent* other) const = 0;

	protected:
		virtual void InitializeColliderComponent() = 0;

		bool m_bIsTrigger;
		bool m_bIsStatic;

	private:

		void InitializeComponent();

		BaseColliderComponent(BaseColliderComponent&& t);
		BaseColliderComponent(const BaseColliderComponent& t);
		BaseColliderComponent& operator=(const BaseColliderComponent& t);
		BaseColliderComponent& operator=(BaseColliderComponent&& t);
	};
}
