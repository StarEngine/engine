#include "SoundEffect.h"
#include "SoundService.h"
#include "../Logger.h"
#include "../Assets/Resource.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/Filepath.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif


namespace star
{
#ifdef DESKTOP
	int SoundEffect::mPlayChannels = 0;
#endif

	SoundEffect::SoundEffect(const tstring& path):
		mbStopped(false),
#ifdef DESKTOP
		mSoundEffect(nullptr),
		mPlayChannel(0)
#else
		mPlayerObjs(MAX_SAMPLES),
		mPlayers(MAX_SAMPLES)
#endif
	{
#ifdef DESKTOP	
		mPlayChannel = mPlayChannels;
		++mPlayChannels;
		
		Filepath real_path(path);
		std::string sound_path = string_cast<std::string>(real_path.GetAssetsPath());
		if(mSoundEffect == nullptr)
		{
			mSoundEffect = Mix_LoadWAV(sound_path.c_str());
			if(!mSoundEffect)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Sound Effect :Could not load song, reason : ")
					+string_cast<tstring>(Mix_GetError()));
			}
		}
#else
		SLEngineItf mEngine = SoundService::GetInstance()->GetEngine();
		for(int i=0; i<MAX_SAMPLES;++i)
		{
			SLresult lRes;

			Resource lResource(star::StarEngine::GetInstance()->GetAndroidApp(), path);
			ResourceDescriptor lDescriptor = lResource.DeScript();
			if(lDescriptor.mDescriptor < 0)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Sound Effect : Could not open file"));
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
			lDataSink.pLocator=&lDataLocatorOut;
			lDataSink.pFormat= NULL;


			const SLuint32 lPlayerIIDCount = 2;
			const SLInterfaceID lPlayerIIDs[] ={ SL_IID_PLAY, SL_IID_SEEK };
			const SLboolean lPlayerReqs[] ={ SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
			lRes = (*mEngine)->CreateAudioPlayer(mEngine,&mPlayerObjs[i], &lDataSource, &lDataSink,lPlayerIIDCount, lPlayerIIDs, lPlayerReqs);
			if (lRes != SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Sound Effect : Can't create audio player"));
				Stop();
				return;
			}

			lRes = (*mPlayerObjs[i])->Realize(mPlayerObjs[i],SL_BOOLEAN_FALSE);
			if (lRes != SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Sound Effect : Can't realise audio player"));
				Stop();
				return;
			}

			lRes = (*mPlayerObjs[i])->GetInterface(mPlayerObjs[i],SL_IID_PLAY, &mPlayers[i]);
			if (lRes != SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Sound Effect : Can't get audio play interface"));
				Stop();
				return;
			}


			if((*mPlayers[i])->SetCallbackEventsMask(mPlayers[i],SL_PLAYSTATE_STOPPED)!=SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Sound Effect : Can't set callback flags"));
			}
			if((*mPlayers[i])->RegisterCallback(mPlayers[i],MusicStoppedCallback,&mPlayers[i])!=SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Sound Effect : Can't set callback"));
			}
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
			if(mPlayers[i] != NULL)
			{
				SLuint32 lPlayerState;
				(*mPlayerObjs[i])->GetState(mPlayerObjs[i], &lPlayerState);
				if(lPlayerState == SL_OBJECT_STATE_REALIZED)
				{
					(*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_PAUSED);
					(*mPlayerObjs[i])->Destroy(mPlayerObjs[i]);
					mPlayerObjs[i] = NULL;
					mPlayers[i] = NULL;
					star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Sound Effect : Soundfile Destroyed"));
				}
			}
		}
#endif
	}

	void SoundEffect::Play()
	{
#ifdef DESKTOP
		Mix_PlayChannel(mPlayChannel,mSoundEffect,0);
#else
		for(int i=0; i<MAX_SAMPLES;++i)
		{
			SLresult lRes;
			(*mPlayers[i])->GetPlayState(mPlayers[i],&lRes);
			if( lRes == SL_PLAYSTATE_STOPPED)
			{
				lRes = (*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_PLAYING);
				if (lRes != SL_RESULT_SUCCESS)
				{
					star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Sound Effect : Can't play audio"));
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
			(*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_STOPPED);
		}
#endif
	}
	
	void SoundEffect::Pause()
	{
#ifdef DESKTOP
		Mix_Pause(mPlayChannel);
#else
		for(int i = 0; i < MAX_SAMPLES ; ++i)
		{
			SLresult lres=(*mPlayers[i])->GetPlayState(mPlayers[i],&lres);
			if(lres==SL_PLAYSTATE_PLAYING)
			(*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_PAUSED);
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
			SLresult lres=(*mPlayers[i])->GetPlayState(mPlayers[i],&lres);
			if(lres==SL_PLAYSTATE_PAUSED)
			(*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_PLAYING);
		}
#endif
	}
	
	bool SoundEffect::IsStopped() const
	{
		return mbStopped;
	}

#ifdef ANDROID
	void SoundEffect::MusicStoppedCallback(SLPlayItf caller,void *pContext,SLuint32 event)
	{
		(*caller)->SetPlayState(caller, SL_PLAYSTATE_STOPPED);
	}
#endif
}
