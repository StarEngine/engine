#include "SpriteAnimation.h"
#include "../Context.h"
#include "../Helpers/Helpers.h"

namespace star
{
	SpriteAnimation::SpriteAnimation(
		const tstring & name, const vec2 & uv_scale, float speed,
		int repeat, const tstring & frames, int frames_x, int amount)
		: m_Name(name)
		, m_Speed(speed)
		, m_CurrentFrame(0)
		, m_Repeat(repeat)
		, m_UVScale(uv_scale)
		, m_Frames()
		, m_IsPlaying(false)
	{
		ParseFrameString(frames, frames_x, amount);
	}
	
	SpriteAnimation::SpriteAnimation(const SpriteAnimation & yRef)
		: m_Name(yRef.m_Name)
		, m_Speed(yRef.m_Speed)
		, m_CurrentFrame(yRef.m_CurrentFrame)
		, m_Repeat(yRef.m_Repeat)
		, m_UVScale(yRef.m_UVScale)
		, m_Frames(yRef.m_Frames)
		, m_IsPlaying(yRef.m_IsPlaying)
	{
	}

	SpriteAnimation::~SpriteAnimation()
	{
		m_Frames.clear();
	}

	SpriteAnimation & SpriteAnimation::operator=(const SpriteAnimation & yRef)
	{
		m_Name = yRef.m_Name;
		m_Speed = yRef.m_Speed;
		m_CurrentFrame = yRef.m_CurrentFrame;
		m_Repeat = yRef.m_Repeat;
		m_UVScale = yRef.m_UVScale;
		m_Frames = yRef.m_Frames;
		m_IsPlaying = yRef.m_IsPlaying;

		return *this;
	}

	void SpriteAnimation::Update(const Context & context)
	{
		if(m_IsPlaying)
		{
			m_CurrentFrame += (float)context.mTimeManager->GetSeconds() * m_Speed;
			float size = (float)m_Frames.size();
			if(m_CurrentFrame > size)
			{
				m_CurrentFrame -= size;
			}
		}
	}

	vec4 SpriteAnimation::GetCurrentUV() const
	{
		vec4 uv;
		int currentFrame = (int)m_CurrentFrame;
		
		// UV Scale
		uv.z = m_UVScale.x;
		uv.w = m_UVScale.y;
		
		// UV Offset
		uv.x = m_Frames[currentFrame].x;
		uv.y = m_Frames[currentFrame].y;

		return uv;
	}

	void SpriteAnimation::Play()
	{
		m_IsPlaying = true;
	}

	void SpriteAnimation::Pause()
	{
		m_IsPlaying = false;
	}

	void SpriteAnimation::Stop()
	{
		m_IsPlaying = false;
		m_CurrentFrame = 0;
	}

	const tstring & SpriteAnimation::GetName() const
	{
		return m_Name;
	}
	
	bool SpriteAnimation::IsPlaying() const
	{
		return m_IsPlaying;
	}
	
	void SpriteAnimation::ParseFrameString(
		tstring frames, int frames_x, int amount)
	{
		tstring::size_type index(tstring::npos);
		tstring frame(EMPTY_STRING);
		do
		{
			index = frames.find(_T(';'));
			if(index == tstring::npos)
			{
				frame = frames;
				ParseFrames(frame, frames_x, amount);
				return;
			}
			else
			{
				frame = frames.substr(0,index);
				frames = frames.substr(0, frames.length() - index - 1);
				ParseFrames(frame, frames_x, amount);
			}
		} while ( 1 );
	}
	
	void SpriteAnimation::ParseFrames(const tstring & frame, 
		int frames_x, int amount)
	{
		auto index = frame.find(_T('-'));
		if(index == tstring::npos)
		{
			int f = string_cast<int>(frame);
			ParseFrame(f, frames_x, amount);
		}
		else
		{
			tstring x = frame.substr(0,index);
			tstring y = frame.substr(0, frame.length() - index - 1);
			int nX = string_cast<int>(x);
			int nY = string_cast<int>(y);
			if(nX < nY)
			{
				for ( ; nX <= nY ; ++nX )
				{
					ParseFrame(nX, frames_x, amount);
				}
			}
			else
			{
				for ( ; nX >= nY ; --nX )
				{
					ParseFrame(nX, frames_x, amount);
				}
			}
		}
	}
	
	void SpriteAnimation::ParseFrame(int frame, int frames_x, int amount)
	{
		ASSERT(frame < amount && frame > -1, _T("Invalid frame index."));
		int x = frame % frames_x;
		int y = frame / frames_x;
		
		vec2 uv;
		uv.x = (float)x * m_UVScale.x;
		uv.y = (float)y * m_UVScale.y;

		m_Frames.push_back(uv);
	}
}
