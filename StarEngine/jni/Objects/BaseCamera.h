#pragma once
#include "../defines.h"
#include "../Context.h"
#include "Object.h"

namespace star
{
	class CameraComponent;

	class BaseCamera : public Object
	{
	public:
		BaseCamera(void);
		virtual ~BaseCamera(void);

	protected:
		virtual void Initialize();
		CameraComponent *m_pCamera;

	private:
		BaseCamera(const BaseCamera &);
		BaseCamera(BaseCamera &&);
		BaseCamera & operator=(const BaseCamera &);
		BaseCamera & operator=(BaseCamera&&);
	};
}
