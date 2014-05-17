#pragma once

#include "../defines.h"
#include "../Logger.h"

#ifdef DESKTOP
//#pragma warning (disable : 4172)
//#pragma warning (disable : 4099)
#include <png.h>
//#pragma warning (default : 4172)
//#pragma warning (default : 4099)
#include <glew.h>
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <png.h>
#include <android_native_app_glue.h>
#include "Resource.h"
#endif


namespace star
{
	class Texture2D final
	{
	public:
		//[NOTE]	You're not supposed to make Textures yourself.
		//			Use the TextureManager to load your textures.
		//			This ensures a same texture is not loaded multiple times
		Texture2D(const tstring & pPath);
		~Texture2D();

		const tstring & GetPath() const;
		int32 GetHeight() const;
		int32 GetWidth() const;
		GLuint GetTextureID() const;

	private:
		uint8* ReadPNG();
		void Load();
		
		GLuint	mTextureId;	
		GLint	mFormat;
		int32 mWidth, mHeight;
#ifdef ANDROID
		Resource mResource;
		static void CallbackRead(png_structp png, png_bytep data, png_size_t size);
#else
		tstring mPath;
#endif
		static const tstring LIBPNG_LOG_TAG;

		static void CustomErrorFunction(png_structp pngPtr, png_const_charp error);
		static void CustomWarningFunction(png_structp pngPtr, png_const_charp warning);

		Texture2D(const Texture2D& yRef);
		Texture2D(Texture2D&& yRef);
		Texture2D& operator=(const Texture2D& yRef);
		Texture2D& operator=(Texture2D&& yRef);
	};
}


