#pragma once

#include "TimeManager.h"
#include "AssetManaging/TextureManager.h"

namespace star
{
	struct Context 
	{
		TimeManager* mTimeManager;
		TextureManager* mTextureManager;
	};
}