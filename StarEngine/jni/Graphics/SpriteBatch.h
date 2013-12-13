#pragma once
#include <vector>
#include "../defines.h"
#include <memory>
#include "Shader.h"
#include "../Components/Graphics/SpriteComponent.h"
#include "../Components/Graphics/TextComponent.h"

namespace star
{
	class SpriteBatch final
	{
	public:
		enum SpriteSortingMode
		{
			BackToFront,
			FrontToBack,
			TextureID
		};

		~SpriteBatch();
		static SpriteBatch * GetInstance();

		void Initialize();
		void Flush();
		void AddSpriteToQueue(const SpriteInfo* spriteInfo);
		void AddTextToQueue(const TextInfo* text);

		void SetSpriteSortingMode(SpriteSortingMode mode);

	private:
		SpriteBatch();
		void Begin();
		void End();
		void CreateSpriteQuads();
		void CreateTextQuads();
		void SortSprites(SpriteSortingMode mode);
		void DrawSprites();
		void FlushSprites(uint32 start, uint32 size, uint32 texture);
		void DrawTextSprites();

		static SpriteBatch * m_pSpriteBatch;
		static const uint32 BATCHSIZE = 50;
		static const uint32 VERTEX_AMOUNT = 18;
		static const uint32 UV_AMOUNT = 12;
		static const uint32 FIRST_REAL_ASCII_CHAR = 31;

		std::vector<const SpriteInfo*> m_SpriteQueue;
		std::vector<const TextInfo*> m_TextQueue;

		//[TODO] Check if can be changed to vector<vec4 or vec2>
		std::vector<vec4> m_VertexBuffer;
		std::vector<float32> m_UvCoordBuffer;
		std::vector<float32> m_IsHUDBuffer;
		std::vector<Color> m_ColorBuffer;
		
		GLuint m_VertexID,
			   m_UVID,
			   m_IsHUDID;

		GLuint	m_TextureSamplerID,
				m_ColorID,
				m_ScalingID,
				m_ViewInverseID,
				m_ProjectionID;

		Shader* m_ShaderPtr;	

		SpriteSortingMode m_SpriteSortingMode;

		SpriteBatch(const SpriteBatch& yRef);
		SpriteBatch(SpriteBatch&& yRef);
		SpriteBatch& operator=(const SpriteBatch& yRef);
		SpriteBatch& operator=(SpriteBatch&& yRef);
	};
}
