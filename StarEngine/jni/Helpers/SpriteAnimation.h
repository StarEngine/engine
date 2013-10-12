#pragma once

#include "../defines.h"
#include <vector>

namespace star
{
	struct Context;

	class SpriteAnimation final
	{
	public:
		SpriteAnimation(const tstring & name, const vec2 & uv_scale, 
			float speed, int repeat, const tstring & frames, 
			int frames_x, int amount);
		SpriteAnimation(const SpriteAnimation &);
		~SpriteAnimation();

		SpriteAnimation & operator=(const SpriteAnimation &);

		void Update(const Context & context);
		vec4 GetCurrentUV() const;

		void Play();
		void Pause();
		void Stop();

		const tstring & GetName() const;
		bool IsPlaying() const;

	private:
		void ParseFrameString(tstring frames, int frames_x, int amount);
		void ParseFrames(const tstring & frame, int frames_x, int amount);
		void ParseFrame(int frame, int frames_x, int frames_y);

		tstring m_Name;
		float m_Speed, m_CurrentFrame;
		int m_Repeat;
		vec2 m_UVScale;

		std::vector<vec2> m_Frames;
		bool m_IsPlaying;
	};
}
