#pragma once
#include "UIImage.h"

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

		void SetSelectedCallback(
			const std::function<void(float32)> & callback
			);

		void SetDownCallback(
			const std::function<void(float32)> & callback
			);

		void SetSliderOffset(float32 min, float32 max);
		void SetSliderOffset(const vec2 & offset);
		void SetSliderMinOffset(float32 min);
		void SetSliderMaxOffset(float32 max);

	protected:
		void SetPositionAccordingToPercent();
		void CalculateSliderDimension();

		bool m_SliderIsHorizontal;
		bool m_SliderIsDown;

		UIButton * m_pSlider;
		float32 m_Percent, m_SliderDimension;
		vec2 m_SliderOffset;

		std::function<void(float32)>
			m_SelectCallback,
			m_DownCallback;

	private:
		UISlider(const UISlider &);
		UISlider(UISlider &&);
		UISlider & operator=(const UISlider &);
		UISlider & operator=(UISlider &&);
	};
}
