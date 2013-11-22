#include "UITextField.h"
#include "../../Components/Graphics/TextComponent.h"

namespace star
{
	UITextField::UITextField(
		const tstring & name,
		const tstring & text,
		const tstring & fontName,
		const Color & color
		)
		: UIElement(name)
	{
		m_pTextComponent = 
			new TextComponent(fontName, true);
		
		AddComponent(m_pTextComponent);

		m_pTextComponent->SetColor(color);
		m_pTextComponent->SetText(text);
	}

	UITextField::UITextField(
		const tstring & name,
		const tstring & text,
		const tstring & fontName,
		const tstring & fontPath,
		float32 fontSize,
		const Color & color
		)
		: UIElement(name)
	{
		m_pTextComponent = 
			new TextComponent(fontPath, fontName, fontSize, true);
		
		AddComponent(m_pTextComponent);

		m_pTextComponent->SetColor(color);
		m_pTextComponent->SetText(text);
	}

	UITextField::~UITextField(void)
	{

	}

	void UITextField::Initialize()
	{
		UIElement::Initialize();
	}
	
	void UITextField::SetHorizontalAlignment(HorizontalAlignment alignment)
	{
		UIElement::SetHorizontalAlignment(alignment);

		switch(m_HorizontalAlignment)
		{
			case HorizontalAlignment::Left:
				GetTransform()->SetCenterX(0);
				break;
			case HorizontalAlignment::Center:
				GetTransform()->SetCenterX(
					float32(m_pTextComponent->GetTextWidth()) / 2.0f
					);
				break;
			case HorizontalAlignment::Right:
				GetTransform()->SetCenterX(
					float32(m_pTextComponent->GetTextWidth())
					);
				break;
		}

	}

	void UITextField::SetVerticalAlignment(VerticalAlignment alignment)
	{
		UIElement::SetVerticalAlignment(alignment);

		switch(m_VerticalAlignment)
		{
			case VerticalAlignment::Bottom:
				GetTransform()->SetCenterY(0);
				break;
			case VerticalAlignment::Center:
				GetTransform()->SetCenterY(
					float32(m_pTextComponent->GetTextHeight()) / -2.0f
					);
				break;
			case VerticalAlignment::Top:
				GetTransform()->SetCenterY(
					float32(-m_pTextComponent->GetTextHeight())
					);
				break;
		}
	}

	void UITextField::SetText(const tstring & text)
	{
		m_pTextComponent->SetText(text);
	}

	const tstring & UITextField::GetText() const
	{
		return m_pTextComponent->GetText();
	}

	void UITextField::SetColor(const Color & color)
	{
		m_pTextComponent->SetColor(color);
	}

	void UITextField::Update(const Context& context)
	{
		UIElement::Update(context);
	}

	void UITextField::Draw()
	{
		UIElement::Draw();
	}
}