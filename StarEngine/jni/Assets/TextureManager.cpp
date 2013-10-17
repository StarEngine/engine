#include "TextureManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "Texture2D.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star 
{
	std::shared_ptr<TextureManager> TextureManager::mTextureManager = nullptr;
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

		if(mTextureMap.find(name) != mTextureMap.end())
		{
			return (false);
		}

#ifdef DESKTOP
		mTextureMap[name] = std::shared_ptr<Texture2D>(new Texture2D(path));
#else
		mTextureMap[name] = std::shared_ptr<Texture2D>(new Texture2D(path, star::StarEngine::GetInstance()->GetAndroidApp()));
#endif
		
		// [COMMENT] Remove commented Code! Ty...
		//mPathList.push_back(path);

		return (true);
	}

	bool TextureManager::DeleteTexture(const tstring& name)
	{
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
		//[COMMENT] Why assert and check? It should break before it ever gets the chance to exit the function
		ASSERT(mTextureManager != nullptr, _T("Texture manager is invalid."));
		// [COMMENT] Remove commented Code! Ty...
		//if(mTextureManager == nullptr)
		//{
		//	return 0;
		//}

		if(mTextureMap.find(name) != mTextureMap.end())
		{
			return mTextureMap[name]->GetTextureID();
		}
		return 0;
	}

	//ivec2 contains first width, then height
	// [COMMENT] oh Really? Don't place obvious comments please...
	//	 1) That's local that it first contains width
	//	 2) You can see it in your code...
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
}
