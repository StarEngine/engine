#include "Shader.h"
#include "../Logger.h"
#include "../Helpers/Helpers.h"
#include "../StarEngine.h"

namespace star
{
	Shader::Shader()
		: m_ShaderID(0)
		, m_VertexShader(0)
		, m_FragmentShader(0)
	{

	}

	Shader::Shader(const tstring& vsFile, const tstring& fsFile)
		: m_ShaderID(0)
		, m_VertexShader(0)
		, m_FragmentShader(0)
	{
		Init(vsFile, fsFile);
	}

	Shader::Shader(const GLchar* inLineVert, const GLchar* inLineFrag)
		: m_ShaderID(0)
		, m_VertexShader(0)
		, m_FragmentShader(0)
	{
		Init(inLineVert,inLineFrag);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	bool Shader::Init(const tstring& vsFile, const tstring& fsFile)
	{	
		if(!CompileShader(&m_VertexShader, GL_VERTEX_SHADER, vsFile ))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
				_T("Shader::Init: \
				   Failed To load Vertex Shader"),
				   STARENGINE_LOG_TAG);
			return false;
		}
		
		if(!CompileShader(&m_FragmentShader, GL_FRAGMENT_SHADER, fsFile))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
				 _T("Shader::Init: \
					Failed To load Fragment Shader"),
					STARENGINE_LOG_TAG);
			return false;
		}
		
		return GLInit();
	}

	bool Shader::Init(const GLchar* inLineVert, const GLchar* inLineFrag)
	{
		if(!CompileShader(&m_VertexShader, GL_VERTEX_SHADER, inLineVert ))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
				_T("Shader::Init: \
					Failed To load Vertex Shader"),
					STARENGINE_LOG_TAG);
			return false;
		}
		
		if(!CompileShader(&m_FragmentShader, GL_FRAGMENT_SHADER, inLineFrag))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
				 _T("Shader::Init \
					Failed To load Fragment Shader"),
					STARENGINE_LOG_TAG);
			return false;
		}
		return GLInit();
	}

	bool Shader::GLInit()
	{
		m_ShaderID = glCreateProgram();

		if(m_ShaderID == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("Shader::GLInit: Failed to create program!"),
				STARENGINE_LOG_TAG);
		}

		glAttachShader(m_ShaderID, m_VertexShader);
		glAttachShader(m_ShaderID, m_FragmentShader);

		//[TODO] Move outside of this class!
		//[TODO] Write material class for more flexibility
		glBindAttribLocation(m_ShaderID, ATTRIB_VERTEX, "Position");
		glBindAttribLocation(m_ShaderID, ATTRIB_UV, "TexCoord");
		//[TODO] end

		glLinkProgram(m_ShaderID);
		GLint status;
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &status);
		if(!status)
		{
			GLint infoLen(0);
			glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLen);
			if(infoLen > 1)
			{
				schar* infoLog = new schar[infoLen];
				glGetProgramInfoLog(m_ShaderID, infoLen, NULL, infoLog);
				tstringstream buffer;
				buffer	<< _T("Shader::GLInit: \
							 Failed to link program: ") 
						<< std::endl 
						<< infoLog;
				Logger::GetInstance()->Log(LogLevel::Error, buffer.str(),
					STARENGINE_LOG_TAG);
				delete infoLog;
				
			}
#ifdef ANDROID
			else
			{
				schar* infoLog = new schar[ANDROID_ERROR_SIZE];
				glGetProgramInfoLog(m_ShaderID, ANDROID_ERROR_SIZE, NULL, infoLog);
				tstringstream buffer;
				buffer << _T("Shader::GLInit: \
							 Failed to link program: ") 
						<< std::endl 
						<< infoLog;
				Logger::GetInstance()->Log(LogLevel::Error, buffer.str());
				delete infoLog;
				
			}
#endif
			glDeleteProgram(m_ShaderID);
			return false;
		}
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);

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
			star::Logger::GetInstance()->Log(LogLevel::Error,
				_T("Shader::CompileShader: Failed Compile"),
				STARENGINE_LOG_TAG);
			GLint infolength;
			glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &infolength);
			if (infolength > 1) 
			{
				schar* buf = new schar[infolength];
				if (buf) 
				{
					glGetShaderInfoLog(*shader, infolength, NULL, buf);
					tstringstream buffer;
					buffer	<< _T("Shader::CompileShader: \
								 Could not compile shader") 
							<< int32(type) 
							<< _T(": ")
							<< std::endl 
							<< buf;
					Logger::GetInstance()->Log(LogLevel::Error,
						buffer.str(), STARENGINE_LOG_TAG);
					delete buf;
				}
			}
#ifdef ANDROID
			else
			{
				//This is necessary due to an Android bug!
				schar* buf = new schar[ANDROID_ERROR_SIZE];
				if (buf)
				{
					glGetShaderInfoLog(*shader, ANDROID_ERROR_SIZE, NULL, buf);
					tstringstream buffer;
					buffer 	<< _T("Shader::CompileShader: \
								 Could not compile shader") 
							<< int32(type) 
							<< _T(": ")
							<< std::endl 
							<< buf;
					Logger::GetInstance()->Log(LogLevel::Error,
						buffer.str(), STARENGINE_LOG_TAG);
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
		glUseProgram(m_ShaderID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	const GLuint Shader::GetID() const
	{
		return m_ShaderID;
	}

	GLuint Shader::GetUniformLocation(const GLchar* nameInShader) const
	{
		return glGetUniformLocation(m_ShaderID, nameInShader);
	}

	GLuint Shader::GetAttribLocation(const GLchar* nameInShader) const
	{
		return glGetAttribLocation(m_ShaderID, nameInShader);
	}

	void Shader::PrintActiveAttribs() const
	{
		GLint nAttribs;
		GLsizei maxLength;

		glGetProgramiv(m_ShaderID, GL_ACTIVE_ATTRIBUTES, &nAttribs);
		glGetProgramiv(m_ShaderID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

		GLchar* name = new GLchar[maxLength];

		GLint written, size, location;
		GLenum type;
		Logger::GetInstance()->Log(LogLevel::Debug,
			_T(" Location | Name"), STARENGINE_LOG_TAG);
		Logger::GetInstance()->Log(LogLevel::Debug,
			_T("------------------------------------------------"),
			STARENGINE_LOG_TAG);
		for(GLuint i = 0; i < GLuint(nAttribs); ++i)
		{
			glGetActiveAttrib(m_ShaderID, i, maxLength, &written, &size, &type, name);
			location = glGetAttribLocation(m_ShaderID, name);
			Logger::GetInstance()->
				Log(LogLevel::Debug, string_cast<tstring>(location) + _T(" | ") + string_cast<tstring>(name));
		}
		delete name;
	}

	void Shader::PrintActiveUniforms() const
	{
		GLint nUniforms;
		GLsizei maxLength;

		glGetProgramiv(m_ShaderID, GL_ACTIVE_UNIFORMS, &nUniforms);
		glGetProgramiv(m_ShaderID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

		GLchar* name = new GLchar[maxLength];

		GLint size, location;
		GLsizei written;
		GLenum type;
		Logger::GetInstance()->Log(LogLevel::Debug,
			_T(" Location | Name"), STARENGINE_LOG_TAG);
		Logger::GetInstance()->Log(LogLevel::Debug,
			_T("------------------------------------------------"),
			STARENGINE_LOG_TAG);
		for(GLuint i = 0; i < GLuint(nUniforms); ++i)
		{
			glGetActiveUniform(m_ShaderID, i, maxLength, &written, &size, &type, name);
			location = glGetUniformLocation(m_ShaderID, name);
			Logger::GetInstance()->
				Log(LogLevel::Debug, string_cast<tstring>(location) +
				_T(" | ") + string_cast<tstring>(name), STARENGINE_LOG_TAG);
		}
		delete name;
	}
}
