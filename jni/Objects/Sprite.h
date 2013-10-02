#pragma once

#include "../defines.h"
#include "../Shaders/Shader.h"

#ifdef _WIN32
#else

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#endif

namespace star
{

	class Sprite
	{
	public:
		Sprite(tstring filePath, tstring spriteName);
		~Sprite();

		void Draw();

	private:
		void createSquare();

		Shader mShader;
		tstring mSpriteName;

		GLfloat mVertices[8];
		GLfloat mUvCoords[8];
	};
}
