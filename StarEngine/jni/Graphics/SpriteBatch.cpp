#include "SpriteBatch.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"
#include "../Scenes/SceneManager.h"
#include "GraphicsManager.h"
#include "../Components/CameraComponent.h"
#include "../Objects/FreeCamera.h"
#include "../Scenes/BaseScene.h"
#include <algorithm>

namespace star
{
	std::shared_ptr<SpriteBatch> SpriteBatch::m_pSpriteBatch = nullptr;

	SpriteBatch::SpriteBatch(void):
		m_SpriteQueue(),
		m_VertexBuffer(),
		m_UvCoordBuffer(),
		m_WorldMatBuffer(),
		m_Shader()
	{
		m_SpriteQueue.clear();
		
		for(auto vertex : m_VertexBuffer)
		{
			vertex = 0;
		}
		for(auto uv : m_UvCoordBuffer)
		{
			uv = 0;
		}
	}
	
	SpriteBatch::~SpriteBatch(void)
	{
	}

	std::shared_ptr<SpriteBatch> SpriteBatch::GetInstance()
	{
		if(m_pSpriteBatch == nullptr)
		{
			m_pSpriteBatch = std::shared_ptr<SpriteBatch>(new SpriteBatch());
			m_pSpriteBatch->Initialize();
		}
		return m_pSpriteBatch;
	}

	void SpriteBatch::Initialize()
	{
		//Set Shader and shader variables
		#ifdef _WIN32
		Filepath texshaderVertex(_T("WinShaders/"), _T("Texture_Batch_Shader.vert"));
		Filepath texshaderFrag(_T("WinShaders/"), _T("Texture_Batch_Shader.frag"));
#else
		Filepath texshaderVertex(_T("AndroidShaders/"), _T("BaseTexShader.vert"));
		Filepath texshaderFrag(_T("AndroidShaders/"), _T("BaseTexShader.frag"));

#endif
		if(!m_Shader.Init(texshaderVertex.GetFullPath(),texshaderFrag.GetFullPath()))
		{
			Logger::GetInstance()->Log(star::LogLevel::Info, _T("Making Shader Failed"));
		}
	}

	void SpriteBatch::Begin()
	{
	}
	
	void SpriteBatch::End()
	{
		m_SpriteQueue.clear();
	}
	
	void SpriteBatch::Flush()
	{
		Begin();
		FlushSprites();
		End();
	}
	
	void SpriteBatch::FlushSprites()
	{
		m_Shader.Bind();

		//enable vertexAttribs
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		//Create Vertexbuffer
		CreateSpriteQuad();

		//DRAW
		int batchStart = 0;
		int batchSize = 0;
		for(unsigned int i = 0; i<m_SpriteQueue.size(); ++i)
		{
			GLuint currTexture = star::TextureManager::GetInstance()->GetTextureID(m_SpriteQueue[i].spriteName);
			GLuint nextTexture;

			//Are the following sprites from the same texture?
			if(i+1<m_SpriteQueue.size() && i != m_SpriteQueue.size())
			{
				nextTexture = star::TextureManager::GetInstance()->GetTextureID(m_SpriteQueue[i+1].spriteName);
				if(currTexture == nextTexture)
				{
					batchSize+=4;
					continue;
				}
			}
			//if No
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, currTexture);
			GLint s_textureId = glGetUniformLocation(m_Shader.GetId(), "textureSampler");
			glUniform1i(s_textureId, 0);

			//Set attributes and buffers
			glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT,0,0, reinterpret_cast<GLvoid*>(&m_VertexBuffer.front()));
			glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&m_UvCoordBuffer.front()));
			
			batchSize += 4;
	
			auto projectionObject = SceneManager::GetInstance()->GetActiveScene()->GetActiveCamera();
			mat4x4 projection = projectionObject->GetComponent<CameraComponent>()->GetProjection();
			//glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"Projection"),1,GL_FALSE,glm::value_ptr(projection));
			
			//mat4x4 world = m_SpriteQueue[i].transform;
			//mat4x4 worldInverse = InverseMatrix(world);
			for(auto sprite : m_SpriteQueue)
			{
				m_WorldMatBuffer.push_back(InverseMatrix(sprite.transform) * projection);
			}

			for(int j = 0; j < ((batchSize/4)); ++j)
			{
				glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"MVP"), 1, GL_FALSE, glm::value_ptr(m_WorldMatBuffer[j]));
				glDrawArrays(GL_TRIANGLE_STRIP,batchStart,4);
				batchStart += 4;
			}

			m_Shader.Unbind();
	
			batchStart += batchSize;
			batchSize = 0;
		}
		m_WorldMatBuffer.clear();
		m_VertexBuffer.clear();
		m_UvCoordBuffer.clear();
		m_SpriteQueue.clear();

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
	}
	
	void SpriteBatch::CreateSpriteQuad()
	{	
		//for every sprite that has to be drawn, push back all vertices 
		//(12 per sprite) into the vertexbuffer and all uvcoords (8 per
		//sprite) into the uvbuffer

		int32 vertexIndex = 0;
		int32 uvIndex = 0;

		for(auto sprite : m_SpriteQueue)
		{
			for(auto vertex : sprite.vertices)
			{
				m_VertexBuffer.push_back(vertex);
			}

			for(auto uvCoord : sprite.uvCoords)
			{
				m_UvCoordBuffer.push_back(uvCoord);
			}
		}
	}

	void SpriteBatch::AddSpriteToQueue(SpriteComponent* sprite)
	{
		SpriteInfo spriteInfo;
		spriteInfo.filePath = sprite->GetFilePath();
		spriteInfo.spriteName = sprite->GetName();
		spriteInfo.height = sprite->GetHeight();
		spriteInfo.width = sprite->GetWidth();
		spriteInfo.transform = sprite->GetTransform()->GetWorldMatrix();
		spriteInfo.vertices = sprite->GetVertices();
		spriteInfo.uvCoords = sprite->GetUVCoords();

		m_SpriteQueue.push_back(spriteInfo);
	}

	mat4x4 SpriteBatch::InverseMatrix(const mat4x4& matrix)
	{
		float x1, y1, z1, w1,
			  x2, y2, z2, w2,
			  x3, y3, z3, w3,
			  x4, y4, z4, w4;

		x1 = matrix[0][0];
		x2 = matrix[1][0];
		x3 = matrix[2][0];
		x4 = matrix[3][0];

		y1 = matrix[0][1];
		y2 = matrix[1][1];
		y3 = matrix[2][1];
		y4 = matrix[3][1];

		z1 = matrix[0][2];
		z2 = matrix[1][2];
		z3 = matrix[2][2];
		z4 = matrix[3][2];

		w1 = matrix[0][3];
		w2 = matrix[1][3];
		w3 = matrix[2][3];
		w4 = matrix[3][3];

		mat4x4 inverseMatrix
		(
		x1, y1, z1, x4,
		x2, y2, z2, y4,
		x3, y3, z3, z4,
		w1, w2, w3, w4
		);

		return inverseMatrix;
	}
}
