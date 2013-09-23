//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   
#include "RectangleColliderComponent.h"


RectangleColliderComponent::RectangleColliderComponent(int width, int height):
	m_CollisionRect(0,0, width, height),
	m_bIsTrigger(false)
{
	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("RectCollisionComponent initialized"));
}


RectangleColliderComponent::~RectangleColliderComponent(void)
{
}

void RectangleColliderComponent::Initialize()
{}


void RectangleColliderComponent::InitializeComponent()
{
	m_bInitialized = true;
}

void RectangleColliderComponent::Update(const star::Context& context)
{
	if(!m_bInitialized)
	{
		return;
	}

	//[TODO]Start CollisionChecking
	//If m_bIsTrigger == true -> Callbacks
}

void RectangleColliderComponent::Draw()
{
	//Nothing to do
}

