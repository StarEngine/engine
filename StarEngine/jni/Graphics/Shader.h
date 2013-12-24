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
#include "../Graphics/Resource.h"
#endif

namespace star
{
	/// <summary>
	/// Processing and loading of a provided vertex and fragment shader.
	/// Can be used for all materials consisting of a vertex and fragment shader.
	/// </summary>
	class Shader final
	{
	public:
		/// <summary>
		/// creates a new instance of the <see cref="Shader"/> class.
		/// </summary>
		/// <param name="vsFile">The vs file.</param>
		/// <param name="fsFile">The fs file.</param>
		Shader(const tstring& vsFile, const tstring& fsFile);
		Shader(const GLchar* inLineVert, const GLchar* inLineFrag);
		~Shader();

		void Bind();
		void Unbind();

		const GLuint GetID() const;
		GLuint GetUniformLocation(const GLchar* nameInShader) const;
		GLuint GetAttribLocation(const GLchar* nameInShader) const;
		void PrintActiveAttribs() const;
		void PrintActiveUniforms() const;

	private:
		bool Init(const tstring& vsFile, const tstring& fsFile);
		bool Init(const GLchar* inLineVert, const GLchar* inLineFrag);

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
