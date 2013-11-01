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

	protected:
		virtual void Update(const Context& context);
		
	private:
		float m_TotalPitch, m_TotalYaw;
		float m_MoveSpeed, m_RotationSpeed;
		bool m_bisStatic;

		FreeCamera(const FreeCamera &);
		FreeCamera(FreeCamera &&);
		FreeCamera & operator=(const FreeCamera &);
		FreeCamera & operator=(FreeCamera&&);
	};
}
