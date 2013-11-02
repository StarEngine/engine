#include "SpriteBatch.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"
#include "../Scenes/SceneManager.h"
#include "GraphicsManager.h"
#include "../Components/CameraComponent.h"
#include "../Objects/FreeCamera.h"
#include "../Scenes/BaseScene.h"
#include <algorithm>
#include "../Helpers/HelpersMath.h"

namespace star
{
	SpriteBatch * SpriteBatch::m_pSpriteBatch = nullptr;

	SpriteBatch::SpriteBatch(void):
		m_SpriteQueue(),
		m_HudSpriteQueue(),
		m_TextBackQueue(),
		m_TextFrontQueue(),
		m_HUDTextQueue(),
		m_VertexBuffer(),
		m_UvCoordBuffer(),
		m_WorldMatBuffer(),
		m_CurrentSprite(0),
		m_CurrentHudSprite(0),
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

	SpriteBatch * SpriteBatch::GetInstance()
	{
		if(m_pSpriteBatch == nullptr)
		{
			m_pSpriteBatch = new SpriteBatch();
			m_pSpriteBatch->Initialize();
		}
		return m_pSpriteBatch;
	}

	void SpriteBatch::Initialize()
	{
		//Set Shader and shader variables
#ifdef DESKTOP
		Filepath texshaderVertex(_T("WinShaders/"), _T("Texture_Batch_Shader.vert"));
		Filepath texshaderFrag(_T("WinShaders/"), _T("Texture_Batch_Shader.frag"));
#else
		Filepath texshaderVertex(_T("AndroidShaders/"), _T("BatchTexShader.vert"));
		Filepath texshaderFrag(_T("AndroidShaders/"), _T("BatchTexShader.frag"));

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
		m_HudSpriteQueue.clear();
		m_TextBackQueue.clear();
		m_TextFrontQueue.clear();
		m_HUDTextQueue.clear();
		m_WorldMatBuffer.clear();
		m_VertexBuffer.clear();
		m_HUDVertexBuffer.clear();
		m_UvCoordBuffer.clear();
		m_HUDUvCoordBuffer.clear();
		m_CurrentSprite = 0;
		m_CurrentHudSprite = 0;
	}
	
	void SpriteBatch::Flush()
	{
		Begin();
		//First background text
		for(auto textDesc : m_TextBackQueue)
		{
			FlushText(textDesc);
		}
		//Sprites
		FlushSprites(m_SpriteQueue);
		//Front text
		for(auto textDesc : m_TextFrontQueue)
		{
			FlushText(textDesc);
		}
		for(auto textDesc : m_HUDTextQueue)
		{
			FlushText(textDesc);
		}
		
		//Clean all variables again
		m_WorldMatBuffer.clear();
		m_VertexBuffer.clear();
		m_UvCoordBuffer.clear();
		m_CurrentSprite = 0;
		m_CurrentHudSprite = 0;

		//HUD
		FlushSprites(m_HudSpriteQueue);

		End();
	}
	
	void SpriteBatch::FlushSprites(std::vector<SpriteInfo> spriteQueue)
	{
		m_Shader.Bind();

		//enable vertexAttribs
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		//Create Vertexbuffer
		CreateSpriteQuad(spriteQueue);

		//DRAW
		int batchStart = 0;
		int batchSize = 0;
		for(unsigned int i = 0; i < spriteQueue.size(); ++i)
		{
			GLuint currTexture = star::TextureManager::GetInstance()->GetTextureID(spriteQueue[i].spriteName);
			GLuint nextTexture;

			//Are the following sprites from the same texture?
			if(i + 1 < spriteQueue.size() && i != spriteQueue.size())
			{
				nextTexture = star::TextureManager::GetInstance()->GetTextureID(spriteQueue[i+1].spriteName);
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

			batchSize += 4;
	
			auto projectionObject = SceneManager::GetInstance()->GetActiveScene()->GetActiveCamera();
			mat4x4 projection = projectionObject->GetComponent<CameraComponent>()->GetProjection();
			mat4x4 viewInverse = projectionObject->GetComponent<CameraComponent>()->GetViewInverse();

			for(int j = 0; j < ((batchSize/4)); ++j)
			{
				//Set attributes and buffers
				glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT,0,0, reinterpret_cast<GLvoid*>(&m_VertexBuffer[12*j]));
				glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, reinterpret_cast<GLvoid*>(&m_UvCoordBuffer[8*j]));
			
				if(spriteQueue[m_CurrentSprite + j].bIsHUD)
				{
					glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"MVP"), 1, GL_FALSE, glm::value_ptr(
						(spriteQueue[m_CurrentSprite + j].transform) * projection));
				}
				else
				{
					glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"MVP"), 1, GL_FALSE, glm::value_ptr(TransposeMatrix(spriteQueue[m_CurrentSprite + j].transform) * projection * viewInverse));
				}
				glDrawArrays(GL_TRIANGLE_STRIP,batchStart,4);
			}			
	
			batchStart += batchSize;
			m_CurrentSprite += batchSize/4;
			batchSize = 0;
		}

		m_Shader.Unbind();

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
	}
	
	void SpriteBatch::FlushText(const TextDesc& textDesc)
	{
		FlushText(textDesc.Text, textDesc.Fontname, textDesc.TransformComp, textDesc.TextColor);
	}

	void SpriteBatch::FlushText(const tstring& text, const tstring& fontname,TransformComponent* transform, Color color)
	{
		if(text == EMPTY_STRING)
		{
			Logger::GetInstance()->Log(LogLevel::Warning,	_T("FontManager::DrawText: Drawing an empty string..."));
			return;
		}
		
		auto curfont = FontManager::GetInstance()->GetFont(fontname);
		float h = curfont.GetSize()/0.63f;
		vec2 position = transform->GetWorldPosition().pos2D();
		vec2 origposition = position;

		std::string conv_text = "";
		conv_text = star::string_cast<std::string>(text);
		std::vector<std::string> lines;
		FontManager::GetInstance()->SplitIntoLines(lines,conv_text);

		GLuint* textures = curfont.GetTextures();
		std::vector<fontUvCoords> tempuvs = curfont.getUvCoords();
		std::vector<fontVertices> tempverts = curfont.getVetrices();
		std::vector<ivec2> tempsizes = curfont.GetLetterDimensions();

		m_Shader.Bind();
		
		//Enable the attributes
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		glActiveTexture(GL_TEXTURE0);
		GLint s_textureId = glGetUniformLocation(m_Shader.GetId(), "textureSampler");
		glUniform1i(s_textureId, 0);
		GLint s_colorId = glGetUniformLocation(m_Shader.GetId(), "colorMultiplier");
		glUniform4f(s_colorId,color.r,color.g,color.b,color.a);
	
		auto projectionObject = star::SceneManager::GetInstance()->GetActiveScene()->GetActiveCamera();
		mat4x4 projection = projectionObject->GetComponent<CameraComponent>()->GetProjection();
		mat4x4 viewInverse = projectionObject->GetComponent<CameraComponent>()->GetViewInverse();
		int offsetX = 0;
		int offsetY = 0;
		for(auto it=lines.begin(); it!=lines.end();++it)
		{
			const char *start_line=it->c_str();
			for(int i=0;start_line[i]!=0;i++) 
			{

				glBindTexture(GL_TEXTURE_2D,textures[ start_line[i] ]);

				//Set attributes and buffers
				glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT,0,0,tempverts[start_line[i]].ver);
				glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, tempuvs[start_line[i]].uv);

				mat4x4 world, offsetTrans;
				
				if(start_line[i] != 0)
				{
					int offset = curfont.GetMaxLetterHeight() - tempsizes[start_line[i]].y;
					offsetTrans = glm::translate(glm::vec3(offsetX, offsetY - curfont.GetMaxLetterHeight() - offset, 0));
					offsetX +=tempsizes[start_line[i]].x;
				}
				else
				{
					offsetTrans = glm::translate(glm::vec3(0, 0, 0));			
				}
				world = transform->GetWorldMatrix() * offsetTrans;

				glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"MVP"),1,GL_FALSE,glm::value_ptr(TransposeMatrix(world) * projection));
				glDrawArrays(GL_TRIANGLE_STRIP,0,4);
			}
			offsetY -= curfont.GetMaxLetterHeight();
			offsetX = 0;
		}	

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
		m_Shader.Unbind();
	}

	void SpriteBatch::CreateSpriteQuad(std::vector<SpriteInfo> spriteQueue)
	{	
		//for every sprite that has to be drawn, push back all vertices 
		//(12 per sprite) into the vertexbuffer and all uvcoords (8 per
		//sprite) into the uvbuffer

		int32 vertexIndex = 0;
		int32 uvIndex = 0;

		for(auto sprite : spriteQueue)
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

	void SpriteBatch::AddSpriteToQueue(SpriteComponent* sprite, bool bIsHud)
	{
		SpriteInfo spriteInfo;
		spriteInfo.filePath = sprite->GetFilePath();
		spriteInfo.spriteName = sprite->GetName();
		spriteInfo.height = sprite->GetHeight();
		spriteInfo.width = sprite->GetWidth();
		spriteInfo.transform = sprite->GetTransform()->GetWorldMatrix();
		spriteInfo.vertices = sprite->GetVertices();
		spriteInfo.uvCoords = sprite->GetUVCoords();
		spriteInfo.bIsHUD = bIsHud;
		
		if(bIsHud)
		{
			m_HudSpriteQueue.push_back(spriteInfo);
		}
		else
		{
			m_SpriteQueue.push_back(spriteInfo);
		}
	}

	void SpriteBatch::AddTextToQueue(const TextDesc& text, bool bInFrontOfSprites)
	{
		if(!bInFrontOfSprites)
		{
			m_TextBackQueue.push_back(text);
		}
		else
		{
			m_TextFrontQueue.push_back(text);
		}
	}

	void SpriteBatch::CleanUp()
	{
		m_Shader.Unbind();

		m_WorldMatBuffer.clear();
		m_VertexBuffer.clear();
		m_UvCoordBuffer.clear();
		m_SpriteQueue.clear();

		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

		delete m_pSpriteBatch;
		m_pSpriteBatch = nullptr;
	}
}
