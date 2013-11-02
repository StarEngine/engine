#include "BaseCamera.h"
#include "../Logger.h"
#include "../Input/InputManager.h"
#include "../StarComponents.h"
#include "../Graphics/GraphicsManager.h"
#include "../Graphics/ScaleSystem.h"

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

	void BaseCamera::Translate(const pos& position)
	{
		float xPos = (position.pos2D().x) / ((ScaleSystem::GetInstance()->GetWorkingResolution().x)/2.0f);
		float yPos = (position.pos2D().y) / ((ScaleSystem::GetInstance()->GetWorkingResolution().y)/2.0f); 
		GetTransform()->Translate(xPos, yPos);
	}
}
