#include "UIObject.h"
#include "../GraphicsManager.h"
#include "UIDock.h"

namespace star
{
	UIObject::UIObject(const tstring & name)
		: Object(name, _T("UI"))
		, m_Position()
		, m_HorizontalAlignment(HorizontalAlignment::Left)
		, m_VerticalAlignment(VerticalAlignment::Bottom)
		, m_pDock(nullptr)
	{

	}

	UIObject::~UIObject()
	{

	}

	void UIObject::Initialize()
	{
		Object::Initialize();
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

	void UIObject::SetUIDock(UIDock * pDock)
	{
		m_pDock = pDock;
	}
	
	UIDock * UIObject::GetUIDock() const
	{
		return m_pDock;
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
	}

	void UIObject::Update(const Context& context)
	{
		Object::Update(context);
	}

	void UIObject::Draw()
	{
		Object::Draw();
	}

	UIDock * UIObject::GetRootDock() const
	{
		UIDock *pDock(nullptr);

		do
		{
			pDock = GetUIDock();
		} while(pDock != nullptr);

		return pDock;
	}

	vec2 UIObject::GetDockDimensions() const
	{
		vec2 dimensions;
		
		if(m_pDock != nullptr)
		{
			dimensions = m_pDock->GetDimensions();
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
				x = dimensions.x - x;
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
				y = dimensions.y - y;
				break;
		}

		GetTransform()->TranslateY(y);
	}
}
