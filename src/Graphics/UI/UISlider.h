#pragma once
#include "UIImage.h"
#include <functional>

namespace star
{
	class UIButton;

	class UISlider : public UIImage
	{
	public:
		UISlider(
			const tstring & name,
			const tstring & file,
			const tstring & fileBackground,
			bool sliderIsHorizontal,
			bool spritesheetIsVertical = true
			);
		UISlider(
			const tstring & name,
			const tstring & file,
			const tstring & spriteName,
			const tstring & fileBackground,
			const tstring & spriteNameBackground,
			bool sliderIsHorizontal,
			bool spritesheetIsVertical = true
			);
		virtual ~UISlider();

		virtual void AfterInitialized();
		virtual void Update(const Context & context);

		void SetPercent(float32 percent);
		float32 GetPercent() const;

		void SetReleasedCallback(
			const std::function<void(float32)> & callback
			);

		void SetDownCallback(
			const std::function<void(float32)> & callback
			);

		void SetSliderOffset(float32 min, float32 max);
		void SetSliderOffset(const vec2 & offset);
		void SetSliderMinOffset(float32 min);
		void SetSliderMaxOffset(float32 max);

		void SetSliderOrthogonalAlignmentCentered(bool redefineCenter = true);
		void SetSliderOrthogonalAlignmentPositive(bool redefineCenter = true);
		void SetSliderOrthogonalAlignmentNegative(bool redefineCenter = true);
		
		void SetSliderOrthogonalOffset(float32 offset);

		void SetSliderCenterPoint(const vec2 & center);
		void SetSliderCenterPoint(float32 x, float32 y);
		void SetSliderCenterX(float32 x);
		void SetSliderCenterY(float32 y);

	protected:
		void SetPositionAccordingToPercent();
		void CalculateSliderDimension();

		bool m_SliderIsHorizontal;
		bool m_SliderIsDown;

		UIButton * m_pSlider;
		float32 m_Percent, m_SliderDimension;
		vec2 m_SliderOffset;

		std::function<void(float32)>
			m_ReleasedCallback,
			m_DownCallback;

	private:
		UISlider(const UISlider &);
		UISlider(UISlider &&);
		UISlider & operator=(const UISlider &);
		UISlider & operator=(UISlider &&);
	};
}
