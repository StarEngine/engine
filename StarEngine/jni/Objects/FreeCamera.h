#pragma once
#include "../defines.h"
#include "../Context.h"
#include "Object.h"
#include "BaseCamera.h"

namespace star
{
	class FreeCamera : public BaseCamera
	{
	public:
		FreeCamera(void);
		virtual ~FreeCamera(void);
		void SetStatic(bool isStatic);
		void SetZoomEnabled(bool canZoom);
		void SetZoomSpeed(float speed);
		bool IsZoomEnabled() const;
		void SetMoveSpeed(float speed);
		
	protected:
		virtual void Update(const Context& context);
		
	private:
		float m_TotalPitch, m_TotalYaw;
		float m_MoveSpeed, m_RotationSpeed;
		float m_Zoom, m_ZoomSpeed;
		bool m_bisStatic, m_bZoom;

		FreeCamera(const FreeCamera &);
		FreeCamera(FreeCamera &&);
		FreeCamera & operator=(const FreeCamera &);
		FreeCamera & operator=(FreeCamera&&);
	};
}
