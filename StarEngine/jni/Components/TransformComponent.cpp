#include "TransformComponent.h"
#include "..\Objects\Object.h"
#include "..\Logger.h"
#include "..\Context.h"
#include "..\Helpers\HelpersMath.h"
#include "..\Graphics\ScaleSystem.h"
#include "..\Graphics\GraphicsManager.h"

namespace star
{
        TransformComponent::TransformComponent(star::Object* parent):
				m_IsChanged(TransformChanged::ROTATION |
					TransformChanged::SCALE |
					TransformChanged::TRANSLATION),
                m_Invalidate(false),
				m_bRotationCenterChanged(false),
				m_bRotationIsLocal(false),
#ifdef STAR2D
                m_WorldPosition(0,0),
                m_LocalPosition(0,0),
				m_CenterPosition(0,0),
				m_UnScaledLocalPos(0,0),
				m_UnScaledWorldPos(0,0),
#else
                m_WorldPosition(0,0,0),
                m_LocalPosition(0,0,0),
				m_UnScaledLocalPos(0,0,0),
				m_UnScaledWorldPos(0,0,0),
#endif
                m_WorldRotation(0),
                m_LocalRotation(0),
#ifdef STAR2D
                m_WorldScale(1,1),
                m_LocalScale(1,1),
				m_UnScaledLocalScale(1,1),
				m_UnScaledWorldScale(1,1),
#else
                m_WorldScale(1,1,1),
                m_LocalScale(1,1,1),
				m_UnScaledLocalScale(1,1,1),
				m_UnScaledWorldScale(1,1,1),

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
                m_UnScaledLocalPos.x = translation.x;
                m_UnScaledLocalPos.y = translation.y;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

        void TransformComponent::Translate(float x, float y)
        {
                Translate(vec2(x, y));
        }

        void TransformComponent::Translate(const vec2 & translation, lay l)
        {
                m_UnScaledLocalPos.x = translation.x;
                m_UnScaledLocalPos.y = translation.y;
                m_UnScaledLocalPos.l = l;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

        void TransformComponent::Translate(float x, float y, lay l)
        {
                Translate(vec2(x, y), l);
        }

        void TransformComponent::Translate(const pos & pos2D)
        {
                m_UnScaledLocalPos = pos2D;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

		void TransformComponent::TranslateX(float x)
		{
			m_UnScaledLocalPos.x = x;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::TranslateY(float y)
		{
			m_UnScaledLocalPos.y = y;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::TranslateL(lay l)
		{
			m_UnScaledLocalPos.l = l;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::Move(const vec2& translation)
		{
			m_UnScaledLocalPos.x += translation.x;
			m_UnScaledLocalPos.y += translation.y;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::Move(float x, float y)
		{
			m_UnScaledLocalPos.x += x;
			m_UnScaledLocalPos.y += y;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::MoveX(float x)
		{
			m_UnScaledLocalPos.x += x;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::MoveY(float y)
		{
			m_UnScaledLocalPos.y += y;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::Rotate(float rotation)
        {
			m_bRotationCenterChanged = false;
			m_bRotationIsLocal = false;
            m_LocalRotation = rotation;
            m_IsChanged |= TransformChanged::ROTATION;
        }

		void TransformComponent::Rotate(float rotation, const pos& centerPoint)
		{
			m_bRotationCenterChanged = true;
			m_bRotationIsLocal = false;
			m_LocalRotation = rotation;
			m_CenterPosition = centerPoint;
			m_IsChanged |= TransformChanged::ROTATION;
		}

		void TransformComponent::RotateLocal(float rotation)
		{
			Rotate(rotation);
			m_bRotationIsLocal = m_pParentObject->GetParent() != nullptr;
		}

		void TransformComponent::RotateLocal(float rotation, const pos& centerPoint)
		{
			Rotate(rotation, centerPoint);
			m_bRotationIsLocal = m_pParentObject->GetParent() != nullptr;
		}

        void TransformComponent::Scale(const vec2 & scale)
        {
                m_UnScaledLocalScale = scale;
                m_IsChanged |= TransformChanged::SCALE;
        }

        void TransformComponent::Scale(float x, float y)
        {
                Scale(vec2(x, y));
        }

        void TransformComponent::Scale(float u)
        {
                Scale(vec2(u, u));
        }

		void TransformComponent::ScaleX(float x)
		{
			m_UnScaledLocalScale.x = x;
            m_IsChanged |= TransformChanged::SCALE;
		}

		void TransformComponent::ScaleY(float y)
		{
			m_UnScaledLocalScale.y = y;
            m_IsChanged |= TransformChanged::SCALE;
		}

        const pos & TransformComponent::GetWorldPosition()
        {
            return m_UnScaledWorldPos;
        }

        const pos & TransformComponent::GetLocalPosition()
        {
                return m_UnScaledLocalPos;
        }

		const pos & TransformComponent::GetScaledWorldPosition()
		{
			return m_WorldPosition;
		}

        float TransformComponent::GetWorldRotation()
        {
                return m_WorldRotation;
        }

        //[TODO] Fix this to const correct (teach cedric)
        float TransformComponent::GetLocalRotation() const
        {
                return m_LocalRotation;
        }

        const vec2 & TransformComponent::GetWorldScale()
        {
                return m_UnScaledWorldScale;
        }

        const vec2 & TransformComponent::GetLocalScale()
        {
                return m_UnScaledLocalScale;
        }

		const vec2 & TransformComponent::GetScaledWorldScale()
		{
			return m_WorldScale;
		}
#else
        void TransformComponent::Translate(const vec3 & translation)
        {
                m_UnScaledLocalPos = translation;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

        void TransformComponent::Translate(float x, float y, float z)
        {
                Translate(vec3(x,y,z));
        }

        void TransformComponent::TranslateXY(float x, float y)
		{
			m_UnScaledLocalPos.x = x;
			m_UnScaledLocalPos.y = y;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateXZ(float x, float z)
		{
			m_UnScaledLocalPos.x = x;
			m_UnScaledLocalPos.z = z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateX(float x)
		{
			m_UnScaledLocalPos.x = x;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateYZ(float y, float z)
		{
			m_UnScaledLocalPos.y = y;
			m_UnScaledLocalPos.z = z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateY(float y)
		{
			m_UnScaledLocalPos.y = y;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateZ(float z)
		{
			m_UnScaledLocalPos.z = z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::Move(const vec3 & translation)
        {
                m_UnScaledLocalPos += translation;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

        void TransformComponent::Move(float x, float y, float z)
        {
                Move(vec3(x,y,z));
        }

        void TransformComponent::MoveXY(float x, float y)
		{
			m_UnScaledLocalPos.x += x;
			m_UnScaledLocalPos.y += y;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveXZ(float x, float z)
		{
			m_UnScaledLocalPos.x += x;
			m_UnScaledLocalPos.z += z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveX(float x)
		{
			m_UnScaledLocalPos.x += x;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveYZ(float y, float z)
		{
			m_UnScaledLocalPos.y += y;
			m_UnScaledLocalPos.z += z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveY(float y)
		{
			m_UnScaledLocalPos.y += y;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveZ(float z)
		{
			m_UnScaledLocalPos.z += z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::Rotate(const quat & rotation)
        {
            m_LocalRotation = rotation;
            m_IsChanged |= TransformChanged::ROTATION;
        }

        void TransformComponent::Scale(const vec3 & scale)
        {
                m_UnScaledLocalScale = scale;
                m_IsChanged |= TransformChanged::SCALE;
        }

        void TransformComponent::Scale(float x, float y, float z)
        {
                Scale(vec3(x,y,z));
        }

        void TransformComponent::Scale(float u)
        {
                Scale(vec3(u, u, u));
        }

        void TransformComponent::ScaleXY(float x, float y)
		{
			m_UnScaledLocalScale.x = x;
			m_UnScaledLocalScale.y = y;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleXZ(float x, float z)
		{
			m_UnScaledLocalScale.x = x;
			m_UnScaledLocalScale.z = z;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleX(float x)
		{
			m_UnScaledLocalScale.x = x;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleYZ(float y, float z)
		{
			m_UnScaledLocalScale.y = y;
			m_UnScaledLocalScale.z = z;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleY(float y)
		{
			m_UnScaledLocalScale.y = y;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleZ(float z)
		{
			m_UnScaledLocalScale.z = z;
			m_IsChanged |= TransformChanged::SCALE;
		}

        const vec3 & TransformComponent::GetWorldPosition()
        {
                return m_UnScaledWorldPos;
        }

        const vec3 & TransformComponent::GetLocalPosition()
        {
                return m_LocalPosition / ScaleSystem::GetInstance()->GetScale();
        }

        const quat & TransformComponent::GetWorldRotation()
        {
                return m_WorldRotation;
        }

        const quat & TransformComponent::GetLocalRotation() const
        {
                return m_LocalRotation;
        }

        const vec3 & TransformComponent::GetWorldScale()
        {
                return m_UnScaledWorldScale;
        }

        const vec3 & TransformComponent::GetLocalScale()
        {
                return m_LocalScale / ScaleSystem::GetInstance()->GetScale();
        }
#endif

        const mat4x4 & TransformComponent::GetWorldMatrix() const
        {
			return m_World;
        }

        void TransformComponent::CheckForUpdate(bool force)
        {
			if(m_IsChanged == TransformChanged::NONE && !force && !m_Invalidate
				&& !GraphicsManager::GetInstance()->GetHasWindowChanged())
			{
				return;
			}

			CommonUpdate();

            m_IsChanged = TransformChanged::NONE;

            m_Invalidate = false;
        }
		
		void TransformComponent::CommonUpdate()
		{
			for(auto child : GetParent()->GetChildren())
			{
				child->GetTransform()->IsChanged(true);
			}

			SingleUpdate(m_World);

			auto parent = m_pParentObject->GetParent();
			if(parent != nullptr)
			{
				m_World = parent->GetTransform()->GetWorldMatrix() * m_World;
			}

			DecomposeMatrix(m_World, m_WorldPosition, m_WorldScale, m_WorldRotation);
		}
		
		void TransformComponent::SingleUpdate(mat4x4 & world)
		{
			m_LocalScale = m_UnScaledLocalScale;
			m_LocalPosition = m_UnScaledLocalPos;

			if(m_pParentObject->GetParent() == nullptr)
			{
				m_LocalScale *= ScaleSystem::GetInstance()->GetScale();
				m_LocalPosition *= ScaleSystem::GetInstance()->GetScale();
			}

			mat4x4 matRot, matTrans, matScale, matC, matCI;

			matTrans = glm::translate(m_LocalPosition.pos3D());
			matRot   = glm::toMat4(quat(vec3(0,0,m_LocalRotation)));
			matScale = glm::scale(vec3(m_LocalScale.x,m_LocalScale.y,1));
			
			if(m_bRotationCenterChanged)
			{
				m_bRotationCenterChanged = true;
				vec3 centerPos(m_CenterPosition.x, m_CenterPosition.y, 0);
				centerPos *= ScaleSystem::GetInstance()->GetScale();
				matC = glm::translate(-centerPos);
				matCI = glm::translate(centerPos);

				world = matTrans * matCI * matRot * matScale * matC;
			}
			else
			{
				world = matTrans * matRot * matScale;
			}
		}

        void TransformComponent::Update(const Context& context)
        {
             CheckForUpdate();
        }

		void TransformComponent::UpdateFrozenObjects(const Context& context)
		{
			CommonUpdate();
		}
        
		void TransformComponent::Draw()
		{

		}

		void TransformComponent::IsChanged(bool isChanged)
		{
			m_IsChanged = isChanged;
		}

        void TransformComponent::InitializeComponent()
        {
			CheckForUpdate(true);
			m_Invalidate = true;
        }
}