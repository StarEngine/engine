#include "UISimpleTextButton.h"
#include "UITextField.h"

namespace star
{
	UISimpleTextButton::UISimpleTextButton(
		const tstring & name,
		float width,
		float height,
		const tstring & text,
		const tstring & fontName,
		const Color & color
		)
		: UIUserElement(name)
		, m_pTextField(nullptr)
		, m_Dimensions(width, height)
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

	UISimpleTextButton::UISimpleTextButton(
		const tstring & name,
		float width,
		float height,
		const tstring & text,
		const tstring & fontName,
		const tstring & fontPath,
		float32 fontSize,
		const Color & color
		)
		: UIUserElement(name)
		, m_pTextField(nullptr)
		, m_Dimensions(width, height)
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

	UISimpleTextButton::UISimpleTextButton(
		const tstring & name,
		const tstring & text,
		const tstring & fontName,
		const Color & color
		)
		: UIUserElement(name)
		, m_pTextField(nullptr)
		, m_Dimensions(1, 1)
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

	UISimpleTextButton::UISimpleTextButton(
		const tstring & name,
		const tstring & text,
		const tstring & fontName,
		const tstring & fontPath,
		float32 fontSize,
		const Color & color
		)
		: UIUserElement(name)
		, m_pTextField(nullptr)
		, m_Dimensions(1, 1)
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

	UISimpleTextButton::~UISimpleTextButton()
	{

	}

	void UISimpleTextButton::AfterInitialized()
	{
		if(m_Dimensions.x == 1)
		{
			m_Dimensions.x = float32(m_pTextField->GetWidth());
			m_Dimensions.y = float32(m_pTextField->GetHeight());
		}
		GoIdle();
		SetTextCentered();
		UIUserElement::AfterInitialized();
	}

	void UISimpleTextButton::SetIdleColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::IDLE)] = color;
	}

#ifdef DESKTOP
	void UISimpleTextButton::SetHoverColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::HOVER)] = color;
	}
#endif

	void UISimpleTextButton::SetClickColor(const Color & color)
	{
		m_StateColors[uint8(ElementStates::CLICK)] = color;
	}

	void UISimpleTextButton::SetDisableColor(const Color & color)
	{
		m_StateColors[3] = color;
	}

	void UISimpleTextButton::SetText(const tstring & text)
	{
		m_pTextField->SetText(text);
	}

	const tstring & UISimpleTextButton::GetText() const
	{
		return m_pTextField->GetText();
	}

	void UISimpleTextButton::TranslateText(const vec2& translation)
	{
		m_pTextField->Translate(translation);
	}

	void UISimpleTextButton::TranslateText(float32 x, float32 y)
	{
		m_pTextField->Translate(x, y);
	}

	void UISimpleTextButton::TranslateTextX(float32 x)
	{
		m_pTextField->TranslateX(x);
	}

	void UISimpleTextButton::TranslateTextY(float32 y)
	{
		m_pTextField->TranslateY(y);
	}

	void UISimpleTextButton::SetHorizontalAlignmentText(HorizontalAlignment alignment)
	{
		m_pTextField->SetHorizontalAlignment(alignment);
	}

	void UISimpleTextButton::SetVerticalAlignmentText(VerticalAlignment alignment)
	{
		m_pTextField->SetVerticalAlignment(alignment);
	}
	
	void UISimpleTextButton::SetTextCentered()
	{
		m_pTextField->SetAlignmentCentered();
	}

	void UISimpleTextButton::SetDimensions(const vec2 & dimensions)
	{
		m_Dimensions = dimensions;
		RepositionChildren();
	}

	void UISimpleTextButton::SetDimensions(float32 x, float32 y)
	{
		m_Dimensions.x = x;
		m_Dimensions.y = y;
		RepositionChildren();
	}

	void UISimpleTextButton::SetDimensionsX(float32 x)
	{
		m_Dimensions.x = x;
		RepositionChildren();
	}

	void UISimpleTextButton::SetDimensionsY(float32 y)
	{
		m_Dimensions.y = y;
		RepositionChildren();
	}

	vec2 UISimpleTextButton::GetDimensions() const
	{
		return m_Dimensions;
	}

	void UISimpleTextButton::GoIdle()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);

		UIUserElement::GoIdle();
	}

#ifdef DESKTOP
	void UISimpleTextButton::GoHover()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);

		UIUserElement::GoHover();
	}
#endif

	void UISimpleTextButton::GoDown()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);

		UIUserElement::GoDown();
	}

	void UISimpleTextButton::GoDisable()
	{
		m_pTextField->SetColor(m_StateColors[int8(m_ElementState)]);

		UIUserElement::GoDisable();
	}
}
