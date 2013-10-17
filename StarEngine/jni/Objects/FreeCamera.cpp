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
		,m_RotationSpeed(static_cast<float>(PI)/2)
		,m_pCamera(nullptr)
		,m_bisStatic(false)
	{
	}

	FreeCamera::~FreeCamera()
	{
	}
	
	void FreeCamera::SetStatic(bool isStatic)
	{
		m_bisStatic = isStatic;
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
			vec2 look = vec2(0,0);

			if(!m_bisStatic)
			{
#ifdef DESKTOP
				move.y = InputManager::GetInstance()->IsKeyboardKeyDown('Z')?1.0f:0.0f;
				if(move.y == 0) move.y = -(InputManager::GetInstance()->IsKeyboardKeyDown('S')?1.0f:0.0f);
				if(move.y == 0) move.y = InputManager::GetInstance()->GetThumbstickPosition().y;
	
				move.x = InputManager::GetInstance()->IsKeyboardKeyDown('D')?1.0f:0.0f;
				if(move.x == 0) move.x = -(InputManager::GetInstance()->IsKeyboardKeyDown('Q')?1.0f:0.0f);
				if(move.x == 0) move.x = InputManager::GetInstance()->GetThumbstickPosition().x;

				//if(InputManager::GetInstance()->IsMouseButtonDownWIN(VK_LBUTTON))
				//{
				//	auto mouseMove = InputManager::GetInstance()->GetMouseMovement();
				//	look = vec2(static_cast<float>(mouseMove.x),static_cast<float>(mouseMove.y));
				//}
				if(look.x == 0 && look.y == 0)
				{
					look = InputManager::GetInstance()->GetThumbstickPosition(false);
					look.y *= -1;
				}
#endif
			}

			//CALCULATE TRANSFORMS
			auto transform = GetComponent<TransformComponent>();
			auto currPos = transform->GetWorldPosition();
			auto currRot = transform->GetWorldRotation();
	
			currPos.y += static_cast<float>(move.y * m_MoveSpeed * context.mTimeManager->GetSeconds());
			currPos.x += static_cast<float>(move.x * m_MoveSpeed * context.mTimeManager->GetSeconds());
	
			//ROTATION
			//m_TotalYaw += look.x * m_RotationSpeed * context.mTimeManager->GetSeconds();
			//m_TotalPitch += look.y * m_RotationSpeed * context.mTimeManager->GetSeconds();
			//
			//quat finalOrientation(vec3(m_TotalYaw,m_TotalPitch,0));
			//
			transform->Translate(currPos);
			//transform->Rotate(finalOrientation);
		}
	
		Object::Update(context);
	}
}
