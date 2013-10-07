#pragma once

#include "../defines.h"

#ifdef _WIN32
#include "SDL.h"
#include "SDL_mixer.h"
#else
#include "android_native_app_glue.h"
#include  <SLES/OpenSLES.h>
#include  <SLES/OpenSLES_Android.h>
#include  <SLES/OpenSLES_AndroidConfiguration.h>
#endif

namespace star
{

	class SoundService
	{
	public:
		static SoundService* GetInstance();
		~SoundService(){}
		status Start();
		void Stop();

		status PlaySoundFile(const tstring& path);
		status PlaySoundEffect(const tstring& path){}

		//For looptimes : -1 repeat forever, 0 play once 
		status PlayBackgroundMusic(const tstring& path, int looptimes = 0) {}

		void StopSound();

	private:
		SoundService();

		static SoundService* mSoundService;
#ifdef _WIN32
		Mix_Music * mMusic;
#else
		SLObjectItf mEngineObj;
		SLEngineItf mEngine;
		SLObjectItf mOutputMixObj;

		SLObjectItf mPlayerObj;
		SLPlayItf mPlayer;
		SLSeekItf mPlayerSeek;
#endif
		SoundService(const SoundService& yRef);
		SoundService(SoundService&& yRef);
		SoundService& operator=(const SoundService& yRef);
	};
}
