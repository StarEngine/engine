#include "BaseSound.h"
#include "AudioManager.h"
#include "../Logger.h"
#include "../Assets/Resource.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/Filepath.h"
#include "../Helpers/Math.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif


namespace star
{
#ifdef ANDROID
	const SLInterfaceID BaseSound::PLAYER_ID_ARR[] = 
		{SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME};
	const SLboolean BaseSound::PLAYER_REQ_ARR[] =
		{SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
#endif

	BaseSound::~BaseSound()
	{
	}

	void BaseSound::Play(int32 loopTime)
	{
		mSoundState = SoundState::playing;
		mbIsLooping = loopTime == -1;
	}

	void BaseSound::Stop()
	{
		mSoundState = SoundState::stopped;
	}

	void BaseSound::Pause()
	{
		mSoundState = SoundState::paused;
	}

	void BaseSound::Resume()
	{
		mSoundState = SoundState::playing;
	}
	
	bool BaseSound::IsStopped() const
	{
		return mSoundState == SoundState::stopped;
	}

	bool BaseSound::IsPlaying() const
	{
		return mSoundState == SoundState::playing;
	}

	bool BaseSound::IsPaused() const
	{
		return mSoundState == SoundState::paused;
	}

	bool BaseSound::IsLooping() const
	{
		return mbIsLooping && IsPlaying();
	}

	void BaseSound::SetCompleteVolume(
		float32 volume,
		float32 channelVolume,
		float32 masterVolume
		)
	{
		mSoundVolume.Volume = volume;
		mSoundVolume.ChannelVolume = channelVolume;
		mSoundVolume.MasterVolume = masterVolume;
		SetVolume(mSoundVolume.GetVolume());
	}

	void BaseSound::SetBaseVolume(
		float32 volume
		)
	{
		mSoundVolume.Volume = volume;
		SetVolume(mSoundVolume.GetVolume());
	}

	void BaseSound::SetChannelVolume(
		float32 volume
		)
	{
		mSoundVolume.ChannelVolume = volume;
		SetVolume(mSoundVolume.GetVolume());
	}

	void BaseSound::SetMasterVolume(
		float32 volume
		)
	{
		mSoundVolume.MasterVolume = volume;
		SetVolume(mSoundVolume.GetVolume());
	}

	float32 BaseSound::GetBaseVolume() const
	{
		return mSoundVolume.Volume;
	}

	void BaseSound::SetVolume(float32 volume)
	{
#ifdef DESKTOP
		volume = Clamp(volume, 0.0f, 1.0f);
		int32 vol(int32(volume * float32(MIX_MAX_VOLUME)));
		SetSoundVolume(vol);
#endif
	}

	void BaseSound::IncreaseVolume(float32 volume)
	{
		mSoundVolume.Volume += volume;
		mSoundVolume.Volume = Clamp(mSoundVolume.Volume, 0.0f, 1.0f);
		SetVolume(mSoundVolume.GetVolume());
	}

	void BaseSound::DecreaseVolume(float32 volume)
	{
		mSoundVolume.Volume -= volume;
		mSoundVolume.Volume = Clamp(mSoundVolume.Volume, 0.0f, 1.0f);
		SetVolume(mSoundVolume.GetVolume());
	}

	void BaseSound::SetChannel(uint8 channel)
	{
		if(!mNoChannelAssigned)
		{
			UnsetChannel();
		}
		mChannel = channel;
		mNoChannelAssigned = false;
	}

	void BaseSound::UnsetChannel()
	{
		mNoChannelAssigned = true;
	}

	uint8 BaseSound::GetChannel() const
	{
		return mChannel;
	}

	BaseSound::BaseSound(uint8 channel)
		: mbIsLooping(false)
		, mNoChannelAssigned(true)
#ifdef DESKTOP
		, mIsMuted(false)
		, mVolume(1)
#else
		, mPath(EMPTY_STRING)
#endif
		, mChannel(0)
		, mSoundVolume()
		, mSoundState(SoundState::stopped)

	{
	}

#ifdef ANDROID
	void BaseSound::CreateSoundDetails()
	{

	}

	void BaseSound::CreateSound(
		SLObjectItf & sound,
		SLEngineItf & engine,
		SLPlayItf & player,
		const tstring & path
		)
	{
		SLresult lRes;

		Resource lResource(path);

		ResourceDescriptor lDescriptor = lResource.DeScript();
		if(lDescriptor.mDescriptor < 0)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Could not open file"), STARENGINE_LOG_TAG);
			return;
		}
		SLDataLocator_AndroidFD lDataLocatorIn;
		lDataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
		lDataLocatorIn.fd = lDescriptor.mDescriptor;
		lDataLocatorIn.offset = lDescriptor.mStart;
		lDataLocatorIn.length = lDescriptor.mLength;

		SLDataFormat_MIME lDataFormat;
		lDataFormat.formatType = SL_DATAFORMAT_MIME;
		lDataFormat.mimeType = NULL;
		lDataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;

		SLDataSource lDataSource;
		lDataSource.pLocator = &lDataLocatorIn;
		lDataSource.pFormat = &lDataFormat;

		SLDataLocator_OutputMix lDataLocatorOut;
		lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
		lDataLocatorOut.outputMix = AudioManager::GetInstance()->GetOutputMixObject();

		SLDataSink lDataSink;
		lDataSink.pLocator = &lDataLocatorOut;
		lDataSink.pFormat = NULL;

		lRes = (*engine)->CreateAudioPlayer(
			engine,
			&sound,
			&lDataSource,
			&lDataSink,
			PLAYER_ID_COUNT,
			PLAYER_ID_ARR,
			PLAYER_REQ_ARR
			);

		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Can't create audio player"), STARENGINE_LOG_TAG);
			Stop();
			return;
		}

		lRes = (*sound)->Realize(sound, SL_BOOLEAN_FALSE);

		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Can't realise audio player"), STARENGINE_LOG_TAG);
			Stop();
			return;
		}

		lRes = (*sound)->GetInterface(sound, SL_IID_PLAY, &player);

		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Can't get audio play interface"), STARENGINE_LOG_TAG);
			Stop();
			return;
		}

		if((*player)->SetCallbackEventsMask(
			player, SL_PLAYSTATE_STOPPED) != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Can't set callback flags"), STARENGINE_LOG_TAG);
		}

		CreateSoundDetails();

		RegisterCallback(player);
	}

	void BaseSound::DestroySound(
		SLObjectItf & sound,
		SLPlayItf & player
		)
	{
		if(player != NULL)
		{
			SLuint32 lPlayerState;
			(*sound)->GetState(sound, &lPlayerState);
			if(lPlayerState == SL_OBJECT_STATE_REALIZED)
			{
				(*player)->SetPlayState(player,SL_PLAYSTATE_PAUSED);
				(*sound)->Destroy(sound);
				sound = NULL;
				player = NULL;
				star::Logger::GetInstance()->Log(star::LogLevel::Error,
					_T("Sound: Soundfile Destroyed"), STARENGINE_LOG_TAG);
			}
		}
	}

	void BaseSound::ResumeSound(SLPlayItf & player)
	{
		SLresult lres = 
			(*player)->GetPlayState(player, &lres);
		if(lres == SL_PLAYSTATE_PAUSED)
		{
			(*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
		}
	}

	void BaseSound::SetSoundVolume(
		SLObjectItf & sound,
		SLPlayItf & player,
		float32 volume
		)
	{
		SLVolumeItf volumeItf;
		if(GetVolumeInterface(sound, player, &volumeItf))
		{
			volume = Clamp(volume, 0.0f, 1.0f);
			volume = (volume / 10.0f) + 0.9f;
			SLmillibel actualMillibelLevel, maxMillibelLevel;
			SLresult result = (*volumeItf)->GetMaxVolumeLevel(
					volumeItf,
					&maxMillibelLevel
					);
			Logger::GetInstance()->Log(result == SL_RESULT_SUCCESS,
					_T("Sound: Couldn't get the maximum volume level!"), STARENGINE_LOG_TAG);
			actualMillibelLevel = SLmillibel(
					(1.0f - volume) *
					float32(SL_MILLIBEL_MIN - maxMillibelLevel))
							+ maxMillibelLevel;
			result = (*volumeItf)->SetVolumeLevel(
				volumeItf,
				actualMillibelLevel
				);
			Logger::GetInstance()->Log(result == SL_RESULT_SUCCESS,
					_T("Sound: Couldn't set the volume!"), STARENGINE_LOG_TAG);
		}
	}

	bool BaseSound::GetVolumeInterface(
		const SLObjectItf & sound,
		const SLPlayItf & player,
		void * pInterface
		) const
	{
		if(player != nullptr)
		{
			SLuint32 lPlayerState;
			(*sound)->GetState(sound, &lPlayerState);
			if(lPlayerState == SL_OBJECT_STATE_REALIZED)
			{
				SLresult result = (*sound)->GetInterface(
					sound, SL_IID_VOLUME, pInterface
					);
				bool isOK = result == SL_RESULT_SUCCESS;
				Logger::GetInstance()->Log(isOK,
					_T("Sound: Couldn't get the interface!"),
					STARENGINE_LOG_TAG);
				return isOK;
			}
		}
		return false;
	}

	float32 BaseSound::GetSoundVolume(
		const SLObjectItf & sound,
		const SLPlayItf & player
		) const
	{
		SLVolumeItf volumeItf;
		if(GetVolumeInterface(sound, player, &volumeItf))
		{
			SLmillibel actualMillibelLevel, maxMillibelLevel;
			SLresult result = result = (*volumeItf)->GetVolumeLevel(
					volumeItf,
					&actualMillibelLevel
					);
			Logger::GetInstance()->Log(result == SL_RESULT_SUCCESS,
					_T("Sound: Couldn't get the volume!"),
					STARENGINE_LOG_TAG);
			result = (*volumeItf)->GetMaxVolumeLevel(
					volumeItf,
					&maxMillibelLevel
					);
			Logger::GetInstance()->Log(result == SL_RESULT_SUCCESS,
					_T("Sound: Couldn't get the maximum volume level!"),
					STARENGINE_LOG_TAG);
			float32 posMinVol = float32(SL_MILLIBEL_MIN) * -1.0f;
			float32 volume =
					float32(actualMillibelLevel + posMinVol) /
					float32(posMinVol + maxMillibelLevel);
			return volume;
		}
		return 0;
	}

	void BaseSound::SetSoundMuted(
		SLObjectItf & sound,
		SLPlayItf & player,
		bool muted
		)
	{
		SLVolumeItf volumeItf;
		if(GetVolumeInterface(sound, player, &volumeItf))
		{
			SLresult result = (*volumeItf)->SetMute(
				volumeItf, SLboolean(muted)
				);
			Logger::GetInstance()->Log(result == SL_RESULT_SUCCESS,
					_T("BaseSound::SetMuted: Couldn't set muted state!"),
					STARENGINE_LOG_TAG);
		}
	}

	bool BaseSound::GetSoundMuted(
		const SLObjectItf & sound,
		const SLPlayItf & player
		) const
	{
		SLVolumeItf volumeItf;
		if(GetVolumeInterface(sound, player, &volumeItf))
		{
			SLboolean isMuted;
			SLresult result = (*volumeItf)->GetMute(
				volumeItf, &isMuted
				);
			Logger::GetInstance()->Log(result == SL_RESULT_SUCCESS,
					_T("BaseSound::SetMuted: Couldn't get muted state!"),
					STARENGINE_LOG_TAG);
			return bool(isMuted);
		}
		return false;
	}
#else
	void BaseSound::SetSoundMuted(bool muted)
	{
		mIsMuted = muted;
		if(mIsMuted)
		{
			mVolume = GetBaseVolume();
			SetVolume(0);
		}
		else
		{
			SetVolume(mVolume);
		}
	}
#endif

	BaseSound::SoundVolume::SoundVolume()
		: Volume(1.0f)
		, ChannelVolume(1.0f)
		, MasterVolume(1.0f)
	{

	}

	float32 BaseSound::SoundVolume::GetVolume() const
	{
		return Volume * ChannelVolume * MasterVolume;
	}
}
