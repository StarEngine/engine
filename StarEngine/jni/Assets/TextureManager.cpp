#include "TextureManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "Texture2D.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star 
{
	TextureManager * TextureManager::mTextureManager = nullptr;
	TextureManager::~TextureManager()
	{
		mTextureMap.clear();
		mPathList.clear();
	}

	TextureManager::TextureManager(void)
		: mTextureMap()
		, mPathList()
	{

	}

	TextureManager * TextureManager::GetInstance()
	{
		if(mTextureManager == nullptr)
		{
			mTextureManager = new TextureManager();
		}
		return (mTextureManager);
	}

	bool TextureManager::LoadTexture(const tstring& path, const tstring& name)
	{
		Logger::GetInstance()->Log(mTextureManager != nullptr,
			_T("Texture manager is invalid."), STARENGINE_LOG_TAG);


		if(mTextureMap.find(name) != mTextureMap.end())
		{
			return (false);
		}

		auto pathit = mPathList.find(path);
		if(pathit != mPathList.end())
		{
			tstring nameold = pathit->second;
			auto nameit = mTextureMap.find(nameold);
			if(nameit!= mTextureMap.end())
			{
				mTextureMap[name] = nameit->second;
				return (true);
			}
			mPathList.erase(pathit);
			return (false);
		}



#ifdef DESKTOP
		mTextureMap[name] = std::make_shared<Texture2D>(path);
#else
		mTextureMap[name] = std::make_shared<Texture2D>(path, star::StarEngine::GetInstance()->GetAndroidApp());
#endif
		
		mPathList[path]=name;

		return (true);
	}

	bool TextureManager::DeleteTexture(const tstring& name)
	{
		Logger::GetInstance()->Log(mTextureManager != nullptr,
			_T("Texture manager is invalid."), STARENGINE_LOG_TAG);

		auto it = mTextureMap.find(name);
		if(it != mTextureMap.end())
		{
			mTextureMap.erase(it);
			return (true);
		}
		return (false);
	}

	GLuint TextureManager::GetTextureID(const tstring& name)
	{
		Logger::GetInstance()->Log(mTextureManager != nullptr,
			_T("Texture manager is invalid."), STARENGINE_LOG_TAG);

		if(mTextureMap.find(name) != mTextureMap.end())
		{
			return mTextureMap[name]->GetTextureID();
		}
		return 0;
	}

	ivec2 TextureManager::GetTextureDimensions(const tstring& name)
	{
		Logger::GetInstance()->Log(mTextureManager != nullptr,
			_T("Texture manager is invalid."), STARENGINE_LOG_TAG);

		auto it = mTextureMap.find(name);
		if(it != mTextureMap.end())
		{
			return (ivec2(it->second->GetWidth(), it->second->GetHeight()));
		}
		return ivec2(0,0);
	}

	void TextureManager::EraseAllTextures()
	{
		 mTextureMap.clear();
		 mPathList.clear();
	}

	bool TextureManager::ReloadAllTextures()
	{
		mTextureMap.clear();
		for(auto it = mPathList.begin(); it != mPathList.end(); ++it)
		{
#ifdef DESKTOP
			mTextureMap[it->second] = std::make_shared<Texture2D>(it->first);
#else
			mTextureMap[it->second] = std::make_shared<Texture2D>(it->first, star::StarEngine::GetInstance()->GetAndroidApp());
#endif
		}
		return (true);
	}
}
