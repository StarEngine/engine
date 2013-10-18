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
	typedef struct{
		GLfloat ver[12];
	}fontVertices;

	typedef struct{
		GLfloat uv[8];
	}fontUvCoords;

	class Font
	{
	public:
		Font(){}
		~Font(){};

		bool Init(const tstring& path, int32 size, FT_Library& library);
		void DeleteFont();

		GLuint GetListBase()const {return mList_base;}
		GLuint* GetTextures()const {return mTextures;}
		float GetSize()const {return mSize;}
		const std::vector<fontUvCoords>& getUvCoords()const {return mUVcoordsList;}
		const std::vector<fontVertices>& getVetrices()const {return mVecticesList;}
		const std::vector<ivec2>& GetLetterDimensions() const {return mLetterSizeList;}
		const int& GetMaxLetterHeight() const {return mMaxLetterHeight;}

	private:
		void Make_D_List(FT_Face face, char ch, GLuint list_base, GLuint * tex_base);
		int32 NextPowerOfTwo(const int32& a);

		FT_Face mFace;
		GLuint* mTextures;
		GLuint mList_base;
		int mMaxLetterHeight;

		std::vector< fontUvCoords > mUVcoordsList;
		std::vector< fontVertices > mVecticesList;
		std::vector< ivec2 > mLetterSizeList;
		float mSize;
	};
}
