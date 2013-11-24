#include "SpriteBatch.h"
#include "SpriteSortMode.h"
#include "SpriteInfo.h"
#include "../Logger.h"

namespace star
{
	SpriteBatch * SpriteBatch::m_pSpriteBatch = nullptr;

	SpriteBatch::SpriteBatch()
		: m_Shader()
		, m_SpriteSortMode()
	{
		
	}
	
	SpriteBatch::~SpriteBatch()
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
		tstring vShader(_T("WinShaders/Texture_Batch_Shader.vert")),
				fShader(_T("WinShaders/Texture_Batch_Shader.frag"));
#else
		tstring vShader(_T("AndroidShaders/BatchTexShader.vert")),
				fShader(_T("AndroidShaders/BatchTexShader.frag"));
#endif
		if(!m_Shader.Init(vShader, fShader))
		{
			Logger::GetInstance()->Log(star::LogLevel::Info, 
				_T("Initialization of Spritebatch Shader has Failed!"));
		}
	}

	void SpriteBatch::Begin()
	{
		Begin(SpriteSortMode::BackToFront);
	}

	void SpriteBatch::Begin(SpriteSortMode spriteSortMode)
	{
		m_SpriteSortMode = spriteSortMode;
		if(m_SpriteSortMode == SpriteSortMode::Immediate)
		{
			Setup();
		}
	}

	void SpriteBatch::Setup()
	{
		//[TODO] Pass the viewProjection matrix to the shader.
	}

	void SpriteBatch::Draw(const SpriteInfo& spriteInfo)
	{
		//[TODO]
		//Create a new batch item (spriteBatcher->CreateBatchItem())
		//Set the depth and texture to the item 
		//Set all other values
		if(m_SpriteSortMode == SpriteSortMode::Immediate)
		{
			//Batcher->DrawBatch();
		}
	}
	
	void SpriteBatch::End()
	{
		if(m_SpriteSortMode != SpriteSortMode::Immediate)
		{
			Setup();
			//Batcher->DrawBatch();
		}
	}
	
	void SpriteBatch::CleanUp()
	{
		m_Shader.Unbind();


		//Unbind attributes and buffers
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_UV);

		delete m_pSpriteBatch;
		m_pSpriteBatch = nullptr;
	}
}
