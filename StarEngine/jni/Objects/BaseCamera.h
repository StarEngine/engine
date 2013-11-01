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

		void Translate(const pos& position);

	protected:
		virtual void Initialize();
		virtual void Update(const Context& context);
		
		CameraComponent *m_pCamera;
	private:
		
		BaseCamera(const BaseCamera &);
		BaseCamera(BaseCamera &&);
		BaseCamera & operator=(const BaseCamera &);
		BaseCamera & operator=(BaseCamera&&);
	};
}
