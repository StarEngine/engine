#include "SoundEffect.h"
#include "SoundService.h"
#include "../Logger.h"
#include "../AssetManaging/Resource.h"
#include "../Helpers/Helpers.h"

#ifndef _WIN32
#include "../StarEngine.h"
#endif


namespace star
{
#ifdef _WIN32
	int SoundEffect::PlayChannels = 0;
#endif

	SoundEffect::SoundEffect(const tstring& path):
		bStopped(false),
#ifdef _WIN32
		// [COMMENT] use nullnptr
		mSoundEffect(NULL),
		mPlayChannel(0)
#else
		mPlayerObjs(MAX_SAMPLES),
		mPlayers(MAX_SAMPLES)
#endif
	{
#ifdef _WIN32	
		mPlayChannel = PlayChannels;
		++PlayChannels;
		std::string sound_path = string_cast<std::string>(path);
		// [COMMENT] use nullnptr
		if(mSoundEffect == NULL)
		{
			mSoundEffect = Mix_LoadWAV(sound_path.c_str());
			if(!mSoundEffect)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Audio :Could not load song, reason : ")+string_cast<tstring>(Mix_GetError()));
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
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Audio : Could not open file"));
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
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("AudioFile : Can't create audio player"));
				Stop();
				return;
			}

			lRes = (*mPlayerObjs[i])->Realize(mPlayerObjs[i],SL_BOOLEAN_FALSE);
			if (lRes != SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("AudioFile : Can't realise audio player"));
				Stop();
				return;
			}

			lRes = (*mPlayerObjs[i])->GetInterface(mPlayerObjs[i],SL_IID_PLAY, &mPlayers[i]);
			if (lRes != SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("AudioFile : Can't get audio play interface"));
				Stop();
				return;
			}


			if((*mPlayers[i])->SetCallbackEventsMask(mPlayers[i],SL_PLAYSTATE_STOPPED)!=SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("AudioFile : Can't set callback flags"));
			}
			if((*mPlayers[i])->RegisterCallback(mPlayers[i],MusicStoppedCallback,&mPlayers[i])!=SL_RESULT_SUCCESS)
			{
				star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("AudioFile : Can't set callback"));
			}
		}
#endif
	}

	SoundEffect::~SoundEffect()
	{
#ifdef _WIN32
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
					star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("AudioFile : Soundfile Destroyed"));
				}
			}
		}
#endif
	}

	void SoundEffect::Play()
	{
#ifdef _WIN32

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
					star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Audio : Can't play audio"));
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
#ifdef _WIN32
		Mix_HaltChannel(mPlayChannel);
#else	
		for(int i = 0 ; i < MAX_SAMPLES ; ++i)
		{
			(*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_STOPPED);
		}
#endif
	}
	
	// [COMMENT] Pauze is written with an 's'... so Pause!
	void SoundEffect::Pauze()
	{
#ifdef _WIN32
		Mix_HaltChannel(mPlayChannel);
#else
		// [COMMENT] please seperate your operators with spaces, like the for loop loop on line 175
		for(int i=0; i<MAX_SAMPLES;++i)
		{
			SLresult lres=(*mPlayers[i])->GetPlayState(mPlayers[i],&lres);
			if(lres==SL_PLAYSTATE_PLAYING)
			(*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_PAUSED);
		}
#endif
	}

	void SoundEffect::Resume()
	{
#ifdef _WIN32
		Mix_HaltChannel(mPlayChannel);
#else
		// [COMMENT] please seperate your operators with spaces, like the for loop loop on line 175
		for(int i=0; i<MAX_SAMPLES;++i)
		{
			SLresult lres=(*mPlayers[i])->GetPlayState(mPlayers[i],&lres);
			if(lres==SL_PLAYSTATE_PAUSED)
			(*mPlayers[i])->SetPlayState(mPlayers[i],SL_PLAYSTATE_PLAYING);
		}
#endif
	}


#ifndef _WIN32
	void SoundEffect::MusicStoppedCallback(SLPlayItf caller,void *pContext,SLuint32 event)
	{
		(*caller)->SetPlayState(caller, SL_PLAYSTATE_STOPPED);
	}
#endif
}
