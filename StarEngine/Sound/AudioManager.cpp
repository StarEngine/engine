#include "AudioManager.h"
#include "../Logger.h"
#include "../Context.h"
//#include "Texture2D.h"

#ifndef _WIN32
#include "../EventLoop.h"
#endif

namespace star 
{
	AudioManager* AudioManager::mAudioManager = nullptr;

	void AudioManager::EraseSounds()
	{
		/*std::map<tstring, Texture2D*>::iterator iter;
		for(iter= mSoundsList.begin(); iter != mSoundsList.end(); ++iter)
		{
			mSoundsList.erase(iter);
		}
		mPathList.clear();*/
	}


	AudioManager* AudioManager::GetInstance()
	{
		if(mAudioManager == nullptr)
		{
			mAudioManager = new AudioManager();
		}
		return (mAudioManager);
	}

	bool AudioManager::LoadSound(const tstring& path, const tstring& name)
	{
		if(mAudioManager == nullptr)
		{
			return (false);
		}

		/*if(std::find(mPathList.begin(), mPathList.end(), path)!=mPathList.end())
		{
			return (false);
		}*/
		/*
		if(mSoundsList.find(name) != mSoundsList.end())
		{
			return (false);
		}

#ifdef _WIN32

		Texture2D* temp = new Texture2D(path);
#else
		Texture2D* temp = new Texture2D(path,star::EventLoop::mApplicationPtr);
#endif
		mTextureList[name] = temp;
		//mPathList.push_back(path);
*/
		return (true);
	}

	bool AudioManager::DeleteSound(const tstring& name)
	{
		/*
		auto it = mSoundsList.find(name);
		if(it != mSoundsList.end())
		{
			mSoundsList.erase(it);
			return (true);
		}
		*/
		return (false);
	}

	GLuint AudioManager::GetSound(const tstring& name)
	{
		/*
		ASSERT(mAudioManager != nullptr, _T("Sound manager is invalid."));
		if(mAudioManager == nullptr)
		{
			return 0;
		}

		if(mSoundsList.find(name) != mSoundsList.end())
		{
			return mSoundsList[name]->getTextureID();
		}
		*/
		return 0;
	}
}
