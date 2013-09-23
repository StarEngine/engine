//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   

#include "TransformComponent.h"
#include "..\SceneGraph\Object.h"

TransformComponent::TransformComponent(void):
	m_IsChanged(TransformChanged::NONE),
	m_Invalidate(false),

	m_WorldPosition(vec3(0,0,0)),
	m_LocalPosition(vec3(0,0,0)),
	m_WorldRotation(),
	m_LocalRotation(),
	m_WorldScale(vec3(1,1,1)),
	m_LocalScale(vec3(1,1,1)),
	m_World()
{
	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("TransformComponent Added"));
}

TransformComponent::TransformComponent(Object* parent) :
	m_IsChanged(TransformChanged::NONE),
	m_Invalidate(false),

	m_WorldPosition(vec3(0,0,0)),
	m_LocalPosition(vec3(0,0,0)),
	m_WorldRotation(),
	m_LocalRotation(),
	m_WorldScale(vec3(1,1,1)),
	m_LocalScale(vec3(1,1,1)),
	m_World()
{
	m_pParentObject = parent;
	star::Logger::GetSingleton()->Log(star::LogLevel::Info,_T("TransformComponent Added"));
}

TransformComponent::~TransformComponent(void)
{
}

void TransformComponent::Translate(vec3 translation)
{
	m_LocalPosition = translation;
	m_IsChanged |= TransformChanged::TRANSLATION;
}

void TransformComponent::Translate(float x, float y, float z)
{
	Translate(vec3(x,y,z));
}

void TransformComponent::Rotate(quat rotation)
{
	m_LocalRotation = rotation;
	m_IsChanged |= TransformChanged::ROTATION;
}

void TransformComponent::Scale(vec3 scale)
{
	m_LocalScale = scale;
	m_IsChanged |= TransformChanged::SCALE;
}

void TransformComponent::Scale(float x, float y, float z)
{
	Scale(vec3(x,y,z));
}

void TransformComponent::CheckForUpdate(bool force)
{
	if(m_IsChanged == TransformChanged::NONE && !force && !m_Invalidate)
	{
		return;
	}

	if(m_pParentObject==nullptr)
	{
		return;
	}

	if(m_IsChanged != TransformChanged::NONE || force || m_Invalidate)
	{
		mat4x4 matRot, matTrans, matScale;

		matTrans = translate(m_LocalPosition);
		matRot   = toMat4(m_LocalRotation);
		matScale = scale(m_LocalScale);

		m_World = matScale * matRot * matTrans;

		auto parentGameObj = m_pParentObject->GetParent();

		if(parentGameObj == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
			m_WorldScale = m_LocalScale;
			m_WorldRotation = m_LocalRotation;
		}
		else
		{
			m_World =  m_World * parentGameObj->GetComponent<TransformComponent>()->GetWorldMatrix();
			m_WorldPosition;
			m_WorldRotation = quat(m_World);
			m_WorldScale;
		}


		m_IsChanged = TransformChanged::NONE;
	}

	m_Invalidate = false;
}

void TransformComponent::Update(const star::Context& context)
{
	CheckForUpdate(true);
}

void TransformComponent::InitializeComponent()
{
	m_Invalidate = true;
}
