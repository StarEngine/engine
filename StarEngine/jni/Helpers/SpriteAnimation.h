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
			float32 speed, int32 repeat, const tstring & frames, 
			int32 frames_x, int32 frames_y, int32 amount);
		SpriteAnimation(const SpriteAnimation &);
		SpriteAnimation(SpriteAnimation &&);
		~SpriteAnimation();

		SpriteAnimation & operator=(const SpriteAnimation &);
		SpriteAnimation & operator=(SpriteAnimation &&);

		void Update(const Context & context);
		vec4 GetCurrentUV() const;

		void Play();
		void PlayAtFrame(int32 startFrame);
		void Replay();
		void Pause();
		void Stop();

		const tstring & GetName() const;
		bool IsPlaying() const;

		void SetCallback(const std::function<void()> & callback);

		int32 GetCurrentFrame() const;

	private:
		void ParseFrameString(tstring frames, int32 frames_x, int32 frames_y, int32 amount);
		void ParseFrames(const tstring & frame, int32 frames_x, int32 frames_y, int32 amount);
		void ParseFrame(int32 frame, int32 frames_x, int32 frames_y, int32 amount);

		tstring m_Name;
		float32 m_Speed, m_CurrentFrame;
		int32 m_Repeat;
		int32 m_CurrentRepeats;
		vec2 m_UVScale;

		std::function<void()> m_Callback;

		std::vector<vec2> m_Frames;
		bool m_IsPlaying;
	};
}
