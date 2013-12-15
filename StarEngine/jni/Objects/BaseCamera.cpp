#include "BaseCamera.h"
#include "../Logger.h"
#include "../Input/InputManager.h"
#include "../StarComponents.h"
#include "../Graphics/GraphicsManager.h"

namespace star
{
	BaseCamera::BaseCamera():
		Object()
		,m_pCamera(nullptr)
	{
		//Camera Component
		m_pCamera = new CameraComponent();
		AddComponent(m_pCamera);
	}

	BaseCamera::~BaseCamera()
	{
	}

	void BaseCamera::Initialize()
	{
		
	}

	void BaseCamera::Translate(const vec2& translation)
	{
		GetComponent<CameraComponent>()->Translate(translation);
	}

	void BaseCamera::Translate(float32 x, float32 y)
	{
		GetComponent<CameraComponent>()->Translate(x, y);
	}

	void BaseCamera::TranslateX(float32 x)
	{
		GetComponent<CameraComponent>()->TranslateX(x);
	}

	void BaseCamera::TranslateY(float32 y)
	{
		GetComponent<CameraComponent>()->TranslateY(y);
	}

	void BaseCamera::ConvertScreenToWorld(vec2 & pos)
	{
		GetComponent<CameraComponent>()->ConvertScreenToWorld(pos);
	}
}
