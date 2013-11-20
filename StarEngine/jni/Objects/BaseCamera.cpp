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
	}

	BaseCamera::~BaseCamera()
	{
	}

	void BaseCamera::Initialize()
	{
		//Camera Component
		m_pCamera = new CameraComponent();
		AddComponent(m_pCamera);

		m_pCamera->SetActive();
	}
}
