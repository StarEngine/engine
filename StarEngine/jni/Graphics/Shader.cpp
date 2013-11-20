#include "Shader.h"
#include "../Logger.h"
#include "../Helpers/Helpers.h"
#include "../StarEngine.h"

namespace star
{
	Shader::Shader()
		: mShaderID(0),
		mVertexShader(0),
		mFragmentShader(0)
	{

	}

	Shader::Shader(const tstring& vsFile, const tstring& fsFile)
		: mShaderID(0),
		mVertexShader(0),
		mFragmentShader(0)
	{
		Init(vsFile, fsFile);
	}

	Shader::Shader(const GLchar* inLineVert, const GLchar* inLineFrag)
		: mShaderID(0),
		mVertexShader(0),
		mFragmentShader(0)
	{
		Init(inLineVert,inLineFrag);
	}

	Shader::~Shader()
	{
		glDeleteProgram(mShaderID);
	}

	bool Shader::Init(const tstring& vsFile, const tstring& fsFile)
	{	
		if(!CompileShader(&mVertexShader, GL_VERTEX_SHADER, vsFile ))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
				_T("Failed To load Vertex Shader"));
			return false;
		}
		
		if(!CompileShader(&mFragmentShader, GL_FRAGMENT_SHADER, fsFile))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
				 _T("Failed To load Fragment Shader"));
			return false;
		}
		
		return GLInit();
	}

	bool Shader::Init(const GLchar* inLineVert, const GLchar* inLineFrag)
	{
		if(!CompileShader(&mVertexShader, GL_VERTEX_SHADER, inLineVert ))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
				_T("Failed To load Vertex Shader"));
			return false;
		}
		
		if(!CompileShader(&mFragmentShader, GL_FRAGMENT_SHADER, inLineFrag))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
				 _T("Failed To load Fragment Shader"));
			return false;
		}
		return GLInit();
	}

	bool Shader::GLInit()
	{
		mShaderID = glCreateProgram();

		if(mShaderID == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Error, _T("Failed to create program!"));
		}

		glAttachShader(mShaderID, mVertexShader);
		glAttachShader(mShaderID, mFragmentShader);

		//[TODO] Move outside of this class!
		glBindAttribLocation(mShaderID, ATTRIB_VERTEX, "Position");
		glBindAttribLocation(mShaderID, ATTRIB_UV, "TexCoord");
		//[TODO] end

		glLinkProgram(mShaderID);
		GLint status;
		glGetProgramiv(mShaderID, GL_LINK_STATUS, &status);
		if(!status)
		{
			GLint infoLen(0);
			glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &infoLen);
			if(infoLen > 1)
			{
				schar* infoLog = new schar[infoLen];
				glGetProgramInfoLog(mShaderID, infoLen, NULL, infoLog);
				tstringstream buffer;
				buffer << _T("Failed to link program") << _T(" : "); 
				buffer << std::endl << infoLog;
				Logger::GetInstance()->Log(LogLevel::Error, buffer.str());
				delete infoLog;
				
			}
#ifdef ANDROID
			else
			{
				schar* infoLog = new schar[ANDROID_ERROR_SIZE];
				glGetProgramInfoLog(mShaderID, ANDROID_ERROR_SIZE, NULL, infoLog);
				tstringstream buffer;
				buffer << _T("Failed to link program") << _T(": "); 
				buffer << std::endl << infoLog;
				Logger::GetInstance()->Log(LogLevel::Error, buffer.str());
				delete infoLog;
				
			}
#endif
			glDeleteProgram(mShaderID);
			return false;
		}
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragmentShader);

		return true;
	}

	bool Shader::CompileShader(GLuint* shader, GLenum type, const tstring& file)
	{		
		schar* source;

		uint32 size;
		schar * buffer = ReadBinaryFile(file, size);
		source = new schar[size+1];
		memcpy(source, buffer, size);

		delete [] buffer;

		source[size] = '\0';

		bool returnValue(CompileShader(shader, type, source));

		delete[] source;

		return returnValue;
	}

	bool Shader::CompileShader(GLuint* shader, GLenum type, const GLchar* inLineFile)
	{		
		*shader = glCreateShader(type);
		glShaderSource(*shader, 1, &inLineFile, NULL);
		glCompileShader(*shader);
		GLint status;
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
		if(status == 0)
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Shader: Failed Compile"));
			GLint infolength;
			glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &infolength);
			if (infolength > 1) 
			{
				schar* buf = new schar[infolength];
				if (buf) 
				{
					glGetShaderInfoLog(*shader, infolength, NULL, buf);
					tstringstream buffer;
					buffer << _T("Could not compile shader") << (int32)type << _T(": "); 
					buffer << std::endl << buf;
					Logger::GetInstance()->Log(LogLevel::Error, buffer.str());
					delete buf;
				}
			}
#ifdef ANDROID
			else
			{
				//This is necessairy due to an android bug!
				schar* buf = new schar[ANDROID_ERROR_SIZE];
				if (buf)
				{
					glGetShaderInfoLog(*shader, ANDROID_ERROR_SIZE, NULL, buf);
					tstringstream buffer;
					buffer << _T("Could not compile shader");
					buffer << (int32)type << _T(" : ") << std::endl << buf;
					Logger::GetInstance()->Log(LogLevel::Error, buffer.str());
					delete buf;
				}
			}
#endif
			glDeleteShader(*shader);
			shader = 0;
			return false;
		}
		return true;
	}

	void Shader::Bind()
	{
		glUseProgram(mShaderID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	const GLuint Shader::GetID() const
	{
		return mShaderID;
	}

	GLuint Shader::GetUniformLocation(const GLchar* nameInShader) const
	{
		return glGetUniformLocation(mShaderID, nameInShader);
	}

	GLuint Shader::GetAttribLocation(const GLchar* nameInShader) const
	{
		return glGetAttribLocation(mShaderID, nameInShader);
	}

	void Shader::PrintActiveAttribs() const
	{
		GLint nAttribs;
		GLsizei maxLength;

		glGetProgramiv(mShaderID, GL_ACTIVE_ATTRIBUTES, &nAttribs);
		glGetProgramiv(mShaderID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

		GLchar* name = new GLchar[maxLength];

		GLint written, size, location;
		GLenum type;
		Logger::GetInstance()->Log(LogLevel::Debug,_T(" Location | Name"));
		Logger::GetInstance()->Log(LogLevel::Debug,_T("------------------------------------------------"));
		for(GLuint i = 0; i < GLuint(nAttribs); ++i )
		{
			glGetActiveAttrib(mShaderID, i, maxLength, &written, &size, &type, name);
			location = glGetAttribLocation(mShaderID, name);
			Logger::GetInstance()->
				Log(LogLevel::Debug, string_cast<tstring>(location) + _T(" | ") + string_cast<tstring>(name));
		}
		delete name;
	}

	void Shader::PrintActiveUniforms() const
	{
		GLint nUniforms;
		GLsizei maxLength;

		glGetProgramiv(mShaderID, GL_ACTIVE_UNIFORMS, &nUniforms);
		glGetProgramiv(mShaderID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

		GLchar* name = new GLchar[maxLength];

		GLint size, location;
		GLsizei written;
		GLenum type;
		Logger::GetInstance()->Log(LogLevel::Debug,_T(" Location | Name"));
		Logger::GetInstance()->Log(LogLevel::Debug,_T("------------------------------------------------"));
		for(GLuint i = 0; i < GLuint(nUniforms); ++i )
		{
			glGetActiveUniform(mShaderID, i, maxLength, &written, &size, &type, name);
			location = glGetUniformLocation(mShaderID, name);
			Logger::GetInstance()->
				Log(LogLevel::Debug, string_cast<tstring>(location) + _T(" | ") + string_cast<tstring>(name));
		}
		delete name;
	}
}
