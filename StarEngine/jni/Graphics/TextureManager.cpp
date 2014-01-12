#include "TextureManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "Texture2D.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star 
{
	TextureManager::~TextureManager()
	{
		m_TextureMap.clear();
		m_PathList.clear();
	}

	TextureManager::TextureManager(void)
		: m_TextureMap()
		, m_PathList()
	{

	}

	void TextureManager::LoadTexture(const tstring& path, const tstring& name)
	{

		if(m_TextureMap.find(name) != m_TextureMap.end())
		{
			return;
		}

		auto pathit = m_PathList.find(path);
		if(pathit != m_PathList.end())
		{
			tstring nameOld = pathit->second;
			auto nameit = m_TextureMap.find(nameOld);
			if(nameit != m_TextureMap.end())
			{
				m_TextureMap[name] = nameit->second;
				return;
			}
			m_PathList.erase(pathit);
			return;
		}

		m_TextureMap[name] = std::make_shared<Texture2D>(path);
		
		m_PathList[path] = name;
	}

	bool TextureManager::DeleteTexture(const tstring& name)
	{
		auto it = m_TextureMap.find(name);
		if(it != m_TextureMap.end())
		{
			m_TextureMap.erase(it);
			return true;
		}
		return false;
	}

	GLuint TextureManager::GetTextureID(const tstring& name)
	{
		if(m_TextureMap.find(name) != m_TextureMap.end())
		{
			return m_TextureMap[name]->GetTextureID();
		}
		return 0;
	}

	ivec2 TextureManager::GetTextureDimensions(const tstring& name)
	{
		auto it = m_TextureMap.find(name);
		if(it != m_TextureMap.end())
		{
			return (ivec2(it->second->GetWidth(), it->second->GetHeight()));
		}
		return ivec2(0,0);
	}

	void TextureManager::EraseAllTextures()
	{
		 m_TextureMap.clear();
		 m_PathList.clear();
	}

	bool TextureManager::ReloadAllTextures()
	{
		m_TextureMap.clear();
		for(auto it = m_PathList.begin(); it != m_PathList.end(); ++it)
		{
			m_TextureMap[it->second] = std::make_shared<Texture2D>(it->first);
		}
		return true;
	}
}
