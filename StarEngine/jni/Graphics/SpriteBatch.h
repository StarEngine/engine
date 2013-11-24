#pragma once
#include "../defines.h"
#include "Shader.h"
namespace star
{
	enum SpriteSortMode;
	struct SpriteInfo;

	class Shader;

	class SpriteBatch final
	{
	public:
		~SpriteBatch();
		static SpriteBatch * GetInstance();

		void Begin();
		//[TODO] Make blendstate class. now only alphablending is supported
		//[TODO] Make SamplerState class. now only nearest neighbour is supported
		//[TODO] Make DepthStencilState class. now only the one we set in the graphicsManager is supported
		//[TODO] Make RasterizerState class. now only the default is supported
		//[TODO] Allow to pass a custom material. Now only the default material is supported

		//[TODO] How does monogame pass the positions to the shader?? 
		void Begin(SpriteSortMode spriteSortMode);

		void Draw(const SpriteInfo& spriteInfo);

		void End();

		void Initialize();
		void CleanUp();

	private:
		SpriteBatch();
		void Setup();
		
		static SpriteBatch * m_pSpriteBatch;
		Shader m_Shader;	
		SpriteSortMode m_SpriteSortMode;

		SpriteBatch(const SpriteBatch& yRef);
		SpriteBatch(SpriteBatch&& yRef);
		SpriteBatch& operator=(const SpriteBatch& yRef);
		SpriteBatch& operator=(SpriteBatch&& yRef);
	};
}
