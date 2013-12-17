#include "SpriteBatch.h"
#include "../Objects/Object.h"
#include "../StarComponents.h"
#include "../Scenes/SceneManager.h"
#include "GraphicsManager.h"
#include "../Components/CameraComponent.h"
#include "../Objects/FreeCamera.h"
#include "../Scenes/BaseScene.h"
#include <algorithm>
#include "../Helpers/Math.h"
#include "ScaleSystem.h"
#include "Font.h"

namespace star
{
	SpriteBatch * SpriteBatch::m_pSpriteBatch = nullptr;

	SpriteBatch::SpriteBatch(void)
		: m_SpriteQueue()
		, m_TextQueue()
		, m_VertexBuffer()
		, m_UvCoordBuffer()
		, m_IsHUDBuffer()
		, m_ColorBuffer()
		, m_TextureSamplerID(0)
		, m_ColorID(0)
		, m_ScalingID(0)
		, m_ViewInverseID(0)
		, m_ProjectionID(0)
		, m_ShaderPtr(nullptr)
		, m_SpriteSortingMode(SpriteSortingMode::BackToFront)
	{

	}
	
	SpriteBatch::~SpriteBatch(void)
	{
		delete m_ShaderPtr;
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
		tstring vShader(_T("Shaders/VertexPosColTexShader.vert")),
				fShader(_T("Shaders/VertexPosColTexShader.frag"));

		m_ShaderPtr = new Shader();
		if(!m_ShaderPtr->Init(vShader, fShader))
		{
			Logger::GetInstance()->
				Log(star::LogLevel::Info, 
				_T("Initialization of Spritebatch Shader has Failed!"), 
				STARENGINE_LOG_TAG);
		}

		m_VertexID = m_ShaderPtr->GetAttribLocation("position");
		m_UVID = m_ShaderPtr->GetAttribLocation("texCoord");
		m_IsHUDID = m_ShaderPtr->GetAttribLocation("isHUD");
		m_ColorID = m_ShaderPtr->GetAttribLocation("colorMultiplier");

		m_TextureSamplerID = m_ShaderPtr->GetUniformLocation("textureSampler");
		m_ScalingID = m_ShaderPtr->GetUniformLocation("scaleMatrix");
		m_ViewInverseID = m_ShaderPtr->GetUniformLocation("viewInverseMatrix");
		m_ProjectionID = m_ShaderPtr->GetUniformLocation("projectionMatrix");
	}

	void SpriteBatch::Flush()
	{
		Begin();
		DrawSprites();

		//Clear vertex, uv, color and isHud buffer
		m_VertexBuffer.clear();
		m_UvCoordBuffer.clear();
		m_IsHUDBuffer.clear();
		m_ColorBuffer.clear();

		DrawTextSprites();

		End();
	}
	
	void SpriteBatch::Begin()
	{
		m_ShaderPtr->Bind();
		
		//[TODO] Test android!
		glEnableVertexAttribArray(m_VertexID);
		glEnableVertexAttribArray(m_UVID);
		glEnableVertexAttribArray(m_IsHUDID);
		glEnableVertexAttribArray(m_ColorID);

		//Create Vertexbuffer
		SortSprites(m_SpriteSortingMode);
		CreateSpriteQuads();
		
		//Set uniforms
		glUniform1i(m_TextureSamplerID, 0);
		float scaleValue = ScaleSystem::GetInstance()->GetScale();
		mat4 scaleMat = Scale(scaleValue, scaleValue, 0);
		glUniformMatrix4fv(m_ScalingID, 1, GL_FALSE, ToPointerValue(scaleMat));

		const mat4& viewInverseMat = GraphicsManager::GetInstance()->GetViewInverseMatrix();
		glUniformMatrix4fv(m_ViewInverseID, 1, GL_FALSE, ToPointerValue(viewInverseMat));

		const mat4& projectionMat = GraphicsManager::GetInstance()->GetProjectionMatrix();
		glUniformMatrix4fv(m_ProjectionID, 1, GL_FALSE, ToPointerValue(projectionMat));
	}
	
	void SpriteBatch::DrawSprites()
	{			
		uint32 batchStart(0);
		uint32 batchSize(0);
		GLuint texture(0);
		for(const SpriteInfo* currentSprite : m_SpriteQueue)
		{	
			//If != -> Flush
			if(texture != currentSprite->textureID)
			{
				FlushSprites(batchStart, batchSize, texture);

				batchStart += batchSize;
				batchSize = 0;

				texture = currentSprite->textureID;
			}
			++batchSize;
		}	
		FlushSprites(batchStart, batchSize, texture);
	}

	void SpriteBatch::FlushSprites(uint32 start, uint32 size, uint32 texture)
	{
		if(size > 0)
		{	
			//[TODO] Check if this can be optimized
			glBindTexture(GL_TEXTURE_2D, texture);
		
			//Set attributes and buffers
			glVertexAttribPointer(m_VertexID, 4, GL_FLOAT, 0, 0, 
				reinterpret_cast<GLvoid*>(&m_VertexBuffer.at(0)));
			glVertexAttribPointer(m_UVID, 2, GL_FLOAT, 0, 0, 
				reinterpret_cast<GLvoid*>(&m_UvCoordBuffer.at(0)));
			glVertexAttribPointer(m_IsHUDID, 1, GL_FLOAT, 0, 0,
				reinterpret_cast<GLvoid*>(&m_IsHUDBuffer.at(0)));
			glVertexAttribPointer(m_ColorID, 4, GL_FLOAT, 0, 0,
				reinterpret_cast<GLvoid*>(&m_ColorBuffer.at(0)));

			glDrawArrays(GL_TRIANGLES, start * 6, size * 6);	
		}
	}
	
	void SpriteBatch::End()
	{
		//Unbind attributes and buffers
		glDisableVertexAttribArray(m_VertexID);
		glDisableVertexAttribArray(m_UVID);
		glDisableVertexAttribArray(m_IsHUDID);
		glDisableVertexAttribArray(m_ColorID);

		m_ShaderPtr->Unbind();

		m_SpriteQueue.clear();
		m_TextQueue.clear();

		m_VertexBuffer.clear();
		m_UvCoordBuffer.clear();
		m_IsHUDBuffer.clear();
		m_ColorBuffer.clear();
	}

	void SpriteBatch::DrawTextSprites()
	{	
		CreateTextQuads();

		//FlushText once per TextComponent (same font)
		//Check per text how many characters -> Forloop drawing
		int32 startIndex(0);
		for(const TextInfo* text : m_TextQueue)
		{
			GLuint* textures = text->font->GetTextures();

			const tchar *start_line = text->text.c_str();
			for(int32 i = 0 ; start_line[i] != 0 ; ++i) 
			{
				if(start_line[i] > FIRST_REAL_ASCII_CHAR)
				{
					glBindTexture(GL_TEXTURE_2D, textures[start_line[i]]);

					//Set attributes and buffers
					glVertexAttribPointer(m_VertexID, 4, GL_FLOAT, 0, 0,
						reinterpret_cast<GLvoid*>(&m_VertexBuffer.at(0)));
					glVertexAttribPointer(m_UVID, 2, GL_FLOAT, 0, 0, 
						reinterpret_cast<GLvoid*>(&m_UvCoordBuffer.at(0)));
					glVertexAttribPointer(m_IsHUDID, 1, GL_FLOAT, 0, 0,
						reinterpret_cast<GLvoid*>(&m_IsHUDBuffer.at(0)));
					glVertexAttribPointer(m_ColorID, 4, GL_FLOAT, 0, 0,
						reinterpret_cast<GLvoid*>(&m_ColorBuffer.at(0)));
					glDrawArrays(GL_TRIANGLES, startIndex * 6, 6);
				}
				++startIndex;
			}
		}
	}

	void SpriteBatch::CreateSpriteQuads()
	{	
		//for every sprite that has to be drawn, push back all vertices 
		//(VERTEX_AMOUNT per sprite) into the vertexbuffer and all uvcoords 
		//(UV_AMOUNT per sprite) into the uvbuffer and the isHUD bool
		/*
		*  TL    TR
		*   0----1 
		*   |   /| 
		*   |  / |
		*   | /  |
		*   |/   |
		*   2----3
		*  BL    BR
		*/

		for(const SpriteInfo* sprite : m_SpriteQueue)
		{
			//Push back all vertices
			
			mat4 transformMat = Transpose(sprite->transformPtr->GetWorldMatrix());

			vec4 TL = vec4(0, sprite->vertices.y, 0, 1);
			Mul(TL, transformMat, TL);

			vec4 TR = vec4(sprite->vertices.x, sprite->vertices.y, 0, 1);
			Mul(TR, transformMat, TR);

			vec4 BL = vec4(0, 0, 0, 1);
			Mul(BL, transformMat, BL);

			vec4 BR = vec4(sprite->vertices.x, 0, 0, 1);
			Mul(BR, transformMat, BR);

			//0
			m_VertexBuffer.push_back(TL);

			//1
			m_VertexBuffer.push_back(TR);

			//2
			m_VertexBuffer.push_back(BL);

			//1
			m_VertexBuffer.push_back(TR);

			//3
			m_VertexBuffer.push_back(BR);

			//2
			m_VertexBuffer.push_back(BL);

			//Push back all uv's

			//0
			m_UvCoordBuffer.push_back(sprite->uvCoords.x);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);

			//1
			m_UvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);

			//2
			m_UvCoordBuffer.push_back(sprite->uvCoords.x);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y);

			//1
			m_UvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y + sprite->uvCoords.w);

			//3
			m_UvCoordBuffer.push_back(sprite->uvCoords.x + sprite->uvCoords.z);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y);

			//2
			m_UvCoordBuffer.push_back(sprite->uvCoords.x);
			m_UvCoordBuffer.push_back(sprite->uvCoords.y);

			//bool & color buffer
			for(uint32 i = 0; i < 6; ++i)
			{
				m_IsHUDBuffer.push_back(float32(sprite->bIsHud));
				//rgba
				m_ColorBuffer.push_back(sprite->colorMultiplier);
			}
		}
	}

	void SpriteBatch::CreateTextQuads()
	{
		//for every sprite that has to be drawn, push back all vertices 
		//(VERTEX_AMOUNT per sprite) into the vertexbuffer and all uvcoords 
		//(UV_AMOUNT per sprite) into the uvbuffer and the isHUD bool
		/*
		*  TL    TR
		*   0----1 
		*   |   /| 
		*   |  / |
		*   | /  |
		*   |/   |
		*   2----3
		*  BL    BR
		*/
		for(const TextInfo* text : m_TextQueue)
		{
			//Variables per textcomponent
			mat4 transformMat, offsetMatrix; 
			const mat4& worldMat = text->transformPtr->GetWorldMatrix();
			int32 line_counter(0);
			int32 offsetX(text->horizontalTextOffset.at(line_counter));
			int32 offsetY(0);
			int32 fontHeight(text->font->GetMaxLetterHeight() + text->font->GetMinLetterHeight());
			for(auto it : text->text)
			{
				const CharacterInfo& charInfo = text->font->GetCharacterInfo(static_cast<suchar>(it));
				offsetMatrix = Translate
					(vec3(
						offsetX, 
						offsetY + charInfo.letterDimensions.y + text->textHeight - fontHeight, 
						0));
				offsetX += charInfo.letterDimensions.x;

				transformMat = Transpose(worldMat * offsetMatrix);

				vec4 TL = vec4(0, charInfo.vertexDimensions.y, 0, 1);
				Mul(TL, transformMat, TL);

				vec4 TR = vec4(charInfo.vertexDimensions.x, charInfo.vertexDimensions.y, 0, 1);
				Mul(TR, transformMat, TR);

				vec4 BL = vec4(0, 0, 0, 1);
				Mul(BL, transformMat, BL);

				vec4 BR = vec4(charInfo.vertexDimensions.x, 0, 0, 1);
				Mul(BR, transformMat, BR);

				//0
				m_VertexBuffer.push_back(TL);

				//1
				m_VertexBuffer.push_back(TR);

				//2
				m_VertexBuffer.push_back(BL);

				//1
				m_VertexBuffer.push_back(TR);

				//3
				m_VertexBuffer.push_back(BR);

				//2
				m_VertexBuffer.push_back(BL);

				//Push back all uv's

				//0
				m_UvCoordBuffer.push_back(0);
				m_UvCoordBuffer.push_back(0);

				//1
				m_UvCoordBuffer.push_back(charInfo.uvDimensions.x);
				m_UvCoordBuffer.push_back(0);

				//2
				m_UvCoordBuffer.push_back(0);
				m_UvCoordBuffer.push_back(charInfo.uvDimensions.y);

				//1
				m_UvCoordBuffer.push_back(charInfo.uvDimensions.x);
				m_UvCoordBuffer.push_back(0);

				//3
				m_UvCoordBuffer.push_back(charInfo.uvDimensions.x);
				m_UvCoordBuffer.push_back(charInfo.uvDimensions.y);

				//2
				m_UvCoordBuffer.push_back(0);
				m_UvCoordBuffer.push_back(charInfo.uvDimensions.y);

				//bool & color buffer
				for(uint32 i = 0; i < 6; ++i)
				{
					m_IsHUDBuffer.push_back(float32(text->bIsHud));
					//rgba
					m_ColorBuffer.push_back(text->colorMultiplier);
				}

				if(it == _T('\n'))
				{
					offsetY -= text->font->GetMaxLetterHeight() + text->verticalSpacing;
					++line_counter;
					offsetX = text->horizontalTextOffset.at(line_counter);
				}
			}
		}
	}

	void SpriteBatch::SortSprites(SpriteSortingMode mode)
	{
		switch(mode)
		{
		case SpriteSortingMode::BackToFront:
			std::sort(m_SpriteQueue.begin(), m_SpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
			{
				return a->transformPtr->GetWorldPosition().l < b->transformPtr->GetWorldPosition().l;
			});
			break;
		case SpriteSortingMode::FrontToBack:
			std::sort(m_SpriteQueue.begin(), m_SpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
			{
				return a->transformPtr->GetWorldPosition().l > b->transformPtr->GetWorldPosition().l;
			});
			break;
		case SpriteSortingMode::TextureID:
			std::sort(m_SpriteQueue.begin(), m_SpriteQueue.end(), [](const SpriteInfo* a, const SpriteInfo* b) -> bool
			{
				return a->textureID < b->textureID;
			});
			break;
		default:
			Logger::GetInstance()->Log(false, _T("SpriteBatch::SortSprites: Please implement this SpriteSortingMode"));
			break;
		}
	}

	void SpriteBatch::AddSpriteToQueue(const SpriteInfo* spriteInfo)
	{
		m_SpriteQueue.push_back(spriteInfo);		
	}

	void SpriteBatch::AddTextToQueue(const TextInfo* text)
	{
		m_TextQueue.push_back(text);
	}

	void SpriteBatch::SetSpriteSortingMode(SpriteSortingMode mode)
	{
		m_SpriteSortingMode = mode;
	}
}
