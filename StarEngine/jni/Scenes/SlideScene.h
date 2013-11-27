#pragma once

#include "../defines.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Scenes/BaseScene.h"
#include "../Graphics/UI/Index.h"

namespace star
{
	class SlideScene : public BaseScene
	{
	public:
		SlideScene(const tstring& name, const tstring & nextScene);
		virtual ~SlideScene();

		virtual void CreateObjects();
		virtual void AfterInitializedObjects();

		virtual void OnActivate();
		virtual void OnDeactivate();

		virtual void Update(const star::Context& context);
		virtual void Draw();
		
		int16 AddSlide(
			const tstring & file,
			float32 active_time
			);

		int16 AddSlide(
			const tstring & file,
			float32 active_time,
			const Color & fade_in_start_color,
			const Color & fade_in_end_color,
			float32 fade_in_time
			);

		int16 AddSlide(
			const tstring & file,
			float32 active_time,
			const Color & fade_in_start_color,
			const Color & fade_in_end_color,
			float32 fade_in_time,
			const Color & fade_out_start_color,
			const Color & fade_out_end_color,
			float32 fade_out_time
			);

		void SetKeyboardInputEnabled(bool enable);
		void SetFingerInputEnabled(bool enable);

	protected:
		star::UIDock * m_pSlideMenu;
		std::vector<tstring> m_Slides;

	private:
		void GoNextSlide();

		uint8 m_CurrentSlide;
		float32 m_TotalTime;
		tstring m_NextScene;

		bool m_AllowKeyboardInput,
			 m_AllowFingerInput;

		SlideScene(const SlideScene& t);
		SlideScene(SlideScene&& t);
		SlideScene& operator=(const SlideScene& t);
		SlideScene& operator=(SlideScene&& t);
	};
}
