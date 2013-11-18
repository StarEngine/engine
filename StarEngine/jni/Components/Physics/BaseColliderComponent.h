#pragma once

#include "../BaseComponent.h"
#include "../../defines.h"

namespace star
{
	struct Context;
	class CircleColliderComponent;
	class RectangleColliderComponent;

	class BaseColliderComponent : public BaseComponent
	{
	public:
		BaseColliderComponent();
		BaseColliderComponent(const tstring* layers, uint8 n = 1);
		virtual ~BaseColliderComponent();

		void Update(const Context& context);
		

		void SetAsTrigger(bool isTrigger);
		bool IsTrigger() const;

		void SetAsStatic(bool isStatic);
		bool IsStatic() const;

		virtual bool CollidesWithPoint(const vec2& point) const = 0;
		virtual bool CollidesWithLine(const vec2& point1, const vec2& point2) const = 0;
		virtual void CollidesWith(const BaseColliderComponent* other) const = 0;

	protected:
		virtual void InitializeColliderComponent() = 0;
		virtual void Draw();
		bool RectangleCircleCollision(
			const RectangleColliderComponent* rect, 
			const CircleColliderComponent* circle) const;
		bool m_bIsTrigger;
		bool m_bIsStatic;
		vec2 FindClosestPointToOOBB(
			const vec2& point, 
			const RectangleColliderComponent* oobb) const;
		const tstring* m_Layers;
		uint8 m_NrOfElementsInLayers;
		static const tstring DEFAULT_LAYER_NAME;

	private:

		void InitializeComponent();

		BaseColliderComponent(BaseColliderComponent&& t);
		BaseColliderComponent(const BaseColliderComponent& t);
		BaseColliderComponent& operator=(const BaseColliderComponent& t);
		BaseColliderComponent& operator=(BaseColliderComponent&& t);
	};
}
