#pragma once

#include "BaseSound.h"

#include <map>

namespace star
{
	class SoundFile final : public BaseSound
	{
	public:
		SoundFile(const tstring& path);
		~SoundFile();

		void Play(int32 looptimes = 0);
		void PlayQueued(int32 looptimes = 0);
		void Stop();
		void Pause();
		void Resume();

#ifdef ANDROID
		void SetVolume(float volume);
#endif
		float GetVolume() const;

		void SetMuted(bool muted);
		bool IsMuted() const;

	protected:
#ifdef DESKTOP
		void SetSoundVolume(int volume);
		static void MusicStoppedCallback();
#else
		void CreateSoundDetails();
		void RegisterCallback(SLPlayItf & player);

		static void MusicStoppedCallback(
			SLPlayItf caller,
			void *pContext,
			SLuint32 event
			);
#endif

	private:
		int32 mLoopTimes;
		bool mbQueuedPlay;
#ifdef ANDROID
		SLObjectItf mPlayerObj;
		SLPlayItf mPlayer;
		SLSeekItf mPlayerSeek;
#else
		Mix_Music * mpSound;
#endif

		SoundFile(const SoundFile& yRef);
		SoundFile(SoundFile&& yRef);
		SoundFile& operator=(const SoundFile& yRef);
		SoundFile& operator=(SoundFile&& yRef);
	};
}
