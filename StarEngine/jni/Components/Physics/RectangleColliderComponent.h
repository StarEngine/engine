#pragma once
#include "BaseColliderComponent.h"
#include "../../Helpers\Rect.h"

namespace star
{
	struct Context;
	class CircleColliderComponent;

	class RectangleColliderComponent final : public BaseColliderComponent
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="RectangleColliderComponent"/> class.
		/// If you use this constructor, make sure to
		/// a) Add a <see cref="SpriteComponent"/> or <see cref="SpriteSheetComponent"/>
		/// before you add this component, 
		/// the width and height of the visible part of the sprite will be used to 
		/// determine the size of the colliders.
		/// b) Use SetCollisionRectSize to define the size of the collider. 
		/// Using collision layers is strongly advised, so use this constructor with care.
		/// The collider will be added to the default collision group.
		/// </summary>
		RectangleColliderComponent();
		/// <summary>
		/// Initializes a new instance of the <see cref="RectangleColliderComponent"/> class.
		/// Using collision layers is strongly advised, so use this constructor with care.
		/// The collider will be added to the default collision group.
		/// </summary>
		/// <param name="size">The size of the collider.</param>
		RectangleColliderComponent(const vec2& size);
		/// <summary>
		/// Initializes a new instance of the <see cref="RectangleColliderComponent"/> class.
		/// Using collision layers is strongly advised, so use this constructor with care.
		/// The collider will be added to the default collision group.
		/// </summary>
		/// <param name="width">The width of the collider.</param>
		/// <param name="height">The width of the collider.</param>
		RectangleColliderComponent(
			float32 width, 
			float32 height);

		/// <summary>
		/// Initializes a new instance of the <see cref="RectangleColliderComponent"/> class.
		/// If you use this constructor, make sure to
		/// a) Add a <see cref="SpriteComponent"/> or <see cref="SpriteSheetComponent"/>
		/// before you add this component, 
		/// the width and height of the visible part of the sprite will be used to 
		/// determine the size of the colliders.
		/// b) Use SetCollisionRectSize to define the size of the collider.
		/// </summary>
		/// <param name="layers">An array of layers to add the component to.</param>
		/// <param name="n">The number of layers in the array.</param>
		RectangleColliderComponent(
			const tstring* layers, 
			uint8 n = 1);
		/// <summary>
		/// Initializes a new instance of the <see cref="RectangleColliderComponent"/> class.
		/// </summary>
		/// <param name="size">The size of the collider.</param>		
		/// <param name="layers">An array of layers to add the component to.</param>
		/// <param name="n">The number of layers in the array.</param>
		RectangleColliderComponent(
			const vec2& size, 
			const tstring* layers, 
			uint8 n = 1);
		/// <summary>
		/// Initializes a new instance of the <see cref="RectangleColliderComponent"/> class.
		/// </summary>
		/// <param name="width">The width of the collider.</param>
		/// <param name="height">The width of the collider.</param>		
		/// <param name="layers">An array of layers to add the component to.</param>
		/// <param name="n">The number of layers in the array.</param>
		RectangleColliderComponent(
			float32 width, 
			float32 height, 
			const tstring* layers, 
			uint8 n = 1);

		/// <summary>
		/// Finalizes an instance of the <see cref="RectangleColliderComponent"/> class.
		/// </summary>
		~RectangleColliderComponent();

		/// <summary>
		/// Determines if there is a collision between a provided point and this collider.
		/// </summary>
		/// <param name="point">The point to check the collision with.</param>
		/// <returns>True if there is a collision</returns>
		bool CollidesWithPoint(const vec2& point) const;

		/// <summary>
		/// Determines if there is a collision between a provided line and this collider.
		/// </summary>
		/// <param name="point1">First point of the line.</param>
		/// <param name="point2">Second point of the line.</param>
		/// <returns>True if there is a collision</returns>
		bool CollidesWithLine(
			const vec2& point1, 
			const vec2& point2
			) const;
		/// <summary>
		/// Determines if there is a collision between an other collider component and this collider.
		/// This function is internally used by the Collision Manager, 
		/// Using this function yourself is not advised.
		/// </summary>
		/// <param name="other">The other collider component.</param>
		/// <returns>True if there is a collision</returns>
		bool CollidesWith(const BaseColliderComponent* other) const;

		/// <summary>
		/// Gets the collision rectangle.
		/// </summary>
		/// <returns>The collision rectangle.</returns>
		Rect GetCollisionRect() const;
		/// <summary>
		/// Gets the center point of the collider.
		/// </summary>
		/// <returns>The center point</returns>
		vec2 GetCenterPoint() const;
		/// <summary>
		/// Gets the unit vector in the x direction, correctly orientated according to the rotation 
		/// of this collider.
		/// </summary>
		/// <returns>The Unit vector.</returns>
		vec2 GetOrientatedUnitVecX() const;
		/// <summary>
		/// Gets the unit vector in the y direction, correctly orientated according to the rotation 
		/// of this collider.
		/// </summary>
		/// <returns>The Unit vector.</returns>
		vec2 GetOrientatedUnitVecY() const;

		/// <summary>
		/// Gets the width of the collision rectangle.
		/// </summary>
		/// <returns>The width of the collisionn rectangle</returns>
		float32 GetCollisionRectWidth() const;
		/// <summary>
		/// Gets the height of the collision rectangle.
		/// </summary>
		/// <returns>The height of the collisionn rectangle</returns>
		float32 GetCollisionRectHeight() const;
		/// <summary>
		/// Gets the size of the colliison rectangle.
		/// </summary>
		/// <param name="outVec">The size of the collision rectangle.</param>
		void GetColliisonRectSize(vec2& outVec) const;

		/// <summary>
		/// Sets the size of the collision rectangle.
		/// </summary>
		/// <param name="width">The new width of the collision rectangle.</param>
		/// <param name="height">The new height of the collision rectangle.</param>
		void SetCollisionRectSize(
			float32 width, 
			float32 height);
		/// <summary>
		/// Sets the size of the collision rectangle.
		/// </summary>
		/// <param name="size">The new size of the collision rectangle.</param>
		void SetCollisionRectSize(const vec2& size);

	protected:
		/// <summary>
		/// Initializes the collider component.
		/// </summary>
		void InitializeColliderComponent();
		/// <summary>
		/// Draws this instance.
		/// </summary>
		void Draw();
		/// <summary>
		/// Collision check between 2 object orientated rectangles.
		/// </summary>
		/// <param name="rect1">The first rectangle.</param>
		/// <param name="rect2">The second rectangle.</param>
		/// <returns>True if a collision exists.</returns>
		bool OOBBRectangleRectangleCollision(
			const Rect& rect1, 
			const Rect& rect2
			) const;
		/// <summary>
		/// Collision check between 2 axis aligned rectangles.
		/// </summary>
		/// <param name="rect1">The first rectangle.</param>
		/// <param name="rect2">The second rectangle.</param>
		/// <returns>True if a collision exists.</returns>
		bool AABBRectangleRectangleCollision(
			const Rect& rect1, 
			const Rect& rect2
			) const;

		/// <summary>
		/// Test for the Seperating axis theorem. 
		/// Tests if 2 rectangles overlap over a certain axis.
		/// </summary>
		/// <param name="rect1">The first rectangle.</param>
		/// <param name="rect2">The second rectangle.</param>
		/// <param name="axis">The axis to check the overlap on.</param>
		/// <returns>True if an overlap occurs</returns>
		bool CalculateAxisSpecificCollision(
			const Rect& rect1, 
			const Rect& rect2, 
			const vec2& axis
			) const;
		/// <summary>
		/// Test for the Seperating axis theorem. 
		/// Tests if a rectangle and a line overlap over a certain axis.
		/// </summary>
		/// <param name="rect">The rectangle.</param>
		/// <param name="point1">The first point of the line.</param>
		/// <param name="point2">The second point of the line.</param>
		/// <param name="axis">The axis to check the overlap on.</param>
		/// <returns>True if an overlap occurs</returns>
		bool CalculateAxisSpecificCollision(
			const Rect& rect, 
			const vec2& point1, 
			const vec2& point2, 
			const vec2& axis
			) const;
		/// <summary>
		/// Test for the Seperating axis theorem. 
		/// Tests if a rectangle and a point overlap over a certain axis.
		/// </summary>
		/// <param name="rect1">The rectangle.</param>
		/// <param name="point1">The point.</param>
		/// <param name="axis">The axis to check the overlap on.</param>
		/// <returns>True if an overlap occurs</returns>
		bool CalculateAxisSpecificCollision(
			const Rect& rect1, 
			const vec2& point1, 
			const vec2& axis
			) const;

		Rect m_CollisionRect;

	private:
		vec2 m_CustomColliderSize;
		/// <summary>
		/// Creates the dimensions of the collider, based on the size of the visible part of the
		/// optionally provided <see cref="SpriteComponent"/> or <see cref="SpriteSheetComponent"/>,
		/// or on the size passed by the SetCollisionRectSize method.
		/// </summary>
		void CreateDimensions();

		/// <summary>
		/// Calculates the minimum of all elements in a given array.
		/// </summary>
		/// <param name="vec">The array.</param>
		/// <param name="size">The size of the array.</param>
		/// <returns></returns>
		float32 CalculateMinimum(
			const float32* vec, 
			uint8 size
			) const;
		/// <summary>
		/// Calculates the maximum of all elements in a given array.
		/// </summary>
		/// <param name="vec">The array.</param>
		/// <param name="size">The size of the array.</param>
		/// <returns></returns>
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
