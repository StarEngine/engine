#pragma once

#include "BaseSound.h"
#include "SoundFile.h"
#include "SoundEffect.h"
#include <vector>
#include <map>

namespace star
{

	class SoundService
	{
	public:
		static SoundService * GetInstance();
		~SoundService();
		void Start();
		void Stop();

		void LoadMusic(const tstring& path, const tstring& name, uint8 channel = 0);
		void LoadSoundEffect(const tstring& path, const tstring& name, uint8 channel = 0);

		void PlayMusic(const tstring& path,
			const tstring& name,
			uint8 channel = 0,
			int loopTimes = 0,
			float volume = 1.0f
			);

		void PlayMusic(const tstring& name,
			int loopTimes = 0,
			float volume = 1.0f
			);

		void PlaySoundEffect(
			const tstring& path,
			const tstring& name,
			uint8 channel = 0,
			int loopTimes = 0,
			float volume = 1
			);

		void PlaySoundEffect(
			const tstring& name,
			int loopTimes = 0.0f,
			float volume = 1.0f
			);

		void AddToBackgroundQueue(const tstring& name);

		void PlayBackgroundQueue();
		void PlayNextSongInQueue();

		void SetMusicVolume(const tstring& name, float volume);
		float GetMusicVolume(const tstring& name) const;

		void SetEffectVolume(const tstring& name, float volume);
		float GetEffectVolume(const tstring& name) const;

		void IncreaseMusicVolume(const tstring& name, float volume);
		void DecreaseMusicVolume(const tstring& name, float volume);

		void IncreaseEffectVolume(const tstring& name, float volume);
		void DecreaseEffectVolume(const tstring& name, float volume);

		void SetMusicMuted(const tstring& name, bool muted);
		bool IsMusicMuted(const tstring& name) const;

		void SetEffectMuted(const tstring& name, bool muted);
		bool IsEffectMuted(const tstring& name) const;

		void AddSoundToChannel(uint8 channel, BaseSound * pSound);
		void RemoveSoundFromChannel(uint8 channel, BaseSound * pSound);

		void SetChannelVolume(uint8 channel, float volume);
		float GetChannelVolume(uint8 channel);

		void IncreaseChannelVolume(uint8 channel, float volume);
		void DecreaseChannelVolume(uint8 channel, float volume);

		void SetChannelMuted(uint8 channel, bool muted);
		bool IsChannelMuted(uint8 channel);

		void SetMusicChannel(const tstring & name, uint8 channel);
		void UnsetMusicChannel(const tstring & name);

		void SetEffectChannel(const tstring & name, uint8 channel);
		void UnsetEffectChannel(const tstring & name);

		void StopSound(const tstring& name);
		void StopAllSounds();
		void PauseAllSounds();
		void ResumeAllSounds();
		void DeleteAllSounds();

		void SetVolume(float volume);
		float GetVolume() const;

		void IncreaseVolume(float volume);
		void DecreaseVolume(float volume);

#ifdef ANDROID
		const SLEngineItf& GetEngine() const;
		const SLObjectItf& GetOutputMixObject() const;
#endif

	private:
		struct SoundChannel
		{
			float mVolume;
			bool mIsMuted;
			std::vector<BaseSound*> mSounds;
			uint8 mChannel;

			SoundChannel();
			~SoundChannel();

			void SetVolume(float volume);
			float GetVolume() const;

			void IncreaseVolume(float volume);
			void DecreaseVolume(float volume);

			void SetMuted(bool muted);
			bool IsMuted() const;
		};

		SoundService();
		SoundChannel & GetChannel(uint8 channel, const tstring & sender,
			bool & result);

		static SoundService * mSoundService;
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

		float mVolume;

#ifdef ANDROID
		SLObjectItf mEngineObj;
		SLEngineItf mEngine;
		SLObjectItf mOutputMixObj;
		SLVolumeItf mOutputMixVolume;
#endif
		SoundService(const SoundService& yRef);
		SoundService(SoundService&& yRef);
		SoundService& operator=(const SoundService& yRef);
		SoundService& operator=(SoundService&& yRef);
	};
}
