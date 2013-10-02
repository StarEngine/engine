#include "SoundService.h"
#include "../Logger.h"

#ifdef _WIN32

#else
#include "../EventLoop.h"
#include "../AssetManaging/Resource.h"
#endif

namespace star
{
	SoundService* SoundService::mSoundService = nullptr;

	SoundService* SoundService::GetInstance()
	{
		if(mSoundService==nullptr)
		{
			mSoundService = new SoundService();
		}
		return mSoundService;
	}

	SoundService::SoundService():
		mEngine(NULL),
		mEngineObj(NULL),
		mOutputMixObj(NULL),
		mPlayerObj(NULL),
		mPlayer(NULL),
		mPlayerSeek(NULL)
	{

	}

	status SoundService::Start()
	{
#ifdef _WIN32
#else
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Audio : Started making Audio Engine"));
		SLresult lRes;
		const SLuint32 lEngineMixIIDCount =1;
		const SLInterfaceID lEngineMixIIDs[]={SL_IID_ENGINE};
		const SLboolean lEngineMixReqs[]={SL_BOOLEAN_TRUE};
		const SLuint32 lOutputMixIIDCount=0;
		const SLInterfaceID lOutputMixIIDs[]={NULL};
		const SLboolean lOutputMixReqs[]={NULL};

		lRes = slCreateEngine(&mEngineObj, 0, NULL, lEngineMixIIDCount, lEngineMixIIDs, lEngineMixReqs);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't make Audio Engine"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mEngineObj)->Realize(mEngineObj, SL_BOOLEAN_FALSE);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't realize Engine"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mEngineObj)->GetInterface(mEngineObj,SL_IID_ENGINE, &mEngine);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't fetch engine interface"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj, lOutputMixIIDCount, lOutputMixIIDs,lOutputMixReqs);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't create outputmix"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mOutputMixObj)->Realize(mOutputMixObj,SL_BOOLEAN_FALSE);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't realise output object"));
			Stop();
			return STATUS_KO;
		}
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Audio : Succesfull made Audio Engine"));
#endif
		return STATUS_OK;
	}

	void SoundService::Stop()
	{
		StopSound();
#ifdef _WIN32
#else
		if(mOutputMixObj != NULL)
		{
			(*mOutputMixObj)->Destroy(mOutputMixObj);
			mOutputMixObj = NULL;
		}
		if(mEngineObj!=NULL)
		{
			(*mEngineObj)->Destroy(mEngineObj);
			mEngineObj=NULL;
			mEngine=NULL;
		}
#endif
		star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Audio : Stopped audio Engine"));
	}

	status SoundService::PlaySoundFile(const tstring path)
	{
		SLresult lRes;
#ifdef _WIN32
#else
		Resource lResource(star::EventLoop::mApplicationPtr, path);
		ResourceDescriptor lDescriptor = lResource.DeScript();
		if(lDescriptor.mDescriptor<0)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Could not open file"));
			return STATUS_KO;
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
		lDataLocatorOut.outputMix = mOutputMixObj;

		SLDataSink lDataSink;
		lDataSink.pLocator=&lDataLocatorOut;
		lDataSink.pFormat= NULL;


		const SLuint32 lPlayerIIDCount = 2;
		const SLInterfaceID lPlayerIIDs[] ={ SL_IID_PLAY, SL_IID_SEEK };
		const SLboolean lPlayerReqs[] ={ SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
		lRes = (*mEngine)->CreateAudioPlayer(mEngine,&mPlayerObj, &lDataSource, &lDataSink,lPlayerIIDCount, lPlayerIIDs, lPlayerReqs);
		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't create audio player"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mPlayerObj)->Realize(mPlayerObj,SL_BOOLEAN_FALSE);
		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't realise audio player"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mPlayerObj)->GetInterface(mPlayerObj,SL_IID_PLAY, &mPlayer);
		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't get audio play interface"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mPlayerObj)->GetInterface(mPlayerObj,SL_IID_SEEK, &mPlayerSeek);
		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't get audio seek interface"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mPlayerSeek)->SetLoop(mPlayerSeek,SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't set audio loop"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mPlayer)->SetPlayState(mPlayer,SL_PLAYSTATE_PLAYING);
		if (lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Error, _T("Audio : Can't play audio"));
			Stop();
			return STATUS_KO;
		};

#endif
		return STATUS_OK;

	}

	void SoundService::StopSound()
	{
#ifdef _WIN32
#else
		if(mPlayer !=NULL)
		{
			SLuint32 lPlayerState;
			(*mPlayerObj)->GetState(mPlayerObj,&lPlayerState);
			if(lPlayerState == SL_OBJECT_STATE_REALIZED)
			{
				(*mPlayer)->SetPlayState(mPlayer,SL_PLAYSTATE_PAUSED);
				(*mPlayerObj)->Destroy(mPlayerObj);
				mPlayerObj=NULL;
				mPlayer=NULL;
				mPlayerSeek=NULL;
			}
		}
#endif
	}

}
