#pragma once

#include "../defines.h"

#ifdef _WIN32
#include <stdlib.h>
#include <libs/OpenGL/GLEW/include/GL/glew.h>
#else
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <iostream>
#include <fstream>
#include "../EventLoop.h"
#include "../AssetManaging/Resource.h"
#endif

namespace star
{
	// Attribute index.
	enum
	{
		ATTRIB_VERTEX,
		ATTRIB_TEXTUREPOSITON,
		NUM_ATTRIBUTES
	};

	class Shader {
	public:
		Shader() {}
		// [COMMENT] CONST CORRECTNESS! These are basics...
		// if you pass an object (e.g.: a string) and it is just
		// an input parameter, pass it like "const tstring& value"
		Shader(tstring vsFile, tstring fsFile);
		~Shader();
		// [COMMENT] see previous comment]
		bool Init(tstring vsFile, tstring fsFile);

		void Bind();
		void Unbind();

		// [COMMENT] id? Wtf does id do? it seems like it's a getter..
		// so call it then GetID(); so that we atleast know what happens.
		// oh yes, and also... CONST CORRECTNESS!!!
		GLuint id();

	private:
		// [COMMENT] see const correctness comment....
		char* TextFileReading(tstring fileName);
		bool CompileShader(GLuint* shader, GLenum type, tstring file);

		GLuint mShaderID;
		GLuint mVertexShader;
		GLuint mFragmentShader;

		Shader(const Shader& t);
		Shader(Shader&& t);
		Shader& operator=(const Shader& t);
	};
}
