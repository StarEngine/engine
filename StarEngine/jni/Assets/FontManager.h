#pragma once

#include <memory>
#include <map>
#include <vector>
#include "../defines.h"
#include "../Helpers/Filepath.h"
#include "../Helpers/Helpers.h"
#include "Font.h"
#include "../Graphics/Shader.h"

#include "../Graphics/Color.h"

#include "ft2build.h"
#include "freetype/freetype.h"

#ifdef DESKTOP
#include <glew.h>
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

namespace star
{
	class Texture2D;

	class FontManager
	{
	public:
		~FontManager(void) {}

		static std::shared_ptr<FontManager> GetInstance();

		bool LoadFont(const tstring& path, const tstring& name, int32 size);
		bool DeleteFont(const tstring& name);
		void EraseFonts();
		bool DrawText(const tstring& text, const tstring& fontname, ivec2 position, Color color = Color::Black);

	private:
		//Data Members
		static std::shared_ptr<FontManager> mFontManager;

		FT_Library mLibrary;

		std::map<tstring, Font> mFontList;
		std::vector<tstring> mPathList;

		Shader m_Shader;

		FontManager(void);
		mat4x4 InverseMatrix(const mat4x4& matrix);

		FontManager(const FontManager& yRef);
		FontManager(FontManager&& yRef);
		FontManager& operator=(const FontManager& yRef);
	};
}
