#include "Shader.h"
#include "../Logger.h"
#include "../Helpers/Helpers.h"
#include "../StarEngine.h"

namespace star
{
	Shader::Shader(const tstring& vsFile, const tstring& fsFile)
		: m_ProgramID(0)
		, m_VertexShader(0)
		, m_FragmentShader(0)
	{
		Init(vsFile, fsFile);
	}

	Shader::Shader(const GLchar* inlineVert, const GLchar* inlineFrag)
		: m_ProgramID(0)
		, m_VertexShader(0)
		, m_FragmentShader(0)
	{
		Init(inlineVert,inlineFrag);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramID);
	}

	bool Shader::Init(const tstring& vsFile, const tstring& fsFile)
	{	
		if(!CompileShader(&m_VertexShader, GL_VERTEX_SHADER, vsFile ))
		{
			LOG(LogLevel::Error, 
				_T("Shader::Init: \
Failed To load Vertex Shader ") + vsFile,
				   STARENGINE_LOG_TAG);
			return false;
		}
		
		if(!CompileShader(&m_FragmentShader, GL_FRAGMENT_SHADER, fsFile))
		{
			LOG(LogLevel::Error, 
				 _T("Shader::Init: \
Failed To load Fragment Shader ") + fsFile,
					STARENGINE_LOG_TAG);
			return false;
		}
		
		return GLInit();
	}

	bool Shader::Init(const GLchar* inlineVert, const GLchar* inlineFrag)
	{
		if(!CompileShader(&m_VertexShader, GL_VERTEX_SHADER, inlineVert ))
		{
			LOG(LogLevel::Error, 
				_T("Shader::Init: \
Failed To load Vertex Shader ") + string_cast<tstring>(inlineVert),
				   STARENGINE_LOG_TAG);
			return false;
		}
		
		if(!CompileShader(&m_FragmentShader, GL_FRAGMENT_SHADER, inlineFrag))
		{
			LOG(LogLevel::Error, 
				 _T("Shader::Init: \
Failed To load Fragment Shader ") + string_cast<tstring>(inlineFrag),
					STARENGINE_LOG_TAG);
			return false;
		}
		return GLInit();
	}

	bool Shader::GLInit()
	{
		m_ProgramID = glCreateProgram();

		if(m_ProgramID == 0)
		{
			LOG(LogLevel::Error,
				_T("Shader::GLInit: Failed to create program!"),
				STARENGINE_LOG_TAG);
		}

		glAttachShader(m_ProgramID, m_VertexShader);
		glAttachShader(m_ProgramID, m_FragmentShader);

		glLinkProgram(m_ProgramID);
		GLint status;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status);
		if(!status)
		{
			GLint infoLen(0);
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLen);
			if(infoLen > 1)
			{
				schar* infoLog = new schar[infoLen];
				glGetProgramInfoLog(m_ProgramID, infoLen, NULL, infoLog);
				tstringstream buffer;
				buffer	<< _T("Shader::GLInit: Failed to link program: ")
						<< infoLog;
				LOG(LogLevel::Error, buffer.str(),
					STARENGINE_LOG_TAG);
				delete infoLog;
				
			}
#ifdef ANDROID
			else
			{
				schar* infoLog = new schar[ANDROID_ERROR_SIZE];
				glGetProgramInfoLog(m_ProgramID, ANDROID_ERROR_SIZE, NULL, infoLog);
				tstringstream buffer;
				buffer << _T("Shader::GLInit: Failed to link program: ")
						<< infoLog;
				LOG(LogLevel::Error, buffer.str());
				delete infoLog;
				
			}
#endif
			glDeleteProgram(m_ProgramID);
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

	bool Shader::CompileShader(GLuint* shader, GLenum type, const GLchar* inlineFile)
	{		
		*shader = glCreateShader(type);
		glShaderSource(*shader, 1, &inlineFile, NULL);
		glCompileShader(*shader);
		GLint status;
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
		if(status == 0)
		{
			LOG(LogLevel::Error,
				_T("Shader::CompileShader: Failed Compile"),
				STARENGINE_LOG_TAG);
			GLint infolength;
			glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &infolength);
			if (infolength > 1) 
			{
				schar* buf = new schar[infolength];
				if (buf) 
				{
					tstring stringType;
					switch(type)
					{
					case GL_VERTEX_SHADER:
						stringType = _T("GL_VERTEX_SHADER");
						break;
					case GL_FRAGMENT_SHADER:
						stringType = _T("GL_FRAGMENT_SHADER");
						break;
					default:
						stringType = _T("UNKNOWN_SHADER_TYPE");
						break;
					}
					glGetShaderInfoLog(*shader, infolength, NULL, buf);
					tstringstream buffer;
					buffer	<< _T("Shader::CompileShader: \
Could not compile shader of type ") 
							<< stringType
							<< _T(": ")
							<< buf;
					LOG(LogLevel::Error,
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
					tstring stringType;
					switch(type)
					{
					case GL_VERTEX_SHADER:
						stringType = _T("GL_VERTEX_SHADER");
						break;
					case GL_FRAGMENT_SHADER:
						stringType = _T("GL_FRAGMENT_SHADER");
						break;
					default:
						stringType = _T("UNKNOWN_SHADER_TYPE");
						break;
					}
					glGetShaderInfoLog(*shader, ANDROID_ERROR_SIZE, NULL, buf);
					tstringstream buffer;
					buffer 	<< _T("Shader::CompileShader: \
Could not compile shader of type ") 
							<< stringType
							<< _T(": ")
							<< buf;
					LOG(LogLevel::Error,
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
		glUseProgram(m_ProgramID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	const GLuint Shader::GetProgramID() const
	{
		return m_ProgramID;
	}

	GLuint Shader::GetUniformLocation(const GLchar* nameInShader) const
	{
		return glGetUniformLocation(m_ProgramID, nameInShader);
	}

	GLuint Shader::GetAttribLocation(const GLchar* nameInShader) const
	{
		return glGetAttribLocation(m_ProgramID, nameInShader);
	}

	void Shader::PrintActiveAttribs() const
	{
		GLint nAttribs;
		GLsizei maxLength;

		glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTES, &nAttribs);
		glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

		GLchar* name = new GLchar[maxLength];

		GLint written, size, location;
		GLenum type;
		DEBUG_LOG(LogLevel::Info,
			_T(" Location | Name"), STARENGINE_LOG_TAG);
		DEBUG_LOG(LogLevel::Info,
			_T("------------------------------------------------"),
			STARENGINE_LOG_TAG);
		for(GLuint i = 0; i < GLuint(nAttribs); ++i)
		{
			glGetActiveAttrib(
				m_ProgramID, 
				i, 
				maxLength, 
				&written, 
				&size, 
				&type, 
				name
				);
			location = glGetAttribLocation(m_ProgramID, name);
			Logger::GetInstance()->
				DebugLog(LogLevel::Info, 
					string_cast<tstring>(location) +
					_T(" | ") + 
					string_cast<tstring>(name), 
					STARENGINE_LOG_TAG
				);
		}
		delete name;
	}

	void Shader::PrintActiveUniforms() const
	{
		GLint nUniforms;
		GLsizei maxLength;

		glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &nUniforms);
		glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

		GLchar* name = new GLchar[maxLength];

		GLint size, location;
		GLsizei written;
		GLenum type;
		DEBUG_LOG(LogLevel::Info,
			_T(" Location | Name"), STARENGINE_LOG_TAG);
		DEBUG_LOG(LogLevel::Info,
			_T("------------------------------------------------"),
			STARENGINE_LOG_TAG);
		for(GLuint i = 0; i < GLuint(nUniforms); ++i)
		{
			glGetActiveUniform(
				m_ProgramID, 
				i, 
				maxLength, 
				&written, 
				&size, 
				&type, 
				name
				);
			location = glGetUniformLocation(m_ProgramID, name);
			Logger::GetInstance()->
				DebugLog(LogLevel::Info, 
					string_cast<tstring>(location) +
					_T(" | ") + 
					string_cast<tstring>(name), 
					STARENGINE_LOG_TAG
				);
		}
		delete name;
	}
}
