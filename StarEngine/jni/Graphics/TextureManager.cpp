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

	void TextureManager::LoadTexture(const tstring& path, const tstring& name)
	{

		if(mTextureMap.find(name) != mTextureMap.end())
		{
			return;
		}

		auto pathit = mPathList.find(path);
		if(pathit != mPathList.end())
		{
			tstring nameOld = pathit->second;
			auto nameit = mTextureMap.find(nameOld);
			if(nameit != mTextureMap.end())
			{
				mTextureMap[name] = nameit->second;
				return;
			}
			mPathList.erase(pathit);
			return;
		}

		mTextureMap[name] = std::make_shared<Texture2D>(path);
		
		mPathList[path] = name;
	}

	bool TextureManager::DeleteTexture(const tstring& name)
	{
		auto it = mTextureMap.find(name);
		if(it != mTextureMap.end())
		{
			mTextureMap.erase(it);
			return true;
		}
		return false;
	}

	GLuint TextureManager::GetTextureID(const tstring& name)
	{
		if(mTextureMap.find(name) != mTextureMap.end())
		{
			return mTextureMap[name]->GetTextureID();
		}
		return 0;
	}

	ivec2 TextureManager::GetTextureDimensions(const tstring& name)
	{
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
			mTextureMap[it->second] = std::make_shared<Texture2D>(it->first);
		}
		return true;
	}
}
