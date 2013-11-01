#pragma once
#include "BaseColliderComponent.h"
#include "../../defines.h"
#include "../../Helpers\Rect.h"
#include <vector>

namespace star
{
	struct Context;

	class RectangleColliderComponent final : public BaseColliderComponent
	{
	public:
		RectangleColliderComponent(const vec2& leftTop, const vec2& rightTop,
			const vec2& leftBottom, const vec2& rightBottom);
		RectangleColliderComponent(const Rect& rect);
		RectangleColliderComponent(const vec2& leftTop, const vec2& rightTop,
			const vec2& leftBottom, const vec2& rightBottom, 
			const tstring* layers, uint8 n = 1);
		RectangleColliderComponent(const Rect& rect, const tstring* layers, uint8 n = 1);
		~RectangleColliderComponent();

		bool CollidesWithPoint(const pos& point) const;
		bool CollidesWithLine(const pos& point1, const pos& point2) const;
		void CollidesWith(const BaseColliderComponent* other) const;

		const Rect& GetCollisionRect() const;
		void SetCollisionRect(const Rect& rect);

	protected:
		void InitializeColliderComponent();
		bool RectangleRectangleCollision(const Rect& rect1, const Rect& rect2) const;
		bool CalculateAxisSpecificCollision(const Rect& rect1, const Rect& rect2, const vec2& axis) const;

		Rect m_CollisionRect;

	private:

		float CalculateMinimum(std::vector<float> vec) const;
		float CalculateMaximum(std::vector<float> vec) const;

		RectangleColliderComponent(const RectangleColliderComponent& t);
		RectangleColliderComponent(RectangleColliderComponent&& t);
		RectangleColliderComponent& operator=(const RectangleColliderComponent& t);
		RectangleColliderComponent& operator=(RectangleColliderComponent&& t);
	};
}
