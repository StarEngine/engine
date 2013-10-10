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
		// [COMMENT] Pauze is written with an 's'... so Pause!
		void Pauze();
		void Resume();
		// [COMMENT] Const correctness!! Cmon, this is basics!
		bool IsStopped() { return bStopped; }

	private:
		// [COMMENT] why not respecting your own naming convention?
		// Either never use m as a prefix for datamembers, or do it 
		// for all your datamembers, but don't do it just for some of them...
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
