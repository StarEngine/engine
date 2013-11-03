#pragma once

#include "BaseColliderComponent.h"
#include "../../defines.h"

namespace star
{
	struct Context;

	class CircleColliderComponent final : public BaseColliderComponent
	{
	public:
		CircleColliderComponent(float radius);
		CircleColliderComponent(float radius, const tstring* layers, uint8 n = 1);
		~CircleColliderComponent(void);

		bool CollidesWithPoint(const vec2& point) const;
		bool CollidesWithLine(const vec2& point1, const vec2& point2) const;
		void CollidesWith(const BaseColliderComponent* other) const;

		float GetRadius() const;
		void SetRadius(float radius);
		float GetRealRadius() const;

	protected:
		void InitializeColliderComponent();
		bool CircleCircleCollision(const CircleColliderComponent* collider1, 
		const CircleColliderComponent* collider2) const;

		float m_Radius;

	private:
		CircleColliderComponent(CircleColliderComponent&& t);
		CircleColliderComponent(const CircleColliderComponent& t);
		CircleColliderComponent& operator=(const CircleColliderComponent& t);
		CircleColliderComponent& operator=(CircleColliderComponent&& t);
	};
}
