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

	class BaseColliderComponent : public BaseComponent
	{
		typedef std::function<void(BaseColliderComponent* collider)> Callback;

	public:
		BaseColliderComponent();
		BaseColliderComponent(
			const tstring* layers, 
			uint8 n = 1);
		virtual ~BaseColliderComponent();

		void Update(const Context& context);
		
		void SetOnEnterCallback(Callback onEnter);
		void SetOnStayCallback(Callback onStay);
		void SetOnExitCallback(Callback onExit);

		void TriggerOnEnter(BaseColliderComponent* other);
		void TriggerOnStay(BaseColliderComponent* other);
		void TriggerOnExit(BaseColliderComponent* other);

		void SetAsTrigger(bool isTrigger);
		bool IsTrigger() const;

		void SetAsStatic(bool isStatic);
		bool IsStatic() const;

		void SetEntered(bool hasEntered);
		bool GetEntered() const;

		void SetExited(bool hasLeft);
		bool GetExited() const;

		void SetDrawColor(const Color& color);
		const Color& GetDrawColor() const;

		void EnableDrawing(bool enable);

		const PointerArray<tstring>& GetLayers() const;

		virtual bool CollidesWithPoint(const vec2& point) const = 0;
		virtual bool CollidesWithLine(
			const vec2& point1, 
			const vec2& point2
			) const = 0;
		virtual bool CollidesWith(const BaseColliderComponent* other) const = 0;

	protected:
		virtual void InitializeColliderComponent() = 0;
		virtual void Draw();

		bool m_bIsTrigger;
		bool m_bIsStatic;
		bool m_bCanDraw;
		Color m_DrawColor;

		bool RectangleCircleCollision(
			const RectangleColliderComponent* rect, 
			const CircleColliderComponent* circle
			) const;
		vec2 FindClosestPointToOOBB(
			const vec2& point, 
			const RectangleColliderComponent* oobb
			) const;
		PointerArray<tstring> m_Layers;
		static const tstring DEFAULT_LAYER_NAME;

	private:
		bool m_bEntered;
		bool m_bExited;

		Callback m_OnEnter;
		Callback m_OnStay;
		Callback m_OnExit;

		void InitializeComponent();

		BaseColliderComponent(BaseColliderComponent&& t);
		BaseColliderComponent(const BaseColliderComponent& t);
		BaseColliderComponent& operator=(const BaseColliderComponent& t);
		BaseColliderComponent& operator=(BaseColliderComponent&& t);
	};
}
