#include "HelpersAndroid.h"

#ifdef ANDROID

#include <memory>
#include <android_native_app_glue.h>
#include "../StarEngine.h"
#include "Helpers.h"
#include "../Logger.h"

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
		star::Logger::GetInstance()->Log(asset != NULL,
			_T("Couldn't find '") + path + _T("'."), STARENGINE_LOG_TAG);
		data.size = AAsset_getLength(asset);
		data.data = new schar[sizeof(schar) * data.size];
		AAsset_read(asset, data.data, data.size);
		AAsset_close(asset);
	}

	bool ReadFileAssetSafe(const tstring & path, star::SerializedData & data, bool logWarning)
	{
		auto app = star::StarEngine::GetInstance()->GetAndroidApp();
		auto manager = app->activity->assetManager;
		AAsset* asset = AAssetManager_open(
				manager,
				star::string_cast<sstring>(path.c_str()).c_str(),
				AASSET_MODE_UNKNOWN
				);
		bool result = asset != NULL;
		if(result)
		{
			data.size = AAsset_getLength(asset);
			data.data = new schar[sizeof(schar) * data.size];
			AAsset_read(asset, data.data, data.size);
			AAsset_close(asset);
		}
		else if(logWarning)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Warning,
				_T("Couldn't find '") + path + _T("'."), STARENGINE_LOG_TAG);
		}
		return result;
	}
}

#endif
