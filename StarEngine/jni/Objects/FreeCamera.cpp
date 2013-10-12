#include "FreeCamera.h"
#include "../Logger.h"
#include "../Input/InputManager.h"
#include "../StarComponents.h"

namespace star
{
	FreeCamera::FreeCamera():
		Object()
		,m_TotalPitch(0)
		,m_TotalYaw(0)
		,m_MoveSpeed(1.0f)
		,m_RotationSpeed(static_cast<float>(3.14)/2.0f)
		,m_pCamera(nullptr)
		,m_bisStatic(false)
	{
	}

	FreeCamera::~FreeCamera()
	{
	}

	void FreeCamera::Initialize()
	{
		//Camera Component
		m_pCamera = new CameraComponent();
		AddComponent(m_pCamera);
	
		Object::Initialize();
	
		m_pCamera->SetActive();
	}

	void FreeCamera::Update(const Context& context)
	{
		if(m_pCamera->IsActive())
		{
			//HANDLE INPUT
			vec3 move = vec3(0,0,0);
	
			if(!m_bisStatic)
			{
#ifdef _WIN32
				move.y = InputManager::GetInstance()->IsKeyboardKeyDown('Z')?1.0f:0.0f;
				if(move.y == 0) move.y = -(InputManager::GetInstance()->IsKeyboardKeyDown('S')?1.0f:0.0f);
				if(move.y == 0) move.y = InputManager::GetInstance()->GetThumbstickPosition().y;
	
				move.x = InputManager::GetInstance()->IsKeyboardKeyDown('D')?1.0f:0.0f;
				if(move.x == 0) move.x = -(InputManager::GetInstance()->IsKeyboardKeyDown('Q')?1.0f:0.0f);
				if(move.x == 0) move.x = InputManager::GetInstance()->GetThumbstickPosition().x;
#endif
			}
			vec2 look = vec2(0,0);
	
			//CALCULATE TRANSFORMS
			auto transform = GetComponent<TransformComponent>();
			auto currPos = transform->GetWorldPosition();
	
			currPos.y += static_cast<float>(move.y * m_MoveSpeed * context.mTimeManager->GetSeconds());
			currPos.x += static_cast<float>(move.x * m_MoveSpeed * context.mTimeManager->GetSeconds());
	
			transform->Translate(currPos);
		}
	
		Object::Update(context);
	}
}
