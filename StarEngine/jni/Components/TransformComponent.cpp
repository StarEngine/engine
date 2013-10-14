#include "TransformComponent.h"
#include "..\SceneGraph\Object.h"
#include "..\Logger.h"
#include "..\Context.h"
#include "..\Helpers\HelpersMath.h"

namespace star
{
	TransformComponent::TransformComponent(void):
		m_IsChanged(TransformChanged::NONE),
		m_Invalidate(false),
#ifdef STAR2D
		m_WorldPosition(0,0),
		m_LocalPosition(0,0),
#else
		m_WorldPosition(0,0,0),
		m_LocalPosition(0,0,0),
#endif
		m_WorldRotation(),
		m_LocalRotation(),
#ifdef STAR2D
		m_WorldScale(1,1),
		m_LocalScale(1,1),
#else
		m_WorldScale(1,1,1),
		m_LocalScale(1,1,1),
#endif
		m_World(),
		BaseComponent()
	{

	}

	TransformComponent::TransformComponent(star::Object* parent):
		m_IsChanged(TransformChanged::NONE),
		m_Invalidate(false),
#ifdef STAR2D
		m_WorldPosition(0,0),
		m_LocalPosition(0,0),
#else
		m_WorldPosition(0,0,0),
		m_LocalPosition(0,0,0),
#endif
		m_WorldRotation(),
		m_LocalRotation(),
#ifdef STAR2D
		m_WorldScale(1,1),
		m_LocalScale(1,1),
#else
		m_WorldScale(1,1,1),
		m_LocalScale(1,1,1),
#endif
		m_World()
	{
		m_pParentObject = parent;
	}

	TransformComponent::~TransformComponent(void)
	{
	}

#ifdef STAR2D
	void TransformComponent::Translate(const vec2 & translation)
	{
		m_LocalPosition = translation;
		m_IsChanged |= TransformChanged::TRANSLATION;
	}

	void TransformComponent::Translate(float x, float y)
	{
		Translate(vec2(x, y));
	}

	void TransformComponent::Rotate(float rotation)
	{
		m_LocalRotation = rotation;
		m_IsChanged |= TransformChanged::ROTATION;
	}

	void TransformComponent::Scale(const vec2 & scale)
	{
		m_LocalScale = scale;
		m_IsChanged |= TransformChanged::SCALE;
	}

	void TransformComponent::Scale(float x, float y)
	{
		Scale(vec2(x, y));
	}

	const vec2 & TransformComponent::GetWorldPosition()
	{
		CheckForUpdate();
		return m_WorldPosition;
	}

	const vec2 & TransformComponent::GetLocalPosition() const
	{
		return m_LocalPosition;
	}

	float TransformComponent::GetWorldRotation()
	{
		CheckForUpdate();
		return m_WorldRotation;
	}

	//[TODO] Fix this to const correct (teach cedric)
	float TransformComponent::GetLocalRotation() const
	{
		return m_LocalRotation;
	}

	const vec2 & TransformComponent::GetWorldScale()
	{
		CheckForUpdate();
		return m_WorldScale;
	}

	const vec2 & TransformComponent::GetLocalScale() const
	{
		return m_LocalScale;
	}
#else
	void TransformComponent::Translate(const vec3 & translation)
	{
		m_LocalPosition = translation;
		m_IsChanged |= TransformChanged::TRANSLATION;
	}

	void TransformComponent::Translate(float x, float y, float z)
	{
		Translate(vec3(x,y,z));
	}

	void TransformComponent::Rotate(const quat & rotation)
	{
		m_LocalRotation = rotation;
		m_IsChanged |= TransformChanged::ROTATION;
	}

	void TransformComponent::Scale(const vec3 & scale)
	{
		m_LocalScale = scale;
		m_IsChanged |= TransformChanged::SCALE;
	}

	void TransformComponent::Scale(float x, float y, float z)
	{
		Scale(vec3(x,y,z));
	}

	const vec3 & TransformComponent::GetWorldPosition()
	{
		CheckForUpdate();
		return m_WorldPosition;
	}

	const vec3 & TransformComponent::GetLocalPosition() const
	{
		return m_LocalPosition;
	}

	const quat & TransformComponent::GetWorldRotation()
	{
		CheckForUpdate();
		return m_WorldRotation;
	}

	const quat & TransformComponent::GetLocalRotation() const
	{
		return m_LocalRotation;
	}

	const vec3 & TransformComponent::GetWorldScale()
	{
		CheckForUpdate();
		return m_WorldScale;
	}

	const vec3 & TransformComponent::GetLocalScale() const
	{
		return m_LocalScale;
	}
#endif

	mat4x4 TransformComponent::GetWorldMatrix()
	{
		CheckForUpdate();
		return m_World;
	}

	void TransformComponent::CheckForUpdate(bool force)
	{
		if(m_IsChanged == TransformChanged::NONE && !force && !m_Invalidate)
		{
			return;
		}

		if(m_pParentObject == nullptr)
		{
			return;
		}

		mat4x4 matRot, matTrans, matScale;

#ifdef STAR2D
		matTrans = glm::translate(vec3(m_LocalPosition.x, m_LocalPosition.y, 0));
		float rotDegrees = RadiansToDegrees(m_LocalRotation);
		matRot   = glm::toMat4(quat(vec3(0,0,m_LocalRotation)));
		matScale = glm::scale(vec3(m_LocalScale.x,m_LocalScale.y,0));
#else
		matTrans = glm::translate(m_LocalPosition);
		matRot   = glm::toMat4(m_LocalRotation);
		matScale = glm::scale(m_LocalScale);
#endif

		m_World = matTrans * matRot * matScale;

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
		}

		m_IsChanged = TransformChanged::NONE;

		m_Invalidate = false;
	}

	void TransformComponent::Update(const Context& context)
	{
		CheckForUpdate(true);
	}

	void TransformComponent::InitializeComponent()
	{
		m_Invalidate = true;
	}
}
