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
		void SetZoomSpeed(float32 speed);
		bool IsZoomEnabled() const;
		void SetMoveSpeed(float32 speed);
		
	protected:
		virtual void Update(const Context& context);
		
	private:
		float32 m_TotalPitch, m_TotalYaw;
		float32 m_MoveSpeed, m_RotationSpeed;
		float32 m_Zoom, m_ZoomSpeed;
		bool m_bisStatic, m_bZoom;

		FreeCamera(const FreeCamera &);
		FreeCamera(FreeCamera &&);
		FreeCamera & operator=(const FreeCamera &);
		FreeCamera & operator=(FreeCamera&&);
	};
}
