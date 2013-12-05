#include "UICursor.h"
#include "../../Components/Graphics/SpritesheetComponent.h"
#include "../../Input/InputManager.h"

namespace star
{
	UICursor::UICursor(
		const tstring & name,
		const tstring & spriteFile,
		const tstring & spritesheetName
		)
		: UIBaseCursor(name)
		, m_pCursorSprite(nullptr)
		, m_Offsets()
		, m_DefaultOffset(0, 0)
	{
		m_pCursorSprite = new SpritesheetComponent(
			spriteFile,
			name,
			spritesheetName
			);
		m_pCursorSprite->SetHUDOptionEnabled(true);
		AddComponent(m_pCursorSprite);
	}

	UICursor::UICursor(
		const tstring & name,
		const tstring & spriteFile,
		const tstring & spriteName,
		const tstring & spritesheetName
		)
		: UIBaseCursor(name)
		, m_pCursorSprite(nullptr)
		, m_Offsets()
		, m_DefaultOffset(0, 0)
	{
		m_pCursorSprite = new SpritesheetComponent(
			spriteFile,
			spriteName,
			spritesheetName
			);
		m_pCursorSprite->SetHUDOptionEnabled(true);
		AddComponent(m_pCursorSprite);
	}

	UICursor::~UICursor()
	{
	}

	void UICursor::SetCenterPoint(const vec2 & center)
	{
		SetCenterPoint(center.x, center.y);
	}

	void UICursor::SetCenterPoint(float32 x, float32 y)
	{
		SetCenterX(x);
		SetCenterY(y);
	}

	void UICursor::SetCenterX(float32 x)
	{
		GetTransform()->SetCenterX(x);
	}

	void UICursor::SetCenterY(float32 y)
	{
		GetTransform()->SetCenterY(
			m_pCursorSprite->GetHeight() - y
			);
	}

	void UICursor::SetDefaultCenterPosition(const vec2 & center)
	{
		m_DefaultOffset = center;
	}
	
	void UICursor::SetDefaultCenterPosition(float32 x, float32 y)
	{
		SetDefaultCenterPosition(
			vec2(x, y)
			);
	}

	void UICursor::SetState(const tstring & state)
	{
		if(!m_IsLocked)
		{
			if(!m_pCursorSprite->PlayAnimationSafe(
				state,
				m_pCursorSprite->GetCurrentFrame()
				))
			{
				Logger::GetInstance()->Log(LogLevel::Warning,
					_T("UICursor::SetState: State '")
					+ state + _T("' is not defined in the used spritesheet."),
					STARENGINE_LOG_TAG);
			}

			auto it = m_Offsets.find(state);
			if(it != m_Offsets.end())
			{
				SetCenterPoint(it->second);
			}
			else
			{
				SetCenterPoint(m_DefaultOffset);
			}
			UIBaseCursor::SetState(state);
		}
	}

	void UICursor::SetStateOffset(
		const tstring & state,
		const vec2 & offset
		)
	{
		m_Offsets[state] = offset;
	}

	void UICursor::SetStateOffset(
		const tstring & state,
		float32 x,
		float32 y
		)
	{
		 SetStateOffset(
			 state,
			 vec2(x, y)
			 );
	}

	void UICursor::SetColorMultiplier(const Color & color)
	{
		m_pCursorSprite->SetColorMultiplier(color);
	}
	
	void UICursor::Update(const Context & context)
	{
		auto pos = InputManager::GetInstance()->GetCurrentFingerPosCP(0);
		GetTransform()->Translate(pos);

		UIBaseCursor::Update(context);
	}
}
