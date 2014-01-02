#include "SoundFile.h"
#include "AudioManager.h"
#include "../Logger.h"
#include "../Graphics/Resource.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/FilePath.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star
{
	SoundFile::SoundFile(const tstring& path, uint8 channel)
		: BaseSound(channel)
		, mLoopTimes(0)
		, mbQueuedPlay(false)
#ifdef ANDROID
		, mPlayerObj(nullptr)
		, mPlayer(nullptr)
		, mPlayerSeek(nullptr)
#else
		, mpSound(nullptr)
#endif
	{
#ifdef ANDROID
		SLEngineItf engine = AudioManager::GetInstance()->GetEngine();
		CreateSound(mPlayerObj, engine, mPlayer, path);
#else
		FilePath real_path(path);
		sstring sound_path = string_cast<sstring>(real_path.GetCorrectPath());
		mpSound = Mix_LoadMUS(sound_path.c_str());
		if(!mpSound)
		{
			LOG(LogLevel::Error,
				_T("SoundFile: Could not load sound, reason : ")
				+ string_cast<tstring>(Mix_GetError()),
				STARENGINE_LOG_TAG);
		}
#endif
		SetChannel(channel);
	}

	SoundFile::~SoundFile()
	{
#ifdef DESKTOP
		if(mpSound != nullptr)
		{	
			Mix_FreeMusic(mpSound);
			mpSound = nullptr;
		}
#else
		DestroySound(mPlayerObj, mPlayer);
#endif
		if(!mNoChannelAssigned)
		{
			UnsetChannel();
		}
	}

	void SoundFile::Play(int32 looptimes)
	{
		BaseSound::Play(looptimes);
		mLoopTimes = looptimes;
		LOG(LogLevel::Info,
			_T("Sound File: Playing File , Looptimes = ") +
			star::string_cast<tstring>(mLoopTimes),
			STARENGINE_LOG_TAG);
#ifdef DESKTOP
		Mix_HookMusicFinished(NULL);
		Mix_PlayMusic(mpSound, mLoopTimes);
#else
		SLresult lRes;
		if(mLoopTimes == -1)
		{
			lRes = (*mPlayerSeek)->SetLoop(
				mPlayerSeek,
				SL_BOOLEAN_TRUE,
				0,
				SL_TIME_UNKNOWN
				);

			if (lRes != SL_RESULT_SUCCESS)
			{
				LOG(
					LogLevel::Error,
					_T("Sound File: Can't set audio loop"),
					STARENGINE_LOG_TAG
					);
				Stop();
				return;
			}
		}

		lRes = (*mPlayer)->SetPlayState(mPlayer,SL_PLAYSTATE_PLAYING);
		if (lRes != SL_RESULT_SUCCESS)
		{
			LOG(LogLevel::Error,
				_T("Sound File: Can't play audio"), STARENGINE_LOG_TAG);
			Stop();
			return;
		};
#endif
	}
	
	void SoundFile::PlayQueued(int32 looptimes)
	{
		BaseSound::Play(looptimes);
		mLoopTimes = looptimes;
		mbQueuedPlay = true;

#ifdef DESKTOP
		Mix_HookMusicFinished(MusicStoppedCallback);
		Mix_PlayMusic(mpSound, mLoopTimes);
#else
		Play(mLoopTimes);
#endif
	}

	void SoundFile::Stop()
	{		
		BaseSound::Stop();
#ifdef DESKTOP
		Mix_PauseMusic();
		Mix_RewindMusic();
#else	
		(*mPlayer)->SetPlayState(mPlayer, SL_PLAYSTATE_STOPPED);
#endif
	}

	void SoundFile::Pause()
	{
		BaseSound::Pause();
#ifdef DESKTOP
		Mix_PauseMusic();
#else
		(*mPlayer)->SetPlayState(mPlayer, SL_PLAYSTATE_PAUSED);
#endif
	}

	void SoundFile::Resume()
	{
		BaseSound::Resume();
#ifdef DESKTOP
		Mix_ResumeMusic();
#else
		ResumeSound(mPlayer);
#endif
	}

	void SoundFile::SetChannel(uint8 channel)
	{
		BaseSound::SetChannel(channel);
		AudioManager::GetInstance()->AddSoundToChannel(channel, this);
	}

	void SoundFile::UnsetChannel()
	{
		BaseSound::UnsetChannel();
		AudioManager::GetInstance()->RemoveSoundFromChannel(mChannel, this);
	}

#ifdef ANDROID
	void SoundFile::SetVolume(float32 volume)
	{
		SetSoundVolume(mPlayerObj, mPlayer, volume);
	}
#endif
	float32 SoundFile::GetVolume() const
	{
#ifdef ANDROID
		return GetSoundVolume(mPlayerObj, mPlayer);
#else
		if(mIsMuted)
		{
			return mVolume;
		}
		else
		{
			float32 volume = float32(Mix_VolumeMusic(-1));
			return volume / float32(MIX_MAX_VOLUME);
		}
#endif
	}

	void SoundFile::SetMuted(bool muted)
	{
#ifdef ANDROID
		SetSoundMuted(mPlayerObj, mPlayer, muted);
#else
		SetSoundMuted(muted);
#endif
	}

	bool SoundFile::IsMuted() const
	{
#ifdef ANDROID
		return GetSoundMuted(mPlayerObj, mPlayer);
#else
		return mIsMuted;
#endif
	}

#ifdef DESKTOP
	void SoundFile::SetSoundVolume(int32 volume)
	{
		Mix_VolumeMusic(volume);
	}

	void SoundFile::MusicStoppedCallback()
	{
		AudioManager::GetInstance()->PlayNextSongInQueue();
	}
#else
	void SoundFile::CreateSoundDetails()
	{
		SLresult lRes =
			(*mPlayerObj)->GetInterface(
				mPlayerObj,
				SL_IID_SEEK,
				&mPlayerSeek
				);
		if (lRes != SL_RESULT_SUCCESS)
		{
			LOG(LogLevel::Error,
				_T("SoundFile : Can't get audio seek interface"),
				STARENGINE_LOG_TAG);
			Stop();
			return;
		}
	}

	void SoundFile::RegisterCallback(SLPlayItf & player)
	{
		if((*player)->RegisterCallback(
			player, MusicStoppedCallback,
			&player) != SL_RESULT_SUCCESS)
		{
			LOG(LogLevel::Error,
				_T("SoundFile: Can't set callback"), STARENGINE_LOG_TAG);
		}
	}

	void SoundFile::MusicStoppedCallback(
		SLPlayItf caller,
		void *pContext,SLuint32 event
		)
	{
		SoundFile* file =
			reinterpret_cast<SoundFile*>(pContext);

		LOG(LogLevel::Info,
			_T("Sound File: Callback Entered, Looptimes = ") +
			star::string_cast<tstring>(file->mLoopTimes),
			STARENGINE_LOG_TAG
			);

		if(file->mLoopTimes == 0)
		{
			SLPlayItf pPlay = file->mPlayer;
			(*pPlay)->SetPlayState(pPlay, SL_PLAYSTATE_STOPPED);
			if(file->mbQueuedPlay)
			{
				star::AudioManager::GetInstance()->PlayNextSongInQueue();
			}
		}
		else
		{
			SLPlayItf pPlay = file->mPlayer;
			(*pPlay)->SetPlayState(pPlay, SL_PLAYSTATE_STOPPED);
			file->mLoopTimes -= 1;
			file->Play(file->mLoopTimes);
		}
	}
#endif
}
