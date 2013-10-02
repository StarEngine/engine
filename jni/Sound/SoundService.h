#pragma once

#include "../defines.h"

#ifdef _WIN32
#include "../OpenSL/OpenSLES.h"
#include "../OpenSL/OpenSLES_Platform.h"
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
		status Start();
		void Stop();

		status PlaySoundFile(const tstring path);
		void StopSound();


	private:
		SoundService();

		static SoundService* mSoundService;

		SLObjectItf mEngineObj;
		SLEngineItf mEngine;
		SLObjectItf mOutputMixObj;

		SLObjectItf mPlayerObj;
		SLPlayItf mPlayer;
		SLSeekItf mPlayerSeek;

	SoundService(const SoundService& yRef);
	SoundService(SoundService&& yRef);
	SoundService& operator=(const SoundService& yRef);
	};
}
