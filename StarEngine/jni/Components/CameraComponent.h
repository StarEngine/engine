#pragma once
#include "..\defines.h"

namespace star
{
	class CameraComponent:public BaseComponent
	{
	public:
		CameraComponent(void);
		virtual ~CameraComponent(void);

		virtual void Update(const Context& context);
		virtual void Draw() {};

		void SetFieldOfView(float fov) {m_FOV = fov;}
		void SetOrthoSize(float size) {m_Size = size;}
		void SetNearClippingPlane(float nearPlane) {m_NearPlane = nearPlane;}
		void SetFarClippingPlane(float farPlane) {m_FarPlane = farPlane;}
		
		void SetActive();
		bool IsActive() const {return m_bIsActive;}

		mat4x4 GetView() const {return m_View;}
		mat4x4 GetProjection() const {return m_Projection;}
		mat4x4 GetViewInverse() const {return m_ViewInverse;}

	protected:
		virtual void InitializeComponent() {};

	private:
		mat4x4 MatrixPerspectiveFOV(float FovY, float ratio, float nearPlane, float farPlane);
		mat4x4 MatrixOrtho(float width, float height, float nearPlane, float farPlane);
		mat4x4 MatrixLookAt(const vec3& eye, const vec3& at, const vec3& up);

		mat4x4	m_Projection,
				m_View,
				m_ViewInverse;

		float	m_FarPlane,
				m_NearPlane,
				m_FOV,
				m_Size;

		bool m_bIsActive, m_bPerspectiveProjection;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		CameraComponent(const CameraComponent& t);
		CameraComponent& operator=(const CameraComponent& t);
	};
}
