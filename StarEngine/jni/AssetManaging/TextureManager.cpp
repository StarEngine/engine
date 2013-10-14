#include "TextureManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "Texture2D.h"

#ifndef _WIN32
#include "../StarEngine.h"
#endif

namespace star 
{
	std::shared_ptr<TextureManager> TextureManager::mTextureManager = nullptr;
	TextureManager::~TextureManager()
	{
		for(auto texture : mTextureList)
		{
			delete texture.second;
		}
		mTextureList.clear();
		mPathList.clear();
	}

	std::shared_ptr<TextureManager> TextureManager::GetInstance()
	{
		if(mTextureManager == nullptr)
		{
			mTextureManager = std::shared_ptr<TextureManager>(new TextureManager());
		}
		return (mTextureManager);
	}

	bool TextureManager::LoadTexture(const tstring& path, const tstring& name)
	{
		if(mTextureManager == nullptr)
		{
			return (false);
		}

		/*if(std::find(mPathList.begin(), mPathList.end(), path)!=mPathList.end())
		{
			return (false);
		}*/

		if(mTextureList.find(name) != mTextureList.end())
		{
			return (false);
		}

#ifdef _WIN32

		Texture2D* temp = new Texture2D(path);
#else
		Texture2D* temp = new Texture2D(path, star::StarEngine::GetInstance()->GetAndroidApp());
#endif
		mTextureList[name] = temp;
		//mPathList.push_back(path);

		return (true);
	}

	bool TextureManager::DeleteTexture(const tstring& name)
	{
		auto it = mTextureList.find(name);
		if(it != mTextureList.end())
		{
			delete it->second;
			mTextureList.erase(it);
			return (true);
		}
		return (false);
	}

	GLuint TextureManager::GetTextureID(const tstring& name)
	{
		//[COMMENT] Why assert and check? It should break before it ever gets the chance to exit the function
		ASSERT(mTextureManager != nullptr, _T("Texture manager is invalid."));
		//if(mTextureManager == nullptr)
		//{
		//	return 0;
		//}

		if(mTextureList.find(name) != mTextureList.end())
		{
			return mTextureList[name]->getTextureID();
		}
		return 0;
	}

	//ivec2 contains first width, then height
	ivec2 TextureManager::GetTextureDimensions(const tstring& name)
	{
		auto it = mTextureList.find(name);
		if(it != mTextureList.end())
		{
			return (ivec2(it->second->getWidth(),it->second->getHeight()));
		}
		return ivec2(0,0);
	}
}
