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

	TextureManager::TextureManager(void)
		: mTextureList()
		, mPathList()
	{

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

		// [COMMENT] Remove commented Code! Ty...

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
		// [COMMENT] Remove commented Code! Ty...
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
		// [COMMENT] Remove commented Code! Ty...
		//if(mTextureManager == nullptr)
		//{
		//	return 0;
		//}

		if(mTextureList.find(name) != mTextureList.end())
		{
			return mTextureList[name]->GetTextureID();
		}
		return 0;
	}

	//ivec2 contains first width, then height
	// [COMMENT] oh Really? Don't place obvious comments please...
	//	 1) That's local that it first contains width
	//	 2) You can see it in your code...
	ivec2 TextureManager::GetTextureDimensions(const tstring& name)
	{
		auto it = mTextureList.find(name);
		if(it != mTextureList.end())
		{
			return (ivec2(it->second->GetWidth(), it->second->GetHeight()));
		}
		return ivec2(0,0);
	}

	void TextureManager::EraseTextures()
	{
		 auto iter = mTextureList.begin();
		 for(iter; iter != mTextureList.end(); ++iter)
		 {
			 delete iter->second;
		 }
		 mTextureList.clear();
		 mPathList.clear();
	}
}
