#pragma once

#include "../defines.h"

#ifdef DESKTOP
#include "SDL.h"
#include "SDL_mixer.h"
#else
#include "android_native_app_glue.h"
#include  <SLES/OpenSLES.h>
#include  <SLES/OpenSLES_Android.h>
#include  <SLES/OpenSLES_AndroidConfiguration.h>
#endif

#include "SoundFile.h"
#include "SoundEffect.h"
#include <map>
#include <vector>

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

		//You can load sounds at runtime but for ensuring smooth play preload with LoadMusic
		//For looptimes : -1 repeat forever, 0 play once 
		//Volume default 1, range 0 to 1
		//This will interrupt the background playing queue
		//For multiple music tracks at the same time, load them as sound effects
		void PlaySoundFile(const tstring& path, const tstring& name, int loopTimes=0, float volume=1);

		//For looptimes : -1 repeat forever, 0 play once 
		//Volume default 1, range 0 to 1
		//This will interrupt the background playing queue
		//For multiple music tracks at the same time, load them as sound effects
		void PlaySoundFile(const tstring& name, int loopTimes=0, float volume=1);

		//You can load sound effects at runtime but for ensuring smooth play preload with LoadEffect
		//For looptimes : -1 repeat forever, 0 play once 
		//Volume default 1, range 0 to 1
		void PlaySoundEffect(const tstring& path, const tstring& name, int loopTimes=0, float volume=1);

		//For looptimes : -1 repeat forever, 0 play once 
		//Volume default 1, range 0 to 1
		void PlaySoundEffect(const tstring& name, int loopTimes=0, float volume=1);

		void AddToBackgroundQueue(const tstring& name);

		//This will interrupt the any music that is playing
		//excluding the sound effects
		//For multiple music tracks at the same time, load them as sound effects
		void PlayBackgroundQueue();
		void PlayNextSongInQueue();

		//This sets the volume of the music track that is playing
		//Min volume is 0, max volume is 1, anything above will be capped to 1
		void SetMusicVolume(const tstring& name, float volume);
		float	 GetMusicVolume(const tstring& name);

		//This sets the volume of the music track that is playing
		//Min volume is 0, max volume is 128, anything above will be capped to 128
		void SetEffectVolume(const tstring& name, float volume);
		float	 GetEffectVolume(const tstring& name);

		void StopSound(const tstring& name);
		void StopAllSound();
		void PauseAllSound();
		void ResumeAllSound();
		void DeleteAllSound();
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
