#pragma once
#include "BaseColliderComponent.h"
#include "../../defines.h"
#include "../../Helpers\Rect.h"
#include <vector>

namespace star
{
	struct Context;
	class CircleColliderComponent;

	class RectangleColliderComponent final : public BaseColliderComponent
	{
	public:
		RectangleColliderComponent();
		RectangleColliderComponent(const vec2& size);
		RectangleColliderComponent(float width, float height);

		RectangleColliderComponent(const tstring* layers, uint8 n = 1);
		RectangleColliderComponent(const vec2& size, const tstring* layers, uint8 = 1);
		RectangleColliderComponent(float width, float height, const tstring* layers, uint8 = 1);

		~RectangleColliderComponent();

		bool CollidesWithPoint(const pos& point) const;
		bool CollidesWithLine(const pos& point1, const pos& point2) const;
		void CollidesWith(const BaseColliderComponent* other) const;

		Rect GetCollisionRect() const;

		float GetCollisionRectWidth() const;
		float GetCollisionRectHeight() const;
		vec2 GetColliisonRectSize() const;

		void SetCollisionRectSize(float width, float height);
		void SetCollisionRectSize(const vec2& size);

	protected:
		void InitializeColliderComponent();
		bool OOBBRectangleRectangleCollision(const Rect& rect1, const Rect& rect2) const;
		bool AABBRectangleRectangleCollision(const Rect& rect1, const Rect& rect2) const;
		bool CalculateAxisSpecificCollision(const Rect& rect1, const Rect& rect2, const vec2& axis) const;
		bool RectangleCircleCollision(const RectangleColliderComponent* collider1, const CircleColliderComponent* collider2) const;

		Rect m_CollisionRect;

	private:
		bool m_bDefaultInitialized;

		float CalculateMinimum(std::vector<float> vec) const;
		float CalculateMaximum(std::vector<float> vec) const;

		RectangleColliderComponent(const RectangleColliderComponent& t);
		RectangleColliderComponent(RectangleColliderComponent&& t);
		RectangleColliderComponent& operator=(const RectangleColliderComponent& t);
		RectangleColliderComponent& operator=(RectangleColliderComponent&& t);
	};
}
