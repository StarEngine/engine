#pragma once
#include "../defines.h"
#include "../Context.h"
#include "../SceneGraph/Object.h"

namespace star
{
	class CameraComponent;

	class FreeCamera : public Object
	{
	public:
		FreeCamera(void);
		~FreeCamera(void);

		void SetStatic(bool isStatic) {m_bisStatic=  isStatic;};
		virtual void Update(const Context& context);

	protected:
		virtual void Initialize();
		

	private:
		float m_TotalPitch, m_TotalYaw;
		float m_MoveSpeed, m_RotationSpeed;
		CameraComponent *m_pCamera;
		bool m_bisStatic;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		FreeCamera(const FreeCamera &);
		FreeCamera & operator=(const FreeCamera &);
	};
}
