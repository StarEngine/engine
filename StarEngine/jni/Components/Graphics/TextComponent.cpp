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
#include "SpriteComponent.h"
#include "SpritesheetComponent.h"

namespace star
{
	TextComponent::TextComponent(
		const tstring& fontName
		)
		: BaseComponent()
		, m_FontSize(0)
		, m_StringLength(0)
		, m_WrapWidth(NO_WRAPPING)
		, m_FileName(EMPTY_STRING)
		, m_OrigText(EMPTY_STRING)
		, m_EditText(EMPTY_STRING)
		, m_TextColor(Color::Black)
		, m_TextInfo(nullptr)
		, m_Font(nullptr)
		, m_TextAlignment(HorizontalAlignment::left)
	{
		const auto * font = 
			FontManager::GetInstance()->GetFont(fontName);
		m_FileName = font->GetFontPath();
		m_FontSize = font->GetFontSize();

		m_Font = FontManager::GetInstance()->GetFont(fontName);
		m_TextInfo = new TextInfo();
	}

	TextComponent::TextComponent(
		const tstring& fontPath,
		const tstring& fontName,
		uint32 fontSize
		)
		: BaseComponent()
		, m_FontSize(fontSize)
		, m_StringLength(0)
		, m_WrapWidth(NO_WRAPPING)
		, m_FileName(fontPath)
		, m_OrigText(EMPTY_STRING)
		, m_EditText(EMPTY_STRING)
		, m_TextColor(Color::Black)
		, m_TextInfo(nullptr)
		, m_Font()
		, m_TextAlignment(HorizontalAlignment::left)
	{
		if(!FontManager::GetInstance()->LoadFont(
				m_FileName,
				fontName,
				m_FontSize
				))
		{
			Logger::GetInstance()->Log(LogLevel::Error,
				_T("TextComponent : Could not load Font '")
				+ m_FileName + _T("'."), STARENGINE_LOG_TAG);
		}

		m_Font = FontManager::GetInstance()->GetFont(fontName);
		m_TextInfo = new TextInfo();
	}

	void TextComponent::InitializeComponent()
	{
		if(m_pParentObject->HasComponent<SpritesheetComponent>(this)
			|| m_pParentObject->HasComponent<SpriteComponent>(this))
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("Object '") + m_pParentObject->GetName() +
				_T("': Can't add a TextComponent when already \
having a Spritesheet- or SpriteComponent."));
			m_pParentObject->RemoveComponent(this);
		}
		else
		{
			if(m_WrapWidth == NO_WRAPPING)
			{
				CleanTextUp(m_OrigText);
				CalculateTextDimensions();
			}
			else
			{
				CleanTextUp(CheckWrapping(
							m_OrigText,
							m_WrapWidth
							));
			}

			FillTextInfo();
		}
	}

	void TextComponent::FillTextInfo()
	{
		m_TextInfo->font = m_Font;
		m_TextInfo->colorMultiplier = m_TextColor;		
		m_TextInfo->transformPtr = m_pParentObject->GetTransform();
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
			m_Dimensions.y = (m_Font->GetMaxLetterHeight() * lines)
				+ (m_TextInfo->verticalSpacing * (lines - 1));
			GetTransform()->SetDimensionsYSafe(m_Dimensions.y);
		}
	}

	void TextComponent::CalculateTextHeight()
	{
		auto count = std::count(m_EditText.begin(), m_EditText.end(), _T('\n'));
		++count;
		m_Dimensions.y = (m_Font->GetMaxLetterHeight() * count)
				+ (m_TextInfo->verticalSpacing * (count - 1));
		m_TextInfo->textHeight = m_Dimensions.y;
		GetTransform()->SetDimensionsYSafe(m_Dimensions.y);
	}
	
	void TextComponent::CleanTextUp(const tstring & str)
	{
		size_t length = str.length();
		m_EditText = EMPTY_STRING;
		for(size_t i = 0 ; i < length ; ++i)
		{
			if(str[i] == _T('\t'))
			{
				m_EditText += TAB;
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
		if(m_bInitialized)
		{
			m_TextInfo->horizontalTextOffset.clear();
			if(m_TextAlignment == HorizontalAlignment::center)
			{
				uint32 counter(0);
				uint32 length = GetLongestLine(m_EditText);
				if(length == 0)
				{
					m_TextInfo->text = m_EditText;
				}
				else
				{
					m_TextInfo->text = EMPTY_STRING;
					tstring substr(EMPTY_STRING);
					for(size_t i = 0 ; i < m_EditText.length() ; ++i)
					{
						if(m_EditText[i] == _T('\n'))
						{
							m_TextInfo->text += substr + _T('\n');

							uint32 diff = length - m_Font->GetStringLength(substr);
							if(diff > 0)
							{
								diff /= 2;
							}
							m_TextInfo->horizontalTextOffset.push_back(diff);
							
							substr = EMPTY_STRING;
							counter = 0;
						}
						else
						{
							substr += m_EditText[i];
							++counter;
						}
					}
					m_TextInfo->text += substr;

					uint32 diff = length - m_Font->GetStringLength(substr);
					if(diff > 0)
					{
						diff /= 2;
					}
					m_TextInfo->horizontalTextOffset.push_back(diff);
				}
			}
			else if(m_TextAlignment == HorizontalAlignment::right)
			{
				uint32 counter(0);
				uint32 length = GetLongestLine(m_EditText);
				if(length == 0)
				{
					m_TextInfo->text = m_EditText;
				}
				else
				{
					m_TextInfo->text = EMPTY_STRING;
					tstring substr(EMPTY_STRING);
					for(size_t i = 0 ; i < m_EditText.length() ; ++i)
					{
						if(m_EditText[i] == _T('\n'))
						{
							m_TextInfo->text += substr + _T('\n');

							uint32 diff = length - m_Font->GetStringLength(substr);
							m_TextInfo->horizontalTextOffset.push_back(diff);

							substr = EMPTY_STRING;
							counter = 0;
						}
						else
						{
							substr += m_EditText[i];
							++counter;
						}
					}
				
					m_TextInfo->text += substr;

					uint32 diff = length - m_Font->GetStringLength(substr);
					m_TextInfo->horizontalTextOffset.push_back(diff);
				}
			}
			else
			{	
				GetLongestLine(m_EditText);
				m_TextInfo->text = m_EditText;
				m_TextInfo->horizontalTextOffset.push_back(0);
				auto n = std::count(m_EditText.begin(), m_EditText.end(), _T('\n'));
				for( ; n > 0 ; --n)
				{
					m_TextInfo->horizontalTextOffset.push_back(0);
				}
			}
		}
	}
	
	int32 TextComponent::GetLongestLine(const tstring & str)
	{
		int32 length(0);
		if(m_bInitialized)
		{
			tstring substr(EMPTY_STRING);
			for(size_t i = 0 ; i < str.length() ; ++i)
			{
				if(str[i] == _T('\n'))
				{
					int32 strLength = m_Font->GetStringLength(substr);
					if(strLength > length)
					{
						length = strLength;
						m_Dimensions.x = strLength;
						GetTransform()->SetDimensionsXSafe(m_Dimensions.x);
					}
					substr = EMPTY_STRING;
				}
				else
				{
					substr += str[i];
				}
			}

			int32 strLength = m_Font->GetStringLength(substr);
			if(strLength > length)
			{
				length = strLength;
				m_Dimensions.x = strLength;
				GetTransform()->SetDimensionsXSafe(m_Dimensions.x);
			}
		}
		return length;
	}

	TextComponent::~TextComponent()
	{
		delete m_TextInfo;
	}

	void TextComponent::Draw()
	{
		if(m_TextInfo->text.size() == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Warning, _T("Trying to draw empty textComponent"));
			return;
		}
		SpriteBatch::GetInstance()->AddTextToQueue(m_TextInfo);
	}

	void TextComponent::Update(const Context& context)
	{
		FillTextInfo();
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
		
		if(m_TextInfo->bIsHud)
		{
			objectPos.x += left;
			objectPos.y += bottom;
		}
		
		textW = float32(m_Font->GetStringLength(m_OrigText));
		textH = float32(m_Font->GetMaxLetterHeight());

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

		m_StringLength = m_Font->GetStringLength(m_OrigText);
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
			m_Dimensions.x = 0;
			GetTransform()->SetDimensionsXSafe(m_Dimensions.x);
			if(m_bInitialized)
			{
				CleanTextUp(CheckWrapping(
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
		const tstring& stringIn,
		int32 wrapWidth
		)
	{
		tstring line(EMPTY_STRING),
				returnString(EMPTY_STRING);

		PointerArray<tstring, uint32> words;
		SplitString(words, stringIn, _T(' '));

		m_Dimensions.y = m_Font->GetMaxLetterHeight();
		GetTransform()->SetDimensionsYSafe(m_Dimensions.y);

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
				int32 w = m_Font->GetStringLength(
					line + words.elements[i]
				);

				if( w > m_Dimensions.x)
				{
					m_Dimensions.x = w;
					GetTransform()->SetDimensionsXSafe(m_Dimensions.x);
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
	
	void TextComponent::SetVerticalSpacing(uint32 spacing)
	{
		m_TextInfo->verticalSpacing = spacing;
		if(m_bInitialized && m_WrapWidth != NO_WRAPPING)
		{
			CleanTextUp(CheckWrapping(
						m_OrigText,
						m_WrapWidth
						));
		}
	}

	void TextComponent::SetHUDOptionEnabled(bool enabled)
	{
		m_TextInfo->bIsHud = enabled;
	}

	bool TextComponent::IsHUDOptionEnabled() const
	{
		return m_TextInfo->bIsHud;
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
