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

		void Translate(const vec2& translation);
		void Translate(float32 x, float32 y);
		void TranslateX(float32 x);
		void TranslateY(float32 y);

		void ConvertScreenToWorld(vec2 & posInOut);

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
