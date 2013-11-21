#pragma once

#include "..\defines.h"

namespace star
{
	struct Context;
	class BaseScene;
	class TransformComponent;
	class Object;

	class BaseComponent
	{
	public:
		BaseComponent();
		BaseComponent(Object* parent);
		virtual ~BaseComponent();

		void Initialize();
		void BaseUpdate(const Context& context);
		void BaseDraw();
		virtual void Update(const Context& context) = 0;
		virtual void Draw() = 0;

		bool IsInitialized() const;

		Object* GetParent() const;
		void SetParent(Object* parent);

		BaseScene* GetGameScene() const;
		TransformComponent* GetTransform() const;

		virtual bool CheckCulling(
			float left,
			float right,
			float top,
			float bottom
			) const;

		void SetEnabled(bool bEnabled);
		bool IsEnabled() const;

		void SetVisible(bool bVisible);
		bool IsVisible() const;

	protected:
		virtual void InitializeComponent() = 0;

		Object* m_pParentObject;
		bool	m_bInitialized,
				m_bIsEnabled,
				m_bIsVisible;

	private:
		BaseComponent(const BaseComponent& t);
		BaseComponent(BaseComponent&& t);
		BaseComponent& operator=(const BaseComponent& t);
		BaseComponent& operator=(BaseComponent&& t);
	};
}
