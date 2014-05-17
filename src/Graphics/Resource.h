#pragma once

#ifndef _WIN32

#include "../defines.h"
#include <android_native_app_glue.h>

class EventLoop;

namespace star
{
	struct ResourceDescriptor
	{
		int32 mDescriptor;
		off_t mStart;
		off_t mLength;
	};

	class Resource
	{
	public:
		Resource(const tstring & pPath);

		const tstring & GetPath() const;

		bool Open();
		void Close();
		bool Read(void* pBuffer, size_t pCount);

		off_t GetLength() const;
		const void* GetBufferize() const;
		ResourceDescriptor DeScript();

	private:
		tstring mPath;
		AAsset* mAsset;
	};
}

#endif
