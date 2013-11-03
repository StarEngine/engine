#include "Shader.h"
#include "../Logger.h"
#include "../Helpers/Helpers.h"
#include "../StarEngine.h"

namespace star
{
	Shader::Shader()
		// [COMMENT] Initialize all your datamembers!
	{

	}

	Shader::Shader( const tstring& vsFile, const tstring& fsFile )
		// [COMMENT] Initialize all your datamembers!
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
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Failed To load Vertex Shader"));
			return false;
		}
		
		if(!CompileShader(&mFragmentShader, GL_FRAGMENT_SHADER, fsFile))
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Failed To load Fragment Shader"));
			return false;
		}
		
		glAttachShader(mShaderID, mVertexShader);
		glAttachShader(mShaderID,mFragmentShader);

		glBindAttribLocation(mShaderID,ATTRIB_VERTEX,"Position");
		glBindAttribLocation(mShaderID,ATTRIB_TEXTUREPOSITON,"TexCoord");

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
		if(resource.Open() == STATUS_KO)
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Android Shader : Failed to open file"));
			return false;
		}
	
		int32 length = resource.GetLength();
		//star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : File size :")+star::string_cast<tstring>(length));
		char* doc = reinterpret_cast<char*>( malloc (length+1));

		if(resource.Read(doc,length) == STATUS_KO)
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Android Shader : Failed to read file"));
			resource.Close();
			return false;
		}
		doc[length]=0;

		/*tstring filecontent= tstring(doc);

		star::Logger::GetInstance()->Log(LogLevel::Info,filecontent);*/

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
					buffer << _T("Could not compile shader") << (int)type << _T(" : ") << std::endl << buf;
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
					buffer << _T("Could not compile shader") << (int)type << _T(" : ") << std::endl << buf;
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

	const GLfloat* Shader::GetProjection() const
	{
		return GlProjection;
	}

	const GLfloat* Shader::GetTranslation() const
	{
		return GlTranslation;
	}

	const char* Shader::TextFileReading(const tstring& fileName)
	{
		char* text(NULL);
		// [COMMENT] playing a dangerous game here
		// 1) Don't use C style memory allocations => Use C++ way (new / delete)
		// 2) Prevent using C-style strings ( char arrays )
		// 3) If you do use c-Arrays => don't forget them to delete them
		//	  In this case you return it, so you have to delete it outside
		//	  this function ( even more dangerous )
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
					//[COMMENT] A memory leak starts below
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
