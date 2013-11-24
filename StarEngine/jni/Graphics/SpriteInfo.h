#pragma once

#include "../defines.h"

namespace star
{
	struct SpriteInfo
	{
		//pass width and height
		vec2 dimensions;
		//pass left bottom and right top
		float32 uvCoords[4];
		tstring spriteName;
		mat4 transform;
	};
}