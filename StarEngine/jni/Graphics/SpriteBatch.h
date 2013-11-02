#pragma once
#include <vector>
#include "../defines.h"
#include <memory>
#include "Shader.h"
#include "../Components/Graphics/SpriteComponent.h"
#include "../Assets/FontManager.h"

namespace star
{
	struct SpriteInfo
	{
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> uvCoords;
		tstring filePath, spriteName;
		int32 width, height;
		mat4x4 transform;
		bool bIsHUD;
	};

	class SpriteBatch
	{
	public:
		~SpriteBatch(void);
		static SpriteBatch * GetInstance();

		void Initialize();
		void Flush();
		void AddSpriteToQueue(SpriteComponent* sprite, bool bIsHud = false);
		void AddTextToQueue(const TextDesc& text, bool bInFrontOfSprites);
		void CleanUp();

	private:
		SpriteBatch(void);
		void Begin();
		void End();
		void CreateSpriteQuad(std::vector<SpriteInfo> spriteQueue);
		void FlushSprites(std::vector<SpriteInfo> spriteQueue);
		void FlushText(const TextDesc& textDesc);
		void FlushText(const tstring& text, const tstring& fontname,TransformComponent* transform, Color color);

		static SpriteBatch * m_pSpriteBatch;
		static const int BATCHSIZE = 50;

		std::vector<SpriteInfo> m_SpriteQueue,
								m_HudSpriteQueue;
		std::vector<TextDesc> m_TextBackQueue,
							  m_TextFrontQueue,
							  m_HUDTextQueue;
		std::vector<GLfloat> m_VertexBuffer,
							 m_HUDVertexBuffer;
		std::vector<GLfloat> m_UvCoordBuffer,
							 m_HUDUvCoordBuffer;
		std::vector<mat4x4> m_WorldMatBuffer;
		int m_CurrentSprite,
			m_CurrentHudSprite;
		Shader m_Shader;	

		//disabling default copy constructor
		SpriteBatch(const SpriteBatch& yRef);
		SpriteBatch(SpriteBatch&& yRef);
		SpriteBatch& operator=(const SpriteBatch& yRef);
		SpriteBatch& operator=(SpriteBatch&& yRef);
	};
}
