#pragma once
#include "BaseComponent.h"
#include "..\defines.h"
#include "..\Helpers\Rect.h"

namespace star
{
	struct Context;

	class RectangleColliderComponent final : public BaseComponent
	{
	public:
		RectangleColliderComponent(uint16 width, uint16 height);
		~RectangleColliderComponent(void);

		void Initialize();
		void Update(const Context& context);
		void Draw();

		void SetAsTrigger(bool isTrigger) {m_bIsTrigger = isTrigger;}
		bool IsTrigger() const {return m_bIsTrigger;}

		const Rect GetCollisionRect() const {return m_CollisionRect;}
		Rect CollisionTest(const Rect& collider);

	private:
		void InitializeComponent();

		bool m_bIsTrigger;
		Rect m_CollisionRect;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		RectangleColliderComponent(const RectangleColliderComponent& t);
		RectangleColliderComponent(RectangleColliderComponent&& t);
		RectangleColliderComponent& operator=(const RectangleColliderComponent& t);
	};
}
