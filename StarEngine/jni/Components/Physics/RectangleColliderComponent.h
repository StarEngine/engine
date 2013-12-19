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
		/// <summary>
		/// Initializes a new instance of the <see cref="RectangleColliderComponent"/> class.
		/// If you use this default constructor, make sure to
		/// a) Add a <see cref="SpriteComponent"/> or <see cref="SpriteSheetComponent"/>
		/// before you add this component, 
		/// the width and height of the visible part of the sprite will be used to determine the size of the colliders.
		/// </summary>
		RectangleColliderComponent();
		RectangleColliderComponent(const vec2& size);
		RectangleColliderComponent(
			float32 width, 
			float32 height);

		RectangleColliderComponent(
			const tstring* layers, 
			uint8 n = 1);
		RectangleColliderComponent(
			const vec2& size, 
			const tstring* layers, 
			uint8 = 1);
		RectangleColliderComponent(
			float32 width, 
			float32 height, 
			const tstring* layers, 
			uint8 = 1);

		~RectangleColliderComponent();

		bool CollidesWithPoint(const vec2& point) const;
		bool CollidesWithLine(
			const vec2& point1, 
			const vec2& point2
			) const;
		bool CollidesWith(const BaseColliderComponent* other) const;

		Rect GetCollisionRect() const;
		vec2 GetCenterPoint() const;
		vec2 GetOrientatedUnitVecX() const;
		vec2 GetOrientatedUnitVecY() const;

		float32 GetCollisionRectWidth() const;
		float32 GetCollisionRectHeight() const;
		void GetColliisonRectSize(vec2& outVec) const;

		void SetCollisionRectSize(
			float32 width, 
			float32 height);
		void SetCollisionRectSize(const vec2& size);

	protected:
		void InitializeColliderComponent();
		void Draw();
		bool OOBBRectangleRectangleCollision(
			const Rect& rect1, 
			const Rect& rect2
			) const;
		bool AABBRectangleRectangleCollision(
			const Rect& rect1, 
			const Rect& rect2
			) const;

		bool CalculateAxisSpecificCollision(
			const Rect& rect1, 
			const Rect& rect2, 
			const vec2& axis
			) const;
		bool CalculateAxisSpecificCollision(
			const Rect& rect, 
			const vec2& point1, 
			const vec2& point2, 
			const vec2& axis
			) const;
		bool CalculateAxisSpecificCollision(
			const Rect& rect1, 
			const vec2& point1, 
			const vec2& axis
			) const;

		Rect m_CollisionRect;

	private:
		vec2 m_CustomColliderSize;
		void CreateDimensions();

		float32 CalculateMinimum(
			const float32* vec, 
			uint8 size
			) const;
		float32 CalculateMaximum(
			const float32* vec,
			uint8 size
			) const;

		RectangleColliderComponent(const RectangleColliderComponent& t);
		RectangleColliderComponent(RectangleColliderComponent&& t);
		RectangleColliderComponent& operator=(const RectangleColliderComponent& t);
		RectangleColliderComponent& operator=(RectangleColliderComponent&& t);
	};
}
