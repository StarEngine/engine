#include "AudioManager.h"
#include "../Logger.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/Math.h"

#ifdef ANDROID
#include "../Assets/Resource.h"
#endif

namespace star
{
	AudioManager * AudioManager::mSoundService = nullptr;
	bool AudioManager::mbIsInitialized = false;

	AudioManager * AudioManager::GetInstance()
	{
		if(mSoundService == nullptr)
		{
			mSoundService = new AudioManager();
		}
		return mSoundService;
	}

	AudioManager::AudioManager()
		: mMusicList()
		, mMusicPathList()
		, mEffectsList()
		, mSoundEffectPathList()
		, mBackgroundQueue()
		, mQueueIterator()
		, mChannels()
		, mEmptyChannel()
		, mCurrentSoundFile(nullptr)
		, mCurrentSoundEffect(nullptr)
		, mVolume(1.0f)
		, mbMusicMuted(false)
		, mbSoundEffectsMuted(false)
#ifdef ANDROID
		, mEngineObj(nullptr)
		, mEngine(nullptr)
		, mOutputMixObj(nullptr)
		, mOutputMixVolume(nullptr)
#endif
	{
		mQueueIterator = mBackgroundQueue.begin();
	}

	AudioManager::~AudioManager()
	{
		for(auto & music : mMusicList)
		{
			delete music.second;
		}

		mMusicList.clear();

		for(auto & effect : mEffectsList)
		{
			delete effect.second;
		}

		mEffectsList.clear();

		mChannels.clear();
	}

	void AudioManager::Start()
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
		int32 flags = MIX_INIT_OGG | MIX_INIT_MP3;
		int32 innited = Mix_Init(flags);
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
		Mix_AllocateChannels(16);

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

	void AudioManager::Stop()
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

	void AudioManager::LoadMusic(const tstring& path, const tstring& name, uint8 channel)
	{
		LoadMusic(path, name, 1.0f, channel);
	}

	void AudioManager::LoadSoundEffect(const tstring& path, const tstring& name, uint8 channel)
	{
		LoadSoundEffect(path, name, 1.0f, channel);
	}

	void AudioManager::LoadMusic(
		const tstring& path,
		const tstring& name,
		float32 volume,
		uint8 channel
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
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

		SoundFile* music = new SoundFile(path, channel);
		music->SetCompleteVolume(
			volume,
			GetChannelVolume(channel),
			GetVolume()
			);
		mMusicList[name] = music;
		mMusicPathList[path] = name;
		return;
	}

	void AudioManager::LoadSoundEffect(
		const tstring& path,
		const tstring& name,
		float32 volume,
		uint8 channel
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

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

		SoundEffect* effect = new SoundEffect(path, channel);
		effect->SetCompleteVolume(
			volume,
			GetChannelVolume(channel),
			GetVolume()
			);
		mEffectsList[name] = effect;
		mSoundEffectPathList[path] = name;
	}

	void AudioManager::PlayMusic(
		const tstring& path,
		const tstring& name,
		uint8 channel,
		int32 loopTimes
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbMusicMuted)return;

		if(mMusicList.find(name) == mMusicList.end())
		{
			LoadMusic(path, name, channel);
		}
		return PlayMusic(name, loopTimes);
	}

	void AudioManager::PlayMusic(
		const tstring& name,
		int32 loopTimes
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbMusicMuted)return;

		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			if(mCurrentSoundFile != nullptr) mCurrentSoundFile->Stop();
			mCurrentSoundFile = mMusicList[name];
			mCurrentSoundFile->Play(loopTimes);
			return;
		}
		else
		{
			mCurrentSoundFile = nullptr;
			star::Logger::GetInstance()->
				Log(LogLevel::Warning,
				_T("AudioManager::PlayMusic: Couldn't find the song '") + name +
				_T("'."));
		}
	}

	void AudioManager::PlaySoundEffect(
		const tstring& path,
		const tstring& name,
		uint8 channel,
		int32 loopTimes
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbSoundEffectsMuted)return;

		if(mEffectsList.find(name) == mEffectsList.end())
		{
			LoadSoundEffect(path, name, channel);
		}
		PlaySoundEffect(name, loopTimes);
	}

	void AudioManager::PlaySoundEffect(
		const tstring& name,
		int32 loopTimes
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbSoundEffectsMuted)return;

		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			mCurrentSoundEffect = mEffectsList[name];
			mCurrentSoundEffect->Play(loopTimes);
		}
		else
		{
			star::Logger::GetInstance()->
				Log(LogLevel::Warning,
				_T("AudioManager::PlaySoundEffect: Couldn't find effect '") + name +
				_T("'."));
		}
	}

	void AudioManager::PlayMusic(
		const tstring& path,
		const tstring& name,
		float32 volume,
		uint8 channel,
		int32 loopTimes
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbMusicMuted)return;

		if(mMusicList.find(name) == mMusicList.end())
		{
			LoadMusic(path, name, channel);
		}
		return PlayMusic(name, volume, loopTimes);
	}

	void AudioManager::PlayMusic(
		const tstring& name,
		float32 volume,
		int32 loopTimes
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbMusicMuted)return;

		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			if(mCurrentSoundFile != nullptr) mCurrentSoundFile->Stop();
			mCurrentSoundFile = mMusicList[name];
			mCurrentSoundFile->Play(loopTimes);
			mCurrentSoundFile->SetBaseVolume(volume);
			return;
		}
		else
		{
			mCurrentSoundFile = nullptr;
			star::Logger::GetInstance()->
				Log(LogLevel::Warning,
				_T("AudioManager::PlayMusic: Couldn't find the song '") + name +
				_T("'."));
		}
	}

	void AudioManager::PlaySoundEffect(
		const tstring& path,
		const tstring& name,
		float32 volume,
		uint8 channel,
		int32 loopTimes
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbSoundEffectsMuted)return;

		if(mEffectsList.find(name) == mEffectsList.end())
		{
			LoadSoundEffect(path, name, channel);
		}
		PlaySoundEffect(name, volume, loopTimes);
	}

	void AudioManager::PlaySoundEffect(
		const tstring& name,
		float32 volume,
		int32 loopTimes
		)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbSoundEffectsMuted)return;

		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			mCurrentSoundEffect = mEffectsList[name];
			mCurrentSoundEffect->Play(loopTimes);
			mCurrentSoundEffect->SetBaseVolume(volume);
		}
		else
		{
			star::Logger::GetInstance()->
				Log(LogLevel::Warning,
				_T("AudioManager::PlaySoundEffect: Couldn't find effect '") + name +
				_T("'."));
		}
	}

	void AudioManager::AddToBackgroundQueue(const tstring& name)
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
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
				_T("SoundService::AddToBackgroundQueue: Couldn't find background song '") + name +
				_T("'."));
		}
	}

	void AudioManager::PlayBackgroundQueue()
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbMusicMuted)return;

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

	void AudioManager::PlayNextSongInQueue()
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		if(mbMusicMuted)return;

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
			mQueueIterator == mBackgroundQueue.begin();
			(*mQueueIterator)->PlayQueued(0);
		}
	}

	void AudioManager::PauseMusic(const tstring & name)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->Pause();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::PauseMusic: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::ResumeMusic(const tstring & name)
	{

		if(mbMusicMuted)return;

		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->Resume();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::ResumeMusic: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::StopMusic(const tstring & name)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->Stop();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::StopMusic: Couldn't find '") +
				name + _T("'."));
		}
	}

	bool AudioManager::IsMusicPaused(const tstring & name) const
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			return it->second->IsPaused();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsMusicPaused: Couldn't find '") +
				name + _T("'."));
		}
		return false;
	}

	bool AudioManager::IsMusicStopped(const tstring & name) const
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			return it->second->IsStopped();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsMusicStopped: Couldn't find '") +
				name + _T("'."));
		}
		return false;
	}

	bool AudioManager::IsMusicPlaying(const tstring & name) const
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			return it->second->IsPlaying();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsMusicPlaying: Couldn't find '") +
				name + _T("'."));
		}
		return false;
	}

	bool AudioManager::IsMusicLooping(const tstring & name) const
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			return it->second->IsLooping();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsMusicLooping: Couldn't find '") +
				name + _T("'."));
		}
		return false;
	}

	void AudioManager::PauseEffect(const tstring & name)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->Pause();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::PauseEffect: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::ResumeEffect(const tstring & name)
	{

		if(mbSoundEffectsMuted)return;

		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->Resume();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::ResumeEffect: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::StopEffect(const tstring & name)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->Stop();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::StopEffect: Couldn't find '") +
				name + _T("'."));
		}
	}

	bool AudioManager::IsEffectPaused(const tstring & name) const
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			return it->second->IsPaused();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsEffectPaused: Couldn't find '") +
				name + _T("'."));
		}
		return false;
	}

	bool AudioManager::IsEffectStopped(const tstring & name) const
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			return it->second->IsStopped();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsEffectStopped: Couldn't find '") +
				name + _T("'."));
		}
		return false;
	}

	bool AudioManager::IsEffectPlaying(const tstring & name) const
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			return it->second->IsPlaying();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsEffectPlaying: Couldn't find '") +
				name + _T("'."));
		}
		return false;
	}

	bool AudioManager::IsEffectLooping(const tstring & name) const
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			return it->second->IsLooping();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsEffectLooping: Couldn't find '") +
				name + _T("'."));
		}
		return false;
	}

	void AudioManager::SetMusicVolume(const tstring& name, float32 volume)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->SetBaseVolume(volume);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::SetMusicVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	float32 AudioManager::GetMusicVolume(const tstring& name) const
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			return it->second->GetVolume();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::SetMusicVolume: Couldn't find '") +
				name + _T("'."));
		}
		return 0;
	}

	void AudioManager::SetEffectVolume(const tstring& name, float32 volume)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->SetBaseVolume(volume);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::SetEffectVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	float32 AudioManager::GetEffectVolume(const tstring& name) const
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			return it->second->GetVolume();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::GetEffectVolume: Couldn't find '") +
				name + _T("'."));
		}
		return 0;
	}

	void AudioManager::IncreaseMusicVolume(const tstring& name, float32 volume)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->IncreaseVolume(volume);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IncreaseMusicVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::DecreaseMusicVolume(const tstring& name, float32 volume)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->DecreaseVolume(volume);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::DecreaseMusicVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::IncreaseEffectVolume(const tstring& name, float32 volume)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->IncreaseVolume(volume);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IncreaseEffectVolume: Couldn't find '") +
				name + _T("'."));
		}
	}
	void AudioManager::DecreaseEffectVolume(const tstring& name, float32 volume)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->DecreaseVolume(volume);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::DecreaseEffectVolume: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::MuteAllMusic( bool mute )
	{
		mbMusicMuted=mute;
		for(auto& it : mMusicList)
		{
			it.second->SetMuted(mute);
		}
	}

	void AudioManager::SetMusicMuted(const tstring& name, bool muted)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->SetMuted(muted);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::SetMusicMuted: Couldn't find '") +
				name + _T("'."));
		}
	}

	bool AudioManager::IsMusicMuted(const tstring& name) const
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			return it->second->IsMuted();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsMusicMuted: Couldn't find '") +
				name + _T("'."));
			return false;
		}
	}

	void AudioManager::MuteAllSoundEffects( bool mute )
	{
		mbSoundEffectsMuted=mute;
		for(auto& it : mEffectsList)
		{
			it.second->SetMuted(mute);
		}
	}

	void AudioManager::SetEffectMuted(const tstring& name, bool muted)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->SetMuted(muted);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::SetEffectMuted: Couldn't find '") +
				name + _T("'."));
		}
	}

	bool AudioManager::IsEffectMuted(const tstring& name) const
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			return it->second->IsMuted();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::IsEffectMuted: Couldn't find '") +
				name + _T("'."));
			return false;
		}
	}

	bool AudioManager::ToggleMusicMuted(const tstring& name)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->SetMuted(!it->second->IsMuted());
			return it->second->IsMuted();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::ToggleMusicMuted: Couldn't find '") +
				name + _T("'."));
			return false;
		}
	}

	bool AudioManager::ToggleEffectMuted(const tstring& name)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->SetMuted(!it->second->IsMuted());
			return it->second->IsMuted();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::ToggleEffectMuted: Couldn't find '") +
				name + _T("'."));
			return false;
		}
	}

	void AudioManager::AddSoundToChannel(uint8 channel, BaseSound * pSound)
	{
		auto & chnl = mChannels[channel];
		auto it = chnl.mSounds.begin();
		auto end = chnl.mSounds.end();
		for(auto sound : chnl.mSounds)
		{
			if(sound == pSound)
			{
				Logger::GetInstance()->Log(LogLevel::Warning,
					_T("AudioManager::AddSoundToChannel: Trying to add a sound twice in channel '")
					+ string_cast<tstring>(channel) + _T("'."));
				return;
			}
		}
		pSound->SetChannelVolume(chnl.mVolume);
		chnl.mSounds.push_back(pSound);
		chnl.mChannel = channel;
		switch(chnl.mState)
		{
			case ChannelState::paused:
				pSound->Pause();
				break;
			case ChannelState::stopped:
				pSound->Stop();
				break;
		}
	}

	void AudioManager::RemoveSoundFromChannel(uint8 channel, BaseSound * pSound)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::RemoveSoundFromChannel"),
			result
			);
		if(result)
		{
			for(auto it = chnl.mSounds.begin() ;
				it != chnl.mSounds.end() ;
				++it
				)
			{
				if(*it == pSound)
				{
					pSound->SetChannelVolume(1.0f);
					chnl.mSounds.erase(it);
					return;
				}
			}
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("AudioManager::RemoveSoundFromChannel: Sound not found in channel '")
				+ string_cast<tstring>(channel) + _T("'."));
		}
	}

	void AudioManager::SetChannelVolume(uint8 channel, float32 volume)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::SetChannelVolume"),
			result
			);
		if(result)
		{
			chnl.SetVolume(volume);
		}
	}

	float32 AudioManager::GetChannelVolume(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::GetChannelVolume"),
			result
			);
		if(result)
		{
			return chnl.GetVolume();
		}
		return 0;
	}

	void AudioManager::IncreaseChannelVolume(uint8 channel, float32 volume)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::IncreaseChannelVolume"),
			result
			);
		if(result)
		{
			chnl.IncreaseVolume(volume);
		}
	}

	void AudioManager::DecreaseChannelVolume(uint8 channel, float32 volume)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::DecreaseChannelVolume"),
			result
			);
		if(result)
		{
			chnl.DecreaseVolume(volume);
		}
	}

	void AudioManager::SetChannelMuted(uint8 channel, bool muted)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::SetChannelMuted"),
			result
			);
		if(result)
		{
			chnl.SetMuted(muted);
		}
	}

	bool AudioManager::IsChannelMuted(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::IsChannelMuted"),
			result
			);
		if(result)
		{
			return chnl.IsMuted();
		}
		return false;
	}
	
	bool AudioManager::ToggleChannelMuted(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::ToggleChannelMuted"),
			result
			);
		if(result)
		{
			chnl.SetMuted(!chnl.IsMuted());
			return chnl.IsMuted();
		}
		return false;
	}

	void AudioManager::SetMusicChannel(const tstring & name, uint8 channel)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->SetChannel(channel);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::SetMusicChannel: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::UnsetMusicChannel(const tstring & name)
	{
		auto it = mMusicList.find(name);
		if(it != mMusicList.end())
		{
			it->second->UnsetChannel();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::SetMusicChannel: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::SetEffectChannel(const tstring & name, uint8 channel)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->SetChannel(channel);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::SetEffectChannel: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::UnsetEffectChannel(const tstring & name)
	{
		auto it = mEffectsList.find(name);
		if(it != mEffectsList.end())
		{
			it->second->UnsetChannel();
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("AudioManager::UnsetEffectChannel: Couldn't find '") +
				name + _T("'."));
		}
	}

	void AudioManager::PauseChannel(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::PauseChannel"),
			result
			);
		if(result)
		{
			for(auto sound : chnl.mSounds)
			{
				sound->Pause();
			}
			chnl.mState = ChannelState::paused;
		}
	}

	bool AudioManager::IsChannelPaused(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::IsChannelPaused"),
			result
			);
		if(result)
		{
			return chnl.mState == ChannelState::paused;
		}
		return false;
	}
		
	void AudioManager::ResumeChannel(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::ResumeChannel"),
			result
			);
		if(result)
		{
			for(auto sound : chnl.mSounds)
			{
				sound->Resume();
			}
			chnl.mState = ChannelState::playing;
		}
	}

	bool AudioManager::IsChannelPlaying(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::IsChannelPlaying"),
			result
			);
		if(result)
		{
			return chnl.mState == ChannelState::playing;
		}
		return false;
	}

	void AudioManager::StopChannel(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::StopChannel"),
			result
			);
		if(result)
		{
			for(auto sound : chnl.mSounds)
			{
				sound->Stop();
			}
			chnl.mState = ChannelState::stopped;
		}
	}

	bool AudioManager::IsChannelStopped(uint8 channel)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::IsChannelStopped"),
			result
			);
		if(result)
		{
			return chnl.mState == ChannelState::stopped;
		}
		return false;
	}
	
	void AudioManager::PlayChannel(uint8 channel, int32 loopTimes)
	{
		bool result;
		SoundChannel & chnl = GetChannel(
			channel,
			_T("AudioManager::StopChannel"),
			result
			);
		if(result)
		{
			for(auto sound : chnl.mSounds)
			{
				sound->Play(loopTimes);
			}
			chnl.mState = ChannelState::playing;
		}
	}

	void AudioManager::StopAllSounds()
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		for(auto & song : mMusicList)
		{
			song.second->Stop();
		}

		for(auto & effect : mEffectsList)
		{
			effect.second->Stop();
		}
	}

	void AudioManager::PauseAllSounds()
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		for(auto & song : mMusicList)
		{
			song.second->Pause();
		}

		for(auto & effect : mEffectsList)
		{
			effect.second->Pause();
		}
	}

	void AudioManager::ResumeAllSounds()
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		for(auto & song : mMusicList)
		{
			song.second->Resume();
		}

		for(auto & effect : mEffectsList)
		{
			effect.second->Resume();
		}
	}

	void AudioManager::DeleteAllSounds()
	{
		Logger::GetInstance()->Log(mSoundService != nullptr,
			_T("Sound Service is invalid."));

		for(auto & song : mMusicList)
		{
			delete song.second;
		}
		mMusicList.clear();

		for(auto & effect : mEffectsList)
		{
			delete effect.second;
		}	
		mEffectsList.clear();
		
	}

	void AudioManager::SetVolume(float32 volume)
	{
		mVolume = Clamp(volume, 0.0f, 1.0f);

		for(auto & song : mMusicList)
		{
			song.second->SetMasterVolume(volume);
		}

		for(auto & effect : mEffectsList)
		{
			effect.second->SetMasterVolume(volume);
		}
	}

	float32 AudioManager::GetVolume() const
	{
		return mVolume;
	}

	void AudioManager::IncreaseVolume(float32 volume)
	{
		float32 vol = GetVolume();
		vol += volume;
		SetVolume(vol);
	}

	void AudioManager::DecreaseVolume(float32 volume)
	{
		float32 vol = GetVolume();
		vol -= volume;
		SetVolume(vol);
	}

	AudioManager::SoundChannel & AudioManager::GetChannel(
		uint8 channel,
		const tstring & sender,
		bool & result
		)
	{
		auto it = mChannels.find(channel);
		result = it != mChannels.end();
		if(result)
		{
			return it->second;
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				sender + _T(": Couldn't find channel '")
				+ string_cast<tstring>(channel) + _T("'."));
		}
		return mEmptyChannel;
	}

#ifdef ANDROID
	const SLEngineItf& AudioManager::GetEngine() const
	{
		return mEngine;
	}

	const SLObjectItf& AudioManager::GetOutputMixObject() const
	{
		return mOutputMixObj;
	}


#endif

	AudioManager::SoundChannel::SoundChannel()
		: mVolume(1.0f)
		, mIsMuted(false)
		, mSounds()
		, mChannel(0)
		, mState(ChannelState::playing)
	{
	}

	AudioManager::SoundChannel::~SoundChannel()
	{
		for(auto it : mSounds)
		{
			it->SetChannelVolume(1.0f);
			it->UnsetChannel();
		}
		mSounds.clear();
	}

	void AudioManager::SoundChannel::SetVolume(float32 volume)
	{
		mVolume = Clamp(volume, 0.0f, 1.0f);
		for( auto it : mSounds)
		{
			it->SetChannelVolume(mVolume);
		}
	}

	float32 AudioManager::SoundChannel::GetVolume() const
	{
		return mVolume;
	}

	void AudioManager::SoundChannel::IncreaseVolume(float32 volume)
	{
		SetVolume(mVolume + volume);
	}

	void AudioManager::SoundChannel::DecreaseVolume(float32 volume)
	{
		SetVolume(mVolume - volume);
	}

	void AudioManager::SoundChannel::SetMuted(bool muted)
	{
		mIsMuted = muted;
		for( auto it : mSounds)
		{
			it->SetMuted(muted);
		}
	}

	bool AudioManager::SoundChannel::IsMuted() const
	{
		return mIsMuted;
	}
}
