#pragma once
#include "../defines.h"
#include "../Context.h"
#include "../Objects/Object.h"
#include "BaseCamera.h"

namespace star
{
	class CameraComponent;

	class FreeCamera : public BaseCamera
	{
	public:
		FreeCamera(void);
		virtual ~FreeCamera(void);

		void SetStatic(bool isStatic);

	protected:
		virtual void Initialize();
		virtual void BaseUpdate(const Context& context);
		

	private:
		float m_TotalPitch, m_TotalYaw;
		float m_MoveSpeed, m_RotationSpeed;
		CameraComponent *m_pCamera;
		bool m_bisStatic;

		FreeCamera(const FreeCamera &);
		FreeCamera(FreeCamera &&);
		FreeCamera & operator=(const FreeCamera &);
	};
}
