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
				star::string_cast<std::string>(path.c_str()).c_str(),
				AASSET_MODE_UNKNOWN
				);
		ASSERT(asset != NULL, (_T("Couldn't find '") + path + _T("'.")).c_str());
		data.size = AAsset_getLength(asset);
		data.data = new char[sizeof(char) * data.size];
		AAsset_read(asset, data.data, data.size);
		AAsset_close(asset);
	}

	void WriteFileAsset(const tstring & path, const star::SerializedData & data)
	{
		auto app = star::StarEngine::GetInstance()->GetAndroidApp();
		std::stringstream strstr;
		strstr << app->activity->internalDataPath
			   << "/" << star::string_cast<std::string>(path);
		std::string fPath = strstr.str();
		FILE* pFile = std::fopen(fPath.c_str(), "w+");
		bool succesfull = pFile != nullptr;
		ASSERT(succesfull, (_T("FILE: Couldn't find '") + fPath + _T("'.")).c_str());
		if(succesfull)
		{
			int32 res = std::fwrite(data.data, sizeof(char), data.size, pFile);
			ASSERT(res == data.size, _T("FILE: WriteFile has not been completed."));
		}
		std::fclose(pFile);
	}
}

#endif
