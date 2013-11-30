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
		void AddSpriteToQueue(
			const SpriteInfo& spriteInfo,
			bool bIsHud
			);
		void AddTextToQueue(const TextDesc& text, bool bInFrontOfSprites);
		void CleanUp();

	private:
		SpriteBatch(void);
		void Begin();
		void End();
		void CreateSpriteQuad(const std::vector<SpriteInfo>& spriteQueue);
		void FlushSprites(const std::vector<SpriteInfo>& spriteQueue);
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
		static const int32 BATCHSIZE = 50;

		std::vector<SpriteInfo> m_SpriteQueue,
								m_HudSpriteQueue;
		std::vector<TextDesc> m_TextBackQueue,
							  m_TextFrontQueue,
							  m_HUDTextQueue;
		std::vector<GLfloat> m_VertexBuffer,
							 m_HUDVertexBuffer;
		std::vector<GLfloat> m_UvCoordBuffer,
							 m_HUDUvCoordBuffer;
		std::vector<mat4> m_WorldMatBuffer;
		int32 m_CurrentSprite,
			m_CurrentHudSprite;
		Shader m_Shader;	

		SpriteBatch(const SpriteBatch& yRef);
		SpriteBatch(SpriteBatch&& yRef);
		SpriteBatch& operator=(const SpriteBatch& yRef);
		SpriteBatch& operator=(SpriteBatch&& yRef);
	};
}
