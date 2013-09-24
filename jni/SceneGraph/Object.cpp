#include "Object.h"
#include "../StarComponents.h"
#include "../Components/TransformComponent.h"
#include <algorithm>

namespace star
{
	Object::Object(void):
		m_bIsInitialized(false),
		m_pParentGameObject(nullptr),

		m_pComponents(),
		m_pChildren(),
		m_Name(_T("Default")),
		m_CollisionTag(_T("Default"))
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
		{
			return;
		}

		for(auto *comp : m_pComponents)
		{
			if(comp && !comp->IsInitialized())
			{
				comp->Initialize();
			}
		}

		for(auto *child : m_pChildren)
		{
			if(child && !child->m_bIsInitialized)
			{
				child->Initialize();
			}
		}

		m_bIsInitialized = true;
	}

	void Object::Update(const Context& context)
	{
		for(auto *component : m_pComponents)
		{
			if(component)
			{
				component->Update(context);
			}
		}

		for(auto *child : m_pChildren)
		{
			if(child)
			{
				child->Update(context);
			}
		}
	}

	void Object::Draw()
	{
		for(auto *component : m_pComponents)
		{
			if(component)
			{
				component->Draw();
			}
		}

		for(auto *child : m_pChildren)
		{
			if(child)
			{
				child->Draw();
			}
		}
	}

	void Object::AddComponent(BaseComponent *pComponent)
	{
		pComponent->SetParent(this);

		if(m_bIsInitialized && ! pComponent->IsInitialized())
		{
			pComponent->Initialize();
		}

		m_pComponents.push_back(pComponent);

		Logger::GetSingleton()->Log(LogLevel::Info,_T("Component Added"));
	}

	void Object::RemoveComponent(const BaseComponent* pComponent)
	{
		m_pComponents.erase(std::find(m_pComponents.begin(), m_pComponents.end(), pComponent));
		delete pComponent;

		Logger::GetSingleton()->Log(LogLevel::Info,_T("Component Removed"));
	}

	void Object::AddChild(Object *pChild)
	{
		pChild->m_pParentGameObject = this;

		if(m_bIsInitialized && ! pChild->m_bIsInitialized)
		{
			pChild->Initialize();
		}

		m_pChildren.push_back(pChild);

		Logger::GetSingleton()->Log(LogLevel::Info,_T("Child Added"));
	}

	void Object::RemoveChild(const Object* pObject)
	{
		m_pChildren.erase(std::find(m_pChildren.begin(), m_pChildren.end(), pObject));
		delete pObject;

		Logger::GetSingleton()->Log(LogLevel::Info,_T("Child Removed"));
	}

	void Object::CollisionCheck(Object* otherObject)
	{
		auto rectComp = GetComponent<RectangleColliderComponent>();
		auto circleComp = GetComponent<CircleColliderComponent>();
		auto otherRectComp = otherObject->GetComponent<RectangleColliderComponent>();
		auto otherCircleComp = otherObject->GetComponent<CircleColliderComponent>();
		
		if(rectComp != nullptr)
		{
			if(otherRectComp != nullptr)
			{
				RectangleCollision(this, otherObject);
			}
			if(otherCircleComp != nullptr)
			{
				RectangleCircleCollision(this, otherObject);
			}
		}
		if(circleComp != nullptr)
		{
			if(otherRectComp != nullptr)
			{
				RectangleCircleCollision(this, otherObject);
			}
			if(otherCircleComp != nullptr)
			{
				CircleCollision(this, otherObject);
			}
		}
	}

	bool Object::RectangleCollision(Object* object, Object* otherObject)
	{
		auto rect = object->GetComponent<RectangleColliderComponent>()->GetCollisionRect();
		auto otherRect = otherObject->GetComponent<RectangleColliderComponent>()->GetCollisionRect();
		glm::vec2 objectPos = glm::vec2(object->GetComponent<TransformComponent>()->GetWorldPosition().x, object->GetComponent<TransformComponent>()->GetWorldPosition().y);
		glm::vec2 otherObjectPos = glm::vec2(otherObject->GetComponent<TransformComponent>()->GetWorldPosition().x, otherObject->GetComponent<TransformComponent>()->GetWorldPosition().y);

		int left = rect.GetLeft() + static_cast<int>(objectPos.x);
		int right = rect.GetRight() + static_cast<int>(objectPos.x);
		int top = rect.GetTop() + static_cast<int>(objectPos.y); 
		int bottom = rect.GetBottom() + static_cast<int>(objectPos.y);

		int otherLeft = otherRect.GetLeft() + static_cast<int>(otherObjectPos.x);
		int	otherRight = otherRect.GetRight() + static_cast<int>(otherObjectPos.x);
		int otherTop = otherRect.GetTop() + static_cast<int>(otherObjectPos.y);
		int otherBottom = otherRect.GetBottom() + static_cast<int>(otherObjectPos.y);

		if(left > otherRight || right < otherLeft || top > otherBottom || bottom < otherTop)
		{
			Logger::GetSingleton()->Log(LogLevel::Info, _T("They don't collide"));
			return false;
		}
		Logger::GetSingleton()->Log(LogLevel::Info, _T("They do collide"));
		return true;
	}

	bool Object::CircleCollision(Object* object, Object* otherObject)
	{
		auto radius = object->GetComponent<CircleColliderComponent>()->GetRadius();
		auto otherRadius = otherObject->GetComponent<CircleColliderComponent>()->GetRadius();
		glm::vec2 objectPos = glm::vec2(object->GetComponent<TransformComponent>()->GetWorldPosition().x, object->GetComponent<TransformComponent>()->GetWorldPosition().y);
		glm::vec2 otherObjectPos = glm::vec2(otherObject->GetComponent<TransformComponent>()->GetWorldPosition().x, otherObject->GetComponent<TransformComponent>()->GetWorldPosition().y);

		if((objectPos - otherObjectPos).length() > radius + otherRadius)
		{
			Logger::GetSingleton()->Log(LogLevel::Info, _T("They don't collide"));
			return false;
		}
		Logger::GetSingleton()->Log(LogLevel::Info, _T("They do collide"));
		return true;
	}

	bool Object::RectangleCircleCollision(Object* object, Object* otherObject)
	{
		auto rect = object->GetComponent<RectangleColliderComponent>()->GetCollisionRect();
		auto radius = object->GetComponent<CircleColliderComponent>()->GetRadius();
				
		glm::vec2 objectPos = glm::vec2(object->GetComponent<TransformComponent>()->GetWorldPosition().x, object->GetComponent<TransformComponent>()->GetWorldPosition().y);
		glm::vec2 otherObjectPos = glm::vec2(otherObject->GetComponent<TransformComponent>()->GetWorldPosition().x, otherObject->GetComponent<TransformComponent>()->GetWorldPosition().y);

		int left = rect.GetLeft() + static_cast<int>(objectPos.x);
		int right = rect.GetRight() + static_cast<int>(objectPos.x);
		int top = rect.GetTop() + static_cast<int>(objectPos.y); 
		int bottom = rect.GetBottom() + static_cast<int>(objectPos.y);

		// Find the closest point to the circle within the rectangle
		float closestX = glm::clamp(otherObjectPos.x, (float)objectPos.x, (float)(objectPos.x + rect.GetRight()));
		float closestY = glm::clamp(otherObjectPos.y, (float)objectPos.y, (float)(objectPos.y + rect.GetBottom()));

		// Calculate the distance between the circle's center and this closest point
		float distanceX = otherObjectPos.x - closestX;
		float distanceY = otherObjectPos.y - closestY;

		// If the distance is less than the circle's radius, an intersection occurs
		float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
		if( distanceSquared < (radius * radius))
		{
			Logger::GetSingleton()->Log(LogLevel::Info, _T("They do collide"));
		 return true;
		}
		Logger::GetSingleton()->Log(LogLevel::Info, _T("They don't collide"));
		return false;
	}
}
