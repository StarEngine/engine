#include "Texture2D.h"

namespace star
{

	//[NOTE]	You're not supposed to make Textures yourself.
	//			Use the TextureManager to load your textures.
	//			This ensures a same texture is not loaded multiple times

#ifdef _WIN32
	Texture2D::Texture2D(tstring pPath):
			mPath(pPath),
			mTextureId(0),
			mFormat(0),
			mWidth(0),
			mHeight(0),
			mNumber_of_passes(0),
			mImageBuffer(0),
			mPng_ptr(nullptr),
			mInfo_ptr(nullptr),
			mColor_type(0),
			mBit_depth(0),
			mRow_pointers(0)
	{
		this->Load();

	}
#else
	Texture2D::Texture2D(tstring pPath, android_app* pApplication):
			mResource(pApplication , pPath),
			mPath(pPath),
			mTextureId(0),
			mFormat(0),
			mWidth(0),
			mHeight(0),
			mNumber_of_passes(0),
			mImageBuffer(0),
			mPng_ptr(nullptr),
			mInfo_ptr(nullptr),
			mColor_type(0),
			mBit_depth(0),
			mRow_pointers(0)
	{
		this->Load();
	}

	void Texture2D::Callback_Read(png_structp png, png_bytep data, png_size_t size)
	{
		Resource& lReader = *((Resource*)png_get_io_ptr(png));
		if(lReader.read(data,size)!=STATUS_OK)
		{
			lReader.close();
			png_error(png, "Error while reading PNG file");
		}
	}
#endif

	Texture2D::~Texture2D()
	{
		if(mTextureId!=0)
		{
			glDeleteTextures(1,&mTextureId);
			mTextureId=0;
		}
		mWidth=0;
		mHeight=0;
		mFormat=0;
	}
	
	uint8* Texture2D::ReadPNG()
	{
		png_byte header[8];

#ifdef _WIN32
		FILE *fp;
		_wfopen_s(&fp,mPath.c_str(), _T("rb"));

		if(fp==NULL)
		{ 
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : png could not be loaded"));
			return NULL;
		}

		fread(header, 8, 1, fp);
#else
		if(mResource.open()==STATUS_KO)
		{
			mResource.close();
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Could Not Open Resource"));
			return NULL;
		}
		if(mResource.read(header, sizeof(header))==STATUS_KO)
		{
			mResource.close();
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Could Not Read"));
			return NULL;
		}
#endif


		if(png_sig_cmp(header, 0, 8))
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Not a PNG file"));
			return NULL;
		}

		mPng_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if(!mPng_ptr)
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : create struct string failed"));
			return NULL;
		}

		mInfo_ptr = png_create_info_struct(mPng_ptr);
		if(!mInfo_ptr)
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : create info failed"));
			return NULL;
		}

#ifdef _WIN32
		if(setjmp(png_jmpbuf(mPng_ptr)))
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Error during init io"));
			return NULL;
		}

		png_init_io(mPng_ptr, fp);
#else
		png_set_read_fn(mPng_ptr, &mResource, Callback_Read);
		if(setjmp(png_jmpbuf(mPng_ptr)))
		{
			mResource.close();
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Error during init io"));
			return NULL;
		}

#endif
		png_set_sig_bytes(mPng_ptr, 8);
		png_read_info(mPng_ptr,mInfo_ptr);

		png_uint_32 pWidth, pHeight;
		png_get_IHDR(mPng_ptr,mInfo_ptr,&pWidth,&pHeight,&mBit_depth,&mColor_type, NULL,NULL,NULL);
		mWidth = pWidth;
		mHeight = pHeight;

		bool pTransparency = false;
		if(png_get_valid(mPng_ptr, mInfo_ptr, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(mPng_ptr);
			pTransparency=true;

#ifndef _WIN32
			mResource.close();
#endif
			delete [] mRow_pointers;
			delete [] mImageBuffer;
			if(mPng_ptr != NULL)
			{
				png_infop* lInfoPtrP = mInfo_ptr != NULL ? &mInfo_ptr: NULL;
				png_destroy_read_struct(&mPng_ptr, lInfoPtrP, NULL);
			}
			return NULL;
		}

		if(mBit_depth < 8)
			png_set_packing(mPng_ptr);
		else if(mBit_depth==16)
			png_set_strip_16(mPng_ptr);

		switch(mColor_type)
		{
		case PNG_COLOR_TYPE_PALETTE:
			png_set_palette_to_rgb(mPng_ptr);
			mFormat = pTransparency ? GL_RGBA : GL_RGB;
			break;
		case PNG_COLOR_TYPE_RGB:
			mFormat = pTransparency ? GL_RGBA : GL_RGB;
			break;
		case PNG_COLOR_TYPE_RGBA:
			mFormat = GL_RGBA;
			break;
		case PNG_COLOR_TYPE_GRAY:
			png_set_expand_gray_1_2_4_to_8(mPng_ptr);
			mFormat = pTransparency ? GL_LUMINANCE_ALPHA : GL_LUMINANCE;
			break;
		case PNG_COLOR_TYPE_GA:
			png_set_expand_gray_1_2_4_to_8(mPng_ptr);
			mFormat = GL_LUMINANCE_ALPHA;
			break;

		}

		mNumber_of_passes = png_set_interlace_handling(mPng_ptr);
		png_read_update_info(mPng_ptr,mInfo_ptr);

		if(setjmp(png_jmpbuf(mPng_ptr)))
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Error during read image"));
			return NULL;
		}

		png_int_32 pRowSize = png_get_rowbytes(mPng_ptr,mInfo_ptr);
		if(pRowSize<=0)
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : png rowsize smaller or equal to 0"));
			return NULL;
		}

		mImageBuffer = new png_byte[pRowSize * mHeight];
		if(!mImageBuffer)
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Error during image buffer creation"));
			return NULL;
		}

		mRow_pointers = new png_bytep[mHeight];
		if(!mRow_pointers)
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Error during row pointer creation"));
			return NULL;
		}

		for(int i=0; i<mHeight; ++i)
		{
			mRow_pointers[mHeight -(i+1)] = mImageBuffer + i * pRowSize;
		}
		png_read_image(mPng_ptr, mRow_pointers);

#ifdef _WIN32
		fclose(fp);
#else
		mResource.close();
#endif
		png_destroy_read_struct(&mPng_ptr, &mInfo_ptr, NULL);
		delete[] mRow_pointers;

#ifdef _DEBUG
		Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : ")+mPath+_T(" Created Succesfull"));
#endif
		return mImageBuffer;

	}

	status Texture2D::Load()
	{
		this->ReadPNG();
		if(mImageBuffer == NULL)
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : READING PNG FAILED - NO IMAGE BUFFER"));
			return STATUS_KO;
		}

		glGenTextures(1, &mTextureId);
		glBindTexture(GL_TEXTURE_2D, mTextureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat,GL_UNSIGNED_BYTE, mImageBuffer);
		delete[] mImageBuffer;

		if(glGetError() != GL_NO_ERROR)
		{
			Logger::GetSingleton()->Log(LogLevel::Info,_T("PNG : Error loading pnginto OpenGl"));
			if(mTextureId != 0)
			{
				glDeleteTextures(1, &mTextureId);
				mTextureId = 0;
			}
			mWidth =0;
			mHeight = 0;
			mFormat = 0;
			return STATUS_KO;
		}
		return STATUS_OK;
	}

	const tstring Texture2D::getPath()
	{
		return mPath;
	}

	const int32 Texture2D::getHeight()
	{
		return mHeight;
	}

	const int32 Texture2D::getWidth()
	{
		return mWidth;
	}
}
