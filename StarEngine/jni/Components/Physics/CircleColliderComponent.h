#pragma once

#include "BaseColliderComponent.h"
#include "../../defines.h"

namespace star
{
	struct Context;

	class CircleColliderComponent final : public BaseColliderComponent
	{
	public:
		CircleColliderComponent();
		CircleColliderComponent(
			const tstring* layers, 
			uint8 n = 1);
		CircleColliderComponent(float32 radius);
		CircleColliderComponent(
			float32 radius, 
			const tstring* layers, 
			uint8 n = 1);
		CircleColliderComponent(
			float32 radius, 
			const vec2& offset);
		CircleColliderComponent(
			float32 radius, 
			const vec2& offset, 
			const tstring* layers, 
			uint8 n = 1);
		~CircleColliderComponent();

		bool CollidesWithPoint(const vec2& point) const;
		bool CollidesWithLine(
			const vec2& point1, 
			const vec2& point2
			) const;
		bool CollidesWith(const BaseColliderComponent* other) const;

		void SetRadius(float32 radius);
		float32 GetRadius() const;
		float32 GetRealRadius() const;

		vec2 GetPosition() const;
		void GetPosition(vec2& posOut) const;

		void SetDrawSegments(uint32 segments);
		uint32 GetDrawSegments() const;

	protected:
		void InitializeColliderComponent();
		void Draw();
		bool CircleCircleCollision(
			const CircleColliderComponent* collider1, 
			const CircleColliderComponent* collider2
			) const;

		float32 m_Radius;
		vec2 m_Offset;
		bool m_bDefaultInitialized;
		uint32 m_DrawSegments;

	private:
		CircleColliderComponent(CircleColliderComponent&& t);
		CircleColliderComponent(const CircleColliderComponent& t);
		CircleColliderComponent& operator=(const CircleColliderComponent& t);
		CircleColliderComponent& operator=(CircleColliderComponent&& t);
	};
}
