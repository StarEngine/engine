#pragma once

#include <map>
#include <memory>
#include "../defines.h"
#include "../Helpers/Singleton.h"

#ifdef DESKTOP
#include <glew.h>
#else
#include "GLES/gl.h"
#endif

namespace star
{
	class Texture2D;

	class TextureManager final : public Singleton<TextureManager>
	{
	public:
		friend Singleton<TextureManager>;

		void LoadTexture(const tstring& path, const tstring& name);
		bool DeleteTexture(const tstring& name);
		GLuint GetTextureID(const tstring& name);
		ivec2 GetTextureDimensions(const tstring& name);
		void EraseAllTextures();
		bool ReloadAllTextures();

	private:
		std::map<tstring, std::shared_ptr<Texture2D>> m_TextureMap;
		std::map<tstring,tstring> m_PathList;

		TextureManager();
		~TextureManager();

		TextureManager(const TextureManager& yRef);
		TextureManager(TextureManager&& yRef);
		TextureManager& operator=(const TextureManager& yRef);
		TextureManager& operator=(TextureManager&& yRef);
	};
}
