#include "SoundEffect.h"
#include "AudioManager.h"
#include "../Logger.h"
#include "../Graphics/Resource.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/FilePath.h"
#include "../Helpers/Math.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star
{
	SoundEffect::SoundEffect(const tstring& path, uint8 channel)
		: BaseSound(channel)
	#ifdef DESKTOP
		, mpSound(nullptr)
	#else
		, mPlayerObjs(MAX_SAMPLES)
		, mPlayers(MAX_SAMPLES)
	#endif
	{
	#ifdef ANDROID
		SLEngineItf engine = AudioManager::GetInstance()->GetEngine();
		for(int32 i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			CreateSound(mPlayerObjs[i], engine, mPlayers[i], path);
			mLoopTimes.push_back(0);
		}
	#else
		FilePath real_path(path);
		sstring sound_path = string_cast<sstring>(real_path.GetAssetsPath());
		mpSound = Mix_LoadWAV(sound_path.c_str());
		if(!mpSound)
		{
			LOG(LogLevel::Error,
				_T("SoundEffect: Could not load sound, reason : ")
				+ string_cast<tstring>(Mix_GetError()),
				STARENGINE_LOG_TAG);
		}
	#endif
		SetChannel(channel);
	}

	SoundEffect::~SoundEffect()
	{
	#ifdef DESKTOP
		for(auto it : mPlayChannels)
		{
			Mix_HaltChannel(it);
		}
		mPlayChannels.clear();
	#else
		for(int32 i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			DestroySound(mPlayerObjs[i], mPlayers[i]);
		}
	#endif
		if(!mNoChannelAssigned)
		{
			UnsetChannel();
		}
	}

	void SoundEffect::Play(int32 loopTime)
	{
		BaseSound::Play(loopTime);
	#ifdef DESKTOP
		mPlayChannels.push_back(Mix_PlayChannel(-1, mpSound, loopTime));
	#else
		for(int32 i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			SLresult lRes;
			(*mPlayers[i])->GetPlayState(mPlayers[i], &lRes);
			if(lRes == SL_PLAYSTATE_STOPPED)
			{
				mLoopTimes[i] = loopTime;
				lRes = (*mPlayers[i])->SetPlayState(mPlayers[i], SL_PLAYSTATE_PLAYING);
				if (lRes != SL_RESULT_SUCCESS)
				{
					LOG(LogLevel::Error,
						_T("SoundEffect: Can't play audio!"), STARENGINE_LOG_TAG);
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
		BaseSound::Stop();
#ifdef DESKTOP
		for(auto it : mPlayChannels)
		{
			Mix_HaltChannel(it);
		}
		mPlayChannels.clear();
#else	
		for(int32 i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			(*mPlayers[i])->SetPlayState(mPlayers[i], SL_PLAYSTATE_STOPPED);
		}
#endif
	}
	
	void SoundEffect::Pause()
	{
		BaseSound::Pause();
#ifdef DESKTOP
		for(auto it : mPlayChannels)
		{
			Mix_Pause(it);
		}
#else
		for(int32 i = 0 ; i < MAX_SAMPLES ; ++i)
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
		BaseSound::Resume();
#ifdef DESKTOP
		for(auto it : mPlayChannels)
		{
			Mix_Resume(it);
		}
#else
		for(int32 i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			ResumeSound(mPlayers[i]);
		}
#endif
	}

	void SoundEffect::SetChannel(uint8 channel)
	{
		BaseSound::SetChannel(channel);
		AudioManager::GetInstance()->AddSoundToChannel(channel, this);
	}

	void SoundEffect::UnsetChannel()
	{
		BaseSound::UnsetChannel();
		AudioManager::GetInstance()->RemoveSoundFromChannel(mChannel, this);
	}

#ifdef ANDROID
	void SoundEffect::SetVolume(float32 volume)
	{
		for(int32 i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			SetSoundVolume(
				mPlayerObjs[i],
				mPlayers[i],
				volume
				);
		}
	}
#endif

	float32 SoundEffect::GetVolume() const
	{
#ifdef ANDROID
		return GetSoundVolume(mPlayerObjs[0], mPlayers[0]);
#else
		if(mIsMuted)
		{
			return mVolume;
		}
		else
		{
			if(mPlayChannels.size()==0)return 0;
			float32 volume = float32(Mix_Volume(mPlayChannels[0], -1));
			return volume / float32(MIX_MAX_VOLUME);
		}
#endif
	}

	void SoundEffect::SetMuted(bool muted)
	{
#ifdef ANDROID
		for(int32 i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			SetSoundMuted(mPlayerObjs[i], mPlayers[i], muted);
		}
#else
		SetSoundMuted(muted);
#endif
	}

	bool SoundEffect::IsMuted() const
	{
#ifdef ANDROID
		return GetSoundMuted(mPlayerObjs[0], mPlayers[0]);
#else
		return mIsMuted;
#endif
	}

#ifdef DESKTOP
	void SoundEffect::SetSoundVolume(int32 volume)
	{
		for(auto it : mPlayChannels)
		{
			Mix_Volume(it, volume);
		}
	}
#else
	void SoundEffect::RegisterCallback(SLPlayItf & player)
	{
		if((*player)->RegisterCallback(
			player, MusicStoppedCallback,
			this) != SL_RESULT_SUCCESS)
		{
			LOG(LogLevel::Error,
				_T("SoundEffect::RegisterCallback: unable to register the class-defined callback function."),
				STARENGINE_LOG_TAG);
		}
	}

	void SoundEffect::MusicStoppedCallback(
		SLPlayItf caller,
		void *pContext,
		SLuint32 event
		)
	{
		(*caller)->SetPlayState(caller, SL_PLAYSTATE_STOPPED);
		SoundEffect* eff = reinterpret_cast<SoundEffect*>(pContext);
		//Search for the caller in the list
		for(uint32 i = 0 ; i < eff->mPlayers.size() ; ++i)
		{
			if(eff->mPlayers[i] == caller)
			{
				//If infinite loop keep playing
				if(eff->mLoopTimes[i] == -1)
				{
					(*caller)->SetPlayState(caller, SL_PLAYSTATE_PLAYING);
				}
				else
				{
					//check if only play once otherwise keep playing
					if(eff->mLoopTimes[i] != 0)
					{
						(*caller)->SetPlayState(caller, SL_PLAYSTATE_PLAYING);
					}
					--(eff->mLoopTimes[i]);
				}
				break;
			}
		}
	}
#endif
}
