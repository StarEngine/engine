#pragma once

#include "../BaseComponent.h"
#include "../../defines.h"
#include "../../Graphics/Color.h"
#include <functional>

namespace star
{
	struct Context;
	class CircleColliderComponent;
	class RectangleColliderComponent;

	/// <summary>
	/// Base class for other collider components
	/// </summary>
	class BaseColliderComponent : public BaseComponent
	{

	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="BaseColliderComponent"/> class.
		/// Using collision layers is strongly advised, so use this default constructor with care.
		/// The collider will be added to the default collision group.
		/// </summary>
		BaseColliderComponent();

		/// <summary>
		/// Initializes a new instance of the <see cref="BaseColliderComponent"/> class.
		/// The collider will be added to the collision group you specify as argument.
		/// </summary>
		/// <param name="layer">The layer you want to add the component to.</param>
		BaseColliderComponent(const tstring & layer);
		/// <summary>
		/// Initializes a new instance of the <see cref="BaseColliderComponent"/> class.
		/// The collider will be added to the collision groups you specify as arguments.
		/// </summary>
		/// <param name="layers">An array of layers to add the component to.</param>
		/// <param name="n">The number of layers in the array.</param>
		BaseColliderComponent(
			const tstring* layers, 
			uint8 n);
		/// <summary>
		/// Finalizes an instance of the <see cref="BaseColliderComponent"/> class.
		/// </summary>
		virtual ~BaseColliderComponent();

		/// <summary>
		/// Updates this instance.
		/// </summary>
		/// <param name="context"><see cref="Context"/> containing usefull information.</param>
		void Update(const Context& context);
		
		/// <summary>
		/// Sets the callback that will be triggered 1 time for ever collision with another component.
		/// This callback will be triggered the moment this component collides with 
		/// Another component with parent of type <see cref="BaseColliderComponent"/>.
		/// </summary>
		/// <param name="onEnter">
		/// Function to be triggered. (Can be a function pointer, lambda expression, ..).
		/// This function has as argument a <see cref="BaseColliderComponent"/>. 
		/// This is the other component this component collided with.
		/// </param>
		void SetOnEnterCallback(
			std::function<void(BaseColliderComponent* collider)> onEnter);
		/// <summary>
		/// Sets the callback that will be triggered while this component collides with another component.
		/// This callback will be triggered while this component collides with 
		/// Another component with parent of type <see cref="BaseColliderComponent"/>.
		/// </summary>
		/// <param name="onStay">
		/// Function to be triggered. (Can be a function pointer, lambda expression, ..).
		/// This function has as argument a <see cref="BaseColliderComponent"/>. 
		/// This is the other component this component collided with.
		/// </param>
		void SetOnStayCallback(
			std::function<void(BaseColliderComponent* collider)> onStay);
		/// <summary>
		/// Sets the callback that will be triggered 1 time for ever collision with another component.
		/// This callback will be triggered the moment this component stops colliding with 
		/// Another component with parent of type <see cref="BaseColliderComponent"/>.
		/// </summary>
		/// <param name="onExit">
		/// Function to be triggered. (Can be a function pointer, lambda expression, ..).
		/// This function has as argument a <see cref="BaseColliderComponent"/>. 
		/// This is the other component this component collided with.
		/// </param>
		void SetOnExitCallback(
			std::function<void(BaseColliderComponent* collider)> onExit);

		/// <summary>
		/// Triggers the OnEnter callback.
		/// This function is used in the collision manager and should not be used by the user.
		/// </summary>
		/// <param name="other">The colliding component.</param>
		void TriggerOnEnter(BaseColliderComponent* other);
		/// <summary>
		/// Triggers the OnStay callback.
		/// This function is used in the collision manager and should not be used by the user.
		/// </summary>
		/// <param name="other">The colliding component.</param>
		void TriggerOnStay(BaseColliderComponent* other);
		/// <summary>
		/// Triggers the OnExit callback.
		/// </summary>
		/// <param name="other">The colliding component.</param>
		void TriggerOnExit(BaseColliderComponent* other);

		/// <summary>
		/// Sets this component as a trigger.
		/// If the component is a trigger, it means that the 
		/// callbacks will be triggered, but nothing will happen to the component and its object.
		/// Else, the component and its object would really collide and affect movement.
		/// </summary>
		/// <param name="isTrigger">True to set this as a trigger.</param>
		void SetAsTrigger(bool isTrigger);
		/// <summary>
		/// Check if this component is a trigger.
		/// If the component is a trigger, it means that the 
		/// callbacks will be triggered, but nothing will happen to the component and its object.
		/// Else, the component and its object would really collide and affect movement.
		/// </summary>
		/// <returns>True if this component is a trigger.</returns>
		bool IsTrigger() const;

		/// <summary>
		/// Marks this component as static.
		/// Static components will not be transformed.
		/// </summary>
		/// <param name="isStatic">True to set this as static.</param>
		void SetAsStatic(bool isStatic);
		/// <summary>
		/// Checks if this component is static.
		/// Static components will not be transformed.
		/// </summary>
		/// <returns>True if this component is static.</returns>
		bool IsStatic() const;

		/// <summary>
		/// Mark that this component has entered collision.
		/// This function is used in the collision manager and should not be used by the user.
		/// </summary>
		/// <param name="hasEntered">True if this component has entered collision.</param>
		void SetEntered(bool hasEntered);
		/// <summary>
		/// Gets if this component has entered collsion.
		/// This function is used in the collision manager and should not be used by the user.
		/// </summary>
		/// <returns>True if this component has entered collision.</returns>
		bool GetEntered() const;

		/// <summary>
		/// Mark that this component has left collision.
		/// This function is used in the collision manager and should not be used by the user.
		/// </summary>
		/// <param name="hasLeft">True if this component has left collision.</param>
		void SetExited(bool hasLeft);
		/// <summary>
		/// Gets if this component has left collsion.
		/// This function is used in the collision manager and should not be used by the user.
		/// </summary>
		/// <returns>True if this component has left collision.</returns>
		bool GetExited() const;

		/// <summary>
		/// Sets the color of the <see cref="DebugDraw"/> of this component.
		/// </summary>
		/// <param name="color">The color.</param>
		/// <seealso cref="Color"/>
		void SetDrawColor(const Color& color);
		/// <summary>
		/// Gets the color of the <see cref="DebugDraw"/> of this component.
		/// </summary>
		/// <returns>The color.</returns>
		/// <seealso cref="Color"/>
		const Color& GetDrawColor() const;

		/// <summary>
		/// Toggles debug drawing of this component.
		/// </summary>
		/// <param name="enable">True to enable debug drawing.</param>
		void EnableDrawing(bool enable);

		/// <summary>
		/// Gets all layers this component is in.
		/// </summary>
		/// <returns>returns the array and the number of layers</returns>
		/// <seealso cref="PointerArray"/>
		const PointerArray<tstring> & GetLayers() const;

		virtual bool CollidesWithPoint2D(const vec2 & point2D) const = 0;
		virtual bool CollidesWithLine2D(
			const vec2 & point2D1, 
			const vec2 & point2D2
			) const = 0;
		virtual bool CollidesWith(const BaseColliderComponent* other) const = 0;

	protected:
		virtual void InitializeColliderComponent() = 0;
		/// <summary>
		/// Draws this instance.
		/// </summary>
		virtual void Draw();

		bool m_bIsTrigger;
		bool m_bIsStatic;
		bool m_bCanDraw;
		Color m_DrawColor;

		/// <summary>
		/// Checks rectangle vs circle collision.
		/// This includes Axis Aligned Bounding Boxes (AABB)
		/// and Object Orientated Bounding Boxes (OOBB) rectangles.
		/// Collision checks are done with the Seperated Axis Theorem (SAT)
		/// </summary>
		/// <param name="rect">The <see cref="RectangleColliderComponent"/>.</param>
		/// <param name="circle">The <see cref="CircleColliderComponent"/>.</param>
		/// <returns>True when a collision happens.</returns>
		bool RectangleCircleCollision(
			const RectangleColliderComponent* rect, 
			const CircleColliderComponent* circle
			) const;
		/// <summary>
		/// Helper function to find the closest point on a vector to an
		/// Object Orientated Bounding Box (OOBB)
		/// </summary>
		/// <param name="vector">The vector.</param>
		/// <param name="oobb">The Object Orientated Bounding Box (OOBB).</param>
		/// <returns>The closest point to the Object Orientated Bounding Box (OOBB)</returns>
		vec2 FindClosestPointToOOBB(
			const vec2 & vector, 
			const RectangleColliderComponent* oobb
			) const;
		PointerArray<tstring> m_Layers;
		static const tstring DEFAULT_LAYER_NAME;

	private:
		bool m_bEntered;
		bool m_bExited;

		std::function<void(BaseColliderComponent* collider)> m_OnEnter;
		std::function<void(BaseColliderComponent* collider)> m_OnStay;
		std::function<void(BaseColliderComponent* collider)> m_OnExit;

		/// <summary>
		/// Initializes the component.
		/// </summary>
		void InitializeComponent();

		BaseColliderComponent(BaseColliderComponent&& t);
		BaseColliderComponent(const BaseColliderComponent& t);
		BaseColliderComponent& operator=(const BaseColliderComponent& t);
		BaseColliderComponent& operator=(BaseColliderComponent&& t);
	};
}
