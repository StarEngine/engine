#include "Shader.h"
#include "../Logger.h"

namespace star
{

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

	bool Shader::Init( tstring vsFile, tstring fsFile )
	{
		mShaderID = glCreateProgram();

		if(!CompileShader(&mVertexShader, GL_VERTEX_SHADER, vsFile ))
		{
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Failed To load Vertex Shader"));
			return false;
		}else
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Compiled Vertex Shader"));

		if(!CompileShader(&mFragmentShader, GL_FRAGMENT_SHADER, fsFile))
		{
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Failed To load Fragment Shader"));
			return false;
		}else
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Compiled Fragment Shader"));

		glAttachShader(mShaderID, mVertexShader);
		glAttachShader(mShaderID,mFragmentShader);


		glBindAttribLocation(mShaderID,ATTRIB_VERTEX,"position");
		glBindAttribLocation(mShaderID,ATTRIB_TEXTUREPOSITON,"inputTextureCoordinate");

		glLinkProgram(mShaderID);
		GLint status;
		glGetProgramiv(mShaderID,GL_LINK_STATUS,&status);
		if(status==0)
		{
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Failed to link shader"));
			return false;
		}
		else
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Shader Linked"));
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
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Android Shader : Failed to open file"));
			return false;
		}
		tstringstream buffer;
		int32 length = resource.getLength();
		buffer<<length;
		star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Android Shader : File size :")+buffer.str());

		char* doc = (char*) malloc (length+1);
		if(resource.read(doc,length)==STATUS_KO)
		{
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Android Shader : Failed to read file"));
			resource.close();
			return false;
		}
		doc[length]=0;


		tstring filecontent= tstring(doc);

		star::Logger::GetSingleton()->Log(LogLevel::Info,filecontent);


		source = (GLchar*)&doc[0];
		resource.close();
#else
		source = (GLchar*)TextFileReading(file);
#endif


		if(!source)
		{
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Android Shader : Invalid Source"));
			return false;
		}
		*shader = glCreateShader(type);
		glShaderSource(*shader, 1, &source, NULL);
		glCompileShader(*shader);
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
		if(status == 0)
		{
			star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Android Shader : Failed Compile"));
			GLint infolength;
			glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &infolength);

			//GLchar* strInfoLog = new GLchar[infolength + 1];
			//glGetShaderInfoLog(*shader, infolength, NULL, strInfoLog);
			//star::Logger::GetSingleton()->Log(LogLevel::Info, _T("Android Shader : ")+tstring(strInfoLog));
			glDeleteShader(*shader);
			return false;
		}
		return true;
	}

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

	char* Shader::TextFileReading(tstring fileName) {

		char* text="";
		if (fileName != _T("")) {

			FILE *file;

	#ifdef _WIN32
			_wfopen_s(&file,fileName.c_str(), _T("rb"));
	#else
			file = fopen(fileName.c_str(),"rb");
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
