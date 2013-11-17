#include "SoundEffect.h"
#include "SoundService.h"
#include "../Logger.h"
#include "../Assets/Resource.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/Filepath.h"
#include "../Helpers/HelpersMath.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star
{
	#ifdef DESKTOP
	int SoundEffect::PLAY_CHANNELS = 0;
	#endif

	SoundEffect::SoundEffect(const tstring& path)
		: BaseSound()
	#ifdef DESKTOP
		, mPlayChannel(PLAY_CHANNELS++)
		, mpSound(nullptr)
	#else
		, mPlayerObjs(MAX_SAMPLES)
		, mPlayers(MAX_SAMPLES)
	#endif
	{
	#ifdef ANDROID
		SLEngineItf engine = SoundService::GetInstance()->GetEngine();
		for(int i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			CreateSound(mPlayerObjs[i], engine, mPlayers[i], path);
		}
	#else
		Filepath real_path(path);
		sstring sound_path = string_cast<sstring>(real_path.GetAssetsPath());
		mpSound = Mix_LoadWAV(sound_path.c_str());
		if(!mpSound)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("SoundEffect: Could not load sound, reason : ")
				+ string_cast<tstring>(Mix_GetError()));
		}
	#endif
	}

	SoundEffect::~SoundEffect()
	{
	#ifdef DESKTOP
		Mix_HaltChannel(mPlayChannel);
	#else
		for(int i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			DestroySound(mPlayerObjs[i], mPlayers[i]);
		}
	#endif
	}

	void SoundEffect::Play(int loopTime)
	{
	#ifdef DESKTOP
		Mix_PlayChannel(mPlayChannel, mpSound, loopTime);
	#else
		for(int i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			SLresult lRes;
			(*mPlayers[i])->GetPlayState(mPlayers[i],&lRes);
			if( lRes == SL_PLAYSTATE_STOPPED)
			{
				lRes = (*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_PLAYING);
				if (lRes != SL_RESULT_SUCCESS)
				{
					star::Logger::GetInstance()->Log(star::LogLevel::Error,
						_T("SoundEffect: Can't play audio!"));
					Stop();
					return;
				};
				return;
			}
		}
#endif
	}

	void SoundEffect::Stop()
	{		
#ifdef DESKTOP
		Mix_HaltChannel(mPlayChannel);
#else	
		for(int i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			(*mPlayers[i])->SetPlayState(mPlayers[i], SL_PLAYSTATE_STOPPED);
		}
#endif
	}
	
	void SoundEffect::Pause()
	{
#ifdef DESKTOP
		Mix_Pause(mPlayChannel);
#else
		for(int i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			SLresult lres = (*mPlayers[i])->GetPlayState(
				mPlayers[i], &lres
				);
			if(lres == SL_PLAYSTATE_PLAYING)
			{
				(*mPlayers[i])->SetPlayState(
					mPlayers[i],SL_PLAYSTATE_PAUSED
					);
			}
		}
#endif
	}

	void SoundEffect::Resume()
	{
#ifdef DESKTOP
		Mix_Resume(mPlayChannel);
#else
		for(int i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			ResumeSound(mPlayers[i]);
		}
#endif
	}

#ifdef ANDROID
	void SoundEffect::SetVolume(float volume)
	{
		for(int i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			SetSoundVolume(
				mPlayerObjs[i],
				mPlayers[i],
				volume
				);
		}
	}
#endif

	float SoundEffect::GetVolume() const
	{
#ifdef ANDROID
		return GetSoundVolume(mPlayerObjs[0], mPlayers[0]);
#else
		float volume = float(Mix_Volume(mPlayChannel, -1));
		return volume / float(MIX_MAX_VOLUME);
#endif
	}

#ifdef DESKTOP
	void SoundEffect::SetSoundVolume(int volume)
	{
		Mix_Volume(mPlayChannel, volume);
	}
#else
	void SoundEffect::RegisterCallback(SLPlayItf & player)
	{
		if((*player)->RegisterCallback(
			player, MusicStoppedCallback,
			&player) != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("SoundEffect: Can't set callback"));
		}
	}

	void SoundEffect::MusicStoppedCallback(SLPlayItf caller,void *pContext,SLuint32 event)
	{
		(*caller)->SetPlayState(caller, SL_PLAYSTATE_STOPPED);
	}
#endif
}
