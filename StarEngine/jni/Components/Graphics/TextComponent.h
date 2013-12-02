#pragma once

#include "../BaseComponent.h"
#include "../../defines.h"
#include "../../Assets/FontManager.h"
#include "../../Graphics/Color.h"
#include <vector>

namespace star
{
	class Font;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(
			const tstring& fontName,
			bool bInFront = true
			);

		TextComponent(
			const tstring& fontPath,
			const tstring& fontName,
			uint32 fontSize,
			bool bInFront = true
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

		int32 GetTextWidth() const;
		int32 GetTextHeight() const;

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
	
	private:
		uint32	m_FontSize;
		int32	m_TextWidth,
				m_TextHeight;

		int32 m_WrapWidth;

		tstring m_FileName,
				m_FontName,
				m_OrigText,
				m_EditText;

		Color m_TextColor;
		TextDesc m_TextDesc;

		HorizontalAlignment m_TextAlignment;

		bool m_bInFront;

		tstring CheckWrapping(
			const Font& font,
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
