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
	m_Width(width),
	m_Height(height),
	m_bIsTrigger(false)
{
}


RectangleColliderComponent::~RectangleColliderComponent(void)
{
}

void RectangleColliderComponent::InitializeComponent()
{
	Assert(m_Width > 0, _T("Negative Width"));
	Assert(m_Height> 0, _T("Negative Height"));

	m_bInitialized = true;
}

void RectangleColliderComponent::Update(float deltaTime)
{
	if(!m_bInitialized)
		return;

	//[TODO]Start CollisionChecking
	//If m_bIsTrigger == true -> Callbacks
}

void RectangleColliderComponent::Draw()
{
	//Nothing to do
}

