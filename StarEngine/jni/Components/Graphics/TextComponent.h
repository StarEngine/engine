#pragma once

#include "../../defines.h"
#include "../BaseComponent.h"
#include "../../Graphics/Color.h"
#include <vector>
#include "../../Assets/FontManager.h"

namespace star
{
	class Font;
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(const tstring& fileName,const tstring& tag, int32 fontSize, bool bInFront = true);
		virtual ~TextComponent();

		void Draw();
		virtual void Update(const Context& context);
		void SetText(const tstring& text);
		const tstring& GetText() const;
		void SetColor(const Color& color);
		const Color& GetColor() const;
		//Default set to -1, Set width to -1 to disable wrapping
		void SetWrapWidth(float32 width);
		float32 GetWrapWidth() const;
		int32 GetMaxTextWidth();
		int32 GetTotalTextHeight();
		
	protected:
		virtual void InitializeComponent();
	
	private:
		int32 m_FontSize;
		tstring m_FileName;
		tstring m_FontName;

		Color m_TextColor;
		TextDesc m_TextDesc;
		float32 m_WrapWidth;
		int32 m_MaxWidth;
		int32 m_MaxHeight;
		tstring m_OrigText;
		tstring m_EditedText;
		std::vector<sstring> m_SplittedText;

		bool m_bCheckedWrapping, 
			 m_bInFront;

		tstring CheckWrapping(const Font& font, const tstring& stringIn, float32 wrapWidth);
		void SplitString(std::vector<tstring>& wordArrayIn,const tstring& stringIn, const tstring& delimiter);
		void SplitIntoLines(std::vector<sstring> &list, const sstring &string);

		TextComponent(const TextComponent &);
		TextComponent(TextComponent &&);
		TextComponent& operator=(const TextComponent &);
		TextComponent& operator=(TextComponent &&);
	};
}
