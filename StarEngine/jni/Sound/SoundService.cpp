#include "SoundService.h"
#include "../Logger.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/HelpersMath.h"

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
		: mMusicList()
		, mMusicPathList()
		, mEffectsList()
		, mSoundEffectPathList()
		, mBackgroundQueue()
		, mQueueIterator()
		, m_CurrentSoundFile(nullptr)
		, m_CurrentSoundEffect(nullptr)
		, m_Volume(1.0f)
#ifdef ANDROID
		, mEngineObj(nullptr)
		, mEngine(nullptr)
		, mOutputMixObj(nullptr)
		, mOutputMixVolume(nullptr)
#endif
	{
		mQueueIterator = mBackgroundQueue.begin();
	}

	SoundService::~SoundService()
	{
		for(auto music : mMusicList)
		{
			delete music.second;
		}

		mMusicList.clear();

		for(auto effect : mEffectsList)
		{
			delete effect.second;
		}

		mEffectsList.clear();
	}

	void SoundService::Start()
	{
		if(mbIsInitialized) return;

		mbIsInitialized = true;
		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Audio : Started making Audio Engine"));

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
			star::Logger::GetInstance()->Log(star::LogLevel::Info, 
				_T("Audio :Could not init Ogg and Mp3, reason : ") +
				string_cast<tstring>(Mix_GetError()));
		}

		if(Mix_OpenAudio(audio_rate, audio_format,audio_channels,audio_buffers))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info,
				_T("Audio : Could Not open Audio Mix SDL"));
			Stop();
			return;
		}

		//check What we got
		int32 actual_rate, actual_channels;
		uint16 actual_format;

		Mix_QuerySpec(&actual_rate,&actual_format,&actual_channels);
		tstringstream buffer;
		buffer << "Actual Rate : " << actual_rate;
		buffer << ", Actual Format : " << actual_format;
		buffer << ", Actual Channels : " << actual_channels;
		buffer << std::endl;
		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Audio : SDL specs : ") + buffer.str());
		Mix_Volume(-1,100);
#else
		
		SLresult lRes;
		const SLuint32 lEngineMixIIDCount = 1;
		const SLInterfaceID lEngineMixIIDs[] = { SL_IID_ENGINE };
		const SLboolean lEngineMixReqs[] = { SL_BOOLEAN_TRUE };
		const SLuint32 lOutputMixIIDCount= 1;
		const SLInterfaceID lOutputMixIIDs[] = { SL_IID_VOLUME };
		const SLboolean lOutputMixReqs[] = { SL_BOOLEAN_FALSE};

		lRes = slCreateEngine(
			&mEngineObj,
			0,
			NULL,
			lEngineMixIIDCount,
			lEngineMixIIDs,
			lEngineMixReqs
			);

		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Audio : Can't make Audio Engine"));
			Stop();
			return;
		}

		lRes = (*mEngineObj)->Realize(mEngineObj, SL_BOOLEAN_FALSE);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Audio : Can't realize Engine"));
			Stop();
			return;
		}

		lRes = (*mEngineObj)->GetInterface(
			mEngineObj,
			SL_IID_ENGINE,
			&mEngine
			);

		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Audio : Can't fetch engine interface"));
			Stop();
			return;
		}

		lRes = (*mEngine)->CreateOutputMix(
			mEngine,
			&mOutputMixObj,
			lOutputMixIIDCount,
			lOutputMixIIDs,
			lOutputMixReqs
			);

		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Audio : Can't create outputmix"));
			Stop();
			return;
		}

		lRes = (*mOutputMixObj)->Realize(mOutputMixObj,SL_BOOLEAN_FALSE);
		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Audio : Can't realise output object"));
			Stop();
			return;
		}

		lRes = (*mOutputMixObj)->GetInterface(
			mOutputMixObj,
			SL_IID_VOLUME,
			&mOutputMixVolume
			);

		if(lRes != SL_RESULT_SUCCESS)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Warning,
				_T("Audio : Can't get volume interface!"));
			mOutputMixVolume = nullptr;
		}
		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Audio : Succesfull made Audio Engine"));
#endif
	}

	void SoundService::Stop()
	{
		StopAllSounds();
		DeleteAllSounds();

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
		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Audio : Stopped audio Engine"));
	}

	void SoundService::LoadMusic(const tstring& path, const tstring& name)
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mMusicList.find(name) != mMusicList.end())
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Sound Service: The music file '") + name +
				_T("' is already loaded."));
			return;
		}

		auto pathit = mMusicPathList.find(path);
		if(pathit != mMusicPathList.end())
		{
			star::Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Sound Service : Sound File Path Already Exists"));
			tstring nameold = pathit->second;
			auto nameit = mMusicList.find(nameold);
			if(nameit != mMusicList.end())
			{
				star::Logger::GetInstance()->Log(LogLevel::Warning,
					_T("Sound Service: Found sound file of old path, making copy for new name"));
				mMusicList[name] = nameit->second;
				return;
			}
			mMusicPathList.erase(pathit);
			return;
		}

		SoundFile* music = new SoundFile(path);
		mMusicList[name] = music;
		mMusicPathList[path] = name;
		return;
	}

	void SoundService::LoadSoundEffect(const tstring& path, const tstring& name)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		if(mEffectsList.find(name) != mEffectsList.end())
		{
			star::Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Sound Service: The effect '") + name +
				_T("' already exists."));
		}

		auto pathit = mSoundEffectPathList.find(path);
		if(pathit != mSoundEffectPathList.end())
		{
			star::Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Sound Service: Sound Effect Path Already Exists"));
			tstring nameold = pathit->second;
			auto nameit = mMusicList.find(nameold);
			if(nameit!= mMusicList.end())
			{
				star::Logger::GetInstance()->
					Log(LogLevel::Warning,
					_T("Sound Service: Found Sound Effect of old path, making copy for new name"));
				mMusicList[name] = nameit->second;
			}
			mSoundEffectPathList.erase(pathit);
		}

		SoundEffect* effect = new SoundEffect(path);
		mEffectsList[name] = effect;
		mSoundEffectPathList[path] = name;
	}

	void SoundService::PlayMusic(
		const tstring& path,
		const tstring& name,
		int loopTimes,
		float volume
		)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		if(mMusicList.find(name) == mMusicList.end())
		{
			LoadMusic(path, name);
		}
		return PlayMusic(name, loopTimes, volume * GetVolume());
	}

	void SoundService::PlayMusic(
		const tstring& name,
		int loopTimes,
		float volume
		)
	{
		ASSERT(mSoundService != nullptr, _T("Sound Service is invalid."));

		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			if(m_CurrentSoundFile != nullptr) m_CurrentSoundFile->Stop();
			m_CurrentSoundFile = mMusicList[name];
			m_CurrentSoundFile->Play(loopTimes);
			m_CurrentSoundFile->SetVolume(volume * GetVolume());
			return;
		}
		else
		{
			m_CurrentSoundFile = nullptr;
			star::Logger::GetInstance()->
				Log(LogLevel::Warning,
				_T("Sound Service: Couldn't find the song '") + name +
				_T("'."));
		}
		
	}

	void SoundService::PlaySoundEffect(
		const tstring& path,
		const tstring& name,
		int loopTimes,
		float volume
		)
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mEffectsList.find(name) == mEffectsList.end())
		{
			LoadSoundEffect(path, name);
		}
		PlaySoundEffect(name, loopTimes, volume * GetVolume());
	}

	void SoundService::PlaySoundEffect(
		const tstring& name,
		int loopTimes,
		float volume
		)
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			m_CurrentSoundEffect = mEffectsList[name];
			m_CurrentSoundEffect->Play(loopTimes);
			m_CurrentSoundEffect->SetVolume(volume * GetVolume());
		}
		else
		{
			star::Logger::GetInstance()->
				Log(LogLevel::Warning,
				_T("Sound Service: Couldn't find effect '") + name +
				_T("'."));
		}
		
	}

	void SoundService::AddToBackgroundQueue(const tstring& name)
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			mBackgroundQueue.push_back(mMusicList[name]);
		}
		else
		{
			star::Logger::GetInstance()->
				Log(LogLevel::Warning,
				_T("Sound Service: Couldn't find background song '") + name +
				_T("'."));
		}
	}

	void SoundService::PlayBackgroundQueue()
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		mQueueIterator = mBackgroundQueue.begin();
		if(mQueueIterator != mBackgroundQueue.end())
		{
			(*mQueueIterator)->PlayQueued(0);
		}
		else
		{
			star::Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Sound Service : No song in background queue."));
		}
	}

	void SoundService::PlayNextSongInQueue()
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mBackgroundQueue.size() == 0)
		{
			return;
		}

		++mQueueIterator;
		if(mQueueIterator != mBackgroundQueue.end())
		{
			(*mQueueIterator)->PlayQueued(0);
		}
		else
		{
			mQueueIterator==mBackgroundQueue.begin();
			(*mQueueIterator)->PlayQueued(0);
		}
	}

	void SoundService::SetMusicVolume(const tstring& name, float volume)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->SetVolume(volume * GetVolume());
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::SetMusicVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	float SoundService::GetMusicVolume(const tstring& name) const
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			if(GetVolume() == 0)
			{
				return 0;
			}
			else
			{
				return it->second->GetVolume() / GetVolume();
			}
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::SetMusicVolume: Couldn't find '") +
				name + _T("'."));
		}
		return 0;
	}

	void SoundService::SetEffectVolume(const tstring& name, float volume)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->SetVolume(volume * GetVolume());
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::SetEffectVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	float SoundService::GetEffectVolume(const tstring& name) const
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			if(GetVolume() == 0)
			{
				return 0;
			}
			else
			{
				return it->second->GetVolume() / GetVolume();
			}
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::GetEffectVolume: Couldn't find '") +
				name + _T("'."));
		}
		return 0;
	}

	void SoundService::IncreaseMusicVolume(const tstring& name, float volume)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->IncreaseVolume(volume * GetVolume());
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::IncreaseMusicVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	void SoundService::DecreaseMusicVolume(const tstring& name, float volume)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->DecreaseVolume(volume * GetVolume());
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::DecreaseMusicVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	void SoundService::IncreaseEffectVolume(const tstring& name, float volume)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->IncreaseVolume(volume * GetVolume());
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::IncreaseEffectVolume: Couldn't find '") +
				name + _T("'."));
		}
	}
	void SoundService::DecreaseEffectVolume(const tstring& name, float volume)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->DecreaseVolume(volume * GetVolume());
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::DecreaseEffectVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	void SoundService::SetMusicMuted(const tstring& name, bool muted)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->SetMuted(muted);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::SetMusicMuted: Couldn't find '") +
				name + _T("'."));
		}
	}

	bool SoundService::IsMusicMuted(const tstring& name) const
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			return it->second->IsMuted();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::IsMusicMuted: Couldn't find '") +
				name + _T("'."));
			return false;
		}
	}

	void SoundService::SetEffectMuted(const tstring& name, bool muted)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->SetMuted(muted);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::SetEffectMuted: Couldn't find '") +
				name + _T("'."));
		}
	}

	bool SoundService::IsEffectMuted(const tstring& name) const
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			return it->second->IsMuted();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("SoundService::IsEffectMuted: Couldn't find '") +
				name + _T("'."));
			return false;
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

	void SoundService::StopAllSounds()
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		for(auto song : mMusicList)
		{
			song.second->Stop();
		}

		for(auto effect : mEffectsList)
		{
			effect.second->Stop();
		}
	}

	void SoundService::PauseAllSounds()
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		for(auto song : mMusicList)
		{
			song.second->Pause();
		}

		for(auto effect : mEffectsList)
		{
			effect.second->Pause();
		}
	}

	void SoundService::ResumeAllSounds()
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		for(auto song : mMusicList)
		{
			song.second->Resume();
		}

		for(auto effect : mEffectsList)
		{
			effect.second->Resume();
		}
	}

	void SoundService::DeleteAllSounds()
	{
		ASSERT(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		for(auto song : mMusicList)
		{
			delete song.second;
		}
		mMusicList.clear();

		for(auto effect : mEffectsList)
		{
			delete effect.second;
		}	
		mEffectsList.clear();
		
	}

	void SoundService::SetVolume(float volume)
	{
		float oldVol = m_Volume;
		m_Volume = Clamp(volume, 0.0f, 1.0f);

		for(auto song : mMusicList)
		{
			float vol = song.second->GetVolume();
			vol /= oldVol;
			vol *= m_Volume;
			song.second->SetVolume(vol);
		}

		for(auto effect : mEffectsList)
		{
			float vol = effect.second->GetVolume();
			vol /= oldVol;
			vol *= m_Volume;
			effect.second->SetVolume(vol);
		}
	}

	float SoundService::GetVolume() const
	{
		return m_Volume;
	}

	void SoundService::IncreaseVolume(float volume)
	{
		float vol = GetVolume();
		vol += volume;
		SetVolume(vol);
	}

	void SoundService::DecreaseVolume(float volume)
	{
		float vol = GetVolume();
		vol -= volume;
		SetVolume(vol);
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
