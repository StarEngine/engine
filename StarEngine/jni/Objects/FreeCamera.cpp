#include "FreeCamera.h"
#include "../Logger.h"
#include "../Input/InputManager.h"
#include "../StarComponents.h"
#include "../Graphics/GraphicsManager.h"

namespace star
{
	FreeCamera::FreeCamera():
		BaseCamera()
		,m_TotalPitch(0)
		,m_TotalYaw(0)
		,m_MoveSpeed(1.0f)
		,m_Zoom(1.0f)
		,m_ZoomSpeed(0.5f)
		,m_RotationSpeed(static_cast<float32>(PI)/2)
		,m_bisStatic(false)
		,m_bZoom(false)
	{
	}

	FreeCamera::~FreeCamera()
	{
	}
	
	void FreeCamera::SetStatic(bool isStatic)
	{
		m_bisStatic = isStatic;
	}

	void FreeCamera::SetZoomEnabled(bool canZoom)
	{
		m_bZoom = canZoom;
	}

	bool FreeCamera::IsZoomEnabled() const
	{
		return m_bZoom;
	}
	
	void FreeCamera::SetZoomSpeed(float32 speed)
	{
		m_ZoomSpeed = speed;
	}
	
	void FreeCamera::SetMoveSpeed(float32 speed)
	{
		m_MoveSpeed = speed;
	}

	void FreeCamera::Update(const Context& context)
	{
		if(m_pCamera->IsActive())
		{
			//HANDLE INPUT
			vec3 move = vec3(0,0,0);
			vec2 look = vec2(0,0);

#ifdef DESKTOP
			if(!m_bisStatic)
			{
				move.y = InputManager::GetInstance()->IsKeyboardKeyDown('Z') ? 1.0f : 0.0f;
				if(move.y == 0) 
				{
					move.y = -(InputManager::GetInstance()->IsKeyboardKeyDown('S') ? 1.0f : 0.0f);
				}
				if(move.y == 0) 
				{
					move.y = InputManager::GetInstance()->GetThumbstickPosition().y;
				}

				move.x = InputManager::GetInstance()->IsKeyboardKeyDown('D') ? 1.0f : 0.0f;
				if(move.x == 0) 
				{
					move.x = -(InputManager::GetInstance()->IsKeyboardKeyDown('Q') ? 1.0f : 0.0f);
				}
				//if it's still 0, that's why second check
				if(move.x == 0) 
				{
					move.x = InputManager::GetInstance()->GetThumbstickPosition().x;
				}

				//if no keyboard input, check controller input
				if(look.x == 0 && look.y == 0)
				{
					look = InputManager::GetInstance()->GetThumbstickPosition(false);
					look.y *= -1;
				}
			}
			if(m_bZoom)
			{
				if(InputManager::GetInstance()->IsKeyboardKeyDown('O'))
				{
					m_Zoom += m_ZoomSpeed * static_cast<float32>(context.mTimeManager->GetSeconds());
					m_pCamera->SetZoom(m_Zoom);
				}
				else if(InputManager::GetInstance()->IsKeyboardKeyDown('P'))
				{
					m_Zoom -= m_ZoomSpeed * static_cast<float32>(context.mTimeManager->GetSeconds());
					m_pCamera->SetZoom(m_Zoom);
				}
			}
#endif
			if(move != vec3() || look != vec2())
			{
				//CALCULATE TRANSFORMS
				auto transform = GetComponent<TransformComponent>();
				auto currPos = transform->GetLocalPosition();
				auto currRot = transform->GetLocalRotation();
				
				float64 deltaTime = context.mTimeManager->GetSeconds();
				move *= m_MoveSpeed * deltaTime;
	
				currPos.y += static_cast<float32>(move.y);
				currPos.x += static_cast<float32>(move.x);

				transform->Translate(currPos);
			}
		}
	}
}
