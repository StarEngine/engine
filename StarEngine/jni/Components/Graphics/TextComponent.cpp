#include "TextComponent.h"
#include "../../Assets/Font.h"
#include "../../Logger.h"
#include "../../Assets/TextureManager.h"
#include "../../Graphics/GraphicsManager.h"
#include "../TransformComponent.h"
#include "../../Objects/FreeCamera.h"
#include "../CameraComponent.h"
#include "../../Objects/Object.h"
#include "../../Graphics/SpriteBatch.h"

namespace star
{
	TextComponent::TextComponent(const tstring& fileName,const tstring& name, int32 fontSize, bool bInFront)
		: BaseComponent()
		, m_FontSize(fontSize)
		, m_FileName(fileName)
		, m_FontName(name)
		, m_TextColor(Color::Black)
		, m_WrapWidth(NO_WRAPPING)
		, m_MaxWidth(0)
		, m_MaxHeight(0)
		, m_OrigText(EMPTY_STRING)
		, m_EditedText(EMPTY_STRING)
		, m_bCheckedWrapping(true)
		, m_bInFront(bInFront)
	{

	}

	void TextComponent::InitializeComponent()
	{
		if(!FontManager::GetInstance()->LoadFont(m_FileName,m_FontName,m_FontSize))
		{
			Logger::GetInstance()->Log(LogLevel::Error,_T("TextComponent : Could not load Font ") + m_FileName);
		}
		m_TextDesc.Fontname = m_FontName;
		m_TextDesc.TextColor = m_TextColor;
	}

	TextComponent::~TextComponent()
	{
	}

	void TextComponent::Draw()
	{	
		if(m_WrapWidth != NO_WRAPPING && !m_bCheckedWrapping)
		{
			m_SplittedText.clear();
			sstring text = string_cast<sstring>(m_OrigText);
			star::FontManager::GetInstance()->SplitIntoLines(m_SplittedText,text);
			tstring totalline = EMPTY_STRING;
			for(auto line : m_SplittedText)
			{
				tstring checkedline = CheckWrapping(FontManager::GetInstance()->GetFont(m_FontName),string_cast<tstring>(line),m_WrapWidth);
				totalline += checkedline + _T("\n");
			}
			m_SplittedText.clear();
			star::FontManager::GetInstance()->SplitIntoLines(m_SplittedText,string_cast<sstring>(totalline));
			m_bCheckedWrapping=true;
		}

		m_TextDesc.Text = m_SplittedText;
		m_TextDesc.TransformComp = m_pParentObject->GetTransform();

		SpriteBatch::GetInstance()->AddTextToQueue(m_TextDesc, m_bInFront);
	}

	void TextComponent::Update(const Context& context)
	{

	}

	void TextComponent::SetText(const tstring& text)
	{
		m_OrigText = text;
		m_EditedText = m_OrigText;
		//This is in case the text is reset while there was already a set wrapping width
		if(m_WrapWidth != NO_WRAPPING)
		{
			m_bCheckedWrapping=false;
		}
		else
		{
			m_SplittedText.clear();
			sstring text = string_cast<sstring>(m_OrigText);
			m_SplittedText.push_back(text);
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

	void TextComponent::SetWrapWidth(float32 width )
	{
		m_WrapWidth = width;
		if(m_WrapWidth!= NO_WRAPPING)
		{
			m_bCheckedWrapping = false;
		}
		else
		{
			m_EditedText = m_OrigText;
		}
	}

	float32 TextComponent::GetWrapWidth() const
	{
		return m_WrapWidth;
	}

	tstring TextComponent::CheckWrapping(const Font& font, const tstring& stringIn,float32 wrapWidth )
	{
		tstring line = EMPTY_STRING;
		tstring returnString = EMPTY_STRING;
		std::vector<tstring>wordArray;
		SplitString(wordArray,stringIn,_T(" "));
		m_MaxHeight = font.GetMaxLetterHeight();
		for(uint32 i=0; i < wordArray.size(); ++i)
		{
			int32 w = font.GetStringLength(line + wordArray[i]);
			if(w>m_MaxWidth)m_MaxWidth=w;
			if( w > int32(wrapWidth))
			{
				m_MaxWidth+=font.GetMaxLetterHeight();
				returnString += line + _T("\n");
				line = EMPTY_STRING;
			}
			line += wordArray[i] + _T(" ");
		}
		return returnString + line;
	}

	void TextComponent::SplitString( std::vector<tstring>& wordArrayIn,const tstring& stringIn , const tstring& delimiter)
	{
		sstring newstring = star::string_cast<sstring>(stringIn);
		sstring newdelemiter= star::string_cast<sstring>(delimiter);
		size_t pos = 0;
		sstring token;
		//Split Everything
		while((pos = newstring.find(newdelemiter))!= sstring::npos)
		{
			token = newstring.substr(0,pos);
			wordArrayIn.push_back(star::string_cast<tstring>(token));
			newstring.erase(0,pos+newdelemiter.length());
		}
		//Push back last remaining piece of string
		wordArrayIn.push_back(star::string_cast<tstring>(newstring));
	}

	int32 TextComponent::GetMaxTextWidth()
	{
		if(m_MaxWidth == 0)
		{
			auto font =FontManager::GetInstance()->GetFont(m_FontName);
			m_MaxWidth = font.GetStringLength(m_OrigText);
		}
		return m_MaxWidth;
	}

	int32 TextComponent::GetTotalTextHeight()
	{
		if(m_MaxHeight == 0)
		{
			auto font =FontManager::GetInstance()->GetFont(m_FontName);
			m_MaxHeight = font.GetMaxLetterHeight();
		}
		return m_MaxHeight;
	}

}
