#include "UIAnimatedTextButton.h"
#include "UITextField.h"

namespace star
{
	UIAnimatedTextButton::UIAnimatedTextButton(
		const tstring & name,
		const tstring & file,
		const tstring & spritesheet,
		const tstring & text,
		const tstring & fontName,
		const Color & color
		)
		: UIAnimatedButton(name, file, spritesheet)
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

	UIAnimatedTextButton::UIAnimatedTextButton(
		const tstring & name,
		const tstring & file,
		const tstring & spritesheet,
		const tstring & text,
		const tstring & fontName,
		const tstring & fontPath,
		uint32 fontSize,
		const Color & color
		)
		: UIAnimatedButton(name, file, spritesheet)
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

	UIAnimatedTextButton::UIAnimatedTextButton(
		const tstring & name,
		const tstring & file,
		const tstring & spriteName,
		const tstring & spritesheet,
		const tstring & text,
		const tstring & fontName,
		const Color & color
		)
		: UIAnimatedButton(name, file, spriteName, spritesheet)
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

	UIAnimatedTextButton::UIAnimatedTextButton(
		const tstring & name,
		const tstring & file,
		const tstring & spriteName,
		const tstring & spritesheet,
		const tstring & text,
		const tstring & fontName,
		const tstring & fontPath,
		uint32 fontSize,
		const Color & color
		)
		: UIAnimatedButton(name, file, spriteName, spritesheet)
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

	UIAnimatedTextButton::~UIAnimatedTextButton()
	{

	}

	void UIAnimatedTextButton::AfterInitialized()
	{
		SetTextCentered();
		UIUserElement::AfterInitialized();
	}

	void UIAnimatedTextButton::SetIdleColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::IDLE)] = color;
	}

#ifdef DESKTOP
	void UIAnimatedTextButton::SetHoverColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::HOVER)] = color;
	}
#endif

	void UIAnimatedTextButton::SetClickColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::CLICK)] = color;
	}

	void UIAnimatedTextButton::SetDisableColor(const Color & color)
	{
		m_StateColors[3] = color;
	}

	void UIAnimatedTextButton::SetText(const tstring & text)
	{
		m_pTextField->SetText(text);
	}

	const tstring & UIAnimatedTextButton::GetText() const
	{
		return m_pTextField->GetText();
	}

	void UIAnimatedTextButton::TranslateText(const vec2& translation)
	{
		m_pTextField->Translate(translation);
	}

	void UIAnimatedTextButton::TranslateText(float32 x, float32 y)
	{
		m_pTextField->Translate(x, y);
	}

	void UIAnimatedTextButton::TranslateTextX(float32 x)
	{
		m_pTextField->TranslateX(x);
	}

	void UIAnimatedTextButton::TranslateTextY(float32 y)
	{
		m_pTextField->TranslateY(y);
	}

	void UIAnimatedTextButton::SetHorizontalAlignmentText(
		HorizontalAlignment alignment,
		bool redefine_center
		)
	{
		m_pTextField->SetHorizontalAlignment(
			alignment,
			redefine_center
			);
	}

	void UIAnimatedTextButton::SetVerticalAlignmentText(
		VerticalAlignment alignment,
		bool redefine_center
		)
	{
		m_pTextField->SetVerticalAlignment(
			alignment,
			redefine_center
			);
	}
	
	void UIAnimatedTextButton::SetTextCentered()
	{
		m_pTextField->SetAlignmentCentered();
	}
	
	void UIAnimatedTextButton::GoIdle()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);
		UIAnimatedButton::GoIdle();
	}

#ifdef DESKTOP
	void UIAnimatedTextButton::GoHover()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);
		UIAnimatedButton::GoHover();
	}
#endif

	void UIAnimatedTextButton::GoDown()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);
		UIAnimatedButton::GoDown();
	}

	void UIAnimatedTextButton::GoDisable()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);
		UIAnimatedButton::GoDisable();
	}
}
