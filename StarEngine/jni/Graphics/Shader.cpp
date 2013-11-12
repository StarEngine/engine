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

	Shader::Shader( const tstring& vsFile, const tstring& fsFile )
		: mShaderID(0),
		mVertexShader(0),
		mFragmentShader(0)
	{
		Init(vsFile,fsFile);
	}

	Shader::~Shader(void)
	{
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragmentShader);
		glDeleteProgram(mShaderID);
	}

	bool Shader::Init(const tstring& vsFile, const tstring& fsFile )
	{
		mShaderID = glCreateProgram();
		
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
		
		glAttachShader(mShaderID, mVertexShader);
		glAttachShader(mShaderID,mFragmentShader);

		glBindAttribLocation(mShaderID,ATTRIB_VERTEX,"Position");
		glBindAttribLocation(mShaderID,ATTRIB_UV,"TexCoord");

		glLinkProgram(mShaderID);
		GLint status;
		glGetProgramiv(mShaderID,GL_LINK_STATUS,&status);
		if(status == 0)
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Failed to link shader"));
			return false;
		}
		
		return true;
	}

	bool Shader::CompileShader(GLuint* shader, GLenum type, const tstring& file)
	{		
		GLint status;
		const GLchar* source;

#ifdef ANDROID
		Resource resource(StarEngine::GetInstance()->GetAndroidApp(), file);
		if(!resource.Open())
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
											 _T("Android Shader : Failed to open file"));
			return false;
		}
	
		int32 length = resource.GetLength();
		char* doc = reinterpret_cast<char*>( malloc (length+1));

		if(!resource.Read(doc,length))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, 
											 _T("Android Shader : Failed to read file"));
			resource.Close();
			return false;
		}
		doc[length]=0;

		source = const_cast<GLchar*>(&doc[0]);
		resource.Close();
#else
		source = const_cast<GLchar*>(TextFileReading(file));
#endif

		if(!source)
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Shader: Invalid Source"));
			return false;
		}
		*shader = glCreateShader(type);
		glShaderSource(*shader, 1, &source, NULL);
		delete[] source;
		glCompileShader(*shader);
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
		if(status == 0)
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Shader : Failed Compile"));
			GLint infolength;
			glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &infolength);
			if (infolength) 
			{
                char* buf = (char*) malloc(infolength);
                if (buf) 
				{
                    glGetShaderInfoLog(*shader, infolength, NULL, buf);
					tstringstream buffer;
					buffer << _T("Could not compile shader") << (int)type << _T(" : "); 
					buffer << std::endl << buf;
                    Logger::GetInstance()->Log(LogLevel::Error, buffer.str());
                    free(buf);
                }
            }
#ifdef ANDROID
			else
			{
				//This is necessairy due to an android bug!
				char* buf = (char*) malloc(4096);
				if (buf)
				{
					glGetShaderInfoLog(*shader, 4096, NULL, buf);
					tstringstream buffer;
					buffer << _T("Could not compile shader");
					buffer << (int)type << _T(" : ") << std::endl << buf;
					Logger::GetInstance()->Log(LogLevel::Error, buffer.str());
					free(buf);
				}
			}
#endif
			glDeleteShader(*shader);
			*shader = 0;
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

	const GLuint Shader::GetId() const
	{
		return mShaderID;
	}

	const char* Shader::TextFileReading(const tstring& fileName)
	{
		char* text(NULL);
		if (fileName != EMPTY_STRING)
		{
			FILE *file;
#ifdef DESKTOP
			_wfopen_s(&file,fileName.c_str(), _T("rb"));
#endif
			if (file != NULL)
			{
				fseek(file, 0,2);
				int count = ftell(file);
				rewind(file);

				if (count > 0)
				{
					text = (char*)malloc(sizeof(char) * (count + 1));
					count = fread(text, sizeof(char), count, file);
					text[count] = '\0';
				}
				fclose(file);
			}
		}
		return text;
	}
}
