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
		const tstring & file_bg,
		bool sliderIsHorizontal,
		bool spritesheetIsVertical
		)
		: UIImage(name, file_bg, name + _T("_bg"))
		, m_SliderIsHorizontal(sliderIsHorizontal)
		, m_pSlider(nullptr)
		, m_SelectCallback(nullptr)
		, m_DownCallback(nullptr)
		, m_Percent(0.5f)
		, m_SliderIsDown(false)
	{
		m_pSlider = new UIButton(
			name + _T("_slider"),
			file,
			spritesheetIsVertical
			);

		AddElement(m_pSlider);
	}

	UISlider::~UISlider()
	{

	}

	void UISlider::AfterInitialized()
	{
		vec2 dimensions = GetDimensions();
		m_pSlider->SetAlignmentCentered();
		m_pSlider->Translate(
			dimensions.x / 2.0f,
			dimensions.y / 2.0f
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
				SetPercent(pos.x / dimensions.x);
			}
			else
			{
				SetPercent(pos.y / dimensions.y);
			}
			if(m_DownCallback != nullptr)
			{
				m_DownCallback(m_Percent);
			}
			if(InputManager::GetInstance()->IsFingerReleasedCP(0))
			{
				m_SliderIsDown = false;
				m_pSlider->SetLocked(false);
				GetScene()->GetStopwatch()->CreateTimer(
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
		vec2 dimensions = GetDimensions();
		if(m_SliderIsHorizontal)
		{
			m_pSlider->TranslateX(
				dimensions.x * m_Percent
					- dimensions.x / 2.0f
				);
		}
		else
		{
			m_pSlider->TranslateY(
				dimensions.y * m_Percent
					- dimensions.y / 2.0f
				);
		}
	}

	void UISlider::SetSelectedCallback(
		const std::function<void(float32)> & callback
		)
	{
		m_SelectCallback = callback;
		m_pSlider->SetSelectCallback(
			[&]() {
				m_SelectCallback(m_Percent);
		});
	}

	void UISlider::SetDownCallback(
		const std::function<void(float32)> & callback
		)
	{
		m_DownCallback = callback;
	}
}
