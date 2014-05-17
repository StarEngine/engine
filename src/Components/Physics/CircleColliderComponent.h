#pragma once

#include "BaseColliderComponent.h"
#include "../../defines.h"

namespace star
{
	struct Context;

	/// <summary>
	/// Circular collider component.
	/// </summary>
	class CircleColliderComponent final : public BaseColliderComponent
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// If you use this constructor, make sure to
		/// a) Add a <see cref="SpriteComponent"/> or <see cref="SpriteSheetComponent"/>
		/// before you add this component, 
		/// the width and height of the visible part of the sprite will be used to 
		/// determine the radius of the colliders.
		/// b) Use SetRadius to define a radius. 
		/// Using collision layers is strongly advised, so use this constructor with care.
		/// The collider will be added to the default collision group.
		/// </summary>
		CircleColliderComponent();
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// If you use this constructor, make sure to
		/// a) Add a <see cref="SpriteComponent"/> or <see cref="SpriteSheetComponent"/>
		/// before you add this component, 
		/// the width and height of the visible part of the sprite will be used to 
		/// determine the radius of the colliders.
		/// b) Use SetRadius to define a radius. 
		/// </summary>
		/// <param name="layer">The name of the layer to add the component to.</param>
		CircleColliderComponent(const tstring & layer);
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// If you use this constructor, make sure to
		/// a) Add a <see cref="SpriteComponent"/> or <see cref="SpriteSheetComponent"/>
		/// before you add this component, 
		/// the width and height of the visible part of the sprite will be used to 
		/// determine the radius of the colliders.
		/// b) Use SetRadius to define a radius. 
		/// </summary>
		/// <param name="layers">An array of layers to add the component to.</param>
		/// <param name="n">The number of layers in the array.</param>
		CircleColliderComponent(
			const tstring* layers, 
			uint8 n
			);
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// Using collision layers is strongly advised, so use this constructor with care.
		/// The collider will be added to the default collision group.
		/// </summary>
		/// <param name="radius">The radius of the collider.</param>
		CircleColliderComponent(float32 radius);
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// </summary>
		/// <param name="radius">The radius of the collider.</param>
		/// <param name="layer">The name of the layer to add the component to.</param>
		CircleColliderComponent(
			float32 radius, 
			const tstring & layer
			);
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// </summary>
		/// <param name="radius">The radius of the collider.</param>
		/// <param name="layers">An array of layers to add the component to.</param>
		/// <param name="n">The number of layers in the array.</param>
		CircleColliderComponent(
			float32 radius, 
			const tstring* layers, 
			uint8 n
			);
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// Using collision layers is strongly advised, so use this constructor with care.
		/// The collider will be added to the default collision group.
		/// </summary>
		/// <param name="radius">The radius of the collider.</param>
		/// <param name="offset">The position of the center of the collider, starting from the left bottom.</param>
		CircleColliderComponent(
			float32 radius, 
			const vec2 & offset
			);
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// </summary>
		/// <param name="radius">The radius of the collider.</param>
		/// <param name="offset">The position of the center of the collider, starting from the left bottom.</param>
		/// <param name="layer">The name of the layer to add the component to.</param>
		CircleColliderComponent(
			float32 radius, 
			const vec2 & offset, 
			const tstring & layer
			);
		/// <summary>
		/// Initializes a new instance of the <see cref="CircleColliderComponent"/> class.
		/// </summary>
		/// <param name="radius">The radius of the collider.</param>
		/// <param name="offset">The position of the center of the collider, starting from the left bottom.</param>
		/// <param name="layers">An array of layers to add the component to.</param>
		/// <param name="n">The number of layers in the array.</param>
		CircleColliderComponent(
			float32 radius, 
			const vec2 & offset, 
			const tstring* layers, 
			uint8 n
			);
		/// <summary>
		/// Finalizes an instance of the <see cref="CircleColliderComponent"/> class.
		/// </summary>
		~CircleColliderComponent();

		/// <summary>
		/// Determines if there is a collision between a provided 2 dimensional point and this collider.
		/// </summary>
		/// <param name="point2D">The 2 dimensional point to check the collision with.</param>
		/// <returns>True if there is a collision</returns>
		bool CollidesWithPoint2D(const vec2& point2D) const;
		/// <summary>
		/// Determines if there is a collision between a provided 2 dimensional line and this collider.
		/// </summary>
		/// <param name="point2D1">First point of the 2 dimensional line.</param>
		/// <param name="point2D2">Second point of the 2 dimensional line.</param>
		/// <returns>True if there is a collision</returns>
		bool CollidesWithLine2D(
			const vec2& point2D1, 
			const vec2& point2D2
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
		/// Sets the radius of the circle collider.
		/// </summary>
		/// <param name="radius">The radius of the circle collider.</param>
		void SetRadius(float32 radius);
		/// <summary>
		/// Gets the radius.
		/// </summary>
		/// <returns>The radius.</returns>
		float32 GetRadius() const;
		/// <summary>
		/// Gets the real radius. This means this method returs the radius, adjusted to the scale system. 
		/// This function is internally used, Using this function yourself is not advised.
		/// </summary>
		/// <returns>The real radius.</returns>
		float32 GetRealRadius() const;

		/// <summary>
		/// Returns the center position of the circle collider.
		/// </summary>
		/// <returns>The center position of the circle collider.</returns>
		vec2 GetPosition() const;
		/// <summary>
		/// Returns the center position of the circle collider.
		/// </summary>
		/// <param name="posOut">The center position of the circle collider.</param>
		void GetPosition(vec2& posOut) const;

		/// <summary>
		/// Define the amount of segments used to draw this component with the <see cref="DebugDraw"/>.
		/// </summary>
		/// <param name="segments">The amount of segments.</param>
		void SetDrawSegments(uint32 segments);
		/// <summary>
		/// Gets the amount of segments used to draw this component with the <see cref="DebugDraw"/>.
		/// </summary>
		/// <returns>The amount of segments.</returns>
		uint32 GetDrawSegments() const;

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
		/// Collision check to check if 2 <see cref="CircleColliderComponent"/>s collide with eachother.
		/// </summary>
		/// <param name="collider1">The first collider.</param>
		/// <param name="collider2">The second collider.</param>
		/// <returns></returns>
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
