#include "Font.h"
#include "../Logger.h"

#ifndef DESKTOP
#include "Resource.h"
#include "../StarEngine.h"
#endif

namespace star
{
	Font::Font():
		mFace(0),
		mTextures(nullptr),
		mMaxLetterHeight(0),
		mUVcoordsList(),
		mVecticesList(),
		mLetterSizeList(),
		mSize(0)
	{
	}

	Font::~Font()
	{
	}

	bool Font::Init(const tstring& path, int32 size, FT_Library& library)
	{
		mSize = static_cast<float32>(size);
		mTextures = new GLuint[FONT_TEXTURES];
		mMaxLetterHeight = 0;

#ifdef DESKTOP
		//Convert from wstring to const schar* trough sstring
		sstring font_path = string_cast<sstring>(path);
		auto error = FT_New_Face(library,font_path.c_str(),0,&mFace);
#else
		Resource resource(StarEngine::GetInstance()->GetAndroidApp(), path);
		if(!resource.Open())
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Font : Failed to open file"));
			return false;
		}

		int32 length = resource.GetLength();
		star::Logger::GetInstance()->Log(LogLevel::Info, _T("Font : File size :")+star::string_cast<tstring>(length));
		mFontBuffer = new BYTE[length]();

		if(!resource.Read(mFontBuffer,length))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Font : Failed to read file"));
			resource.Close();
			return false;
		}

		auto error = FT_New_Memory_Face(library,mFontBuffer,length,0,&mFace);
		resource.Close();
#endif
		if(error == FT_Err_Unknown_File_Format)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Font Manager : Font : ") + path + _T(" ,could be opened but its in unsuported format"));
			return (false);
		}
		else if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Font Manager : Font : ") + path + _T(" ,is invalid and cant be opened or read or its broken"));
			return (false);
		}
		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Font Manager : Font : ") + path + _T(" ,loaded and ready for use"));

		FT_Set_Char_Size(mFace, size << 6, size << 6, FONT_DPI, FONT_DPI);

		glGenTextures(FONT_TEXTURES, mTextures);
		for(suchar i = 0; i < FONT_TEXTURES; ++i)
		{
			Make_D_List(mFace, i, mTextures);
		}
		FT_Done_Face(mFace);
		return true;
	}

	void Font::DeleteFont()
	{

		glDeleteTextures(FONT_TEXTURES,mTextures);
		delete[] mTextures;
#ifdef ANDROID
		delete [] mFontBuffer;
#endif
	}

	void Font::Make_D_List(FT_Face face, schar ch,GLuint * tex_base)
	{

		auto error = FT_Load_Char(face, ch, FT_LOAD_DEFAULT);
		if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Font : could not load Glyph"));
			return;
		}

		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Font : could not load Glyph"));
			return;
		}

		FT_Bitmap& bitmap = face->glyph->bitmap;

		int32 width = NextPowerOfTwo(bitmap.width);
		int32 height = NextPowerOfTwo(bitmap.rows);

		GLubyte* expanded_data = new GLubyte[2 * width * height];

		for(int32 j = 0; j < height; ++j) 
		{
			for(int32 i = 0; i < width; ++i) 
			{
				expanded_data[2 * (i + j * width)] = 255;
				expanded_data[2 * (i + j * width) + 1] = 
					(i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
			}
		}

		glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#ifdef DESKTOP
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
#else
		//For android "internal format" must be the same as "format" in glTexImage2D
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
#endif
		Logger::GetInstance()->CheckGlError();
		delete[] expanded_data;

		float32 x = static_cast<float32>(bitmap.width) / static_cast<float32>(width);
		float32 y = static_cast<float32>(bitmap.rows) / static_cast<float32>(height);
		int32 dimx = (face->glyph->metrics.horiAdvance / 64);
		int32 dimy = ((face->glyph->metrics.horiBearingY) - (face->glyph->metrics.height)) / 64;
		ivec2 tempdim(dimx, dimy);
		if(mMaxLetterHeight<face->glyph->bitmap_top)mMaxLetterHeight = face->glyph->bitmap_top;
		mLetterSizeList.push_back(tempdim);	

		fontVertices tempVertices;
		tempVertices.ver[0] = (GLfloat)bitmap.width;
		tempVertices.ver[1] = (GLfloat)bitmap.rows;
		tempVertices.ver[2] = 0;
		tempVertices.ver[3] = (GLfloat)bitmap.width;
		tempVertices.ver[4] = 0;
		tempVertices.ver[5] = 0;
		tempVertices.ver[6] = 0;
		tempVertices.ver[7] = (GLfloat)bitmap.rows;
		tempVertices.ver[8] = 0;
		tempVertices.ver[9] = 0;
		tempVertices.ver[10] = 0;
		tempVertices.ver[11] = 0;

		mVecticesList.push_back(tempVertices);

		fontUvCoords tempCoords;
		tempCoords.uv[0] = x;
		tempCoords.uv[1] = 0;
		tempCoords.uv[2] = x;
		tempCoords.uv[3] = y;
		tempCoords.uv[4] = 0;
		tempCoords.uv[5] = 0;
		tempCoords.uv[6] = 0;
		tempCoords.uv[7] = y;

		mUVcoordsList.push_back(tempCoords);
	}

	int32 Font::NextPowerOfTwo(int32 a)
	{
		int32 rval = 1;
		while(rval < a)
		{
			rval <<= 1;
		}
		return rval;
	}

	const std::vector<fontUvCoords>& Font::GetUvCoords() const 
	{
		return mUVcoordsList;
	}

	const std::vector<fontVertices>& Font::GetVetrices() const 
	{
		return mVecticesList;
	}

	const std::vector<ivec2>& Font::GetLetterDimensions() const 
	{
		return mLetterSizeList;
	}

	int32 Font::GetMaxLetterHeight() const 
	{
		return mMaxLetterHeight;
	}

	int32 Font::GetStringLength(const tstring& string) const
	{
		int32 length = 0;
		sstring conv_text = star::string_cast<sstring>(string);
		const schar *line = conv_text.c_str();
		for(int32 i = 0; line[i] != 0; ++i) 
		{
			length += mLetterSizeList[line[i]].x;
		}
		return length;
	}
}
