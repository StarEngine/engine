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

		void LoadMusic(const tstring& path, const tstring& name);
		void LoadSoundEffect(const tstring& path, const tstring& name);

		void PlayMusic(const tstring& path,
			const tstring& name,
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
		SoundService();

		static SoundService * mSoundService;
		static bool mbIsInitialized;

		std::map<tstring,SoundFile*> mMusicList;
		std::map<tstring,tstring> mMusicPathList;
		std::map<tstring,SoundEffect*> mEffectsList;
		std::map<tstring,tstring> mSoundEffectPathList;
		std::vector<SoundFile*> mBackgroundQueue;
		std::vector<SoundFile*>::iterator mQueueIterator;

		SoundFile* m_CurrentSoundFile;
		SoundEffect* m_CurrentSoundEffect;

		float m_Volume;

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
