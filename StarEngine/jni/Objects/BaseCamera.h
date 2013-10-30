#pragma once
#include "../defines.h"
#include "../Context.h"
#include "../Objects/Object.h"

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
		virtual void BaseUpdate(const Context& context);
		

	private:
		CameraComponent *m_pCamera;

		BaseCamera(const BaseCamera &);
		BaseCamera(BaseCamera &&);
		BaseCamera & operator=(const BaseCamera &);
	};
}
