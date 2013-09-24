#include "TextureManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "Texture2D.h"

namespace star 
{
	TextureManager* TextureManager::mTextureManager = nullptr;
	TextureManager::~TextureManager(void)
	{
		std::map<tstring, Texture2D*>::iterator iter;
		for(iter= mTextureList.begin(); iter != mTextureList.end();++iter)
		{
			mTextureList.erase(iter);
		}

		mPathList.clear();

	}


	TextureManager* TextureManager::GetInstance()
	{
		if(mTextureManager == nullptr)
		{
			mTextureManager = new TextureManager();
		}
		return mTextureManager;
	}

	bool TextureManager::LoadTexture(tstring path, tstring name)
	{
		if(mTextureManager==nullptr)return false;

		if(std::find(mPathList.begin(), mPathList.end(), path)!=mPathList.end())return false;

		if(mTextureList.find(name) != mTextureList.end())return false;

		Texture2D* temp = new Texture2D(path);
		mTextureList[name] = temp;
		mPathList.push_back(path);

		return true;
	}

	const GLuint& TextureManager::GetTextureID(tstring name)
	{
		if(mTextureManager ==nullptr)return false;

		if(mTextureList.find(name) != mTextureList.end())
		{
			return mTextureList[name]->getTextureID();
		}
		return NULL;
	}

}
