#include "Shader.h"
#include "../Logger.h"
#include "../Helpers/Helpers.h"
#include "../StarEngine.h"

namespace star
{
	Shader::Shader( const tstring& vsFile, const tstring& fsFile )
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

		GLfloat Projection[16] = {
			 1.0f/1280.0f, 0,	0,	0
			,0,	1.0f/720.0f,	0,	0
			,0,	0,	1,	0
			,0,	0,	0,	1};

		GLfloat Translation[16] = {
			 1, 0,	0,	800.0f
			,0,	1,	0,	-400.0f
			,0,	0,	1,	0
			,0,	0,	0,	1};

		GlTranslation = (GLfloat*)malloc(4*4*sizeof(float));
		GlTranslation[0] = Translation[0];
		GlTranslation[1] = Translation[1];
		GlTranslation[2] = Translation[2];
		GlTranslation[3] = Translation[3];
	
		GlTranslation[4] = Translation[4];
		GlTranslation[5] = Translation[5];
		GlTranslation[6] = Translation[6];
		GlTranslation[7] = Translation[7];

		GlTranslation[8] = Translation[8];
		GlTranslation[9] = Translation[9];
		GlTranslation[10] = Translation[10];
		GlTranslation[11] = Translation[11];

		GlTranslation[12] = Translation[12];
		GlTranslation[13] = Translation[13];
		GlTranslation[14] = Translation[14];
		GlTranslation[15] = Translation[15];

		GlProjection = (GLfloat*)malloc(4*4*sizeof(float));
		GlProjection[0] = Projection[0];
		GlProjection[1] = Projection[1];
		GlProjection[2] = Projection[2];
		GlProjection[3] = Projection[3];
	
		GlProjection[4] = Projection[4];
		GlProjection[5] = Projection[5];
		GlProjection[6] = Projection[6];
		GlProjection[7] = Projection[7];

		GlProjection[8] = Projection[8];
		GlProjection[9] = Projection[9];
		GlProjection[10] = Projection[10];
		GlProjection[11] = Projection[11];

		GlProjection[12] = Projection[12];
		GlProjection[13] = Projection[13];
		GlProjection[14] = Projection[14];
		GlProjection[15] = Projection[15];

		return true;
	}

	bool Shader::CompileShader(GLuint* shader, GLenum type, const tstring& file)
	{
		GLint status;
		const GLchar* source;

#ifndef _WIN32
		Resource resource(StarEngine::GetInstance()->GetAndroidApp(), file);
		if(resource.open()==STATUS_KO)
		{
			star::Logger::GetInstance()->Log(LogLevel::Error, _T("Android Shader : Failed to open file"));
			return false;
		}
	
		int32 length = resource.getLength();
		star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : File size :")+star::string_cast<tstring>(length));
		char* doc = reinterpret_cast<char*>( malloc (length+1));

		if(resource.read(doc,length)==STATUS_KO)
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : Failed to read file"));
			resource.close();
			return false;
		}
		doc[length]=0;

		/*tstring filecontent= tstring(doc);

		star::Logger::GetInstance()->Log(LogLevel::Info,filecontent);*/

		source = const_cast<GLchar*>(&doc[0]);
		resource.close();
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
#ifndef _WIN32
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

	const char* Shader::TextFileReading(const tstring& fileName)
	{
		char* text(NULL);
		if (fileName != EMPTY_STRING)
		{
			FILE *file;
#ifdef _WIN32
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
