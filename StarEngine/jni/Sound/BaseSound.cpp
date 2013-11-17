#include "BaseSound.h"
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
#ifdef ANDROID
	const SLInterfaceID BaseSound::PLAYER_ID_ARR[] = 
		{SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME};
	const SLboolean BaseSound::PLAYER_REQ_ARR[] =
		{SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
#endif

	BaseSound::~BaseSound()
	{
	}
	
	bool BaseSound::IsStopped() const
	{
		return mbStopped;
	}

	void BaseSound::SetVolume(float volume)
	{
#ifdef DESKTOP
		volume = Clamp(volume, 0.0f, 1.0f);
		int vol(int(volume * float(MIX_MAX_VOLUME)));
		SetSoundVolume(vol);
#endif
	}

	void BaseSound::IncreaseVolume(float volume)
	{
		float vol = GetVolume();
		vol += volume;
		SetVolume(vol);
	}

	void BaseSound::DecreaseVolume(float volume)
	{
		float vol = GetVolume();
		vol -= volume;
		SetVolume(vol);
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

	BaseSound::BaseSound(uint8 channel)
		: mbStopped(false)
		, mNoChannelAssigned(true)
#ifdef DESKTOP
		, mIsMuted(false)
		, mVolume(0)
#endif
		, mChannel(0)

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

		Resource lResource(
				star::StarEngine::GetInstance()->GetAndroidApp(),
				path
				);

		ResourceDescriptor lDescriptor = lResource.DeScript();
		if(lDescriptor.mDescriptor < 0)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Could not open file"));
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
		lDataLocatorOut.outputMix = SoundService::GetInstance()->GetOutputMixObject();

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
				_T("Sound: Can't create audio player"));
			Stop();
			return;
		}

		lRes = (*sound)->Realize(sound, SL_BOOLEAN_FALSE);

		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Can't realise audio player"));
			Stop();
			return;
		}

		lRes = (*sound)->GetInterface(sound, SL_IID_PLAY, &player);

		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Can't get audio play interface"));
			Stop();
			return;
		}

		if((*player)->SetCallbackEventsMask(
			player, SL_PLAYSTATE_STOPPED) != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Sound: Can't set callback flags"));
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
					_T("Sound: Soundfile Destroyed"));
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
		float volume
		)
	{
		SLVolumeItf volumeItf;
		if(GetVolumeInterface(sound, player, &volumeItf))
		{
			volume = Clamp(volume, 0.0f, 1.0f);
			SLmillibel actualMillibelLevel, maxMillibelLevel;
			SLresult result = (*volumeItf)->GetMaxVolumeLevel(
					volumeItf,
					&maxMillibelLevel
					);
			ASSERT(result == SL_RESULT_SUCCESS,
					_T("Sound: Couldn't get the maximum volume level!"));
			actualMillibelLevel = SLmillibel(
					(1.0f - volume) *
					float(SL_MILLIBEL_MIN - maxMillibelLevel))
							+ maxMillibelLevel;
			result = (*volumeItf)->SetVolumeLevel(
				volumeItf,
				actualMillibelLevel
				);
			ASSERT(result == SL_RESULT_SUCCESS,
					_T("Sound: Couldn't set the volume!"));
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
				ASSERT(isOK, _T("Sound: Couldn't get the interface!"));
				return isOK;
			}
		}
		return false;
	}

	float BaseSound::GetSoundVolume(
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
			ASSERT(result == SL_RESULT_SUCCESS,
					_T("Sound: Couldn't get the volume!"));
			result = (*volumeItf)->GetMaxVolumeLevel(
					volumeItf,
					&maxMillibelLevel
					);
			ASSERT(result == SL_RESULT_SUCCESS,
					_T("Sound: Couldn't get the maximum volume level!"));
			float posMinVol = float(SL_MILLIBEL_MIN) * -1.0f;
			float volume =
					float(actualMillibelLevel + posMinVol) /
					float(posMinVol + maxMillibelLevel);
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
			ASSERT(result == SL_RESULT_SUCCESS,
					_T("BaseSound::SetMuted: Couldn't set muted state!"));
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
			ASSERT(result == SL_RESULT_SUCCESS,
					_T("BaseSound::SetMuted: Couldn't get muted state!"));
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
			mVolume = GetVolume();
			SetVolume(0);
		}
		else
		{
			SetVolume(mVolume);
		}
	}
#endif
}
