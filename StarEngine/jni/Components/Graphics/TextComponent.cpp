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
		, m_EditText(EMPTY_STRING)
		, m_TextColor(Color::Black)
		, m_TextAlignment(HorizontalAlignment::left)
		, m_bInFront(bInFront)
	{
	}

	TextComponent::TextComponent(
		const tstring& fontPath,
		const tstring& fontName,
		uint32 fontSize,
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
		, m_EditText(EMPTY_STRING)
		, m_TextColor(Color::Black)
		, m_TextAlignment(HorizontalAlignment::left)
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
			CleanTextUp(m_OrigText);
			CalculateTextDimensions();
		}
		else
		{
			CleanTextUp(CheckWrapping(
						FontManager::GetInstance()->GetFont(m_FontName),
						m_OrigText,
						m_WrapWidth
						));
		}
	}

	void TextComponent::CalculateTextDimensions()
	{
		if(m_bInitialized)
		{
			GetLongestLine(m_EditText);
			CalculateTextHeight();
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

	void TextComponent::CalculateTextHeight()
	{
		auto count = std::count(m_EditText.begin(), m_EditText.end(), _T('\n'));
		++count;
		auto font = FontManager::GetInstance()->GetFont(m_FontName);
		m_TextHeight = int32(m_TextHeight = (font.GetMaxLetterHeight() * count)
				+ (m_TextDesc.VerticalSpacing * (count - 1)));
	}
	
	void TextComponent::CleanTextUp(const tstring & str)
	{
		size_t length = str.length();
		m_EditText = EMPTY_STRING;
		for(size_t i = 0 ; i < length ; ++i)
		{
			if(str[i] == _T('\t'))
			{
				m_EditText += _T("    ");
			}
			else
			{
				m_EditText += str[i];
			}
		}
		CalculateHorizontalTextOffset();
	}

	void TextComponent::CalculateHorizontalTextOffset()
	{
		m_TextDesc.HorizontalTextOffset.clear();
		auto font = FontManager::GetInstance()->GetFont(m_FontName);
		if(m_TextAlignment == HorizontalAlignment::center)
		{
			uint32 counter(0);
			uint32 length = GetLongestLine(m_EditText);
			if(length == 0)
			{
				m_TextDesc.Text = m_EditText;
			}
			else
			{
				m_TextDesc.Text = EMPTY_STRING;
				tstring substr(EMPTY_STRING);
				for(size_t i = 0 ; i < m_EditText.length() ; ++i)
				{
					if(m_EditText[i] == _T('\n'))
					{
						m_TextDesc.Text += substr + _T('\n');

						uint32 diff = length - font.GetStringLength(substr);
						if(diff > 0)
						{
							diff /= 2;
						}
						m_TextDesc.HorizontalTextOffset.push_back(diff);
							
						substr = EMPTY_STRING;
						counter = 0;
					}
					else
					{
						substr += m_EditText[i];
						++counter;
					}
				}
			
				m_TextDesc.Text += substr;

				uint32 diff = length - font.GetStringLength(substr);
				if(diff > 0)
				{
					diff /= 2;
				}
				m_TextDesc.HorizontalTextOffset.push_back(diff);
			}
		}
		else if(m_TextAlignment == HorizontalAlignment::right)
		{
			uint32 counter(0);
			uint32 length = GetLongestLine(m_EditText);
			if(length == 0)
			{
				m_TextDesc.Text = m_EditText;
			}
			else
			{
				m_TextDesc.Text = EMPTY_STRING;
				tstring substr(EMPTY_STRING);
				for(size_t i = 0 ; i < m_EditText.length() ; ++i)
				{
					if(m_EditText[i] == _T('\n'))
					{
						m_TextDesc.Text += substr + _T('\n');

						uint32 diff = length - font.GetStringLength(substr);
						m_TextDesc.HorizontalTextOffset.push_back(diff);

						substr = EMPTY_STRING;
						counter = 0;
					}
					else
					{
						substr += m_EditText[i];
						++counter;
					}
				}
				
				m_TextDesc.Text += substr;

				uint32 diff = length - font.GetStringLength(substr);
				m_TextDesc.HorizontalTextOffset.push_back(diff);
			}
		}
		else
		{	
			GetLongestLine(m_EditText);
			m_TextDesc.Text = m_EditText;
			m_TextDesc.HorizontalTextOffset.push_back(0);
		}
	}
	
	int32 TextComponent::GetLongestLine(const tstring & str)
	{
		int32 length(0);
		tstring substr(EMPTY_STRING);
		auto font = FontManager::GetInstance()->GetFont(m_FontName);
		for(size_t i = 0 ; i < str.length() ; ++i)
		{
			if(str[i] == _T('\n'))
			{
				int32 strLength = font.GetStringLength(substr);
				if(strLength > length)
				{
					length = strLength;
					m_TextWidth = strLength;
				}
				substr = EMPTY_STRING;
			}
			else
			{
				substr += str[i];
			}
		}

		int32 strLength = font.GetStringLength(substr);
		if(strLength > length)
		{
			length = strLength;
			m_TextWidth = strLength;
		}

		return length;
	}
	
	void TextComponent::AddSpacesToText(tstring & str, uint32 n)
	{
		for(uint32 i = 0 ; i < n ; ++i)
		{
			str += _T(' ');
		}
	}

	TextComponent::~TextComponent()
	{
	}

	void TextComponent::Draw()
	{	
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
		
		float32 teRight = objectPos.x + textWidth;
		float32 texTop = objectPos.y + textHeight;

		return
			(	(objectPos.x >= left && objectPos.x <= right) ||
				(teRight >= left && teRight <= right)
			) &&
			(	(objectPos.y >= bottom && objectPos.y <= top) ||
				(texTop >= bottom && texTop <= top)
			);
	}

	void TextComponent::SetText(const tstring& text)
	{
		m_OrigText = text;
		if (m_WrapWidth != NO_WRAPPING)
		{
			if(m_bInitialized)
			{
				CleanTextUp(CheckWrapping(
						FontManager::GetInstance()->GetFont(m_FontName),
						m_OrigText,
						int32(m_WrapWidth)
						));
			}
		}
		else
		{
			CleanTextUp(m_OrigText);
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
			CalculateTextDimensions();
		}
		else
		{
			m_TextWidth = 0;
			if(m_bInitialized)
			{
				CleanTextUp(CheckWrapping(
							FontManager::GetInstance()->GetFont(m_FontName),
							m_OrigText,
							m_WrapWidth
							));
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
			size_t n_count = words.elements[i].find(_T('\n'));
			if(n_count != tstring::npos)
			{
				if(words.elements[i][0] == _T('\n'))
				{
					returnString += line + _T('\n');
					line = words.elements[i].substr(0, words.elements[i].size() - 1);
				}
				else
				{
					returnString += line + words.elements[i];
					line = EMPTY_STRING;
				}
				++lines;
			}
			else
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
			CleanTextUp(CheckWrapping(
						FontManager::GetInstance()->GetFont(m_FontName),
						m_OrigText,
						m_WrapWidth
						));
		}
	}

	void TextComponent::SetHUDOptionEnabled(bool enabled)
	{
		m_TextDesc.IsHUDText = enabled;
	}

	bool TextComponent::IsHUDOptionEnabled() const
	{
		return m_TextDesc.IsHUDText;
	}

	void TextComponent::AlignTextLeft()
	{
		m_TextAlignment = HorizontalAlignment::left;
		CalculateHorizontalTextOffset();
	}

	void TextComponent::AlignTextCenter()
	{
		m_TextAlignment = HorizontalAlignment::center;
		CalculateHorizontalTextOffset();
	}

	void TextComponent::AlignTextRight()
	{
		m_TextAlignment = HorizontalAlignment::right;
		CalculateHorizontalTextOffset();
	}
}
