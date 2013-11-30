#pragma once
#include <vector>
#include "../defines.h"
#include <memory>
#include "Shader.h"
#include "../Components/Graphics/SpriteComponent.h"
#include "../Assets/FontManager.h"

namespace star
{
	class SpriteBatch final
	{
	public:
		~SpriteBatch(void);
		static SpriteBatch * GetInstance();

		void Initialize();
		void Flush();
		void AddSpriteToQueue(const SpriteInfo& spriteInfo);
		void AddTextToQueue(const TextDesc& text, bool bInFrontOfSprites);

	private:
		SpriteBatch(void);
		void Begin();
		void End();
		void CreateSpriteQuads();
		void DrawSprites();
		void FlushSprites(uint32 start, uint32 size, uint32 texture);
		void FlushText(const TextDesc& textDesc);
		void FlushText(
			const tstring & text,
			const tstring& fontname,
			int32 spacing,
			const std::vector<int32> & horOffset,
			TransformComponent* transform,
			const Color& color,
			bool isHUD
			);

		static SpriteBatch * m_pSpriteBatch;
		static const uint32 BATCHSIZE = 50;
		static const uint32 VERTEX_AMOUNT = 18;
		static const uint32 UV_AMOUNT = 12;

		//[COMMENT] Sadly can't change that to const SpriteInfo&
		std::vector<SpriteInfo> m_SpriteQueue;
		//[TODO] Change
		std::vector<TextDesc> m_TextBackQueue,
							  m_TextFrontQueue,
							  m_HUDTextQueue;

		//[TODO] Check if can be changed to vector<vec4 or vec2>
		std::vector<float32> m_VertexBuffer,
							 m_UvCoordBuffer;

		GLuint	m_TextureSamplerID,
				m_ColorID;

		Shader* m_ShaderPtr;	

		SpriteBatch(const SpriteBatch& yRef);
		SpriteBatch(SpriteBatch&& yRef);
		SpriteBatch& operator=(const SpriteBatch& yRef);
		SpriteBatch& operator=(SpriteBatch&& yRef);
	};
}
