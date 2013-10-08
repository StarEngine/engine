#include "Resource.h"
//#include "../EventLoop.h"
#include "../Logger.h"

namespace star
{
// [COMMENT]  check comment in hader file
	Resource::Resource(android_app* pApplication,tstring pPath):
			mPath(pPath),
			mAssetManager(pApplication->activity->assetManager),
			mAsset(NULL)
	{
	}

	// [COMMENT] watch header file for comment
	const tstring Resource::getPath() const
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
		if(mAsset != NULL)
		{
			AAsset_close(mAsset);
			mAsset = NULL;
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

	// [COMMENT] watch header file for comment
	off_t Resource::getLength()
	{
		return AAsset_getLength(mAsset);
	}

	// [COMMENT] watch header file for comment
	const void* Resource::bufferize()
	{
		return AAsset_getBuffer(mAsset);
	}

	// [COMMENT] watch header file for comment
	ResourceDescriptor Resource::DeScript()
	{
		ResourceDescriptor lDescriptor = { -1, 0, 0 };
		AAsset* lAsset = AAssetManager_open(mAssetManager, mPath.c_str(), AASSET_MODE_UNKNOWN);
		if(lAsset != NULL)
		{
			lDescriptor.mDescriptor = AAsset_openFileDescriptor(lAsset, &lDescriptor.mStart, &lDescriptor.mLength);
			AAsset_close(lAsset);
		}
		return lDescriptor;
	}
}
