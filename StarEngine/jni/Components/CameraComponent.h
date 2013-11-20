#pragma once
#include "..\defines.h"
#include "BaseComponent.h"

namespace star
{
	class CameraComponent : public BaseComponent
	{
	public:
		CameraComponent();
		virtual ~CameraComponent(void);

		virtual void Update(const Context& context);
		virtual void Draw();
		
		void SetFieldOfView(float32 fov);
		void SetOrthoSize(float32 size);
		void SetNearClippingPlane(float32 nearPlane);
		void SetFarClippingPlane(float32 farPlane);
		
		void SetActive();
		bool IsActive() const;
		void Activate();
		void Deactivate();

		void SetZoom(float32 zoom);
		float32 GetZoom() const;

		const mat4 & GetView() const;
		const mat4 & GetProjection() const;
		const mat4 & GetViewInverse() const;
		mat4 GetProjectionViewInverse() const;

	protected:
		virtual void InitializeComponent();

	private:
		mat4 MatrixPerspectiveFOV(float32 FovY, float32 ratio, float32 nearPlane, float32 farPlane);
		mat4 MatrixOrtho(float32 width, float32 height, float32 nearPlane, float32 farPlane);
		mat4 MatrixLookAt(const vec3& eye, const vec3& at, const vec3& up);

		mat4	m_Projection,
				m_View,
				m_ViewInverse;

		float32	m_FarPlane,
				m_NearPlane,
				m_FOV,
				m_Size,
				m_Zoom,
				m_AspectRatio;

		bool m_bIsActive, 
			 m_bPerspectiveProjection;

		CameraComponent(const CameraComponent& t);
		CameraComponent(CameraComponent&& t);
		CameraComponent& operator=(const CameraComponent& t);
		CameraComponent& operator=(CameraComponent&& t);
	};
}
