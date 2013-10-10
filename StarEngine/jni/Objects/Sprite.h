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
		Sprite(const tstring& filePath,const tstring& spriteName);
		~Sprite();

		void Draw();

	private:
		void CreateSquare();

		Shader mShader;
		tstring mSpriteName;

		GLfloat mVertices[12];
		GLfloat mUvCoords[8];

		Sprite(const Sprite &);
		Sprite(Sprite &&);
		Sprite & operator=(const Sprite &);
	};
}
