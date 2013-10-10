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

#include <map>

namespace star
{
	class SoundFile
	{
	public:
		SoundFile(const tstring& path);
		~SoundFile();

		//for infinite loop set "looptimes" to -1
		void Play(int32 looptimes=0);
		void PlayQueued(int32 looptimes=0);
		void Stop();
		void Pause();
		void Resume();
		const bool IsStopped(){return mbStopped;}

	private:
		int32 mLoopTimes;
		bool mbStopped;
		bool mbQueuedPlay;
#ifdef _WIN32
		Mix_Music * mMusic;
		static void MusicStoppedCallback();
#else
		static void MusicStoppedCallback(SLPlayItf caller,void *pContext,SLuint32 event);
		SLObjectItf mPlayerObj;
		SLPlayItf mPlayer;
		SLSeekItf mPlayerSeek;
#endif

		SoundFile(const SoundFile& yRef);
		SoundFile(SoundFile&& yRef);
		SoundFile& operator=(const SoundFile& yRef);
	};
}
