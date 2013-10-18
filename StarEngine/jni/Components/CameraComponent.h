#pragma once
#include "..\defines.h"
#include "BaseComponent.h"

namespace star
{
	class CameraComponent : public BaseComponent
	{
	public:
		CameraComponent(void);
		virtual ~CameraComponent(void);

		virtual void Update(const Context& context);
		virtual void Draw();

		void SetFieldOfView(float fov);
		void SetOrthoSize(float size);
		void SetNearClippingPlane(float nearPlane);
		void SetFarClippingPlane(float farPlane);
		
		void SetActive();
		bool IsActive() const;
		void Activate();
		void Deactivate();

		const mat4x4 & GetView() const;
		mat4x4 GetProjection() const;
		const mat4x4 & GetViewInverse() const;

	protected:
		virtual void InitializeComponent();

	private:
		mat4x4 MatrixPerspectiveFOV(float FovY, float ratio, float nearPlane, float farPlane);
		mat4x4 MatrixOrtho(float width, float height, float nearPlane, float farPlane);
		mat4x4 MatrixLookAt(const vec3 & eye, const vec3& at, const vec3& up);
		mat4x4 InverseMatrix(const mat4x4& matrix);

		mat4x4	m_Projection,
				m_View,
				m_ViewInverse;

		float	m_FarPlane,
				m_NearPlane,
				m_FOV,
				m_Size,
				m_Zoom,
				m_ZoomSpeed,
				m_AspectRatio;

		bool m_bIsActive, m_bPerspectiveProjection;

		CameraComponent(const CameraComponent& t);
		CameraComponent(CameraComponent&& t);
		CameraComponent& operator=(const CameraComponent& t);
	};
}
