#include "Font.h"
#include "../Logger.h"

#ifndef DESKTOP
#include "Resource.h"
#include "../StarEngine.h"
#endif

namespace star
{
	Font::Font():
		m_FontPath(EMPTY_STRING),
		mFace(0),
		mTextures(nullptr),
		mMaxLetterHeight(),
		mMinLetterHeight(),
		mCharacterInfoMap(),
		mSize(0)
	{
	}

	Font::~Font()
	{
		mCharacterInfoMap.clear();
	}

	bool Font::Init(const tstring& path, uint32 size, FT_Library& library)
	{
		mSize = size;
		mTextures = new GLuint[FONT_TEXTURES];
		m_FontPath = path;

#ifdef DESKTOP
		//Convert from wstring to const schar* trough sstring
		sstring font_path = string_cast<sstring>(path);
		FT_Error error = FT_New_Face(library,font_path.c_str(),0,&mFace);
#else
		Resource resource(path);
		if(!resource.Open())
		{
			star::Logger::GetInstance()->Log(LogLevel::Error,
				_T("Font : Failed to open file"), STARENGINE_LOG_TAG);
			return false;
		}

		int32 length = resource.GetLength();
		star::Logger::GetInstance()->Log(LogLevel::Info,
			_T("Font : File size :") + star::string_cast<tstring>(length),
			STARENGINE_LOG_TAG);
		mFontBuffer = new BYTE[length]();

		if(!resource.Read(mFontBuffer,length))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error,
				_T("Font : Failed to read file"), STARENGINE_LOG_TAG);
			resource.Close();
			return false;
		}

		auto error = FT_New_Memory_Face(library,mFontBuffer,length,0,&mFace);
		resource.Close();
#endif
		if(error == FT_Err_Unknown_File_Format)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Font Manager : Font : ") + path +
				_T(" ,could be opened but its in unsuported format"),
				STARENGINE_LOG_TAG);
			return (false);
		}
		else if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Font Manager : Font : ") + path +
				_T(" ,is invalid and cant be opened or read or its broken"),
				STARENGINE_LOG_TAG);
			return (false);
		}
		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Font Manager : Font : ") + path + 
			_T(" ,loaded and ready for use"),
			STARENGINE_LOG_TAG);

		int32 iSize = int32(size);
		FT_Set_Char_Size(mFace, iSize << 6, iSize << 6, FONT_DPI, FONT_DPI);

		glGenTextures(FONT_TEXTURES, mTextures);
		for(suchar i = 0; i < FONT_TEXTURES; ++i)
		{
			mCharacterInfoMap.insert(std::make_pair(i, CharacterInfo()));
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

	void Font::Make_D_List(FT_Face face, suchar ch,GLuint * tex_base)
	{
		auto error = FT_Load_Char(face, ch, FT_LOAD_DEFAULT);
		if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, 
				_T("Font : could not load Glyph"), STARENGINE_LOG_TAG);
			return;
		}

		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Font : could not load Glyph"), STARENGINE_LOG_TAG);
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

		//uvs
		float32 x = static_cast<float32>(bitmap.width) / static_cast<float32>(width);
		float32 y = static_cast<float32>(bitmap.rows) / static_cast<float32>(height);
		//letterheight
		int32 dimX = (face->glyph->metrics.horiAdvance / 64);
		int32 dimY = ((face->glyph->metrics.horiBearingY) - (face->glyph->metrics.height)) / 64;		
		if(mMaxLetterHeight < face->glyph->bitmap_top)
		{
			mMaxLetterHeight = face->glyph->bitmap_top;
		}
		if(mMinLetterHeight > dimY)
		{
			mMinLetterHeight = dimY;
		}
		mCharacterInfoMap.at(ch).letterDimensions = ivec2(dimX, dimY);
		mCharacterInfoMap.at(ch).vertexDimensions = vec2(bitmap.width, bitmap.rows);
		mCharacterInfoMap.at(ch).uvDimensions = vec2(x, y);
	}

	const tstring & Font::GetFontPath() const
	{
		return m_FontPath;
	}

	GLuint* Font::GetTextures() const
	{
		return mTextures;
	}

	uint32 Font::GetFontSize() const 
	{
		return mSize;
	}

	int32 Font::NextPowerOfTwo(int32 number) const
	{
		int32 rval = 1;
		while(rval < number)
		{
			rval <<= 1;
		}
		return rval;
	}

	const std::unordered_map<suchar, CharacterInfo>& Font::GetCharacterInfoMap() const 
	{
		return mCharacterInfoMap;
	}

	const CharacterInfo& Font::GetCharacterInfo(suchar character) const 
	{
		//[COMMENT] Performing a good check here 
		//with std::find will only slow things down
		//If the map.at has an unknown value, it will throw an exception anyway
		return mCharacterInfoMap.at(character);
	}

	int32 Font::GetMaxLetterHeight() const 
	{
		return mMaxLetterHeight;
	}

	int32 Font::GetMinLetterHeight() const 
	{
		return mMinLetterHeight;
	}

	uint32 Font::GetStringLength(const tstring& string) const
	{
		int32 length = 0;
		sstring conv_text = star::string_cast<sstring>(string);
		const schar *line = conv_text.c_str();
		for(uint32 i = 0; line[i] != 0; ++i) 
		{
			length += mCharacterInfoMap.at(line[i]).letterDimensions.x;
		}
		return length;
	}
}
