#include "SpritesheetComponent.h"
#include "../../Graphics/SpriteAnimationManager.h"
#include "../../Logger.h"

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
		m_Animations.clear();
	}

	void SpritesheetComponent::Update(const Context& context)
	{
		if(m_Animations.size() > 0
			&& m_Animations.front().IsPlaying())
		{
			m_Animations.front().Update(context);
			auto uvInfo = m_Animations.front().GetCurrentUV();

			/*
			*  TL    TR
			*   0----1 
			*   |   /| 
			*   |  / |
			*   | /  |
			*   |/   |
			*   2----3
			*  BL    BR
			*/

			SetUVCoords(uvInfo);
		}
		SpriteComponent::Update(context);
	}

	void SpritesheetComponent::Play()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Play();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpritesheetComponent::Restart: There is no animation."),
				STARENGINE_LOG_TAG);
		}
	}

	void SpritesheetComponent::Restart()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Replay();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpritesheetComponent::Restart: There is no animation."),
				STARENGINE_LOG_TAG);
		}
	}

	void SpritesheetComponent::Pause()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Pause();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpritesheetComponent::Pause: There is no animation."),
				STARENGINE_LOG_TAG);
		}
	}

	void SpritesheetComponent::Stop()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Stop();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpritesheetComponent::Stop: There is no animation."),
				STARENGINE_LOG_TAG);
		}
	}

	void SpritesheetComponent::PushAnimation(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		auto ani = m_Spritesheet[animation];
		ani.SetCallback([&]() { PlayNextAnimation(); });
		ani.SetUserCallback(callback);
		m_Animations.push_back(ani);
	}

	void SpritesheetComponent::PlayAnimation(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.pop_front();
		}
		auto ani = m_Spritesheet[animation];
		ani.SetCallback([&]() { PlayNextAnimation(); });
		ani.SetUserCallback(callback);
		m_Animations.push_front(ani);
	}

	void SpritesheetComponent::PlayAnimation(
		const tstring & animation,
		int32 startFrame,
		const std::function<void()> & callback
		)
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.pop_front();
		}
		auto ani = m_Spritesheet[animation];
		ani.SetCallback([&]() { PlayNextAnimation(); });
		ani.SetUserCallback(callback);
		m_Animations.push_front(ani);
		m_Animations.front().PlayAtFrame(startFrame);

	}

	bool SpritesheetComponent::PushAnimationSafe(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		auto it = m_Spritesheet.find(animation);
		if(it != m_Spritesheet.end())
		{
			PushAnimation(animation, callback);
			return true;
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("SpritesheetComponent::PushAnimationSafe: Couldn't find animation '")
			+ animation + _T("'."), STARENGINE_LOG_TAG);
		return false;
	}

	bool SpritesheetComponent::PlayAnimationSafe(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		auto it = m_Spritesheet.find(animation);
		if(it != m_Spritesheet.end())
		{
			PlayAnimation(animation, callback);
			return true;
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("SpritesheetComponent::PlayAnimationSafe: Couldn't find animation '")
			+ animation + _T("'."), STARENGINE_LOG_TAG);
		return false;
	}

	bool SpritesheetComponent::PlayAnimationSafe(
		const tstring & animation,
		int32 startFrame,
		const std::function<void()> & callback
		)
	{
		auto it = m_Spritesheet.find(animation);
		if(it != m_Spritesheet.end())
		{
			PlayAnimation(animation, startFrame, callback);
			return true;
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("SpritesheetComponent::PlayAnimationSafe: Couldn't find animation '")
			+ animation + _T("'."), STARENGINE_LOG_TAG);
		return false;
	}

	void SpritesheetComponent::PlayNextAnimation()
	{
		if(m_Animations.size() > 1)
		{
			m_Animations.pop_front();
			m_Animations.front().Replay();
		}
	}

	void SpritesheetComponent::PlayNextAnimation(int32 startFrame)
	{
		if(m_Animations.size() > 1)
		{
			m_Animations.pop_front();
			m_Animations.front().PlayAtFrame(startFrame);
		}
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

	int32 SpritesheetComponent::GetCurrentFrame() const
	{
		return m_Animations.size() > 0 ? 
					m_Animations.front().GetCurrentFrame() : 0;
	}

	const tstring & SpritesheetComponent::GetcurrentSpritesheet() const
	{
		return m_SpritesheetName;
	}

	int32 SpritesheetComponent::GetFramesHorizontal() const
	{
		int32 nrOfFrames = m_Spritesheet.GetFramesHorizontal();
		if(nrOfFrames == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("GetFramesHorizontal() -- nrOfFrames = 0!"), STARENGINE_LOG_TAG);
		}
		return nrOfFrames;
	}

	int32 SpritesheetComponent::GetFramesVertical() const
	{
		int32 nrOfFrames = m_Spritesheet.GetFramesVertical();
		if(nrOfFrames == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("GetFramesVertical() -- nrOfFrames = 0!"), STARENGINE_LOG_TAG);
		}
		return nrOfFrames;
	}

	int32 SpritesheetComponent::GetWidth() const
	{
		return int32(m_Width);
	}

	int32 SpritesheetComponent::GetHeight() const
	{
		return int32(m_Height);
	}

	void SpritesheetComponent::InitializeComponent()
	{
		SetSpritesheet(m_SpritesheetName);
		SpriteComponent::InitializeComponent();
		m_Width /= GetFramesHorizontal();
		m_Height /= GetFramesVertical();
	}

	void SpritesheetComponent::CreateVertices()
	{
		//0
		m_Vertices[1] = float32(m_Height / GetFramesVertical());

		//1
		m_Vertices[3] = float32(m_Width / GetFramesHorizontal());
		m_Vertices[4] = float32(m_Height / GetFramesVertical());

		//2

		//3
		m_Vertices[9] = float32(m_Width / GetFramesHorizontal());
	}

	void SpritesheetComponent::SetCallbackAnimations( const std::function<void()> & callback )
	{
		for(auto it : m_Animations)
		{
			it.SetCallback(callback);
		}
	}

	bool SpritesheetComponent::IsPlaying()
	{
		return m_Animations.front().IsPlaying();
	}


}
