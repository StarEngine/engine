#include "SpriteSheetComponent.h"
#include "../../Graphics/SpriteAnimationManager.h"
#include "../../Objects/Object.h"
#include "TextComponent.h"

namespace star
{
	SpriteSheetComponent::SpriteSheetComponent
		(const tstring& filePath, const tstring& spriteName,
			const tstring & spritesheet)
		: SpriteComponent(filePath, spriteName)
		, m_SpritesheetName(spritesheet)
		, m_Spritesheet()
		, m_Animations(0)
	{

	}

	SpriteSheetComponent::~SpriteSheetComponent()
	{
		m_Animations.clear();
	}

	void SpriteSheetComponent::Update(const Context& context)
	{
		if(m_Animations.size() > 0
			&& m_Animations.front().IsPlaying())
		{
			m_Animations.front().Update(context);
			auto uvInfo = m_Animations.front().GetCurrentUV();

			SetUVCoords(uvInfo);
		}
		SpriteComponent::Update(context);
	}

	void SpriteSheetComponent::Play()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Play();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpriteSheetComponent::Restart: There is no animation."),
				STARENGINE_LOG_TAG);
		}
	}

	void SpriteSheetComponent::Restart()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Replay();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpriteSheetComponent::Restart: There is no animation."),
				STARENGINE_LOG_TAG);
		}
	}

	void SpriteSheetComponent::Pause()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Pause();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpriteSheetComponent::Pause: There is no animation."),
				STARENGINE_LOG_TAG);
		}
	}

	void SpriteSheetComponent::Stop()
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.front().Stop();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpriteSheetComponent::Stop: There is no animation."),
				STARENGINE_LOG_TAG);
		}
	}

	void SpriteSheetComponent::PushAnimation(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		auto it = m_Spritesheet.find(animation);
		if(it != m_Spritesheet.end())
		{
			PushAnimationUnSafe(animation, callback);
			return;
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("SpriteSheetComponent::PushAnimation: Couldn't find animation '")
			+ animation + _T("'."), STARENGINE_LOG_TAG);
	}

	void SpriteSheetComponent::PlayAnimation(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		auto it = m_Spritesheet.find(animation);
		if(it != m_Spritesheet.end())
		{
			PlayAnimationUnSafe(animation, callback);
			return;
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("SpriteSheetComponent::PlayAnimation: Couldn't find animation '")
			+ animation + _T("'."), STARENGINE_LOG_TAG);
	}

	void SpriteSheetComponent::PlayAnimation(
		const tstring & animation,
		int32 startFrame,
		const std::function<void()> & callback
		)
	{
		auto it = m_Spritesheet.find(animation);
		if(it != m_Spritesheet.end())
		{
			PlayAnimationUnSafe(animation, startFrame, callback);
			return;
		}
		Logger::GetInstance()->Log(LogLevel::Warning,
			_T("SpriteSheetComponent::PlayAnimation: Couldn't find animation '")
			+ animation + _T("'."), STARENGINE_LOG_TAG);
	}

	void SpriteSheetComponent::PushAnimationUnSafe(
		const tstring & animation,
		const std::function<void()> & callback
		)
	{
		auto ani = m_Spritesheet[animation];
		ani.SetCallback([&]() { PlayNextAnimation(); });
		ani.SetUserCallback(callback);
		m_Animations.push_back(ani);
	}

	void SpriteSheetComponent::PlayAnimationUnSafe(
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

	void SpriteSheetComponent::PlayAnimationUnSafe(
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

	void SpriteSheetComponent::PlayNextAnimation()
	{
		if(m_Animations.size() > 1)
		{
			m_Animations.pop_front();
			m_Animations.front().Replay();
		}
	}

	void SpriteSheetComponent::PlayNextAnimation(int32 startFrame)
	{
		if(m_Animations.size() > 1)
		{
			m_Animations.pop_front();
			m_Animations.front().PlayAtFrame(startFrame);
		}
	}

	void SpriteSheetComponent::Reset()
	{
		m_Animations.clear();
	}
	
	void SpriteSheetComponent::SetSpritesheet(const tstring & spritesheet)
	{
		m_SpritesheetName = spritesheet;
		m_Spritesheet = SpriteAnimationManager::GetInstance()->GetSpritesheet(m_SpritesheetName);
		Reset();
		PlayAnimation(m_Spritesheet.GetDefaultAnimation());
	}

	const tstring & SpriteSheetComponent::GetCurrentAnimation() const
	{
		if(m_Animations.size() > 0)
		{
			return m_Animations.front().GetName();
		}
		return EMPTY_STRING;
	}

	int32 SpriteSheetComponent::GetCurrentFrame() const
	{
		return m_Animations.size() > 0 ? 
					m_Animations.front().GetCurrentFrame() : 0;
	}

	const tstring & SpriteSheetComponent::GetCurrentSpritesheet() const
	{
		return m_SpritesheetName;
	}

	int32 SpriteSheetComponent::GetFramesHorizontal() const
	{
		int32 nrOfFrames = m_Spritesheet.GetFramesHorizontal();
		if(nrOfFrames == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("GetFramesHorizontal() -- nrOfFrames = 0!"), STARENGINE_LOG_TAG);
		}
		return nrOfFrames;
	}

	int32 SpriteSheetComponent::GetFramesVertical() const
	{
		int32 nrOfFrames = m_Spritesheet.GetFramesVertical();
		if(nrOfFrames == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("GetFramesVertical() -- nrOfFrames = 0!"), STARENGINE_LOG_TAG);
		}
		return nrOfFrames;
	}

	void SpriteSheetComponent::InitializeComponent()
	{
		if(m_pParentObject->HasComponent<SpriteComponent>(this)
			|| m_pParentObject->HasComponent<TextComponent>(this))
		{
			Logger::GetInstance()->Log(false,
				_T("Object '") + m_pParentObject->GetName() +
				_T("': Can't add a SpriteSheetComponent when \
already having a Sprite- or TextComponent."));
			m_pParentObject->RemoveComponent(this);
		}
		else
		{
			SetSpritesheet(m_SpritesheetName);
			SpriteComponent::InitializeComponent();

			m_WidthSegments = GetFramesHorizontal();
			m_HeightSegments = GetFramesVertical();
			m_Dimensions.x /= m_WidthSegments;
			m_Dimensions.y /= m_HeightSegments;
			GetTransform()->SetDimensionsSafe(m_Dimensions);

			CreateUVCoords();
			FillSpriteInfo();
		}
	}


	void SpriteSheetComponent::SetCallbackAnimations( const std::function<void()> & callback )
	{
		for(auto it : m_Animations)
		{
			it.SetCallback(callback);
		}
	}

	bool SpriteSheetComponent::IsPlaying()
	{
		return m_Animations.front().IsPlaying();
	}
}
