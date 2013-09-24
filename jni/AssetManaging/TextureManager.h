#pragma once

#include <map>
#include <vector>
#include "../defines.h"
#include "libs/OpenGL/GLEW/include/GL/glew.h"

namespace star
{
	class Texture2D;

	class TextureManager
	{
	public:
		~TextureManager(void);

		static TextureManager* GetInstance();

		bool LoadTexture(tstring path, tstring name);
		const GLuint& GetTextureID(tstring name);

	private:
		//Data Members
		static TextureManager* mTextureManager;
		std::map<tstring, Texture2D*> mTextureList;
		std::vector<tstring> mPathList;

		TextureManager(void){}

		//disabling default copy constructor
		TextureManager(const TextureManager& yRef);
		TextureManager& operator=(const TextureManager& yRef);
	};
}
