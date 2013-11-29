#pragma once

#include "BaseSound.h"
#include "SoundFile.h"
#include "SoundEffect.h"
#include <vector>
#include <map>

namespace star
{

	class AudioManager
	{
	public:
		static AudioManager * GetInstance();
		~AudioManager();
		void Start();
		void Stop();

		void LoadMusic(
			const tstring& path,
			const tstring& name,
			uint8 channel = 0
			);
		void LoadSoundEffect(
			const tstring& path,
			const tstring& name,
			uint8 channel = 0
			);

		void LoadMusic(
			const tstring& path,
			const tstring& name,
			float32 volume,
			uint8 channel = 0
			);
		void LoadSoundEffect(
			const tstring& path,
			const tstring& name,
			float32 volume,
			uint8 channel = 0
			);

		void PlayMusic(
			const tstring& path,
			const tstring& name,
			uint8 channel = 0,
			int32 loopTimes = 0
			);
		void PlayMusic(
			const tstring& name,
			int32 loopTimes = 0
			);
		void PlaySoundEffect(
			const tstring& path,
			const tstring& name,
			uint8 channel = 0,
			int32 loopTimes = 0
			);
		void PlaySoundEffect(
			const tstring& name,
			int32 loopTimes = 0.0f
			);

		void PlayMusic(
			const tstring& path,
			const tstring& name,
			float32 volume,
			uint8 channel = 0,
			int32 loopTimes = 0
			);
		void PlayMusic(
			const tstring& name,
			float32 volume,
			int32 loopTimes = 0
			);
		void PlaySoundEffect(
			const tstring& path,
			const tstring& name,
			float32 volume,
			uint8 channel = 0,
			int32 loopTimes = 0
			);
		void PlaySoundEffect(
			const tstring& name,
			float32 volume,
			int32 loopTimes = 0.0f
			);

		void AddToBackgroundQueue(const tstring& name);

		void PlayBackgroundQueue();
		void PlayNextSongInQueue();

		void PauseMusic(const tstring & name);
		void ResumeMusic(const tstring & name);
		void StopMusic(const tstring & name);

		bool IsMusicPaused(const tstring & name) const;
		bool IsMusicStopped(const tstring & name) const;
		bool IsMusicPlaying(const tstring & name) const;
		bool IsMusicLooping(const tstring & name) const;

		void PauseEffect(const tstring & name);
		void ResumeEffect(const tstring & name);
		void StopEffect(const tstring & name);

		bool IsEffectPaused(const tstring & name) const;
		bool IsEffectStopped(const tstring & name) const;
		bool IsEffectPlaying(const tstring & name) const;
		bool IsEffectLooping(const tstring & name) const;

		void SetMusicVolume(const tstring& name, float32 volume);
		float32 GetMusicVolume(const tstring& name) const;

		void SetEffectVolume(const tstring& name, float32 volume);
		float32 GetEffectVolume(const tstring& name) const;

		void IncreaseMusicVolume(const tstring& name, float32 volume);
		void DecreaseMusicVolume(const tstring& name, float32 volume);

		void IncreaseEffectVolume(const tstring& name, float32 volume);
		void DecreaseEffectVolume(const tstring& name, float32 volume);

		void MuteAllMusic(bool mute);
		void SetMusicMuted(const tstring& name, bool muted);
		bool IsMusicMuted(const tstring& name) const;

		void MuteAllSoundEffects(bool mute);
		void SetEffectMuted(const tstring& name, bool muted);
		bool IsEffectMuted(const tstring& name) const;

		bool ToggleMusicMuted(const tstring& name);
		bool ToggleEffectMuted(const tstring& name);

		void AddSoundToChannel(uint8 channel, BaseSound * pSound);
		void RemoveSoundFromChannel(uint8 channel, BaseSound * pSound);

		void SetChannelVolume(uint8 channel, float32 volume);
		float32 GetChannelVolume(uint8 channel);

		void IncreaseChannelVolume(uint8 channel, float32 volume);
		void DecreaseChannelVolume(uint8 channel, float32 volume);

		void SetChannelMuted(uint8 channel, bool muted);
		bool IsChannelMuted(uint8 channel);
		bool ToggleChannelMuted(uint8 channel);

		void SetMusicChannel(const tstring & name, uint8 channel);
		void UnsetMusicChannel(const tstring & name);

		void SetEffectChannel(const tstring & name, uint8 channel);
		void UnsetEffectChannel(const tstring & name);

		void PauseChannel(uint8 channel);
		bool IsChannelPaused(uint8 channel);
		
		void ResumeChannel(uint8 channel);
		bool IsChannelPlaying(uint8 channel);

		void StopChannel(uint8 channel);
		bool IsChannelStopped(uint8 channel);

		void PlayChannel(uint8 channel, int32 loopTimes = 0);

		void StopAllSounds();
		void PauseAllSounds();
		void ResumeAllSounds();
		void DeleteAllSounds();

		void SetVolume(float32 volume);
		float32 GetVolume() const;

		void IncreaseVolume(float32 volume);
		void DecreaseVolume(float32 volume);

#ifdef ANDROID
		const SLEngineItf& GetEngine() const;
		const SLObjectItf& GetOutputMixObject() const;
#endif

	private:
		enum class ChannelState : byte
		{
			paused = 0,
			playing,
			stopped
		};

		struct SoundChannel
		{
			float32 mVolume;
			bool mIsMuted;
			std::vector<BaseSound*> mSounds;
			uint8 mChannel;
			ChannelState mState;

			SoundChannel();
			~SoundChannel();

			void SetVolume(float32 volume);
			float32 GetVolume() const;

			void IncreaseVolume(float32 volume);
			void DecreaseVolume(float32 volume);

			void SetMuted(bool muted);
			bool IsMuted() const;
		};

		AudioManager();
		SoundChannel & GetChannel(uint8 channel, const tstring & sender,
			bool & result);

		static AudioManager * mSoundService;
		static bool mbIsInitialized;

		std::map<tstring,SoundFile*> mMusicList;
		std::map<tstring,tstring> mMusicPathList;
		std::map<tstring,SoundEffect*> mEffectsList;
		std::map<tstring,tstring> mSoundEffectPathList;
		std::vector<SoundFile*> mBackgroundQueue;
		std::vector<SoundFile*>::iterator mQueueIterator;
		std::map<uint8, SoundChannel> mChannels;
		SoundChannel mEmptyChannel;

		SoundFile* mCurrentSoundFile;
		SoundEffect* mCurrentSoundEffect;

		float32 mVolume;

		bool mbMusicMuted,mbSoundEffectsMuted;

#ifdef ANDROID
		SLObjectItf mEngineObj;
		SLEngineItf mEngine;
		SLObjectItf mOutputMixObj;
		SLVolumeItf mOutputMixVolume;
#endif
		AudioManager(const AudioManager& yRef);
		AudioManager(AudioManager&& yRef);
		AudioManager& operator=(const AudioManager& yRef);
		AudioManager& operator=(AudioManager&& yRef);
	};
}
