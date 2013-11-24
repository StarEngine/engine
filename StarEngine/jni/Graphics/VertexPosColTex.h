#pragma once
#include "../defines.h"
#include "Color.h"

namespace star
{
	struct VertexPosColTex
	{
	public:
		VertexPosColTex();
		~VertexPosColTex();

		vec3 Position;
		Color Color;
		vec2 TexCoord;
	};
}


