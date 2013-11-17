#pragma once

#include "BaseSound.h"

namespace star
{
	const int MAX_SAMPLES = 10;

	class SoundEffect final : public BaseSound
	{
	public:
		SoundEffect(const tstring& path);
		~SoundEffect();

		void Play(int loopTime = 0);
		void Stop();
		void Pause();
		void Resume();

	#ifdef ANDROID
		void SetVolume(float volume);
	#endif
		float GetVolume() const;

	private:
#ifdef DESKTOP
		void SetSoundVolume(int volume);

		static int PLAY_CHANNELS;
		int mPlayChannel;
		Mix_Chunk * mpSound;
#else
		void RegisterCallback(SLPlayItf & player);

		static void MusicStoppedCallback(
			SLPlayItf caller,
			void *pContext,
			SLuint32 event
			);

		std::vector<SLObjectItf> mPlayerObjs;
		std::vector<SLPlayItf> mPlayers;
#endif		

		SoundEffect(const SoundEffect& yRef);
		SoundEffect(SoundEffect&& yRef);
		SoundEffect& operator=(const SoundEffect& yRef);
		SoundEffect& operator=(SoundEffect&& yRef);
	};
}
