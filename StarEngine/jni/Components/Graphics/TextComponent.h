#pragma once

#include "../BaseComponent.h"
#include "../../defines.h"
#include "../../Graphics/FontManager.h"
#include "../../Graphics/Color.h"
#include <vector>

namespace star
{
	class Font;

	struct TextInfo
	{
		TextInfo()
			: font(nullptr)
			, transformPtr(nullptr)
			, colorMultiplier(Color::White)
			, bIsHud(false)
			, horizontalTextOffset()
			, verticalSpacing(10)
			, text()
			, textHeight()
		{}
		const Font* font;
		TransformComponent* transformPtr;
		Color colorMultiplier; 
		bool bIsHud;	
		std::vector<int32> horizontalTextOffset;
		int32 verticalSpacing;
		tstring text;	
		int32 textHeight;
	};

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(
			const tstring& fontName
			);

		TextComponent(
			const tstring& fontPath,
			const tstring& fontName,
			uint32 fontSize
			);

		virtual ~TextComponent();

		void Draw();
		virtual void Update(const Context& context);

		virtual bool CheckCulling(
			float left,
			float right,
			float top,
			float bottom
			) const;

		void SetText(const tstring& text);
		const tstring& GetText() const;

		void SetColor(const Color& color);
		const Color& GetColor() const;

		//Default set to -1, Set width to -1 to disable wrapping
		void SetWrapWidth(int32 width);
		int32 GetWrapWidth() const;

		void SetVerticalSpacing(uint32 spacing);

		void SetHUDOptionEnabled(bool enabled);
		bool IsHUDOptionEnabled() const;

		void AlignTextLeft();
		void AlignTextCenter();
		void AlignTextRight();
		
	protected:
		enum class HorizontalAlignment : byte
		{
			left = 0,
			center,
			right
		};

		virtual void InitializeComponent();

		void CalculateTextDimensions();
		void CalculateWrappedTextDimensions(uint8 lines);

		void CalculateTextHeight();
		void CleanTextUp(const tstring & str);

		void CalculateHorizontalTextOffset();
		int32 GetLongestLine(const tstring & str);

		virtual void FillTextInfo();
	
	private:
		uint32	m_FontSize,
				m_StringLength;

		int32 m_WrapWidth;

		tstring m_FileName,
				m_OrigText,
				m_EditText;

		Color m_TextColor;
		TextInfo* m_TextInfo;
		const Font* m_Font;
		HorizontalAlignment m_TextAlignment;

		tstring CheckWrapping(
			const tstring& stringIn,
			int32 wrapWidth
			);

		void SplitString(
			PointerArray<tstring, uint32> & words,
			tstring str,
			tchar delimiter
			);

		void SplitIntoLines(
			std::vector<sstring> &list,
			const sstring &string
			);

		TextComponent(const TextComponent &);
		TextComponent(TextComponent &&);
		TextComponent& operator=(const TextComponent &);
		TextComponent& operator=(TextComponent &&);
	};
}
