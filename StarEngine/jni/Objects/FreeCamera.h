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

		void SetStatic(bool isStatic);
		// [COMMENT] if you make this virtual, why not the destructor then ?! o.O
		virtual void Update(const Context& context);

	protected:
		virtual void Initialize();
		

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
