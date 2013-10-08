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
			NONE,
			TRANSLATION,
			ROTATION,
			SCALE
		};

		TransformComponent(void);
		TransformComponent(Object* parent);
		~TransformComponent(void);

		void Update(const Context& context);
		void Draw() {}

		void Translate(const vec3 & translation);
		void Translate(float x, float y, float z);

		void Rotate(const quat & rotation);
		//void Rotate(float x, float y, float z);

		void Scale(const vec3 & scale);
		void Scale(float x, float y, float z);

		const vec3 & GetWorldPosition();
		vec3 GetLocalPosition() const;
		const quat & GetWorldRotation();
		quat GetLocalRotation() const;
		const vec3 & GetWorldScale();
		vec3 GetLocalScale() const;
		const mat4x4 & GetWorldMatrix();

	private:
		void InitializeComponent();
		void CheckForUpdate(const bool force = false);

		unsigned char m_IsChanged;
		bool m_Invalidate;
		vec3 m_WorldPosition, m_LocalPosition;
		quat m_WorldRotation, m_LocalRotation;
		vec3 m_WorldScale, m_LocalScale;
		mat4x4 m_World;

		TransformComponent(const TransformComponent& yRef);
		TransformComponent(TransformComponent&& t);
		TransformComponent& operator=(const TransformComponent& yRef);
	};
}
