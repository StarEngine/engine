#pragma once

#include "..\defines.h"
#include "BaseComponent.h"

namespace star
{
	struct Context;
	class Object;

	class TransformComponent final: public star::BaseComponent
	{
	public:
		enum TransformChanged : byte
		{
			NONE = 0x00,
			TRANSLATION = 0x01,
			ROTATION = 0x02,
			SCALE = 0x03,
		};

		TransformComponent(void);
		TransformComponent(Object* parent);
		~TransformComponent(void);

		void Update(const Context& context);
		void Draw(){}

		void Translate(const vec3 & translation);
		void Translate(float x, float y, float z);

		void Rotate(const quat & rotation);
		//void Rotate(float x, float y, float z);

		void Scale(const vec3 & scale);
		void Scale(float x, float y, float z);

		const vec3 & GetWorldPosition() { CheckForUpdate(); return m_WorldPosition;}
		vec3 GetLocalPosition() const { return m_LocalPosition; }
		const quat & GetWorldRotation() { CheckForUpdate(); return m_WorldRotation;}
		quat GetLocalRotation() const { return m_LocalRotation; }
		const vec3 & GetWorldScale() { CheckForUpdate(); return m_WorldScale; }
		vec3 GetLocalScale() const { return m_LocalScale; }
		const mat4x4 & GetWorldMatrix() { CheckForUpdate(); return m_World; }

	private:
		void InitializeComponent();
		void CheckForUpdate(const bool force = false);

		unsigned char m_IsChanged;
		bool m_Invalidate;
		vec3 m_WorldPosition, m_LocalPosition;
		quat m_WorldRotation, m_LocalRotation;
		vec3 m_WorldScale, m_LocalScale;
		mat4x4 m_World;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		TransformComponent(const TransformComponent& yRef);
		TransformComponent& operator=(const TransformComponent& yRef);
	};
}
