#pragma once

#include "../defines.h"
#include <vector>
#include <functional>

namespace star
{
	struct Context;

	class SpriteAnimation final
	{
	public:
		SpriteAnimation();
		SpriteAnimation(const tstring & name, const vec2 & uv_scale, 
			float speed, int repeat, const tstring & frames, 
			int frames_x, int frames_y, int amount);
		SpriteAnimation(const SpriteAnimation &);
		~SpriteAnimation();

		SpriteAnimation & operator=(const SpriteAnimation &);

		void Update(const Context & context);
		vec4 GetCurrentUV() const;

		void Play();
		void PlayAtFrame(int startFrame);
		void Replay();
		void Pause();
		void Stop();

		const tstring & GetName() const;
		bool IsPlaying() const;

		void SetCallback(const std::function<void()> & callback);

		int GetCurrentFrame() const;

	private:
		void ParseFrameString(tstring frames, int frames_x, int frames_y, int amount);
		void ParseFrames(const tstring & frame, int frames_x, int frames_y, int amount);
		void ParseFrame(int frame, int frames_x, int frames_y, int amount);

		tstring m_Name;
		float m_Speed, m_CurrentFrame;
		int m_Repeat;
		int m_CurrentRepeats;
		vec2 m_UVScale;

		std::function<void()> m_Callback;

		std::vector<vec2> m_Frames;
		bool m_IsPlaying;
	};
}
