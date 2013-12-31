#pragma once

#include <unordered_map>
#include "../defines.h"
#include "../Helpers/FilePath.h"
#include "../Helpers/Helpers.h"

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
#define FONT_DPI 96
#define FONT_TEXTURES 128

	struct CharacterInfo
	{
		CharacterInfo()
			: vertexDimensions()
			, uvDimensions()
			, letterDimensions() 
		{

		}

		vec2	vertexDimensions,
				uvDimensions;
		ivec2	letterDimensions;

	};

	class Font
	{
	public:
		Font();
		~Font();

		bool Init(const tstring& path, uint32 size, FT_Library& library);
		void DeleteFont();

		const tstring & GetFontPath() const;

		GLuint* GetTextures() const;
		uint32 GetFontSize() const;
		
		const std::unordered_map<suchar, CharacterInfo>& GetCharacterInfoMap() const;
		const CharacterInfo& GetCharacterInfo(suchar character) const;
		int32 GetMaxLetterHeight() const;
		int32 GetMinLetterHeight() const;
		uint32 GetStringLength(const tstring& string) const;

	private:
		void Make_D_List(FT_Face face, suchar ch,GLuint * tex_base);
		int32 NextPowerOfTwo(int32 number) const;

		tstring m_FontPath;
		FT_Face mFace;
		GLuint* mTextures;
		int32	mMaxLetterHeight,
				mMinLetterHeight;

#ifdef ANDROID
		BYTE* mFontBuffer;
#endif
		std::unordered_map<suchar, CharacterInfo> mCharacterInfoMap;
		uint32 mSize;
	};
}
