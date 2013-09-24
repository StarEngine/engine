#include "TestScene.h"
#include "AssetManaging/Texture2D.h"

namespace star
{
	TestScene::TestScene(const tstring & Name):
		BaseScene(Name),
		m_TotalFrames(0),
		m_FPS(0),
		m_PassedMiliseconds(0),
		m_pTestObject(nullptr),
		m_pRectComp(nullptr)
	{
		
	}

	status TestScene::Initialize( const Context& contex )
	{
		m_Initialized=true;

		contex.mTextureManager->LoadTexture(_T("assets/TestDaPng.png"),_T("TestPNG"));

		return STATUS_OK;
	}

	status TestScene::Update(const Context& context)
	{
		++m_TotalFrames;
		m_PassedMiliseconds += float(context.mTimeManager->GetMicroSeconds());
		if(m_PassedMiliseconds >= 1000000)
		{
			m_FPS = m_TotalFrames;
			m_TotalFrames = 0;
			m_PassedMiliseconds -= 1000000;

			tstringstream str;
			str << "FPS: " << m_FPS;

			Logger::GetSingleton()->Log(LogLevel::Info, str.str());
		}
		context.mTextureManager->GetTextureID(_T("TestPNG"));

		return STATUS_OK;
	}

	status TestScene::Draw()
	{
		return STATUS_OK;
	}



}
