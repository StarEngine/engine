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
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("SpritesheetComponent::Restart: There is no animation."));
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
				_T("SpritesheetComponent::Restart: There is no animation."));
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
				_T("SpritesheetComponent::Pause: There is no animation."));
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
				_T("SpritesheetComponent::Stop: There is no animation."));
		}
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

	void SpritesheetComponent::PlayAnimation(const tstring & animation, int32 startFrame)
	{
		if(m_Animations.size() > 0)
		{
			m_Animations.pop_front();
		}
		auto ani = m_Spritesheet[animation];
		ani.SetCallback([&]() { PlayNextAnimation(); });
		m_Animations.push_front(ani);
		m_Animations.front().PlayAtFrame(startFrame);

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
			Logger::GetInstance()->Log(LogLevel::Warning, _T("GetFramesHorizontal() -- nrOfFrames = 0!"));
		}
		return nrOfFrames;
	}

	int32 SpritesheetComponent::GetFramesVertical() const
	{
		int32 nrOfFrames = m_Spritesheet.GetFramesVertical();
		if(nrOfFrames == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Warning, _T("GetFramesVertical() -- nrOfFrames = 0!"));
		}
		return nrOfFrames;
	}

	int32 SpritesheetComponent::GetWidth() const
	{
		return int32(m_Width);
	}

	int32 SpritesheetComponent::GetHeight() const
	{
		return int32(m_Heigth);
	}

	void SpritesheetComponent::InitializeComponent()
	{
		SetSpritesheet(m_SpritesheetName);
		SpriteComponent::InitializeComponent();
		m_Width /= GetFramesHorizontal();
		m_Heigth /= GetFramesVertical();
	}

	void SpritesheetComponent::CreateVertices()
	{
		m_Vertices[0] = (GLfloat)m_Width / GetFramesHorizontal();
		m_Vertices[1] = (GLfloat)m_Heigth / GetFramesVertical();
		m_Vertices[2] = 0;
		m_Vertices[3] = (GLfloat)m_Width / GetFramesHorizontal();
		m_Vertices[4] = 0;
		m_Vertices[5] = 0;
		m_Vertices[6] = 0;
		m_Vertices[7] = (GLfloat)m_Heigth / GetFramesVertical();
		m_Vertices[8] = 0;
		m_Vertices[9] = 0;
		m_Vertices[10] = 0;
		m_Vertices[11] = 0;
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
