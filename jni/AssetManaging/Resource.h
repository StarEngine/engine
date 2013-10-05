#pragma once

#ifndef _WIN32

#include "../defines.h"
#include <android_native_app_glue.h>

class EventLoop;

namespace star
{
	struct ResourceDescriptor
	{
		int32_t mDescriptor;
		off_t mStart;
		off_t mLength;
	};

	class Resource
	{
	public:
		// [COMMENT] const correctness please.... and pass it by
		// reference. thank you!
		Resource(android_app* pApplication,tstring pPath);

		// [COMMENT] pass by reference, thank you very much
		// also please let functions start with a capital.
		const tstring getPath() const;

		status open();
		void close();
		status read(void* pBuffer, size_t pCount);
		//status readAll(void* pBuffer);

		// [COMMENT] const correctness please
		off_t getLength();
		// [COMMENT] what does this function do?
		// name is very confusing and doesnt explain me anything
		const void* bufferize();
		// [COMMENT] what does this function do? I don't know it by reading
		// the name...
		ResourceDescriptor DeScript();

	private:
		tstring mPath;
		AAssetManager* mAssetManager;
		AAsset* mAsset;
	};
}

#endif
