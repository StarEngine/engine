#include "FreeCamera.h"
#include "../Logger.h"
#include "../Input/InputManager.h"
#include "../StarComponents.h"
#include "../Graphics/GraphicsManager.h"
#include "../Graphics/ScaleSystem.h"

namespace star
{
	FreeCamera::FreeCamera():
		BaseCamera()
		,m_TotalPitch(0)
		,m_TotalYaw(0)
		,m_MoveSpeed(100.0f)
		,m_RotationSpeed(static_cast<float>(PI)/2)
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

				if(look.x == 0 && look.y == 0)
				{
					look = InputManager::GetInstance()->GetThumbstickPosition(false);
					look.y *= -1;
				}
#endif
			}
			if(move != vec3() || look != vec2())
			{
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
		}
	}
}
