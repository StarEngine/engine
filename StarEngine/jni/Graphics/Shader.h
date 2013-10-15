#pragma once

#include "../defines.h"

#ifdef _WIN32
#include <stdlib.h>
#include <glew.h>
#else
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <iostream>
#include <fstream>
//#include "../EventLoop.h"
#include "../Assets/Resource.h"
#endif

namespace star
{
	// Attribute index.
	enum
	{
		ATTRIB_VERTEX,
		ATTRIB_TEXTUREPOSITON, //[COMMENT] Change to UV
		ATTRIB_PROJECTION,
		ATTRIB_TRANSLATION,
		NUM_ATTRIBUTES
	};

	class Shader {
	public:
		Shader();
		Shader(const tstring& vsFile, const tstring& fsFile);
		~Shader();

		bool Init(const tstring& vsFile,const tstring& fsFile);

		void Bind();
		void Unbind();

		const GLuint GetId() const;
		const GLfloat* GetProjection() const;
		const GLfloat* GetTranslation() const;

	private:
		const char* TextFileReading(const tstring& fileName);
		bool CompileShader(GLuint* shader, GLenum type, const tstring& file);

		GLuint mShaderID;
		GLuint mVertexShader;
		GLuint mFragmentShader;

		GLfloat* GlProjection;
		GLfloat* GlTranslation;

		Shader(const Shader& t);
		Shader(Shader&& t);
		Shader& operator=(const Shader& t);
	};
}
