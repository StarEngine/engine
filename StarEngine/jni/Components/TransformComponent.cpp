#include "TransformComponent.h"
#include "..\Objects\Object.h"
#include "..\Logger.h"
#include "..\Context.h"
#include "..\Helpers\HelpersMath.h"
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
#else
                m_WorldPosition(0,0,0),
                m_LocalPosition(0,0,0),
#endif
                m_WorldRotation(0),
                m_LocalRotation(0),
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
                m_LocalPosition.x = translation.x;
                m_LocalPosition.y = translation.y;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

        void TransformComponent::Translate(float x, float y)
        {
                Translate(vec2(x, y));
        }

        void TransformComponent::Translate(const vec2 & translation, lay l)
        {
                m_LocalPosition.x = translation.x;
                m_LocalPosition.y = translation.y;
                m_LocalPosition.l = l;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

        void TransformComponent::Translate(float x, float y, lay l)
        {
                Translate(vec2(x, y), l);
        }

        void TransformComponent::Translate(const pos & pos2D)
        {
                m_LocalPosition = pos2D;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

		void TransformComponent::TranslateX(float x)
		{
			m_LocalPosition.x = x;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::TranslateY(float y)
		{
			m_LocalPosition.y = y;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::TranslateL(lay l)
		{
			m_LocalPosition.l = l;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::Move(const vec2& translation)
		{
			m_LocalPosition.x += translation.x;
			m_LocalPosition.y += translation.y;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::Move(float x, float y)
		{
			m_LocalPosition.x += x;
			m_LocalPosition.y += y;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::MoveX(float x)
		{
			m_LocalPosition.x += x;
            m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::MoveY(float y)
		{
			m_LocalPosition.y += y;
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
                m_LocalScale = scale;
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
			m_LocalScale.x = x;
            m_IsChanged |= TransformChanged::SCALE;
		}

		void TransformComponent::ScaleY(float y)
		{
			m_LocalScale.y = y;
            m_IsChanged |= TransformChanged::SCALE;
		}

        const pos & TransformComponent::GetWorldPosition()
        {
            return m_WorldPosition;
        }

        const pos & TransformComponent::GetLocalPosition()
        {
            return m_LocalPosition;
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
                return m_WorldScale;
        }

        const vec2 & TransformComponent::GetLocalScale()
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

        void TransformComponent::TranslateXY(float x, float y)
		{
			m_LocalPosition.x = x;
			m_LocalPosition.y = y;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateXZ(float x, float z)
		{
			m_LocalPosition.x = x;
			m_LocalPosition.z = z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateX(float x)
		{
			m_LocalPosition.x = x;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateYZ(float y, float z)
		{
			m_LocalPosition.y = y;
			m_LocalPosition.z = z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateY(float y)
		{
			m_LocalPosition.y = y;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::TranslateZ(float z)
		{
			m_LocalPosition.z = z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

		void TransformComponent::Move(const vec3 & translation)
        {
                m_LocalPosition += translation;
                m_IsChanged |= TransformChanged::TRANSLATION;
        }

        void TransformComponent::Move(float x, float y, float z)
        {
                Move(vec3(x,y,z));
        }

        void TransformComponent::MoveXY(float x, float y)
		{
			m_LocalPosition.x += x;
			m_LocalPosition.y += y;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveXZ(float x, float z)
		{
			m_LocalPosition.x += x;
			m_LocalPosition.z += z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveX(float x)
		{
			m_LocalPosition.x += x;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveYZ(float y, float z)
		{
			m_LocalPosition.y += y;
			m_LocalPosition.z += z;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveY(float y)
		{
			m_LocalPosition.y += y;
			m_IsChanged |= TransformChanged::TRANSLATION;
		}

        void TransformComponent::MoveZ(float z)
		{
			m_LocalPosition.z += z;
			m_IsChanged |= TransformChanged::TRANSLATION;
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

        void TransformComponent::Scale(float u)
        {
                Scale(vec3(u, u, u));
        }

        void TransformComponent::ScaleXY(float x, float y)
		{
			m_LocalScale.x = x;
			m_LocalScale.y = y;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleXZ(float x, float z)
		{
			m_LocalScale.x = x;
			m_LocalScale.z = z;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleX(float x)
		{
			m_LocalScale.x = x;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleYZ(float y, float z)
		{
			m_LocalScale.y = y;
			m_LocalScale.z = z;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleY(float y)
		{
			m_LocalScale.y = y;
			m_IsChanged |= TransformChanged::SCALE;
		}

        void TransformComponent::ScaleZ(float z)
		{
			m_LocalScale.z = z;
			m_IsChanged |= TransformChanged::SCALE;
		}

        const vec3 & TransformComponent::GetWorldPosition()
        {
                return m_WorldPosition;
        }

        const vec3 & TransformComponent::GetLocalPosition()
        {
                return m_LocalPosition;
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
                return m_WorldScale;
        }

        const vec3 & TransformComponent::GetLocalScale()
        {
                return m_LocalScale;
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
			mat4x4 matRot, matTrans, matScale, matC, matCI;

			matTrans = glm::translate(m_LocalPosition.pos3D());
			matRot   = glm::toMat4(quat(vec3(0,0,m_LocalRotation)));
			matScale = glm::scale(vec3(m_LocalScale.x,m_LocalScale.y,1));
			
			if(m_bRotationCenterChanged)
			{
				m_bRotationCenterChanged = true;
				vec3 centerPos(m_CenterPosition.x, m_CenterPosition.y, 0);
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