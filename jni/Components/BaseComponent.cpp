//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   
#include "BaseComponent.h"

BaseComponent::BaseComponent():
	m_pParentObject(nullptr),
	m_bInitialized(false)
{
}


BaseComponent::~BaseComponent(void)
{
}

void BaseComponent::Initialize()
{
	if(m_bInitialized)
		return;

	InitializeComponent();
	m_bInitialized = true;
}
