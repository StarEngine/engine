#include "SlideScene.h"
#include "SceneManager.h"
#include "../StarComponents.h"
#include "../Input/InputManager.h"
#include "../Helpers/Helpers.h"
#include "../Objects/Object.h"
#include "../Graphics/GraphicsManager.h"
#include "../Actions/Index.h"

namespace star
{
	SlideScene::SlideScene(const tstring & name, const tstring & nextScene)
		: BaseScene(name)
		, m_pSlideMenu(nullptr)
		, m_CurrentSlide(0)
		, m_Slides()
		, m_TotalTime(0)
		, m_AllowKeyboardInput(false)
		, m_AllowFingerInput(true)
		, m_NextScene(nextScene)
	{
		SetCursorHidden(true);
	}

	SlideScene::~SlideScene()
	{
	}

	void SlideScene::CreateObjects()
	{
		m_pSlideMenu = new star::UIDock(_T("SlideMenu"));
		AddObject(m_pSlideMenu);
	}

	void SlideScene::AfterInitializedObjects()
	{
	}

	void SlideScene::OnActivate()
	{

	}

	void SlideScene::OnDeactivate()
	{

	}

	void SlideScene::Update(const star::Context& context)
	{
		if(	(m_AllowFingerInput && InputManager::GetInstance()->IsFingerReleasedCP(0))
			#ifdef DESKTOP
				|| (m_AllowKeyboardInput && InputManager::GetInstance()->IsAnyKeyDown())
			#endif
			)
		{
			GoNextSlide();
		}
	}

	void SlideScene::Draw()
	{
	}

	void SlideScene::GoNextSlide()
	{
		++m_CurrentSlide;
		if(m_CurrentSlide == m_Slides.size())
		{
			tstring name = GetName();
			SceneManager::GetInstance()->SetActiveScene(m_NextScene);
			SceneManager::GetInstance()->GetStopwatch()->CreateTimer(
				_T("RemoveSplashScreenTimer"),
				0.5f,
				false,
				false,
				[&, name] ()
				{
					SceneManager::GetInstance()->RemoveScene(name);
				},
				false
				);
		}
		else if(m_CurrentSlide < m_Slides.size())
		{
			auto slide0 = m_Slides[m_CurrentSlide - 1];
			auto slide1 = m_Slides[m_CurrentSlide];

			m_pSlideMenu->GetChildByName<UIImage>(slide0)
				->SetVisible(false);
			m_pSlideMenu->GetChildByName<UIImage>(slide1)
				->SetVisible(true);

			auto time = GetStopwatch()->ForceEndTimer(
				slide0 + _T("_active")
				);

			GetStopwatch()->ForwardAllTimers(time);
		}
	}

	int16 SlideScene::AddSlide(
		const tstring & file,
		float32 active_time
		)
	{
		int16 id = int16(m_Slides.size());
		tstring name = _T("Slide") + 
			string_cast<tstring>(id);
		m_Slides.push_back(name);
		auto slide =
			new UIImage(
				name,
				file,
				name + _T("_img")
				);
		m_pSlideMenu->AddElement(slide);

		if(id > 0)
		{
			slide->SetVisible(false);
		}

		m_TotalTime += active_time;
		GetStopwatch()->CreateTimer(
			name + _T("_active"),
			m_TotalTime,
			false,
			false,
			[&] () 
			{
				GoNextSlide();
			},
			false
			);

		return id;
	}

	int16 SlideScene::AddSlide(
		const tstring & file,
		float32 active_time,
		const Color & fade_in_start_color,
		const Color & fade_in_end_color,
		float32 fade_in_time
		)
	{
		int16 id = AddSlide(file, active_time);

		if(fade_in_time > 0)
		{
			float32 begin = m_TotalTime - active_time;

			auto slide =
				m_pSlideMenu->GetChildByName<UIImage>(m_Slides[id]);
			slide->SetColorMultiplier(fade_in_start_color);

			GetStopwatch()->CreateTimer(
				m_Slides[id] + _T("_fade_in"),
				begin,
				false,
				false,
				[&, id, fade_in_time, fade_in_start_color, fade_in_end_color]() 
				{
					auto slide =
						m_pSlideMenu->GetChildByName<UIImage>(m_Slides[id]);
					auto fadeAction = new star::TimedFadeAction(
						m_Slides[id] + _T("_fade_in"),
						fade_in_time,
						fade_in_start_color,
						fade_in_end_color);
					slide->AddAction(fadeAction);
				},
				false
				);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SlideScene::AddSlide: fade_im_time should be longer then 0 seconds.")
				);
		}

		return id;
	}

	int16 SlideScene::AddSlide(
		const tstring & file,
		float32 active_time,
		const Color & fade_in_start_color,
		const Color & fade_in_end_color,
		float32 fade_in_time,
		const Color & fade_out_start_color,
		const Color & fade_out_end_color,
		float32 fade_out_time
		)
	{
		int16 id = AddSlide(
			file, active_time,
			fade_in_start_color,
			fade_in_end_color,
			fade_in_time
			);

		if(fade_out_time > 0)
		{
			float32 begin = m_TotalTime - fade_out_time;

			GetStopwatch()->CreateTimer(
				m_Slides[id] + _T("_fade_out"),
				begin,
				false,
				false,
				[&, id, fade_out_time, fade_out_start_color, fade_out_end_color]() 
				{
					auto slide =
						m_pSlideMenu->GetChildByName<UIImage>(m_Slides[id]);
					auto fadeAction = new star::TimedFadeAction(
						m_Slides[id] + _T("_fade_out"),
						fade_out_time,
						fade_out_start_color,
						fade_out_end_color
						);
					slide->AddAction(fadeAction);
				},
				false
				);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SlideScene::AddSlide: fade_out_time should be longer then 0 seconds.")
				);
		}

		return id;
	}

	void SlideScene::SetKeyboardInputEnabled(bool enable)
	{
		m_AllowKeyboardInput = enable;
	}

	void SlideScene::SetFingerInputEnabled(bool enable)
	{
		m_AllowFingerInput = enable;
	}
}
