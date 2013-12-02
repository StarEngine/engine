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

namespace star
{
	SpriteBatch * SpriteBatch::m_pSpriteBatch = nullptr;

	SpriteBatch::SpriteBatch(void):
		m_SpriteQueue(),
		m_TextQueue(),
		m_VertexBuffer(),
		m_UvCoordBuffer(),
		m_IsHUDBuffer(),
		m_TextureSamplerID(0),
		m_ColorID(0),
		m_ScalingID(0),
		m_ViewInverseID(0),
		m_ProjectionID(0),
		m_ShaderPtr(nullptr)
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
#ifdef DESKTOP
		tstring vShader(_T("WinShaders/Texture_Batch_Shader.vert")),
				fShader(_T("WinShaders/Texture_Batch_Shader.frag"));
#else
		tstring vShader(_T("AndroidShaders/BatchTexShader.vert")),
				fShader(_T("AndroidShaders/BatchTexShader.frag"));
#endif
		m_ShaderPtr = new Shader();
		if(!m_ShaderPtr->Init(vShader, fShader))
		{
			Logger::GetInstance()->Log(star::LogLevel::Info, _T("Initialization of Spritebatch Shader has Failed!"));
		}

		m_VertexID = m_ShaderPtr->GetAttribLocation("position");
		m_UVID = m_ShaderPtr->GetAttribLocation("texCoord");
		m_IsHUDID = m_ShaderPtr->GetAttribLocation("isHUD");

		m_TextureSamplerID = m_ShaderPtr->GetUniformLocation("textureSampler");
		m_ColorID = m_ShaderPtr->GetUniformLocation("colorMultiplier");
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

		//Create Vertexbuffer
		CreateSpriteQuads();

		//Set uniforms
		glUniform1i(m_TextureSamplerID, 0);

		float scaleValue = ScaleSystem::GetInstance()->GetScale();
		mat4 scaleMat = Scale(scaleValue, scaleValue, 1.0f);
		glUniformMatrix4fv(m_ScalingID, 1, GL_FALSE, ToPointerValue(scaleMat));

		mat4 viewInverseMat = GraphicsManager::GetInstance()->GetViewInverseMatrix();
		glUniformMatrix4fv(m_ViewInverseID, 1, GL_FALSE, ToPointerValue(viewInverseMat));

		mat4 projectionMat = GraphicsManager::GetInstance()->GetProjectionMatrix();
		glUniformMatrix4fv(m_ProjectionID, 1, GL_FALSE, ToPointerValue(projectionMat));
	}
	
	void SpriteBatch::DrawSprites()
	{			
		uint32 batchStart(0);
		uint32 batchSize(0);
		GLuint texture(0);
		for(auto& currentSprite : m_SpriteQueue)
		{	
			//If != -> Flush
			if(texture != currentSprite.textureID)
			{
				FlushSprites(batchStart, batchSize, texture);

				batchStart += batchSize;
				batchSize = 0;

				texture = currentSprite.textureID;
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
			glVertexAttribPointer(m_VertexID, 3, GL_FLOAT, 0, 0, 
				reinterpret_cast<GLvoid*>(&m_VertexBuffer.at(0)));
			glVertexAttribPointer(m_UVID, 2, GL_FLOAT, 0, 0, 
				reinterpret_cast<GLvoid*>(&m_UvCoordBuffer.at(0)));
			glVertexAttribPointer(m_IsHUDID, 1, GL_FLOAT, 0, 0,
				reinterpret_cast<GLvoid*>(&m_IsHUDBuffer.at(0)));

			//[TODO] Change this, shouldn't be a uniform
			glUniform4f(
				m_ColorID,
				1.f,
				1.f,
				1.f,
				1.f
				);

			glDrawArrays(GL_TRIANGLES, start * 6, size * 6);		
		}
	}
	
	void SpriteBatch::End()
	{
		//Unbind attributes and buffers
		glDisableVertexAttribArray(m_VertexID);
		glDisableVertexAttribArray(m_UVID);
		glDisableVertexAttribArray(m_IsHUDID);
				STARENGINE_LOG_TAG);

		m_ShaderPtr->Unbind();

		m_SpriteQueue.clear();
		m_TextQueue.clear();

		m_VertexBuffer.clear();
		m_UvCoordBuffer.clear();
		m_IsHUDBuffer.clear();
	}

	void SpriteBatch::DrawTextSprites()
	{	
		CreateTextQuads();

		//FlushText once per TextComponent (same font)
		//Check per text how many characters -> Forloop drawing
		for(auto text : m_TextQueue)
		{
			auto curFont = text.font;		
			GLuint* textures = curFont.GetTextures();
			glUniform4f(
				m_ColorID,
				1.f,
				1.f,
				1.f,
				1.f
				);

			int32 line_counter(0);
			int32 offsetX(text.horizontalTextOffset[line_counter]);
			int32 offsetY(0);

			const tchar *start_line = text.text.c_str();
			for(int32 i = 0 ; start_line[i] != 0 ; ++i) 
			{
				if(start_line[i] == _T('\n'))
				{
					offsetY -= curFont.GetMaxLetterHeight() + text.verticalSpacing;
					++line_counter;
					offsetX = text.horizontalTextOffset[line_counter];
				}
				else if(start_line[i] > 31)
				{
					glBindTexture(GL_TEXTURE_2D, textures[start_line[i]]);
					//Set attributes and buffers
					glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT,0,0,
						reinterpret_cast<GLvoid*>(&m_VertexBuffer.at(0)));
					glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, 
						reinterpret_cast<GLvoid*>(&m_UvCoordBuffer.at(0)));		
					glVertexAttribPointer(m_IsHUDID, 1, GL_FLOAT, 0, 0,
						reinterpret_cast<GLvoid*>(&m_IsHUDBuffer.at(0)));
					glDrawArrays(GL_TRIANGLES, i * 6, 6);
				}
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

		for(auto& sprite : m_SpriteQueue)
		{
			//Push back all vertices
			
			mat4 transformMat = Transpose(sprite.transformPtr->GetWorldMatrix());

			//[TODO] Add depth!
			//[TODO] Check if this can be changed :(

			vec4 TL = vec4(0, sprite.vertices.y, 0, 1);
			Mul(TL, transformMat, TL);

			vec4 TR = vec4(sprite.vertices.x, sprite.vertices.y, 0, 1);
			Mul(TR, transformMat, TR);

			vec4 BL = vec4(0, 0, 0, 1);
			Mul(BL, transformMat, BL);

			vec4 BR = vec4(sprite.vertices.x, 0, 0, 1);
			Mul(BR, transformMat, BR);

			//0
			m_VertexBuffer.push_back(TL.x);
			m_VertexBuffer.push_back(TL.y);
			m_VertexBuffer.push_back(TL.z);

			//1
			m_VertexBuffer.push_back(TR.x);
			m_VertexBuffer.push_back(TR.y);
			m_VertexBuffer.push_back(TR.z);

			//2
			m_VertexBuffer.push_back(BL.x);
			m_VertexBuffer.push_back(BL.y);
			m_VertexBuffer.push_back(BL.z);

			//1
			m_VertexBuffer.push_back(TR.x);
			m_VertexBuffer.push_back(TR.y);
			m_VertexBuffer.push_back(TR.z);

			//3
			m_VertexBuffer.push_back(BR.x);
			m_VertexBuffer.push_back(BR.y);
			m_VertexBuffer.push_back(BR.z);

			//2
			m_VertexBuffer.push_back(BL.x);
			m_VertexBuffer.push_back(BL.y);
			m_VertexBuffer.push_back(BL.z);

			//Push back all uv's

			//0
			m_UvCoordBuffer.push_back(sprite.uvCoords.x);
			m_UvCoordBuffer.push_back(sprite.uvCoords.y + sprite.uvCoords.w);

			//1
			m_UvCoordBuffer.push_back(sprite.uvCoords.x + sprite.uvCoords.z);
			m_UvCoordBuffer.push_back(sprite.uvCoords.y + sprite.uvCoords.w);

			//2
			m_UvCoordBuffer.push_back(sprite.uvCoords.x);
			m_UvCoordBuffer.push_back(sprite.uvCoords.y);

			//1
			m_UvCoordBuffer.push_back(sprite.uvCoords.x + sprite.uvCoords.z);
			m_UvCoordBuffer.push_back(sprite.uvCoords.y + sprite.uvCoords.w);

			//3
			m_UvCoordBuffer.push_back(sprite.uvCoords.x + sprite.uvCoords.z);
			m_UvCoordBuffer.push_back(sprite.uvCoords.y);

			//2
			m_UvCoordBuffer.push_back(sprite.uvCoords.x);
			m_UvCoordBuffer.push_back(sprite.uvCoords.y);

			//bool buffer
			for(uint32 i = 0; i < 6; ++i)
			{
				m_IsHUDBuffer.push_back(float32(sprite.bIsHud));
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
		for(auto& text : m_TextQueue)
		{
			//Variables per word
			mat4 transformMat, offsetMatrix; 
			

			int32 offsetX(0);
			int32 offsetY(0);
			for(auto it : text.text)
			{
				//[COMMENT] is this safe?
				auto& charInfo = text.font.GetCharacterInfo(static_cast<suchar>(it));
				int32 offset = text.font.GetMaxLetterHeight() - charInfo.letterDimensions.y;
				offsetMatrix = Translate(vec3(offsetX, offsetY - offset, 0));
				offsetX += charInfo.letterDimensions.x;

				transformMat = Transpose(text.transformPtr->GetWorldMatrix() * offsetMatrix);

				vec4 TL = vec4(0, charInfo.vertexDimensions.y, 0, 1);
				Mul(TL, transformMat, TL);

				vec4 TR = vec4(charInfo.vertexDimensions.x, charInfo.vertexDimensions.y, 0, 1);
				Mul(TR, transformMat, TR);

				vec4 BL = vec4(0, 0, 0, 1);
				Mul(BL, transformMat, BL);

				vec4 BR = vec4(charInfo.vertexDimensions.x, 0, 0, 1);
				Mul(BR, transformMat, BR);

				//0
				m_VertexBuffer.push_back(TL.x);
				m_VertexBuffer.push_back(TL.y);
				m_VertexBuffer.push_back(TL.z);

				//1
				m_VertexBuffer.push_back(TR.x);
				m_VertexBuffer.push_back(TR.y);
				m_VertexBuffer.push_back(TR.z);

				//2
				m_VertexBuffer.push_back(BL.x);
				m_VertexBuffer.push_back(BL.y);
				m_VertexBuffer.push_back(BL.z);

				//1
				m_VertexBuffer.push_back(TR.x);
				m_VertexBuffer.push_back(TR.y);
				m_VertexBuffer.push_back(TR.z);

				//3
				m_VertexBuffer.push_back(BR.x);
				m_VertexBuffer.push_back(BR.y);
				m_VertexBuffer.push_back(BR.z);

				//2
				m_VertexBuffer.push_back(BL.x);
				m_VertexBuffer.push_back(BL.y);
				m_VertexBuffer.push_back(BL.z);

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

				//bool buffer
				for(uint32 i = 0; i < 6; ++i)
				{
					m_IsHUDBuffer.push_back(float32(text.bIsHud));
				}
			}
			//offsetY -= text.font.GetMaxLetterHeight();
			offsetX = 0;
		}
	}

	void SpriteBatch::AddSpriteToQueue(const SpriteInfo& spriteInfo)
	{
		m_SpriteQueue.push_back(spriteInfo);		
	}

	void SpriteBatch::AddTextToQueue(const TextInfo& text)
	{
		m_TextQueue.push_back(text);
	}
}
