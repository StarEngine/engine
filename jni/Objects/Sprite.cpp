#include "Sprite.h"
#include "../Logger.h"
#include "../Helpers/Filepath.h"
#include "../AssetManaging/TextureManager.h"

namespace star
{
	// [COMMENT] const correctnes?
	Sprite::Sprite(tstring filePath, tstring spriteName):
		mSpriteName(spriteName)
	{

#ifdef _WIN32
		Filepath texshaderVertex(_T("WinShaders/"),_T("Texture_Shader.vert"));
		Filepath texshaderFrag(_T("WinShaders/"),_T("Texture_Shader.frag"));
#else
		Filepath texshaderVertex(_T("AndroidShaders/"),_T("BaseTexShader.vert"));
		Filepath texshaderFrag(_T("AndroidShaders/"),_T("BaseTexShader.frag"));

#endif
		if(!mShader.Init(texshaderVertex.GetFullPath(),texshaderFrag.GetFullPath()))
		{
			star::Logger::GetSingleton()->Log(star::LogLevel::Info, _T("Making Shader Failed"));
		}

		star::TextureManager::GetInstance()->LoadTexture(filePath,mSpriteName);

		createSquare();

	}

	Sprite::~Sprite()
	{
		star::TextureManager::GetInstance()->DeleteTexture(mSpriteName);
	}

	// [COMMENT] see comment in header file
	void Sprite::createSquare()
	{
		mVertices[0] = 0.5f;
		mVertices[1] = 0.5f;
		mVertices[2] = 0.5f;
		mVertices[3] = -0.5f;
		mVertices[4] = -0.5f;
		mVertices[5] = 0.5f;
		mVertices[6] = -0.5f;
		mVertices[7] = -0.5f;

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
		GLint s_textureId = glGetUniformLocation(mShader.id(), "textureSampler");
		glUniform1i(s_textureId, 0);

		//Set attributes and buffers
		glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT,0,0, mVertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, mUvCoords);
		glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		mShader.Unbind();
	}

}
