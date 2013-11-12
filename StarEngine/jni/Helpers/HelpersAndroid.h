#pragma once

#ifdef ANDROID

#include "../defines.h"
#include "SerializedData.h"

namespace star
{
	void ReadFileAsset(const tstring & path, SerializedData & data);
}

#endif
