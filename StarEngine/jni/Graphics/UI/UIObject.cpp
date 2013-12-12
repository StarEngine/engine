#include "UIObject.h"
#include "../GraphicsManager.h"
#include "UIDock.h"
#include "../../Scenes/BaseScene.h"

namespace star
{
	UIObject::UIObject(const tstring & name)
		: Object(name, _T("UI"))
		, m_Position()
		, m_HorizontalAlignment(HorizontalAlignment::Left)
		, m_VerticalAlignment(VerticalAlignment::Bottom)
		, m_pParent(nullptr)
	{

	}

	UIObject::~UIObject()
	{
	}

	void UIObject::Initialize()
	{
		Object::Initialize();
	}

	void UIObject::AfterInitialized()
	{
		Object::AfterInitialized();
		Reposition();
		RepositionChildren();
	}
		
	void UIObject::Translate(const vec2& translation)
	{
		m_Position = translation;
		UITranslate();
	}

	void UIObject::Translate(float32 x, float32 y)
	{
		m_Position.x = x;
		m_Position.y = y;
		UITranslate();
	}

	void UIObject::Translate(const vec2& translation, lay l)
	{
		m_Position = translation;
		m_Position.l = l;
		UITranslate();
	}

	void UIObject::Translate(float32 x, float32 y, lay l)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.l = l;
		UITranslate();
	}

	void UIObject::Translate(const pos & pos2D)
	{
		m_Position = pos2D;
		UITranslate();
	}

	void UIObject::TranslateX(float32 x)
	{
		m_Position.x = x;
		UITranslate();
	}

	void UIObject::TranslateY(float32 y)
	{
		m_Position.y = y;
		UITranslate();
	}

	void UIObject::TranslateL(lay l)
	{
		m_Position.l = l;
		UITranslate();
	}

	void UIObject::SetUIParent(UIObject * pParent)
	{
		m_pParent = pParent;
	}
	
	UIObject * UIObject::GetUIParent() const
	{
		return m_pParent;
	}

	const pos & UIObject::GetPosition() const
	{
		return m_Position;
	}

	void UIObject::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		m_HorizontalAlignment = alignment;
		UITranslateX(m_Position.x, GetDockDimensions());
	}

	void UIObject::SetVerticalAlignment(VerticalAlignment alignment)
	{
		m_VerticalAlignment = alignment;
		UITranslateY(m_Position.y, GetDockDimensions());
	}

	void UIObject::SetAlignmentCentered()
	{
		SetHorizontalAlignment(HorizontalAlignment::Center);
		SetVerticalAlignment(VerticalAlignment::Center);
	}

	void UIObject::Reset()
	{
		for(auto child : m_pChildren)
		{
			auto element = dynamic_cast<UIObject*>(child);
			if(element != nullptr)
			{
				element->Reset();
			}
			else
			{
				Logger::GetInstance()->Log(LogLevel::Warning,
					_T("UIObject::Reset: Object '") +
					child->GetName() + _T("' is not a UI Object."),
					STARENGINE_LOG_TAG);
			}
		}

		Object::Reset();
	}

	void UIObject::Reposition()
	{
		UITranslate();
	}
		
	void UIObject::AddChild(Object* pObject)
	{
		auto uiobject = dynamic_cast<UIObject*>(pObject);
		if(uiobject)
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				tstring(_T("UIObject::AddChild: ")) +
				_T("UIObjects should be added via the AddElement(UIObject*) function."),
				STARENGINE_LOG_TAG);
			AddElement(uiobject);
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				tstring(_T("UIObject::AddChild: ")) +
				_T("Adding a non-UIObject to a UIObject is an illegal action."),
				STARENGINE_LOG_TAG);
		}
	}
	
	void UIObject::AddElement(UIObject * pElement)
	{
		pElement->SetUIParent(this);
		pElement->Reposition();
		Object::AddChild(pElement);
	}

	void UIObject::Update(const Context& context)
	{
		Object::Update(context);
	}

	void UIObject::Draw()
	{
		Object::Draw();
	}

	vec2 UIObject::GetDimensions() const
	{
		return vec2(0,0);
	}

	UIObject * UIObject::GetRootParent() const
	{
		UIObject *pParent(nullptr);
		UIObject *pChild = const_cast<UIObject*>(this);

		do
		{
			pChild = pChild->GetUIParent();
			if(pChild != nullptr)
			{
				pParent = pChild;
			}
		} while(pChild != nullptr);

		return pParent;
	}

	vec2 UIObject::GetDockDimensions() const
	{
		vec2 dimensions;
		
		if(m_pParent != nullptr)
		{
			dimensions = m_pParent->GetDimensions();
		}
		else
		{
			dimensions = GraphicsManager::GetInstance()->GetScreenResolution();
		}

		return dimensions;
	}

	void UIObject::UITranslate()
	{
		vec2 dimensions = GetDockDimensions();
		UITranslateX(m_Position.x, dimensions);
		UITranslateY(m_Position.y, dimensions);
	}

	void UIObject::UITranslateX(float32 x, const vec2 & dimensions)
	{
		switch(m_HorizontalAlignment)
		{
			case HorizontalAlignment::Center:
				x += dimensions.x / 2;
				break;
			case HorizontalAlignment::Right:
				x += dimensions.x;
				break;
		}

		GetTransform()->TranslateX(x);
	}

	void UIObject::UITranslateY(float32 y, const vec2 & dimensions)
	{
		switch(m_VerticalAlignment)
		{
			case VerticalAlignment::Center:
				y += dimensions.y / 2;
				break;
			case VerticalAlignment::Top:
				y += dimensions.y;
				break;
		}

		GetTransform()->TranslateY(y);
	}

	void UIObject::RepositionChildren()
	{
		for(auto child : m_pChildren)
		{
			auto element = dynamic_cast<UIObject*>(child);
			if(element != nullptr)
			{
				element->Reposition();
			}
			else
			{
				Logger::GetInstance()->Log(LogLevel::Warning,
					_T("UIObject::RepositionChildren: Object '") +
					child->GetName() + _T("' is not a UI Object."),
					STARENGINE_LOG_TAG);
			}
		}
	}
}
