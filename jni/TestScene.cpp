#include "TestScene.h"

using namespace star;

TestScene::TestScene(tstring Name):	BaseScene(Name),
									m_TotalFrames(0),
									m_PassedMiliseconds(0),
									m_FPS(0)
{

}

status TestScene::Update(Context& context)
{
	++m_TotalFrames;
	m_PassedMiliseconds += context.mTimeManager->GetDeltaTime_Ms();
	if(m_PassedMiliseconds >= 1000)
	{
		m_FPS = m_TotalFrames;
		m_TotalFrames = 0;
		m_PassedMiliseconds -= 1000;

		tstringstream str;
		str << "FPS: " << m_FPS;

		star::Logger::GetSingleton()->Log(star::LogLevel::Info,str.str());
	}

	/*
	double time = context.mTimeManager->GetDeltaTime_uS();
	tstringstream str;
	str << "TestScene DeltaTime in milliseconds: " << time << std::endl;

	star::Logger::GetSingleton()->Log(star::LogLevel::Info,str.str());*/
	return STATUS_OK;
}

status TestScene::Draw()
{
	//star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("TestScene - Going trough Draw"));
	return STATUS_OK;
}
