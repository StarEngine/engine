#include "UITextButton.h"
#include "UITextField.h"

namespace star
{
	UITextButton::UITextButton(
		const tstring & name,
		const tstring & file,
		const tstring & text,
		const tstring & fontName,
		const Color & color,
		bool isVertical
		)
		: UIButton(name, file, isVertical)
		, m_pTextField(nullptr)
	{
		for(uint8 i = 0 ; i < 4 ; ++i)
		{
			m_StateColors[i] = color;
		}

		m_pTextField = new UITextField(
			name + _T("_txt"),
			text,
			fontName,
			color
			);

		AddElement(m_pTextField);
	}

	UITextButton::UITextButton(
		const tstring & name,
		const tstring & file,
		const tstring & text,
		const tstring & fontName,
		const tstring & fontPath,
		uint32 fontSize,
		const Color & color,
		bool isVertical
		)
		: UIButton(name, file, isVertical)
		, m_pTextField(nullptr)
	{
		for(uint8 i = 0 ; i < 4 ; ++i)
		{
			m_StateColors[i] = color;
		}

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

	UITextButton::UITextButton(
		const tstring & name,
		const tstring & file,
		const tstring & spriteName,
		const tstring & text,
		const tstring & fontName,
		const Color & color,
		bool isVertical
		)
		: UIButton(name, file, spriteName, isVertical)
		, m_pTextField(nullptr)
	{
		for(uint8 i = 0 ; i < 4 ; ++i)
		{
			m_StateColors[i] = color;
		}

		m_pTextField = new UITextField(
			name + _T("_txt"),
			text,
			fontName,
			color
			);

		AddElement(m_pTextField);
	}

	UITextButton::UITextButton(
		const tstring & name,
		const tstring & file,
		const tstring & spriteName,
		const tstring & text,
		const tstring & fontName,
		const tstring & fontPath,
		uint32 fontSize,
		const Color & color,
		bool isVertical
		)
		: UIButton(name, file, spriteName, isVertical)
		, m_pTextField(nullptr)
	{
		for(uint8 i = 0 ; i < 4 ; ++i)
		{
			m_StateColors[i] = color;
		}

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

	UITextButton::~UITextButton()
	{

	}
	
	void UITextButton::AfterInitialized()
	{
		SetTextCentered();
		UIButton::AfterInitialized();
	}

	void UITextButton::SetIdleColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::IDLE)] = color;
	}

#ifdef DESKTOP
	void UITextButton::SetHoverColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::HOVER)] = color;
	}
#endif

	void UITextButton::SetClickColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::CLICK)] = color;
	}

	void UITextButton::SetDisableColor(const Color & color)
	{
		m_StateColors[3] = color;
	}

	void UITextButton::SetText(const tstring & text)
	{
		m_pTextField->SetText(text);
	}

	const tstring & UITextButton::GetText() const
	{
		return m_pTextField->GetText();
	}

	void UITextButton::TranslateText(const vec2& translation)
	{
		m_pTextField->Translate(translation);
	}

	void UITextButton::TranslateText(float32 x, float32 y)
	{
		m_pTextField->Translate(x, y);
	}

	void UITextButton::TranslateTextX(float32 x)
	{
		m_pTextField->TranslateX(x);
	}

	void UITextButton::TranslateTextY(float32 y)
	{
		m_pTextField->TranslateY(y);
	}

	void UITextButton::SetHorizontalAlignmentText(
		HorizontalAlignment alignment,
		bool redefine_center
		)
	{
		m_pTextField->SetHorizontalAlignment(
			alignment,
			redefine_center
			);
	}

	void UITextButton::SetVerticalAlignmentText(
		VerticalAlignment alignment,
		bool redefine_center
		)
	{
		m_pTextField->SetVerticalAlignment(
			alignment,
			redefine_center
			);
	}
	
	void UITextButton::SetTextCentered(bool redefine_center)
	{
		m_pTextField->SetAlignmentCentered(redefine_center);
	}
	
	void UITextButton::GoIdle()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);
		UIButton::GoIdle();
	}

#ifdef DESKTOP
	void UITextButton::GoHover()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);
		UIButton::GoHover();
	}
#endif

	void UITextButton::GoDown()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);
		UIButton::GoDown();
	}

	void UITextButton::GoDisable()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);
		UIButton::GoDisable();
	}
}
