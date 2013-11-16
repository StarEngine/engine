#include "HelpersAndroid.h"

#ifdef ANDROID

#include <memory>
#include <android_native_app_glue.h>
#include "../StarEngine.h"
#include "Helpers.h"

namespace star_a
{
	void ReadFileAsset(const tstring & path, star::SerializedData & data)
	{
		auto app = star::StarEngine::GetInstance()->GetAndroidApp();
		auto manager = app->activity->assetManager;
		AAsset* asset = AAssetManager_open(
				manager,
				star::string_cast<sstring>(path.c_str()).c_str(),
				AASSET_MODE_UNKNOWN
				);
		ASSERT(asset != NULL, (_T("Couldn't find '") + path + _T("'.")).c_str());
		data.size = AAsset_getLength(asset);
		data.data = new schar[sizeof(schar) * data.size];
		AAsset_read(asset, data.data, data.size);
		AAsset_close(asset);
	}
}

#endif
