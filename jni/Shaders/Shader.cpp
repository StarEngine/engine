#include "Shader.h"
#include "../Logger.h"

namespace star
{
	// [COMMENT] see comment on the defintion of this function...
	Shader::Shader( tstring vsFile, tstring fsFile )
	{
		Init(vsFile,fsFile);
	}


	Shader::~Shader(void)
	{
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragmentShader);
		glDeleteProgram(mShaderID);

	}

	// [COMMENT] see comment on the defintion of this function...
	bool Shader::Init( tstring vsFile, tstring fsFile )
	{
		mShaderID = glCreateProgram();

		if(!CompileShader(&mVertexShader, GL_VERTEX_SHADER, vsFile ))
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Failed To load Vertex Shader"));
			return false;
		}
		else
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Compiled Vertex Shader"));
		}

		if(!CompileShader(&mFragmentShader, GL_FRAGMENT_SHADER, fsFile))
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Failed To load Fragment Shader"));
			return false;
		}
		else
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Compiled Fragment Shader"));
		}

		glAttachShader(mShaderID, mVertexShader);
		glAttachShader(mShaderID,mFragmentShader);

		glBindAttribLocation(mShaderID,ATTRIB_VERTEX,"position");
		glBindAttribLocation(mShaderID,ATTRIB_TEXTUREPOSITON,"inputTextureCoordinate");

		glLinkProgram(mShaderID);
		GLint status;
		glGetProgramiv(mShaderID,GL_LINK_STATUS,&status);
		if(status == 0)
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Failed to link shader"));
			return false;
		}
		else
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Shader Linked"));
		}
		return true;
	}

	bool Shader::CompileShader(GLuint* shader, GLenum type, tstring file)
	{
		GLint status;
		const GLchar* source;

#ifndef _WIN32
		Resource resource(star::EventLoop::mApplicationPtr,file);
		if(resource.open()==STATUS_KO)
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : Failed to open file"));
			return false;
		}
		// [COMMENT] use the star::string_cast<T>(...) function for this.
		tstringstream buffer;
		int32 length = resource.getLength();
		buffer<<length;
		star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : File size :")+buffer.str());
		// [COMMENT} Please don't use C mallocs here...
		// we're programming in C++ so use the C++ way of doing it
		char* doc = (char*) malloc (length+1);
		if(resource.read(doc,length)==STATUS_KO)
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : Failed to read file"));
			resource.close();
			return false;
		}
		doc[length]=0;

		tstring filecontent= tstring(doc);

		star::Logger::GetInstance()->Log(LogLevel::Info,filecontent);

		// C++0X casts please, thank you very much
		// In other words.. NO C casts...
		source = (GLchar*)&doc[0];
		resource.close();
#else
		source = (GLchar*)TextFileReading(file);
#endif

		if(!source)
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : Invalid Source"));
			return false;
		}
		*shader = glCreateShader(type);
		glShaderSource(*shader, 1, &source, NULL);
		glCompileShader(*shader);
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
		if(status == 0)
		{
			star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : Failed Compile"));
			GLint infolength;
			glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &infolength);
			// [COMMENT] Why is this code in comment?
			// Remove unused code please.
			// we use a revision control system, so just check an older
			// commit if you need it back...
			//GLchar* strInfoLog = new GLchar[infolength + 1];
			//glGetShaderInfoLog(*shader, infolength, NULL, strInfoLog);
			//star::Logger::GetInstance()->Log(LogLevel::Info, _T("Android Shader : ")+tstring(strInfoLog));
			glDeleteShader(*shader);
			return false;
		}
		return true;
	}

	// [COMMENT] You use a different return value version... Don't do it!
	// also please respect the order of your defintions in your header
	// with your implementations in this file.
	// also... check const correctness comment on the defintion.
	unsigned int Shader::id()
	{
		return mShaderID;
	}

	void Shader::Bind()
	{
		glUseProgram(mShaderID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	// [COMMENT] see comment on the defintion of this function...
	char* Shader::TextFileReading(tstring fileName)
	{
		char* text(NULL);
		if (fileName != EMPTY_STRING) {

			FILE *file;
#ifdef _WIN32
			_wfopen_s(&file,fileName.c_str(), _T("rb"));
#endif
			if (file != NULL) {
				fseek(file, 0,2);
				int count = ftell(file);
				rewind(file);

				if (count > 0) {
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
