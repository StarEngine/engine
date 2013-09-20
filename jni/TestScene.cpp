#include "TestScene.h"

using namespace star;

TestScene::TestScene(tstring Name):BaseScene(Name)
{

}

status TestScene::Update()
{
	//star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("TestScene - Going trough Update"));
	return STATUS_OK;
}

status TestScene::Draw()
{
	//star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("TestScene - Going trough Draw"));
	return STATUS_OK;
}
