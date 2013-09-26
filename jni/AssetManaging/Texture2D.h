#pragma once

#include "../defines.h"
#include "../Logger.h"

#ifdef _WIN32
#pragma warning (disable : 4172)
#pragma warning (disable : 4099)
#include "libs/libpng/png.h"
#pragma warning (default : 4172)
#pragma warning (default : 4099)
#include "libs/OpenGL/GLEW/include/GL/glew.h"
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <png.h>
#endif


namespace star
{
	class Texture2D
	{
	public:
		Texture2D(tstring pPath);
		~Texture2D();

		const tstring getPath();
		const int32 getHeight();
		const int32 getWidth();

		const GLuint getTextureID(){return mTextureId;}

	private:
		uint8* ReadPNG();
		status Load();

	private:
		tstring mPath;

		GLuint	mTextureId;	
		GLint	mFormat;

		int32 mWidth, mHeight;
		int32 mNumber_of_passes;

		uint8* mImageBuffer;

		png_structp mPng_ptr;
		png_infop	mInfo_ptr;
		png_int_32	mColor_type;
		png_int_32	mBit_depth;		
		png_bytep * mRow_pointers;

	};
}
