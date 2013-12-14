#pragma once

#include "..\defines.h"
#include "BaseComponent.h"

namespace star
{
	struct Context;
	class Object;

	class TransformComponent final: public BaseComponent
	{
	public:
		enum TransformChanged : byte
		{
			NONE = 0,
			TRANSLATION = 1,
			ROTATION = 2,
			SCALE = 4,
			ALL = 7
		};

		TransformComponent(Object* parent);
		~TransformComponent(void);

		void Update(const Context& context);
		void Draw();
		void IsChanged(bool isChanged);
#ifdef STAR2D
		void Translate(const vec2& translation);
		void Translate(float32 x, float32 y);
		void Translate(const vec2& translation, lay l);
		void Translate(float32 x, float32 y, lay l);
		void Translate(const pos & pos2D);
		void TranslateX(float32 x);
		void TranslateY(float32 y);
		void TranslateL(lay l);

		void Move(const vec2& translation);
		void Move(float32 x, float32 y);
		void MoveX(float32 x);
		void MoveY(float32 y);

		void Rotate(float32 rotation);
		void Rotate(float32 rotation, const vec2& centerPoint);

		void Scale(const vec2& scale);
		void Scale(float32 x, float32 y);
		void Scale(float32 u);
		void ScaleX(float32 x);
		void ScaleY(float32 y);

		void Mirror(bool x, bool y);
		void MirrorX(bool x);
		void MirrorY(bool y);
				
		const pos& GetWorldPosition();
		const pos& GetLocalPosition();
		float32 GetWorldRotation();
		float32 GetLocalRotation() const;
		const vec2& GetWorldScale();
		const vec2& GetLocalScale();

		void SetCenterPoint(const vec2 & centerPoint);
		void SetCenterPoint(float32 x, float32 y);
		void SetCenterX(float32 x);
		void SetCenterY(float32 y);

		void SetDimensions(int32 x, int32 y);
		void SetDimensions(const ivec2 & dimensions);
		void SetDimensionsX(int32 x);
		void SetDimensionsY(int32 y);

		void SetDimensionsSafe(int32 x, int32 y);
		void SetDimensionsSafe(const ivec2 & dimensions);
		void SetDimensionsXSafe(int32 x);
		void SetDimensionsYSafe(int32 y);
#else
		void Translate(const vec3& translation);
		void Translate(float32 x, float32 y, float32 z);
		void TranslateXY(float32 x, float32 y);
		void TranslateXZ(float32 x, float32 z);
		void TranslateX(float32 x);
		void TranslateYZ(float32 y, float32 z);
		void TranslateY(float32 y);
		void TranslateZ(float32 z);

		void Move(const vec3& translation);
		void Move(float32 x, float32 y, float32 z);
		void MoveXY(float32 x, float32 y);
		void MoveXZ(float32 x, float32 z);
		void MoveX(float32 x);
		void MoveYZ(float32 y, float32 z);
		void MoveY(float32 y);
		void MoveZ(float32 z);

		void Rotate(const quat & rotation);

		void Scale(const vec3& scale);
		void Scale(float32 x, float32 y, float32 z);
		void Scale(float32 u);
		void ScaleXY(float32 x, float32 y);
		void ScaleXZ(float32 x, float32 z);
		void ScaleX(float32 x);
		void ScaleYZ(float32 y, float32 z);
		void ScaleY(float32 y);
		void ScaleZ(float32 z);

		const vec3& GetWorldPosition();
		const vec3& GetLocalPosition();
		const quat& GetWorldRotation();
		const quat& GetLocalRotation() const;
		const vec3& GetWorldScale();
		const vec3& GetLocalScale();
#endif
		const mat4 & GetWorldMatrix() const;

	private:
		void InitializeComponent();
		void CheckForUpdate(const bool force = false);
		void CommonUpdate();
		void SingleUpdate(mat4 & world);

		suchar m_IsChanged;
		bool m_Invalidate;

#ifdef STAR2D
		pos m_WorldPosition, m_LocalPosition;
		float32 m_WorldRotation, m_LocalRotation;
		vec2 
			m_WorldScale,
			m_LocalScale,
			m_CenterPosition;
		bool m_IsMirroredX;
		bool m_IsMirroredY;
#else
		vec3 m_WorldPosition, m_LocalPosition;
		quat m_WorldRotation, m_LocalRotation;
		vec3 m_WorldScale, m_LocalScale;
		// [TODO] add 3D mirroring!
#endif
		mat4 m_World;

		TransformComponent(const TransformComponent& yRef);
		TransformComponent(TransformComponent&& yRef);
		TransformComponent& operator=(const TransformComponent& yRef);
		TransformComponent& operator=(TransformComponent&& yRef);
	};
}