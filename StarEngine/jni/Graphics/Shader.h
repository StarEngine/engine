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
	/// Compiles shaders, creates program and links the shaders to the program. 
	/// Provides managed interface for easily creating shader programs.
	/// </summary>
	class Shader final
	{
	public:
		/// <summary>
		/// creates a new instance of the <see cref="Shader"/> class.
		/// </summary>
		/// <param name="vsFile">The vertex shader file.</param>
		/// <param name="fsFile">The fragment shader file.</param>
		Shader(const tstring& vsFile, const tstring& fsFile);
		/// <summary>
		/// creates a new instance of the <see cref="Shader"/> class.
		/// </summary>
		/// <param name="inlineVert">The inline vertex shader.</param>
		/// <param name="inlineFrag">The inline fragment shader.</param>
		Shader(const GLchar* inlineVert, const GLchar* inlineFrag);
		/// <summary>
		/// Finalizes an instance of the <see cref="Shader"/> class.
		/// </summary>
		~Shader();

		/// <summary>
		/// Binds this shader program to openGL.
		/// </summary>
		void Bind();
		/// <summary>
		/// Unbinds this shader program from openGL.
		/// </summary>
		void Unbind();

		/// <summary>
		/// Gets the unique number of this program.
		/// This number is used by OpenGL to reference to this shader program.
		/// </summary>
		/// <returns>The unique program number.</returns>
		const GLuint GetProgramID() const;
		/// <summary>
		/// Looks up the location of this uniform in the shader.
		/// </summary>
		/// <param name="nameInShader">The name of the uniform in the shader.</param>
		/// <returns>The location of the uniform in the shader.</returns>
		GLuint GetUniformLocation(const GLchar* nameInShader) const;
		/// <summary>
		/// Looks up the location of this attribute in the shader.
		/// </summary>
		/// <param name="nameInShader">The name of the attribute in the shader.</param>
		/// <returns>The location of the attribute in the shader.</returns>
		GLuint GetAttribLocation(const GLchar* nameInShader) const;
		/// <summary>
		/// Prints the active attributes.
		/// </summary>
		void PrintActiveAttribs() const;
		/// <summary>
		/// Prints the active uniforms.
		/// </summary>
		void PrintActiveUniforms() const;

	private:
		/// <summary>
		/// Starts the process of compiling shaders, creating the program
		/// and linking the shaders to the program.
		/// </summary>
		/// <param name="vsFile">The vertex shader file.</param>
		/// <param name="fsFile">The fragment shader file.</param>
		/// <returns>True if everything was succesfull.</returns>
		bool Init(const tstring& vsFile, const tstring& fsFile);
		/// <summary>
		/// Starts the process of compiling shaders, creating the program
		/// and linking the shaders to the program.
		/// </summary>
		/// <param name="inlineVert">The inline vertex shader.</param>
		/// <param name="inlineFrag">The inline fragment shader.</param>
		/// <returns>True if everything was succesfull.</returns>
		bool Init(const GLchar* inlineVert, const GLchar* inlineFrag);

		/// <summary>
		/// Compiles the shader.
		/// </summary>
		/// <param name="shader">The shader to compile.</param>
		/// <param name="type">
		/// The type of the shader. Example: GL_VERTEX_SHADER
		/// </param>
		/// <param name="file">The file to compile.</param>
		/// <returns>True if the compilation was succesfull.</returns>
		bool CompileShader(GLuint* shader, GLenum type, const tstring& file);
		/// <summary>
		/// Compiles the shader.
		/// </summary>
		/// <param name="shader">The shader to compile.</param>
		/// <param name="type">
		/// The type of the shader. Example: GL_VERTEX_SHADER
		/// </param>
		/// <param name="inlineFile">The inline file to compile.</param>
		/// <returns>True if the compilation was succesfull.</returns>
		bool CompileShader(GLuint* shader, GLenum type, const GLchar* inlineFile);

		/// <summary>
		/// wraps the OpenGL parts of the shader creation process.
		/// </summary>
		/// <returns>True if everything was succesfull.</returns>
		bool GLInit();
		/// <summary>
		/// wraps the OpenGL parts of the shader compilation process.
		/// </summary>
		/// <returns>True if everything was succesfull.</returns>
		bool GLCompileShader();

		GLuint m_ProgramID;
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
