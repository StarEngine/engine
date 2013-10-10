#include "Sprite.h"
#include "../Logger.h"
#include "../Helpers/Filepath.h"
#include "../AssetManaging/TextureManager.h"

namespace star
{
	Sprite::Sprite(const tstring& filePath,const tstring& spriteName):
		mSpriteName(spriteName)
	{

#ifdef _WIN32
		Filepath texshaderVertex(_T("WinShaders/"), _T("Texture_Shader.vert"));
		Filepath texshaderFrag(_T("WinShaders/"), _T("Texture_Shader.frag"));
#else
		Filepath texshaderVertex(_T("AndroidShaders/"), _T("BaseTexShader.vert"));
		Filepath texshaderFrag(_T("AndroidShaders/"), _T("BaseTexShader.frag"));

#endif
		if(!mShader.Init(texshaderVertex.GetFullPath(),texshaderFrag.GetFullPath()))
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Making Shader Failed"));
		}

		star::TextureManager::GetInstance()->LoadTexture(filePath,mSpriteName);

		CreateSquare();
	}

	Sprite::~Sprite()
	{
		star::TextureManager::GetInstance()->DeleteTexture(mSpriteName);
	}

	void Sprite::CreateSquare()
	{
		mVertices[0] = 512;
		mVertices[1] = 512;
		mVertices[2] = 0;
		mVertices[3] = 512;
		mVertices[4] = 0;
		mVertices[5] = 0;
		mVertices[6] = 0;
		mVertices[7] = 512;
		mVertices[8] = 0;
		mVertices[9] = 0;
		mVertices[10] = 0;
		mVertices[11] = 0;

		mUvCoords[0] = 1.0f;
		mUvCoords[1] = 1.0f;
		mUvCoords[2] = 1.0f;
		mUvCoords[3] = 0.0f;
		mUvCoords[4] = 0.0f;
		mUvCoords[5] = 1.0f;
		mUvCoords[6] = 0.0f;
		mUvCoords[7] = 0.0f;
	}

	void Sprite::Draw()
	{
		mShader.Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(mSpriteName));
		GLint s_textureId = glGetUniformLocation(mShader.GetId(), "textureSampler");
		glUniform1i(s_textureId, 0);

		//Set attributes and buffers
		glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT,0,0, mVertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, mUvCoords);
		glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		
		glUniformMatrix4fv(glGetUniformLocation(mShader.GetId(),"Projection"),1,GL_FALSE,mShader.GetProjection());
		glUniformMatrix4fv(glGetUniformLocation(mShader.GetId(),"Translation"),1,GL_FALSE,mShader.GetTranslation());

		GLfloat getLocation[16];
		glGetUniformfv(mShader.GetId(),glGetUniformLocation(mShader.GetId(),"Projection"),getLocation);
		/*tstringstream buffer;
		for(int i = 0; i < 16; ++i)
		{
			buffer << _T("Projection shader Value [") << i << _T("] : ") << getLocation[i] << std::endl;
			Logger::GetInstance()->Log(LogLevel::Info,buffer.str());
		}
		*/

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		mShader.Unbind();
	}
}
