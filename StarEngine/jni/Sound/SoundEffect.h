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

#include <vector>

namespace star
{
	const int MAX_SAMPLES = 10;

	class SoundEffect final
	{
	public:
		SoundEffect(const tstring& path);
		~SoundEffect();

		//set looptime to -1 for l-inifinte loop
		void Play(int loopTime=0);
		void Stop();
		void Pause();
		void Resume();
		bool IsStopped() const;

	private:
		bool mbStopped;
#ifdef DESKTOP
		Mix_Chunk* mSoundEffect;
		static int mPlayChannels;
		int mPlayChannel;
#else
		static void MusicStoppedCallback(SLPlayItf caller,void *pContext,SLuint32 event);
		std::vector<SLObjectItf> mPlayerObjs;
		std::vector<SLPlayItf> mPlayers;
#endif

		SoundEffect(const SoundEffect& yRef);
		SoundEffect(SoundEffect&& yRef);
		SoundEffect& operator=(const SoundEffect& yRef);
		SoundEffect& operator=(SoundEffect&& yRef);
	};
}
