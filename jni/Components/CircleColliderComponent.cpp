//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   
#include "CircleColliderComponent.h"


CircleColliderComponent::CircleColliderComponent(float radius):
	m_Radius(radius),
	m_bIsTrigger(false)
{
}


CircleColliderComponent::~CircleColliderComponent(void)
{
}

void CircleColliderComponent::Initialize()
{}

void CircleColliderComponent::InitializeComponent()
{
	//Assert(m_Radius > 0, _T("Negative Radius"));
	m_bInitialized = true;
}

void CircleColliderComponent::Update(const star::Context& context)
{
	if(!m_bInitialized)
		return;

	//[TODO]Start CollisionChecking
	//If m_bIsTrigger == true -> Callbacks
}

void CircleColliderComponent::Draw()
{
	//Nothing to do
}

