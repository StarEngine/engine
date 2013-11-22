#pragma once

#include "../BaseComponent.h"
#include "../../defines.h"
#include <functional>

namespace star
{
	struct Context;
	class CircleColliderComponent;
	class RectangleColliderComponent;

	typedef std::function<void()>  Callback;

	class BaseColliderComponent : public BaseComponent
	{
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

		void TriggerOnEnter();
		void TriggerOnStay();
		void TriggerOnExit();

		void SetAsTrigger(bool isTrigger);
		bool IsTrigger() const;

		void SetAsStatic(bool isStatic);
		bool IsStatic() const;

		void SetEntered(bool hasEntered);
		bool GetEntered() const;

		void SetExited(bool hasLeft);
		bool GetExited() const;

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
		bool RectangleCircleCollision(
			const RectangleColliderComponent* rect, 
			const CircleColliderComponent* circle
			) const;
		bool m_bIsTrigger;
		bool m_bIsStatic;
		vec2 FindClosestPointToOOBB(
			const vec2& point, 
			const RectangleColliderComponent* oobb
			) const;
		PointerArray<tstring> m_Layers;
		static const tstring DEFAULT_LAYER_NAME;

	private:
		bool m_Entered;
		bool m_Exited;

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
