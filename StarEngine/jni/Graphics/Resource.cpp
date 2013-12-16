#include "Resource.h"
//#include "../EventLoop.h"
#include "../Logger.h"
#include "../StarEngine.h"
namespace star
{
	Resource::Resource(const tstring & pPath):
			mPath(pPath),
			mAsset(NULL)
	{
	}

	const tstring & Resource::GetPath() const
	{
		return mPath;
	}

	bool Resource::Open()
	{
		mAsset = AAssetManager_open(
			StarEngine::GetInstance()->GetAndroidApp()->activity->assetManager,
			mPath.c_str(), 
			AASSET_MODE_UNKNOWN
			);
		return mAsset != NULL;
	}

	void Resource::Close()
	{
		if(mAsset != NULL)
		{
			AAsset_close(mAsset);
			mAsset = NULL;
		}
	}

	bool Resource::Read(void* pBuffer, size_t pCount)
	{
		int32_t lReadCount = AAsset_read(mAsset, pBuffer, pCount);
		return lReadCount == pCount;
	}

	off_t Resource::GetLength() const
	{
		return AAsset_getLength(mAsset);
	}

	const void* Resource::GetBufferize() const
	{
		return AAsset_getBuffer(mAsset);
	}

	ResourceDescriptor Resource::DeScript()
	{
		ResourceDescriptor lDescriptor = { -1, 0, 0 };
		AAsset* lAsset = AAssetManager_open(
				StarEngine::GetInstance()->GetAndroidApp()->activity->assetManager,
				mPath.c_str(),
				AASSET_MODE_UNKNOWN);
		if(lAsset != NULL)
		{
			lDescriptor.mDescriptor = AAsset_openFileDescriptor(
					lAsset,
					&lDescriptor.mStart,
					&lDescriptor.mLength
					);
			AAsset_close(lAsset);
		}
		return lDescriptor;
	}
}
