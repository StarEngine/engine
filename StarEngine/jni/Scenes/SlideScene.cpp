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
			SceneManager::GetInstance()->SetActiveScene(m_NextScene);
			SceneManager::GetInstance()->RemoveScene(GetName());
		}
		else if(m_CurrentSlide < m_Slides.size())
		{
			auto slide0 = m_Slides[m_CurrentSlide - 1];
			auto slide1 = m_Slides[m_CurrentSlide];

			m_pSlideMenu->GetChildByName<UIImage>(slide0)
				->SetVisible(false);
			m_pSlideMenu->GetChildByName<UIImage>(slide1)
				->SetVisible(true);

			auto time = GetTimerManager()->ForceEndTimer(
				slide0 + _T("_active")
				);

			GetTimerManager()->ForwardAllTimers(time);
		}
	}

	int16 SlideScene::AddSlide(
		const tstring & file,
		float32 activeTime
		)
	{
		int16 id = int16(m_Slides.size());
		tstring name = _T("Slide") + 
			string_cast<tstring>(id);
		m_Slides.push_back(name);
		auto slide =
			new UIImage(
				name,
				file
				);
		m_pSlideMenu->AddElement(slide);

		if(id > 0)
		{
			slide->SetVisible(false);
		}

		m_TotalTime += activeTime;
		GetTimerManager()->CreateTimer(
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
		float32 activeTime,
		const Color & fadeInStartColor,
		const Color & fadeInEndColor,
		float32 fadeInTime
		)
	{
		int16 id = AddSlide(file, activeTime);

		if(fadeInTime > 0)
		{
			float32 begin = m_TotalTime - activeTime;

			auto slide =
				m_pSlideMenu->GetChildByName<UIImage>(m_Slides[id]);
			slide->SetColorMultiplier(fadeInStartColor);

			GetTimerManager()->CreateTimer(
				m_Slides[id] + _T("_fade_in"),
				begin,
				false,
				false,
				[&, id, fadeInTime, fadeInStartColor, fadeInEndColor]() 
				{
					auto slide =
						m_pSlideMenu->GetChildByName<UIImage>(m_Slides[id]);
					auto fadeAction = new star::TimedFadeAction(
						m_Slides[id] + _T("_fade_in"),
						fadeInTime,
						fadeInStartColor,
						fadeInEndColor);
					slide->AddAction(fadeAction);
				},
				false
				);
		}
		else
		{
			LOG(LogLevel::Warning,
				_T("SlideScene::AddSlide: fade_im_time should be longer then 0 seconds."),
				STARENGINE_LOG_TAG
				);
		}

		return id;
	}

	int16 SlideScene::AddSlide(
		const tstring & file,
		float32 activeTime,
		const Color & fadeInStartColor,
		const Color & fadeInEndColor,
		float32 fadeInTime,
		const Color & fadeOutStartColor,
		const Color & fadeOutEndColor,
		float32 fadeOutTime
		)
	{
		int16 id = AddSlide(
			file, activeTime,
			fadeInStartColor,
			fadeInEndColor,
			fadeInTime
			);

		if(fadeOutTime > 0)
		{
			float32 begin = m_TotalTime - fadeOutTime;

			GetTimerManager()->CreateTimer(
				m_Slides[id] + _T("_fade_out"),
				begin,
				false,
				false,
				[&, id, fadeOutTime, fadeOutStartColor, fadeOutEndColor]() 
				{
					auto slide =
						m_pSlideMenu->GetChildByName<UIImage>(m_Slides[id]);
					auto fadeAction = new star::TimedFadeAction(
						m_Slides[id] + _T("_fade_out"),
						fadeOutTime,
						fadeOutStartColor,
						fadeOutEndColor
						);
					slide->AddAction(fadeAction);
				},
				false
				);
		}
		else
		{
			LOG(LogLevel::Warning,
				_T("SlideScene::AddSlide: fadeOutTime should be longer then 0 seconds."),
				STARENGINE_LOG_TAG
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
