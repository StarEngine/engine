#pragma once

#include "../defines.h"

#ifdef DESKTOP
#include <stdlib.h>
#include <glew.h>
#else
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <iostream>
#include <fstream>
#include "../Assets/Resource.h"
#endif

namespace star
{
	// Attribute index.
	enum
	{
		ATTRIB_VERTEX,
		ATTRIB_UV,
		ATTRIB_COLOR,
		ATTRIB_HUD
	};

	class Shader final
	{
	public:
		Shader();
		Shader(const tstring& vsFile, const tstring& fsFile);
		Shader(const GLchar* inLineVert, const GLchar* inLineFrag);
		~Shader();

		bool Init(const tstring& vsFile, const tstring& fsFile);
		bool Init(const GLchar* inLineVert, const GLchar* inLineFrag);

		void Bind();
		void Unbind();

		const GLuint GetID() const;
		GLuint GetUniformLocation(const GLchar* nameInShader) const;
		GLuint GetAttribLocation(const GLchar* nameInShader) const;
		void PrintActiveAttribs() const;
		void PrintActiveUniforms() const;
	private:
		bool CompileShader(GLuint* shader, GLenum type, const tstring& file);
		bool CompileShader(GLuint* shader, GLenum type, const GLchar* inLineFile);

		bool GLInit();
		bool GLCompileShader();

		GLuint m_ShaderID;
		GLuint m_VertexShader;
		GLuint m_FragmentShader;

#ifdef ANDROID
		static const int32 ANDROID_ERROR_SIZE = 4096;
#endif

		Shader(const Shader& t);
		Shader(Shader&& t);
		Shader& operator=(const Shader& t);
		Shader& operator=(Shader&&);
	};
}
