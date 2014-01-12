#pragma once

#include <map>
#include <vector>
#include "../defines.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/Singleton.h"
#include "Font.h"
#include "../Components/TransformComponent.h"
#include "../Graphics/Color.h"
#include "../Graphics/Shader.h"

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
	class FilePath;

	class FontManager final : public Singleton<FontManager> 
	{
	public:
		friend Singleton<FontManager>;

		bool LoadFont(
			const tstring& path, 
			const tstring& name, 
			uint32 size
			);

		const Font* GetFont(const tstring& name);
		bool DeleteFont(const tstring& name);
		void EraseFonts();
		void SplitIntoLines(
			std::vector<sstring> &list, 
			const sstring &string
			);

	private:
		FT_Library mLibrary;

		std::map<tstring, Font*> mFontList;

		FontManager();
		~FontManager();

		void SplitString(
			std::vector<tstring>& wordArrayIn, 
			const tstring& stringIn, 
			const tstring& delimiter
			);

		FontManager(const FontManager& yRef);
		FontManager(FontManager&& yRef);
		FontManager& operator=(const FontManager& yRef);
		FontManager& operator=(FontManager&& yRef);
	};
}
