#include "TextComponent.h"
#include "../CameraComponent.h"
#include "../TransformComponent.h"
#include "../../Logger.h"
#include "../../Assets/Font.h"
#include "../../Assets/TextureManager.h"
#include "../../Graphics/GraphicsManager.h"
#include "../../Graphics/SpriteBatch.h"
#include "../../Objects/FreeCamera.h"
#include "../../Objects/Object.h"

namespace star
{
	TextComponent::TextComponent(
		const tstring& fontName,
		bool bInFront
		)
		: BaseComponent()
		, m_FontSize(0)
		, m_TextWidth(0)
		, m_TextHeight(0)
		, m_WrapWidth(NO_WRAPPING)
		, m_FileName(EMPTY_STRING)
		, m_FontName(fontName)
		, m_OrigText(EMPTY_STRING)
		, m_EditedText(EMPTY_STRING)
		, m_TextColor(Color::Black)
		, m_bInFront(bInFront)
	{
	}

	TextComponent::TextComponent(
		const tstring& fontPath,
		const tstring& fontName,
		float32 fontSize,
		bool bInFront
		)
		: BaseComponent()
		, m_FontSize(fontSize)
		, m_TextWidth(0)
		, m_TextHeight(0)
		, m_WrapWidth(NO_WRAPPING)
		, m_FileName(fontPath)
		, m_FontName(fontName)
		, m_OrigText(EMPTY_STRING)
		, m_EditedText(EMPTY_STRING)
		, m_TextColor(Color::Black)
		, m_bInFront(bInFront)
	{
	}

	void TextComponent::InitializeComponent()
	{
		if(m_FileName == EMPTY_STRING)
		{
			const auto & font = 
				FontManager::GetInstance()->
					GetFont(m_FontName);
			m_FileName = font.GetFontPath();
			m_FontSize = font.GetSize();
		}
		else if(!FontManager::GetInstance()->LoadFont(
				m_FileName,
				m_FontName,
				m_FontSize
				))
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("TextComponent : Could not load Font '")
				+ m_FileName + _T("'."));
		}

		m_TextDesc.Fontname = m_FontName;
		m_TextDesc.TextColor = m_TextColor;

		if(m_WrapWidth == NO_WRAPPING)
		{
			m_EditedText = m_OrigText;
			CalculateTextDimensions();
		}
		else
		{
			m_EditedText = CheckWrapping(
						FontManager::GetInstance()->GetFont(m_FontName),
						m_OrigText,
						m_WrapWidth
						);
		}
	}

	void TextComponent::CalculateTextDimensions()
	{
		if(m_bInitialized)
		{
			auto font = FontManager::GetInstance()->GetFont(m_FontName);
			m_TextWidth = font.GetStringLength(m_EditedText);
			m_TextHeight = font.GetMaxLetterHeight();
		}
	}
	
	void TextComponent::CalculateWrappedTextDimensions(uint8 lines)
	{
		if(m_bInitialized)
		{
			auto font = FontManager::GetInstance()->GetFont(m_FontName);
			m_TextHeight = (font.GetMaxLetterHeight() * lines)
				+ (m_TextDesc.VerticalSpacing * (lines - 1));
		}
	}

	TextComponent::~TextComponent()
	{
	}

	void TextComponent::Draw()
	{	
		m_TextDesc.Text = m_EditedText;
		m_TextDesc.TransformComp = m_pParentObject->GetTransform();

		SpriteBatch::GetInstance()->AddTextToQueue(m_TextDesc, m_bInFront);
	}

	void TextComponent::Update(const Context& context)
	{

	}
	
	bool TextComponent::CheckCulling(
		float left,
		float right,
		float top,
		float bottom
		) const
	{
		float32 textWidth, textHeight, textW, textH;

		pos objectPos = GetTransform()->GetWorldPosition();
		
		auto font = FontManager::GetInstance()->GetFont(m_FontName);
		textW = float32(font.GetStringLength(m_OrigText));
		textH = float32(font.GetMaxLetterHeight());

		textWidth = textW * GetTransform()->GetWorldScale().x;
		textHeight = textH * GetTransform()->GetWorldScale().y;

		return
			(objectPos.x >= left || objectPos.x + textWidth <= right) &&
			(objectPos.y >= bottom || objectPos.y + textHeight <= top);
	}

	void TextComponent::SetText(const tstring& text)
	{
		m_OrigText = text;
		if (m_WrapWidth != NO_WRAPPING)
		{
			if(m_bInitialized)
			{
				m_EditedText = CheckWrapping(
						FontManager::GetInstance()->GetFont(m_FontName),
						m_OrigText,
						int32(m_WrapWidth)
						);
			}
		}
		else
		{
			m_EditedText = m_OrigText;
			
			CalculateTextDimensions();
		}
	}

	const tstring& TextComponent::GetText() const
	{
		return m_OrigText;
	}

	void TextComponent::SetColor(const Color& color)
	{
		m_TextColor = color;
	}

	const Color& TextComponent::GetColor() const
	{
		return m_TextColor;
	}

	void TextComponent::SetWrapWidth(int32 width)
	{
		m_WrapWidth = width;
		if(width == NO_WRAPPING)
		{
			m_EditedText = m_OrigText;
			CalculateTextDimensions();
		}
		else
		{
			m_TextWidth = 0;
			if(m_bInitialized)
			{
				m_EditedText = CheckWrapping(
							FontManager::GetInstance()->GetFont(m_FontName),
							m_OrigText,
							m_WrapWidth
							);
			}
		}
	}

	int32 TextComponent::GetWrapWidth() const
	{
		return m_WrapWidth;
	}

	tstring TextComponent::CheckWrapping(
		const Font& font,
		const tstring& stringIn,
		int32 wrapWidth
		)
	{
		tstring line(EMPTY_STRING),
				returnString(EMPTY_STRING);

		PointerArray<tstring, uint32> words;
		SplitString(words, stringIn, _T(' '));

		m_TextHeight = font.GetMaxLetterHeight();

		uint8 lines(1);

		for(uint32 i = 0; i < words.amount ; ++i)
		{
			int32 w = font.GetStringLength(
				line + words.elements[i]
			);

			if( w > m_TextWidth)
			{
				m_TextWidth = w;
			}

			if( w > wrapWidth)
			{
				returnString += line + _T("\n");
				++lines;
				line = EMPTY_STRING;
			}

			line += words.elements[i] + _T(" ");
		}

		delete [] words.elements;

		CalculateWrappedTextDimensions(lines);

		return returnString + line;
	}

	void TextComponent::SplitString(
		PointerArray<tstring, uint32> & words,
		tstring str,
		tchar delimiter
		)
	{
		words.amount =
			std::count(
				str.begin(),
				str.end(),
				delimiter
				);

		words.elements = new tstring[words.amount];
		size_t pos(0);
		uint32 n(0);

		for( ; n < words.amount - 1 ; ++n)
		{
			pos = str.find(delimiter);
			words.elements[n] = str.substr(0, pos);
			str.erase(0, pos + 1);
		}

		words.elements[n] = str;
	}

	int32 TextComponent::GetTextWidth() const
	{
		return m_TextWidth;
	}

	int32 TextComponent::GetTextHeight() const
	{
		return m_TextHeight;
	}
	
	void TextComponent::SetVerticalSpacing(uint32 spacing)
	{
		m_TextDesc.VerticalSpacing = spacing;
		if(m_bInitialized && m_WrapWidth != NO_WRAPPING)
		{
			m_EditedText = CheckWrapping(
						FontManager::GetInstance()->GetFont(m_FontName),
						m_OrigText,
						m_WrapWidth
						);
		}
	}
}
