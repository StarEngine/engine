#pragma once

#include "BaseSound.h"

#include <map>

namespace star
{
	class SoundFile final : public BaseSound
	{
	public:
		SoundFile(const tstring& path, uint8 channel = 0);
		~SoundFile();

		virtual void Play(int32 looptimes = 0);
		void PlayQueued(int32 looptimes = 0);
		virtual void Stop();
		virtual void Pause();
		virtual void Resume();

		virtual void SetChannel(uint8 channel);
		virtual void UnsetChannel();

#ifdef ANDROID
		void SetVolume(float32 volume);
#endif
		float32 GetVolume() const;

		void SetMuted(bool muted);
		bool IsMuted() const;

	protected:
#ifdef DESKTOP
		void SetSoundVolume(int32 volume);
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
