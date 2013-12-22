#pragma once

#include "../Entity.h"

namespace star
{
	struct Context;
	class BaseScene;
	class TransformComponent;
	class Object;

	/// <summary>
	/// Base class for all other components. 
	/// Manages all general functionality and intergration with <see cref="Object"/>s.
	/// </summary>
	class BaseComponent : public Entity
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="BaseComponent"/> class.
		/// </summary>
		BaseComponent();
		/// <summary>
		/// Initializes a new instance of the <see cref="BaseComponent"/> class.
		/// This constructor takes the <see cref="Object"/> this component is added to.
		/// </summary>
		/// <param name="parent">The parent <see cref="Object"/>.</param>
		BaseComponent(Object* parent);
		/// <summary>
		/// Finalizes an instance of the <see cref="BaseComponent"/> class.
		/// </summary>
		virtual ~BaseComponent();

		/// <summary>
		/// Destroys this component, removing it from the parent object.
		/// </summary>
		void Destroy();

		/// <summary>
		/// Initializes this instance.
		/// </summary>
		void Initialize();
		/// <summary>
		/// Performs the engine related Update.
		/// This method is used internally and should not be used by the user.
		/// </summary>
		/// <param name="context"><see cref="Context"/> containing usefull information.</param>
		void BaseUpdate(const Context& context);
		/// <summary>
		/// Performs the engine related Draw.
		/// This method is used internally and should not be used by the user.
		/// </summary>
		void BaseDraw();

		virtual void Update(const Context& context) = 0;
		virtual void Draw() = 0;

		/// <summary>
		/// Determines whether this instance is initialized.
		/// </summary>
		/// <returns>True if it is initialized</returns>
		bool IsInitialized() const;

		/// <summary>
		/// Gets the parent <see cref="Object"/>.
		/// </summary>
		/// <returns>The parent <see cref="Object"/></returns>
		Object* GetParent() const;
		/// <summary>
		/// Sets the parent <see cref="Object"/>.
		/// </summary>
		/// <param name="parent">The parent <see cref="Object"/>.</param>
		void SetParent(Object* parent);

		/// <summary>
		/// Gets the scene this object and all its components belong to.
		/// </summary>
		/// <returns>The scene this component belongs to.</returns>
		/// <seealso cref="BaseScene"/>
		BaseScene* GetGameScene() const;
		/// <summary>
		/// Gets the transform component.
		/// Every <see cref="Object"/>< is guaranteed to have a <see cref="TransformComponent"/>
		/// </summary>
		/// <returns>The <see cref="TransformComponent"/> of the parent <see cref="Object"/></returns>
		TransformComponent* GetTransform() const;

		/// <summary>
		/// Culling check. The component will not be drawn if it is out of screen.
		/// </summary>
		/// <param name="left">Left of the screen</param>
		/// <param name="right">Right of the screen</param>
		/// <param name="top">Top of the screen</param>
		/// <param name="bottom">Bottom of the screen</param>
		/// <returns>true if the component should be culled</returns>
		virtual bool CheckCulling(
			float left,
			float right,
			float top,
			float bottom
			) const;

		/// <summary>
		/// Sets the component enabled or disabled.
		/// If a component is disabled, it will not draw nor update.
		/// </summary>
		/// <param name="bEnabled">True to enable.</param>
		void SetEnabled(bool bEnabled);
		/// <summary>
		/// Checks if the component is enabled or disabled.
		/// If a component is disabled, it will not draw nor update.
		/// </summary>
		/// <returns>True if the component is enabled</returns>
		bool IsEnabled() const;

		/// <summary>
		/// Sets the component visible or invisible.
		/// If a component is invisible, it will not draw.
		/// </summary>
		/// <param name="bVisible">True to set it visible.</param>
		void SetVisible(bool bVisible);
		/// <summary>
		/// Checks if the component is visible or invisible.
		/// If a component is invisible, it will not draw.
		/// </summary>
		/// <returns>True if the component is visible</returns>
		bool IsVisible() const;

		/// <summary>
		/// Gets the dimensions of this component.
		/// </summary>
		/// <returns>The dimensions of the component.</returns>
		const ivec2 & GetDimensions() const;
		/// <summary>
		/// Gets the width of the component.
		/// </summary>
		/// <returns>The width.</returns>
		virtual int32 GetWidth() const;
		/// <summary>
		/// Gets the height of the component.
		/// </summary>
		/// <returns>The height.</returns>
		virtual int32 GetHeight() const;

	protected:
		virtual void InitializeComponent() = 0;

		Object* m_pParentObject;
		bool	m_bInitialized,
				m_bIsEnabled,
				m_bIsVisible;
		ivec2	m_Dimensions;

	private:
		BaseComponent(const BaseComponent& t);
		BaseComponent(BaseComponent&& t);
		BaseComponent& operator=(const BaseComponent& t);
		BaseComponent& operator=(BaseComponent&& t);
	};
}
