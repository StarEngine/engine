#include "TestScene.h"

using namespace star;

TestScene::TestScene(tstring Name):BaseScene(Name)
{

}

status TestScene::Update(Context& context)
{
	double time = context.mTimeManager->GetDeltaTime_uS();
	tstringstream str;
	str << "TestScene DeltaTime in milliseconds: " << time << std::endl;

	star::Logger::GetSingleton()->Log(star::LogLevel::Info,str.str());
	return STATUS_OK;
}

status TestScene::Draw()
{
	//star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("TestScene - Going trough Draw"));
	return STATUS_OK;
}
