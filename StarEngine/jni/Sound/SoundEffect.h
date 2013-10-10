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

#include <vector>

namespace star
{
	const int MAX_SAMPLES = 10;

	class SoundEffect
	{
	public:
		SoundEffect(const tstring& path);
		~SoundEffect();

		void Play();
		void Stop();
		void Pauze();
		void Resume();
		bool IsStopped(){return bStopped;}

	private:
		bool bStopped;
#ifdef _WIN32
		Mix_Chunk* mSoundEffect;
		static int PlayChannels;
		int mPlayChannel;
#else
		static void MusicStoppedCallback(SLPlayItf caller,void *pContext,SLuint32 event);
		std::vector<SLObjectItf> mPlayerObjs;
		std::vector<SLPlayItf> mPlayers;
#endif

		SoundEffect(const SoundEffect& yRef);
		SoundEffect(SoundEffect&& yRef);
		SoundEffect& operator=(const SoundEffect& yRef);
	};
}
