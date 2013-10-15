#pragma once
#include "../BaseComponent.h"
#include "../../defines.h"
#include "../../Helpers\Rect.h"

namespace star
{
	struct Context;

	class RectangleColliderComponent final : public BaseComponent
	{
	public:
		RectangleColliderComponent(uint16 width, uint16 height);
		~RectangleColliderComponent(void);

		void Update(const Context& context);
		void Draw();

		void SetAsTrigger(bool isTrigger);
		bool IsTrigger() const;

		const Rect & GetCollisionRect() const;
		// [COMMENT] Create Implementation!
		Rect CollisionTest(const Rect& collider);

	private:
		void InitializeComponent();

		bool m_bIsTrigger;
		Rect m_CollisionRect;

		RectangleColliderComponent(const RectangleColliderComponent& t);
		RectangleColliderComponent(RectangleColliderComponent&& t);
		RectangleColliderComponent& operator=(const RectangleColliderComponent& t);
	};
}
