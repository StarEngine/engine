#pragma once

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
	struct TextDesc
	{
		TextDesc()
			:Text(EMPTY_STRING)
			,Fontname(EMPTY_STRING)
			,Position(vec2(0,0))
			,MaxWidth(-1)
			,TextColor(Color::Black)
		{}
		tstring Text;
		tstring Fontname;
		vec2 Position;
		int32 MaxWidth;
		Color TextColor;
	};

	class Texture2D;

	class FontManager
	{
	public:
		~FontManager(void) {}

		static FontManager * GetInstance();

		bool LoadFont(const tstring& path, const tstring& name, int32 size);
		bool DeleteFont(const tstring& name);
		void EraseFonts();
		//If maxWidth is -1, wrapping will not be applied
		bool DrawText(const tstring& text, const tstring& fontname, vec2 position, Color color = Color::Black, int32 maxWidth =-1);
		bool DrawText(TextDesc textDesc);
	private:
		//Data Members
		static FontManager * mFontManager;

		FT_Library mLibrary;

		std::map<tstring, Font> mFontList;
		std::vector<tstring> mPathList;

		Shader m_Shader;

		FontManager(void);
		mat4x4 InverseMatrix(const mat4x4& matrix);
		void SplitIntoLines(std::vector<std::string> &list, const std::string &string);
		tstring CheckWrapping(Font& font, const tstring& stringIn,const int32& wrapWidth);
		void SplitString(std::vector<tstring>& wordArrayIn,const tstring& stringIn, const tstring& delimiter);

		FontManager(const FontManager& yRef);
		FontManager(FontManager&& yRef);
		FontManager& operator=(const FontManager& yRef);
	};
}
