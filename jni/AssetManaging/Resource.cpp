#include "Resource.h"
#include "../EventLoop.h"
#include "../Logger.h"

namespace star
{
	Resource::Resource(android_app* pApplication,tstring pPath):
			mPath(pPath),
			mAssetManager(pApplication->activity->assetManager),
			mAsset(NULL)
	{
	}

	tstring Resource::getPath()
	{
		return mPath;
	}

	status Resource::open()
	{
		mAsset = AAssetManager_open(mAssetManager, mPath.c_str(), AASSET_MODE_UNKNOWN);
		return (mAsset != NULL) ? STATUS_OK : STATUS_KO;
	}

	void Resource::close()
	{
		if(mAsset !=NULL)
		{
			AAsset_close(mAsset);
			mAsset=NULL;
		}
	}

	status Resource::read(void* pBuffer, size_t pCount)
	{
		int32_t lReadCount = AAsset_read(mAsset,pBuffer, pCount);
		return (lReadCount == pCount) ? STATUS_OK : STATUS_KO;
	}

	/*status Resource::readAll(void* pBuffer)
	{
		off_t start;
		off_t length;
		int fd = AAsset_openFileDescriptor(mAsset, &start, &length);
	}*/

	off_t Resource::getLength()
	{
		return AAsset_getLength(mAsset);
	}

	const void* Resource::bufferize()
	{
		return AAsset_getBuffer(mAsset);
	}

}
