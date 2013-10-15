#include "Resource.h"
//#include "../EventLoop.h"
#include "../Logger.h"

namespace star
{
	Resource::Resource(android_app* pApplication, const tstring & pPath):
			mPath(pPath),
			mAssetManager(pApplication->activity->assetManager),
			mAsset(NULL)
	{
	}

	const tstring & Resource::GetPath() const
	{
		return mPath;
	}

	status Resource::Open()
	{
		mAsset = AAssetManager_open(mAssetManager, mPath.c_str(), AASSET_MODE_UNKNOWN);
		return (mAsset != NULL) ? STATUS_OK : STATUS_KO;
	}

	void Resource::Close()
	{
		if(mAsset != NULL)
		{
			AAsset_close(mAsset);
			mAsset = NULL;
		}
	}

	status Resource::Read(void* pBuffer, size_t pCount)
	{
		int32_t lReadCount = AAsset_read(mAsset,pBuffer, pCount);
		return (lReadCount == pCount) ? STATUS_OK : STATUS_KO;
	}

	off_t Resource::GetLength() const
	{
		return AAsset_getLength(mAsset);
	}

	// [COMMENT] watch header file for comment
	const void* Resource::GetBufferize() const
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
