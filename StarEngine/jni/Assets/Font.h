#pragma once

#include <map>
#include <vector>
#include <array>
#include "../defines.h"
#include "../Helpers/Filepath.h"
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
	typedef struct
	{
		GLfloat ver[12];
	} fontVertices;

	typedef struct
	{
		GLfloat uv[8];
	} fontUvCoords;

	class Font
	{
	public:
		Font();
		~Font();

		bool Init(const tstring& path, int32 size, FT_Library& library);
		void DeleteFont();

		GLuint* GetTextures() const {return mTextures;}
		float32 GetSize() const {return mSize;}
		const std::vector<fontUvCoords>& GetUvCoords() const;
		const std::vector<fontVertices>& GetVetrices() const;
		const std::vector<ivec2>& GetLetterDimensions() const;
		int32 GetMaxLetterHeight() const;
		int32 GetStringLength(const tstring& string) const;

	private:
		void Make_D_List(FT_Face face, schar ch,GLuint * tex_base);
		int32 NextPowerOfTwo(int32 a);

		FT_Face mFace;
		GLuint* mTextures;
		int32 mMaxLetterHeight;
#ifdef ANDROID
		BYTE* mFontBuffer;
#endif

		std::vector< fontUvCoords > mUVcoordsList;
		std::vector< fontVertices > mVecticesList;
		std::vector< ivec2 > mLetterSizeList;
		float32 mSize;
	};
}
