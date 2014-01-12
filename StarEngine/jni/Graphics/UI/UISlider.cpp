#include "UISlider.h"
#include "UIButton.h"
#include "../../Helpers/Math.h"
#include "../../Input/InputManager.h"
#include "../../Scenes/BaseScene.h"

namespace star
{
	UISlider::UISlider(
		const tstring & name,
		const tstring & file,
		const tstring & fileBackground,
		bool sliderIsHorizontal,
		bool spritesheetIsVertical
		)
		: UIImage(name, fileBackground)
		, m_SliderIsHorizontal(sliderIsHorizontal)
		, m_pSlider(nullptr)
		, m_ReleasedCallback(nullptr)
		, m_DownCallback(nullptr)
		, m_Percent(0.5f)
		, m_SliderDimension(0)
		, m_SliderOffset(0,0)
		, m_SliderIsDown(false)
	{
		m_pSlider = new UIButton(
			name + _T("_btn"),
			file,
			spritesheetIsVertical
			);

		AddChild(m_pSlider);
	}

	UISlider::UISlider(
		const tstring & name,
		const tstring & file,
		const tstring & spriteName,
		const tstring & fileBackground,
		const tstring & spriteNameBackground,
		bool sliderIsHorizontal,
		bool spritesheetIsVertical
		)
		: UIImage(name, spriteNameBackground, fileBackground)
		, m_SliderIsHorizontal(sliderIsHorizontal)
		, m_pSlider(nullptr)
		, m_ReleasedCallback(nullptr)
		, m_DownCallback(nullptr)
		, m_Percent(0.5f)
		, m_SliderDimension(0)
		, m_SliderOffset(0,0)
		, m_SliderIsDown(false)
	{
		m_pSlider = new UIButton(
			name + _T("_btn"),
			file,
			spriteName,
			spritesheetIsVertical
			);

		AddChild(m_pSlider);
	}

	UISlider::~UISlider()
	{

	}

	void UISlider::AfterInitialized()
	{
		vec2 dimensions = GetDimensions();
		vec2 sliderDimensions = m_pSlider->GetDimensions();
		if(m_SliderIsHorizontal)
		{
			m_pSlider->SetVerticalAlignment(VerticalAlignment::Center);
			m_pSlider->GetTransform()->SetCenterX(sliderDimensions.x / 2);
		}
		else
		{
			m_pSlider->SetHorizontalAlignment(HorizontalAlignment::Center);
			m_pSlider->GetTransform()->SetCenterY(sliderDimensions.y / 2);
		}

		m_pSlider->Translate(
			dimensions.x / 2.0f,
			dimensions.y / 4.0f
			);
		SetPositionAccordingToPercent();
		m_pSlider->SetDownCallback(
			[&] ()
			{
				m_SliderIsDown = true;
				m_pSlider->SetLocked(true);
				GetScene()->SetStateActiveCursor(UI_STATE_CLICK);
				GetScene()->SetActiveCursorLocked(true);
			}
		);

		CalculateSliderDimension();

		UIImage::AfterInitialized();
	}
	
	void UISlider::Update(const Context & context)
	{
		if(m_SliderIsDown)
		{
			vec2 dimensions = GetDimensions();
			auto pos = InputManager::GetInstance()->GetCurrentFingerPosCP(0);
			pos -= GetTransform()->GetWorldPosition().pos2D();
			if(m_SliderIsHorizontal)
			{
				pos.x -= m_SliderOffset.x;
				SetPercent(pos.x / m_SliderDimension);
			}
			else
			{
				pos.y -= m_SliderOffset.x;
				SetPercent(pos.y / m_SliderDimension);
			}
			if(m_DownCallback != nullptr)
			{
				m_DownCallback(m_Percent);
			}
			if(InputManager::GetInstance()->IsFingerReleasedCP(0))
			{
				m_SliderIsDown = false;
				m_pSlider->SetLocked(false);
				GetScene()->GetTimerManager()->CreateTimer(
					GetName() + _T("_locked_timer"),
					0.1f, false, false, [&] ()
					{
						GetScene()->SetActiveCursorLocked(false);
						GetScene()->SetStateActiveCursor(UI_STATE_IDLE);
					}, false);
			}
		}
		UIImage::Update(context);
	}

	void UISlider::SetPercent(float32 percent)
	{
		m_Percent = Clamp<float32>(percent, 0.0f, 1.0f);
		SetPositionAccordingToPercent();
	}

	float32 UISlider::GetPercent() const
	{
		return m_Percent;
	}

	void UISlider::SetPositionAccordingToPercent()
	{
		if(m_SliderIsHorizontal)
		{
			m_pSlider->TranslateX(
					m_SliderOffset.x +
					m_SliderDimension * m_Percent
				);
		}
		else
		{
			m_pSlider->TranslateY(
					m_SliderOffset.x +
					m_SliderDimension * m_Percent
				);
		}
	}

	void UISlider::CalculateSliderDimension()
	{
		vec2 dimensions = GetDimensions();
		m_SliderDimension =
			(m_SliderIsHorizontal ? dimensions.x : dimensions.y) -
			m_SliderOffset.x -
			m_SliderOffset.y;

		SetPositionAccordingToPercent();

	}

	void UISlider::SetReleasedCallback(
		const std::function<void(float32)> & callback
		)
	{
		m_ReleasedCallback = callback;
		m_pSlider->SetReleasedCallback(
			[&]() {
				m_ReleasedCallback(m_Percent);
		});
	}

	void UISlider::SetDownCallback(
		const std::function<void(float32)> & callback
		)
	{
		m_DownCallback = callback;
	}

	void UISlider::SetSliderOffset(float32 min, float32 max)
	{
		m_SliderOffset.x = min;
		m_SliderOffset.y = max;
		CalculateSliderDimension();
	}

	void UISlider::SetSliderOffset(const vec2 & offset)
	{
		m_SliderOffset = offset;
		CalculateSliderDimension();
	}

	void UISlider::SetSliderMinOffset(float32 min)
	{
		m_SliderOffset.x = min;
		CalculateSliderDimension();
	}

	void UISlider::SetSliderMaxOffset(float32 max)
	{
		m_SliderOffset.y = max;
		CalculateSliderDimension();
	}

	void UISlider::SetSliderOrthogonalAlignmentCentered(bool redefineCenter)
	{
		if(m_SliderIsHorizontal)
		{
			m_pSlider->SetVerticalAlignment(
				VerticalAlignment::Center,
				redefineCenter
				);
		}
		else
		{
			m_pSlider->SetHorizontalAlignment(
				HorizontalAlignment::Center,
				redefineCenter
				);
		}
	}

	void UISlider::SetSliderOrthogonalAlignmentPositive(bool redefineCenter)
	{
		if(m_SliderIsHorizontal)
		{
			m_pSlider->SetVerticalAlignment(
				VerticalAlignment::Top,
				redefineCenter
				);
		}
		else
		{
			m_pSlider->SetHorizontalAlignment(
				HorizontalAlignment::Right,
				redefineCenter
				);
		}
	}

	void UISlider::SetSliderOrthogonalAlignmentNegative(bool redefineCenter)
	{
		if(m_SliderIsHorizontal)
		{
			m_pSlider->SetVerticalAlignment(
				VerticalAlignment::Bottom,
				redefineCenter
				);
		}
		else
		{
			m_pSlider->SetHorizontalAlignment(
				HorizontalAlignment::Left,
				redefineCenter
				);
		}
	}
		
	void UISlider::SetSliderOrthogonalOffset(float32 offset)
	{
		if(m_SliderIsHorizontal)
		{
			m_pSlider->TranslateY(offset);
		}
		else
		{
			m_pSlider->TranslateX(offset);
		}
	}

	void UISlider::SetSliderCenterPoint(const vec2 & center)
	{
		m_pSlider->GetTransform()->SetCenterPoint(center);
	}

	void UISlider::SetSliderCenterPoint(float32 x, float32 y)
	{
		m_pSlider->GetTransform()->SetCenterPoint(x, y);
	}

	void UISlider::SetSliderCenterX(float32 x)
	{
		m_pSlider->GetTransform()->SetCenterX(x);
	}

	void UISlider::SetSliderCenterY(float32 y)
	{
		m_pSlider->GetTransform()->SetCenterY(y);
	}
}
