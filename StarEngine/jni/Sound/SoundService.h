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
		void PlaySoundFile(const tstring& path, const tstring& name, int loopTimes=0);
		//For looptimes : -1 repeat forever, 0 play once 
		void PlaySoundFile(const tstring& name, int loopTimes=0);

		//You can load sounds at runtime but for ensuring smooth play preload with LoadMusic
		void PlaySoundEffect(const tstring& path, const tstring& name);
		void PlaySoundEffect(const tstring& name);

		void AddToBackgroundQueue(const tstring& name);
		void PlayBackgroundQueue();
		void PlayNextSongInQueue();

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
#endif
		SoundService(const SoundService& yRef);
		SoundService(SoundService&& yRef);
		SoundService& operator=(const SoundService& yRef);
	};
}
