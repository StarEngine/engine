//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   
#include "Object.h"
#include "../Components/BaseComponent.h"
#include "../Components/TransformComponent.h"
#include <algorithm>

Object::Object(void):
	m_bIsInitialized(false),
	m_pParentGameObject(nullptr),
	
	m_pComponents(),
	m_pChildren(),
	m_Name(_T("Standard"))
{
	m_pComponents.push_back(new TransformComponent(this));
}


Object::~Object(void)
{
	for(auto comp : m_pComponents)
	{
		delete comp;
		comp = nullptr;
	}
	m_pComponents.clear();

	for(auto child : m_pChildren)
	{
		delete child;
		child = nullptr;
	}
	m_pChildren.clear();
}

void Object::Initialize()
{
	if (m_bIsInitialized)
		return;

	for(auto *comp : m_pComponents)
	{
		if(comp && !comp->IsInitialized())
			comp->Initialize();
	}

	for(auto *child : m_pChildren)
	{
		if(child && !child->m_bIsInitialized)
			child->Initialize();
	}

	m_bIsInitialized = true;
}

void Object::Update(const star::Context& context)
{
	for(auto *component : m_pComponents)
	{
		if(component)
			component->Update(context);
	}

	for(auto *child : m_pChildren)
	{
		if(child)
			child->Update(context);
	}
}

void Object::Draw()
{
	for(auto *component : m_pComponents)
	{
		if(component)
			component->Draw();
	}

	for(auto *child : m_pChildren)
	{
		if(child)
			child->Draw();
	}
}

void Object::AddComponent(BaseComponent *pComponent)
{
	pComponent->SetParent(this);

	if(m_bIsInitialized && ! pComponent->IsInitialized())
		pComponent->Initialize();

	m_pComponents.push_back(pComponent);

	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Component Added"));
}

void Object::RemoveComponent(const BaseComponent* pComponent)
{
	m_pComponents.erase(find(m_pComponents.begin(), m_pComponents.end(), pComponent));
	delete pComponent;

	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Component Removed"));
}

void Object::AddChild(Object *pChild)
{
	pChild->m_pParentGameObject = this;

	if(m_bIsInitialized && ! pChild->m_bIsInitialized)
		pChild->Initialize();

	m_pChildren.push_back(pChild);

	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Child Added"));
}

void Object::RemoveChild(const Object* pObject)
{
	m_pChildren.erase(find(m_pChildren.begin(), m_pChildren.end(), pObject));
	delete pObject;

	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("Child Removed"));
}

