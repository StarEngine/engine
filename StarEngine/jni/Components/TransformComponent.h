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

#ifdef STAR2D
		void Translate(ScreenPercent& translation);
		void Translate(ScreenPercentX x, ScreenPercentY y);
		void Translate(ScreenPercent& translation, lay l);
		void Translate(ScreenPercentX x, ScreenPercentY y, lay l);
		void TranslateAbsolute(const pos & pos2D);
		void Rotate(float rotation);

		void Scale(ScreenPercent& scale);
		void Scale(ScreenPercentX x, ScreenPercentY y);
		
		const pos& GetWorldPosition();
		const pos& GetLocalPosition() const;
		float GetWorldRotation();
		float GetLocalRotation() const;
		const vec2& GetWorldScale();
		const vec2& GetLocalScale() const;
#else
		void Translate(const vec3& translation);
		void Translate(float x, float y, float z);

		void Rotate(const quat & rotation);

		void Scale(const vec3& scale);
		void Scale(float x, float y, float z);

		const vec3& GetWorldPosition();
		const vec3& GetLocalPosition() const;
		const quat& GetWorldRotation();
		const quat& GetLocalRotation() const;
		const vec3& GetWorldScale();
		const vec3& GetLocalScale() const;
#endif
		// [COMMENT] Do we need this in 2D?
		mat4x4 GetWorldMatrix();

	private:
		void InitializeComponent();
		void CheckForUpdate(const bool force = false);

		unsigned char m_IsChanged;
		bool m_Invalidate;
#ifdef STAR2D
		pos m_WorldPosition, m_LocalPosition;
		float m_WorldRotation, m_LocalRotation;
		vec2 m_WorldScale, m_LocalScale;
#else
		vec3 m_WorldPosition, m_LocalPosition;
		quat m_WorldRotation, m_LocalRotation;
		vec3 m_WorldScale, m_LocalScale;
#endif
		mat4x4 m_World;

		TransformComponent(const TransformComponent& yRef);
		TransformComponent(TransformComponent&& t);
		TransformComponent& operator=(const TransformComponent& yRef);
	};
}
