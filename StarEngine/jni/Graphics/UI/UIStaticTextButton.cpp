#include "UIStaticTextButton.h"
#include "UITextField.h"

namespace star
{
	UIStaticTextButton::UIStaticTextButton(
		const tstring & name,
		const tstring & file,
		const tstring & text,
		const tstring & fontName,
		const Color & color,
		uint32 widthSegements,
		uint32 heightSegements
		)
		: UIStaticButton(name, file, widthSegements, heightSegements)
		, m_pTextField(nullptr)
	{
		m_pTextField = new UITextField(
			name + _T("_txt"),
			text,
			fontName,
			color
			);

		AddElement(m_pTextField);
	}

	UIStaticTextButton::UIStaticTextButton(
		const tstring & name,
		const tstring & file,
		const tstring & text,
		const tstring & fontName,
		const tstring & fontPath,
		float32 fontSize,
		const Color & color,
		uint32 widthSegements,
		uint32 heightSegements
		)
		: UIStaticButton(name, file, widthSegements, heightSegements)
		, m_pTextField(nullptr)
	{
		m_pTextField = new UITextField(
			name + _T("_txt"),
			text,
			fontName,
			fontPath,
			fontSize,
			color
			);

		AddElement(m_pTextField);
	}

	UIStaticTextButton::~UIStaticTextButton()
	{

	}
	
	void UIStaticTextButton::AfterInitialized()
	{
		SetTextCentered();
		UIStaticButton::AfterInitialized();
	}

	void UIStaticTextButton::SetTextColor(const Color & color)
	{
		m_pTextField->SetColor(color);
	}

	void UIStaticTextButton::SetText(const tstring & text)
	{
		m_pTextField->SetText(text);
	}

	const tstring & UIStaticTextButton::GetText() const
	{
		return m_pTextField->GetText();
	}

	void UIStaticTextButton::TranslateText(const vec2& translation)
	{
		m_pTextField->Translate(translation);
	}

	void UIStaticTextButton::TranslateText(float32 x, float32 y)
	{
		m_pTextField->Translate(x, y);
	}

	void UIStaticTextButton::TranslateTextX(float32 x)
	{
		m_pTextField->TranslateX(x);
	}

	void UIStaticTextButton::TranslateTextY(float32 y)
	{
		m_pTextField->TranslateY(y);
	}

	void UIStaticTextButton::SetHorizontalAlignmentText(HorizontalAlignment alignment)
	{
		m_pTextField->SetHorizontalAlignment(alignment);
	}

	void UIStaticTextButton::SetVerticalAlignmentText(VerticalAlignment alignment)
	{
		m_pTextField->SetVerticalAlignment(alignment);
	}
	
	void UIStaticTextButton::SetTextCentered()
	{
		m_pTextField->SetAlignmentCentered();
	}
}
