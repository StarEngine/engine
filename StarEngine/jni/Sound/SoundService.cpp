#include "SoundService.h"
#include "../Logger.h"
#include "../Helpers/Helpers.h"


#ifdef ANDROID
#include "../Assets/Resource.h"
#endif

namespace star
{
	SoundService * SoundService::mSoundService = nullptr;
	bool SoundService::mbIsInitialized = false;

	SoundService * SoundService::GetInstance()
	{
		if(mSoundService == nullptr)
		{
			mSoundService = new SoundService();
		}
		return mSoundService;
	}

	SoundService::SoundService()
#ifdef ANDROID
		:mEngine(NULL),
		mEngineObj(NULL),
		mOutputMixObj(NULL)
#endif
	{
		mQueueIterator = mBackgroundQueue.begin();
	}

	SoundService::~SoundService()
	{
		for(auto music : mMusicList)
		{
			delete (music.second);
			music.second = nullptr;
		}

		for(auto effect : mEffectsList)
		{
			delete (effect.second);
			effect.second = nullptr;
		}
	}

	status SoundService::Start()
	{
		if(mbIsInitialized)return STATUS_OK;

		mbIsInitialized=true;
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Audio : Started making Audio Engine"));

#ifdef DESKTOP
		int32 audio_rate(44100);
		uint16 audio_format(MIX_DEFAULT_FORMAT);
		int32 audio_channels(2);
		int32 audio_buffers(4096);

		SDL_Init(SDL_INIT_AUDIO);
		int flags = MIX_INIT_OGG | MIX_INIT_MP3;
		int innited = Mix_Init(flags);
		if((innited & flags) != flags)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Audio :Could not init Ogg and Mp3, reason : ")+ string_cast<tstring>(Mix_GetError()));
		}

		if(Mix_OpenAudio(audio_rate, audio_format,audio_channels,audio_buffers))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Audio : Could Not open Audio Mix SDL"));
			Stop();
			return STATUS_KO;
		}

		//check What we got
		int32 actual_rate, actual_channels;
		uint16 actual_format;

		Mix_QuerySpec(&actual_rate,&actual_format,&actual_channels);
		tstringstream buffer;
		buffer << "Actual Rate : " << actual_rate << ", Actual Format : " << actual_format << ", Actual Channels : " << actual_channels << std::endl;
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Audio : SDL specs : ")+buffer.str());
		Mix_Volume(-1,100);
#else
		
		SLresult lRes;
		const SLuint32 lEngineMixIIDCount =1;
		const SLInterfaceID lEngineMixIIDs[]={SL_IID_ENGINE};
		const SLboolean lEngineMixReqs[]={SL_BOOLEAN_TRUE};
		const SLuint32 lOutputMixIIDCount=0;
		const SLInterfaceID lOutputMixIIDs[]={};
		const SLboolean lOutputMixReqs[]={};

		lRes = slCreateEngine(&mEngineObj, 0, NULL, lEngineMixIIDCount, lEngineMixIIDs, lEngineMixReqs);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Audio : Can't make Audio Engine"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mEngineObj)->Realize(mEngineObj, SL_BOOLEAN_FALSE);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Audio : Can't realize Engine"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mEngineObj)->GetInterface(mEngineObj,SL_IID_ENGINE, &mEngine);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Audio : Can't fetch engine interface"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj, lOutputMixIIDCount, lOutputMixIIDs,lOutputMixReqs);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Audio : Can't create outputmix"));
			Stop();
			return STATUS_KO;
		}

		lRes = (*mOutputMixObj)->Realize(mOutputMixObj,SL_BOOLEAN_FALSE);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Audio : Can't realise output object"));
			Stop();
			return STATUS_KO;
		}
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Audio : Succesfull made Audio Engine"));
#endif
		return STATUS_OK;
	}

	void SoundService::Stop()
	{
		StopAllSound();
		DeleteAllSound();

#ifdef DESKTOP
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
#else
		if(mOutputMixObj != NULL)
		{
			(*mOutputMixObj)->Destroy(mOutputMixObj);
			mOutputMixObj = NULL;
		}
		if(mEngineObj != NULL)
		{
			(*mEngineObj)->Destroy(mEngineObj);
			mEngineObj = NULL;
			mEngine = NULL;
		}
#endif
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Audio : Stopped audio Engine"));
	}

	status SoundService::LoadMusic(const tstring& path, const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		if(mMusicList.find(name) != mMusicList.end())
		{
			return (STATUS_KO);
		}

		auto pathit = mMusicPathList.find(path);
		if(pathit!=mMusicPathList.end())
		{
			star::Logger::GetInstance()->Log(LogLevel::Warning,_T("Sound Service : Sound File Path Already Exists"));
			tstring nameold = pathit->second;
			auto nameit = mMusicList.find(nameold);
			if(nameit!= mMusicList.end())
			{
				star::Logger::GetInstance()->Log(LogLevel::Warning,_T("Sound Service : Found sound file of old path, making copy for new name"));
				mMusicList[name]=nameit->second;
				return (STATUS_OK);
			}
			mMusicPathList.erase(pathit);
			return (STATUS_KO);
		}

		SoundFile* music = new SoundFile(path);
		mMusicList[name] = music;
		mMusicPathList[path]=name;
		return (STATUS_OK);
	}

	status SoundService::LoadSoundEffect(const tstring& path, const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		if(mEffectsList.find(name) != mEffectsList.end())
		{
			return (STATUS_KO);
		}

		auto pathit = mSoundEffectPathList.find(path);
		if(pathit!=mSoundEffectPathList.end())
		{
			star::Logger::GetInstance()->Log(LogLevel::Warning,_T("Sound Service : Sound Effect Path Already Exists"));
			tstring nameold = pathit->second;
			auto nameit = mMusicList.find(nameold);
			if(nameit!= mMusicList.end())
			{
				star::Logger::GetInstance()->Log(LogLevel::Warning,_T("Sound Service : Found Sound Effect of old path, making copy for new name"));
				mMusicList[name]=nameit->second;
				return (STATUS_OK);
			}
			mSoundEffectPathList.erase(pathit);
			return (STATUS_KO);
		}

		SoundEffect* effect = new SoundEffect(path);
		mEffectsList[name] = effect;
		mSoundEffectPathList[path]=name;
		return (STATUS_OK);
	}

	status SoundService::PlaySoundFile(const tstring& path, const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		if(mMusicList.find(name)==mMusicList.end())
		{
			LoadMusic(path,name);
		}
		return PlaySoundFile(name);
	}

	status SoundService::PlaySoundFile(const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			mMusicList[name]->Play(0);
			return (STATUS_OK);
		}
		return (STATUS_KO);
	}

	status SoundService::PlaySoundEffect(const tstring& path, const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		if(mEffectsList.find(name)==mEffectsList.end())
		{
			LoadSoundEffect(path,name);
		}
		return PlaySoundFile(name);
	}

	status SoundService::PlaySoundEffect(const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			mEffectsList[name]->Play();
			return (STATUS_OK);
		}
		return (STATUS_KO);
	}

	status SoundService::AddToBackgroundQueue(const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			mBackgroundQueue.push_back(mMusicList[name]);
			return (STATUS_OK);
		}
		return (STATUS_KO);
	}

	status SoundService::PlayBackgroundQueue()
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		mQueueIterator = mBackgroundQueue.begin();
		if(mQueueIterator!=mBackgroundQueue.end())
		{
			(*mQueueIterator)->PlayQueued(0);
			return (STATUS_OK);
		}
		return STATUS_KO;
	}

	void SoundService::PlayNextSongInQueue()
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));
		if(mBackgroundQueue.size()==0)return;

		++mQueueIterator;
		if(mQueueIterator!=mBackgroundQueue.end())
		{
			(*mQueueIterator)->PlayQueued(0);
		}
		else
		{
			mQueueIterator==mBackgroundQueue.begin();
			(*mQueueIterator)->PlayQueued(0);
		}
	}

	void SoundService::StopSound(const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			mMusicList[name]->Stop();
			return;
		}

		auto it2 = mEffectsList.find(name);
		if(it2 != mEffectsList.end())
		{
			mEffectsList[name]->Stop();
			return;
		}
	}

	void SoundService::StopAllSound()
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mMusicList.begin();
		for(it; it!= mMusicList.end();++it)
		{
			it->second->Stop();
		}

		auto it2 = mEffectsList.begin();
		for(it2; it2!= mEffectsList.end();++it2)
		{
			it2->second->Stop();
		}
	}

	void SoundService::PauseAllSound()
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mMusicList.begin();
		for(it; it!= mMusicList.end();++it)
		{
			it->second->Pause();
		}

		auto it2 = mEffectsList.begin();
		for(it2; it2!= mEffectsList.end();++it2)
		{
			it2->second->Pause();
		}
	}

	void SoundService::ResumeAllSound()
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mMusicList.begin();
		for(it; it!= mMusicList.end();++it)
		{
			it->second->Resume();
		}

		auto it2 = mEffectsList.begin();
		for(it2; it2!= mEffectsList.end();++it2)
		{
			it2->second->Resume();
		}
	}

	void SoundService::DeleteAllSound()
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mMusicList.begin();
		for(it; it!= mMusicList.end();++it)
		{
			mMusicList.erase(it);
		}

		auto it2 = mEffectsList.begin();
		for(it2; it2!= mEffectsList.end();++it2)
		{
			mEffectsList.erase(it2);
		}
	}

#ifdef ANDROID
	const SLEngineItf& SoundService::GetEngine() const
	{
		return mEngine;
	}

	const SLObjectItf& SoundService::GetOutputMixObject() const
	{
		return mOutputMixObj;
	}
#endif
}
