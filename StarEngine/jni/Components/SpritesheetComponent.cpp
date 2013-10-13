#include "SpritesheetComponent.h"
#include "../SceneGraph/SpriteAnimationManager.h"
#ifdef _DEBUG
#include "../Logger.h"
#endif

namespace star
{
	SpritesheetComponent::SpritesheetComponent
		(const tstring& filePath, const tstring& spriteName,
			const tstring & spritesheet)
		: SpriteComponent(filePath, spriteName)
		, m_SpritesheetName(spritesheet)
		, m_Spritesheet()
		, m_Animations(0)
	{

	}

	SpritesheetComponent::~SpritesheetComponent()
	{

	}

	void SpritesheetComponent::Update(const Context& context)
	{
		if(m_Animations.size() > 0
			&& m_Animations.front().IsPlaying())
		{
			m_Animations.front().Update(context);
			auto uvInfo = m_Animations.front().GetCurrentUV();

			m_UvCoords[0] = uvInfo.x + uvInfo.z;
			m_UvCoords[1] = uvInfo.y + uvInfo.w;
			m_UvCoords[2] = uvInfo.x + uvInfo.z;
			m_UvCoords[3] = uvInfo.y;
			m_UvCoords[4] = uvInfo.x;
			m_UvCoords[5] = uvInfo.y + uvInfo.w;
			m_UvCoords[6] = uvInfo.x;
			m_UvCoords[7] = uvInfo.y;

		}

		SpriteComponent::Update(context);
	}

	void SpritesheetComponent::Play()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Play();
		}
#ifdef _DEBUG
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning, _T("Tried to resume sprite animation while there is none active."));
		}
#endif
	}

	void SpritesheetComponent::Restart()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Replay();
		}
#ifdef _DEBUG
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning, _T("Tried to restart sprite animation while there is none active."));
		}
#endif
	}

	void SpritesheetComponent::Pause()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Pause();
		}
#ifdef _DEBUG
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning, _T("Tried to pause sprite animation while there is none active."));
		}
#endif
	}

	void SpritesheetComponent::Stop()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Stop();
		}
#ifdef _DEBUG
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning, _T("Tried to stop sprite animation while there is none active."));
		}
#endif
	}

	void SpritesheetComponent::PushAnimation(const tstring & animation)
	{
		auto ani = m_Spritesheet[animation];
		ani.SetCallback([&]() { PlayNextAnimation(); });
		m_Animations.push_back(ani);
	}

	void SpritesheetComponent::PlayAnimation(const tstring & animation)
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.pop_front();
		}
		auto ani = m_Spritesheet[animation];
		ani.SetCallback([&]() { PlayNextAnimation(); });
		m_Animations.push_front(ani);
	}

	void SpritesheetComponent::PlayNextAnimation()
	{
		if(m_Animations.size() > 1)
		{
			m_Animations.pop_front();
			m_Animations.front().Replay();
		}
#ifdef _DEBUG
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning, _T("Tried to go to next sprite animation while there is only one or none."));
		}
#endif
	}

	void SpritesheetComponent::Reset()
	{
		m_Animations.clear();
	}
	
	void SpritesheetComponent::SetSpritesheet(const tstring & spritesheet)
	{
		m_SpritesheetName = spritesheet;
		m_Spritesheet = SpriteAnimationManager::GetInstance()->GetSpritesheet(m_SpritesheetName);
		Reset();
		PlayAnimation(m_Spritesheet.GetDefaultAnimation());
	}

	tstring SpritesheetComponent::GetCurrentAnimation() const
	{
		if(m_Animations.size() > 0)
		{
			return m_Animations.front().GetName();
		}
		return EMPTY_STRING;
	}

	const tstring & SpritesheetComponent::GetcurrentSpritesheet() const
	{
		return m_SpritesheetName;
	}

	void SpritesheetComponent::InitializeComponent()
	{
		SetSpritesheet(m_SpritesheetName);

		SpriteComponent::InitializeComponent();
	}
}
