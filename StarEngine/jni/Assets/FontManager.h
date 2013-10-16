#pragma once

#ifdef _WIN32

#include <map>
#include <vector>
#include "../defines.h"
#include "../Helpers/Filepath.h"
#include "../Helpers/Helpers.h"
#include "Font.h"
#include "../Graphics/Shader.h"

#ifdef _WIN32
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glew.h>
#else

#endif

namespace star
{
	class Texture2D;

	class FontManager
	{
	public:
		~FontManager(void) {}

		static FontManager* GetInstance();

		bool LoadFont(const tstring& path, const tstring& name, int32 size);
		bool DeleteFont(const tstring& name);
		void EraseFonts();
		bool DrawText(const tstring& text, const tstring& fontname, ivec2 position);

	private:
		//Data Members
		static FontManager* mFontManager;

		FT_Library mLibrary;

		std::map<tstring, Font> mFontList;
		std::vector<tstring> mPathList;

		Shader m_Shader;

		FontManager(void);
		mat4x4 InverseMatrix(const mat4x4& matrix);

		FontManager(const FontManager& yRef);
#ifdef _WIN32
		FontManager(FontManager&& yRef);
#endif
		FontManager& operator=(const FontManager& yRef);
	};
}

#endif
